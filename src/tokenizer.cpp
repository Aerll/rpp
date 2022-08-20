///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2020-2022 Aerll - aerlldev@gmail.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright noticeand this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
#include <tokenizer.hpp>

#include <tokenliterals.hpp>
#include <inputstream.hpp>

/*
    Tokenizer
*/
void Tokenizer::run(InputStream& inputStream, bool ignoreLine)
{
    // numberOfPuncAndOp() returns number of all operators and punctuators in the input stream.
    // In most cases punctuators and operators are followed by either identifier, keyword or literal,
    // thus approximately vector needs around twice that number of capacity.
    m_data.reserve(numberOfPuncAndOp(inputStream) * 2); // set approximate capacity

    m_line = m_ignoreLine ? 0 : 1;
    m_enclosed = false;
    m_subtraction = false;
    m_ignoreLine = ignoreLine;

    while (!inputStream.eof()) {
        if (isEnclosed() && m_data.back().value == PU::StringLiteral && inputStream.current() == PU::CharStringLiteral) {
            m_data.push_back({ TLiteral, {}, line(), ValueType::String });
            m_data.push_back({ TPunctuator, PU::StringLiteral, line() });
            m_enclosed = false;
            inputStream.skip();
        }

        Token t = nextToken(inputStream);

        if (!t.value.empty()) {
            m_data.push_back(std::move(t));
        }
    }
}

uint32_t Tokenizer::numberOfPuncAndOp(InputStream& inputStream) const noexcept
{
    uint32_t count = 0;

    bool oneLineComment = false;
    bool multiLineComment = false;
    while (!inputStream.eof()) {
        char c1 = inputStream.next();
        char c2 = inputStream.current();

        if (isOneLineComment(c1, c2))
            oneLineComment = true;
        else if (Token::isNewLine(c1))
            oneLineComment = false;
        else if (isMultiLineComment(c1, c2))
            multiLineComment = true;
        else if (isMultiLineComment(c2, c1))
            multiLineComment = false;
        else if (!oneLineComment && !multiLineComment && (Token::isPunctuator(c1) || Token::isOperator(c1)))
            ++count;
    }

    inputStream.reset();
    return count;
}

Token Tokenizer::nextToken(InputStream& inputStream)
{
    Token token = getNewToken(inputStream);
    setValue(inputStream, token);
    token.line = line();

    return token;
}

Token Tokenizer::getNewToken(InputStream& inputStream)
{
    if (!m_enclosed)
        skipBlank(inputStream);

    char c = inputStream.current();
    if ((isEnclosed() && c != PU::CharStringLiteral) || Token::isLetter(c))
        return getNewTokenFromLiteral(inputStream, ValueType::String);
    else if (Token::isDigit(c))
        return getNewTokenFromLiteral(inputStream, ValueType::Int);
    else if (Token::isPunctuator(c))
        return { TPunctuator };
    else if (Token::isOperator(c))
        return { TOperator };
    else
        return { TInvalid };
}

Token Tokenizer::getNewTokenFromLiteral(InputStream& inputStream, ValueType type)
{
    if (isEnclosed())
        return { TLiteral, getString(inputStream), 0, ValueType::String };
    else if (type == ValueType::String) {
        std::string s = getString(inputStream);

        if (Token::isKeyword(s))
            return { TKeyword, s };
        else
            return { TIdentifier, s };
    }
    else // integer
        return { TLiteral, getInteger(inputStream), 0, ValueType::Int };
}

void Tokenizer::skipBlank(InputStream& inputStream)
{
    while (!inputStream.eof()) {
        char c = inputStream.current();
        char c1 = inputStream.current(1);

        // skip blank
        if (Token::isBlank(c)) {
            if (Token::isNewLine(c)) {
                m_enclosed = false;
                m_subtraction = false;
                nextLine();
            }
            inputStream.skip();
        }
        // skip one line comments
        else if (isOneLineComment(c, c1)) { // check for '//'
            while (!inputStream.eof()) {
                c = inputStream.next();
                if (Token::isNewLine(c)) {
                    nextLine();
                    break;
                }
            }
        }
        // skip multi line comments
        else if (isMultiLineComment(c, c1)) { // check for '/*'
            while (!inputStream.eof()) {
                c = inputStream.next();

                if (isMultiLineComment(inputStream.current(), c)) { // check for '*/'
                    inputStream.skip();
                    break;
                }
                if (Token::isNewLine(c))
                    nextLine();
            }
        }
        else {
            break;
        }
    }
}

void Tokenizer::setValue(InputStream& inputStream, Token& t)
{
    switch (t.cat) {
        case TInvalid:
            t.value = getString(inputStream);
            m_subtraction = false;
            break;

        case TKeyword:
            m_subtraction = false;
            break;

        case TIdentifier:
            ensureValid(t);
            m_subtraction = false;
            break;

        case TLiteral:
            if (isFloat(inputStream)) {
                t.value += inputStream.next();
                t.value += getInteger(inputStream);
                t.type = ValueType::Float;
            }

            ensureValid(t);
            m_subtraction = true;
            break;

        case TPunctuator:
        case TOperator: {
            char c = inputStream.next();
            t.value = c;
            if (isUnaryNegation(inputStream)) {
                t.value += getInteger(inputStream);
                t.cat = TLiteral;
                t.type = ValueType::Int;

                if (isFloat(inputStream)) {
                    t.value += inputStream.next();
                    t.value += getInteger(inputStream);
                    t.type = ValueType::Float;
                }

                ensureValid(t);
                m_subtraction = true;
            }
            else if (
                isOpReturnType(c, inputStream.current()) ||
                isOpEqual(c, inputStream.current()) ||
                isOpNotEqual(c, inputStream.current()) ||
                isOpGreaterOrEqual(c, inputStream.current()) ||
                isOpLessOrEqual(c, inputStream.current())
                ) {
                t.value += inputStream.next();
                m_subtraction = false;
            }
            else if (c == PU::CharStringLiteral) {
                m_enclosed = !m_enclosed;
                m_subtraction = false;
            }
            else
                m_subtraction = false;
            break;
        }
    }
}

void Tokenizer::ensureValid(Token& t)
{
    if (t.type == ValueType::Int || t.type == ValueType::Float) {
        for (auto c : t.value)
            if (Token::isLetter(c)) {
                t.cat = TInvalid;
                break;
            }
    }
    else if (!isEnclosed()) { // string literal, identifier
        if (!Token::isLetter(t.value.front()))
            t.cat = TInvalid;

        for (auto it = t.value.begin() + 1; it != t.value.end(); ++it)
            if (!Token::isLetter(*it) && !Token::isDigit(*it)) {
                t.cat = TInvalid;
                break;
            }
    }
}

std::string Tokenizer::getInteger(InputStream& inputStream)
{
    std::string s;

    while (!inputStream.eof()) {
        s += inputStream.next();
        char c = inputStream.current();

        if (Token::isBlank(c) || Token::isOperator(c) || Token::isPunctuator(c))
            break;
    }
    return s;
}

std::string Tokenizer::getString(InputStream& inputStream)
{
    std::string s;
    
    while (!inputStream.eof()) {
        s += inputStream.next();
        char c = inputStream.current();

        if (!isEnclosed() && (Token::isBlank(c) || Token::isOperator(c) || Token::isPunctuator(c)))
            break;
        else {
            if (c == PU::CharStringLiteral)
                break;
            else if (Token::isNewLine(c))
                break;
        }
    }
    return s;
}

bool Tokenizer::isUnaryNegation(InputStream& inputStream) const noexcept
{
    if (inputStream.current(-1) == OP::CharUnaryNegation) {
        if (!isSubtraction() && Token::isDigit(inputStream.current())) {
            return true;
        }
    }

    return false;
}

bool Tokenizer::isFloat(InputStream& inputStream) const noexcept
{
    if (inputStream.current() == PU::CharDecimalPoint && Token::isDigit(inputStream.current(1)))
        return true;

    return false;
}
