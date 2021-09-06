///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2020 Aerll - aerlldev@gmail.com
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
#ifndef RPP_TOKENIZER_HPP
#define RPP_TOKENIZER_HPP

#include <vector>

#include <token.hpp>

class InputStream;

class Tokenizer final {
public:
    Tokenizer() = default;
    Tokenizer(const Tokenizer&) = delete;
    Tokenizer& operator=(const Tokenizer&) = delete;

    void run(InputStream& inputStream, bool ignoreLine = false);

    std::vector<Token>&& data() noexcept
        { return std::move(m_data); }

private:
    uint32_t numberOfPuncAndOp(InputStream& inputStream) const noexcept;

    Token nextToken(InputStream& inputStream);
    Token getNewToken(InputStream& inputStream);
    Token getNewTokenFromLiteral(InputStream& inputStream, ValueType type);

    void skipBlank(InputStream& inputStream);

    void setValue(InputStream& inputStream, Token& t);
    void ensureValid(Token& t);
    std::string getInteger(InputStream& inputStream);
    std::string getString(InputStream& inputStream);
    bool isUnaryNegation(InputStream& inputStream) const noexcept;
    bool isFloat(InputStream& inputStream) const noexcept;

    bool isEnclosed() const noexcept
        { return m_enclosed; }
    bool isSubtraction() const noexcept
        { return m_subtraction; }

    auto line() const noexcept
        { return m_line; }
    void nextLine() noexcept
        { if (!m_ignoreLine) ++m_line; }

    bool isOneLineComment(char c1, char c2) const noexcept
        { return c1 == '/' && c2 == '/'; }
    bool isMultiLineComment(char c1, char c2) const noexcept
        { return c1 == '/' && c2 == '*'; }
    bool isOpReturnType(char c1, char c2) const noexcept
        { return c1 == '-' && c2 == '>'; }
    bool isOpEqual(char c1, char c2) const noexcept
        { return c1 == '=' && c2 == '='; }
    bool isOpNotEqual(char c1, char c2) const noexcept
        { return c1 == '!' && c2 == '='; }
    bool isOpGreaterOrEqual(char c1, char c2) const noexcept
        { return c1 == '>' && c2 == '='; }
    bool isOpLessOrEqual(char c1, char c2) const noexcept
        { return c1 == '<' && c2 == '='; }

private:
    std::vector<Token> m_data;
    uint32_t m_line;
    bool m_enclosed; // if literal is enclosed
    bool m_subtraction; // if '-' should be treated as subtraction
    bool m_ignoreLine;
};

#endif // RPP_TOKENIZER_HPP