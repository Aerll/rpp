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
#include <error.hpp>

#include <filesystem>

#include <token.hpp>
#include <tokenh.hpp>

/*
    Error
*/
std::string Error::formatExpression(const std::vector<Token*>& tokens)
{
    if (tokens.empty())
        return {};

    std::string s;
    for (auto it = tokens.cbegin(); it != tokens.cend() - 1; ++it) {
        auto t1 = *it;
        auto t2 = *(it + 1);

        s += t1->value;
        // space: '0 0' 'int x'
        if ((t1->cat == TKeyword || t1->cat == TIdentifier || t1->cat == TLiteral) &&
            (t2->cat == TKeyword || t2->cat == TIdentifier || t2->cat == TLiteral)
            ) s += ' ';
        // no space: '1_2' 'pos.x'
        else if (
            *t1 != TH::MemberAccess &&
            *t2 != TH::MemberAccess &&
            t1->value != PU::StringLiteral &&
            t2->value != PU::StringLiteral &&
            *t1 != TH::FunctionCallOpen &&
            *t2 != TH::FunctionCallOpen &&
            *t2 != TH::FunctionCallClose &&
            *t1 != TH::ArraySubscriptOpen &&
            *t2 != TH::ArraySubscriptOpen &&
            *t2 != TH::ArraySubscriptClose &&
            *t1 != TH::Range &&
            *t2 != TH::Range &&
            *t1 != TH::ReturnType &&
            *t2 != TH::ReturnType &&
        // following space: '1, 2'
            t2->value != PU::Separator
            ) s += ' ';
        // following space when next is operator, keyword, identifier or literal: 'Pos() + 1' 'Pos().x + 1'
        else if (
            (*t1 == TH::FunctionCallClose || *t1 == TH::ArraySubscriptClose) &&
            (t2->cat == TOperator || t2->cat == TKeyword || t2->cat == TIdentifier || t2->cat == TLiteral)
            ) s += ' ';
        else if (
            (t1->value == PU::StringLiteral && t2->cat == TOperator) ||
            (t2->value == PU::StringLiteral && t1->cat == TOperator)
            ) s += ' ';
    }
    s += tokens.back()->value;

    return s;
}

std::string Error::strUnexpectedEof()
{
    return "Unexpected end of file.";
}

std::string Error::strUnexpectedToken(const std::string& s)
{
    return "Unexpected token: '" + s + "'.";
}

std::string Error::strUnexpectedToken(const std::string& s, std::string_view expected)
{
    return "Unexpected token: '" + s + "', expected: '" + expected.data() + "'.";
}

std::string Error::strKeywordNotAllowed(const std::string& s)
{
    return "Keyword is not allowed: '" + s + "'.";
}

std::string Error::strIncorrectIdentifier(const std::string& s)
{
    return "Incorrect identifier: '" + s + "'.";
}

std::string Error::strIncorrectLiteralType(const std::string& s, ValueType expected)
{
    return "Incorrect type: '" + s + "'. Expected " + Token::typeToString(expected) + ".";
}

std::string Error::strIncorrectPath(const std::string& s)
{
    return "Incorrect path: '" + s + "'.";
}

std::string Error::strFileNotFound(const std::string& s)
{
    return "File not found: '" + s + "'.";
}

std::string Error::strInvalidOutPath(const std::string& s)
{
    return "Invalid output path: '" + s + "'.";
}

std::string Error::strMissingExpression(const std::string& s)
{
    return "Missing expression: '" + s + "'.";
}

std::string Error::strMissingToken(std::string_view missing)
{
    return std::string{ "Missing token: '" } + missing.data() + "'.";
}

std::string Error::strInvalidExpression(const std::string& s)
{
    return "Invalid expression: '" + s + "'.";
}

std::string Error::strNotAMemberOf(const std::string& s, ValueType type)
{
    return "'" + s + "' is not a member of type '" + Token::typeToString(type) + "'.";
}

std::string Error::strNotAMemberOf(const std::string& s, const std::string& of)
{
    return "'" + s + "' is not a member of '" + of + "'.";
}

std::string Error::strNameCallNotVariable()
{
    return "'name()' can only be used on a variable.";
}

std::string Error::strRedeclaration(const std::string& s)
{
    return "'" + s + "' is already declared.";
}

std::string Error::strUndeclared(const std::string& s)
{
    return "'" + s + "' is undeclared.";
}

std::string Error::strUnassignedVariable(const std::string& s)
{
    return "Variable '" + s + "' is unassigned.";
}

std::string Error::strInvalidContext(const std::string& s)
{
    return "'" + s + "' used in the wrong context.";
}

std::string Error::strMissingValue(const std::string& s)
{
    return "Missing value for '" + s + "'.";
}

std::string Error::strFunctionSignatureNotFound(const std::string& s)
{
    return "Function '" + s + "' is not declared or there is no matching signature.";
}

std::string Error::strNestedSignatureNotFound(const std::string& s)
{
    return "Nested function '" + s + "' is not declared or there is no matching signature.";
}

std::string Error::strPresetSignatureNotFound(const std::string& s)
{
    return "Preset '" + s + "' is not declared or there is no matching signature.";
}

std::string Error::strNestedDifferentReturnType(const std::string& s, ValueType expected)
{
    return "Return type of nested function '" + s + "', differs from the function that it belongs to. Expected " + Token::typeToString(expected) + ".";
}

std::string Error::strReturnInvalidContext()
{
    return "'" + std::string{ KW::Return } + "' can only be used inside a function.";
}

std::string Error::strBreakInvalidContext()
{
    return "'" + std::string{ KW::Break } + "' can only be used inside a loop.";
}

std::string Error::strContinueInvalidContext()
{
    return "'" + std::string{ KW::Continue } + "' can only be used inside a loop.";
}

std::string Error::strInvokeInvalidContext()
{
    return "'" + std::string{ KW::Invoke } +"' can only be used inside a function that declares nested functions.";
}

std::string Error::strMissingProperty(const std::string& s)
{
    return "Missing property for '" + s + "'.";
}

std::string Error::strMissingReturn(const std::string& s)
{
    return "Missing return statement in '" + s + "'.";
}

std::string Error::strIncorrectValueType(ValueType type, ValueType expected)
{
    return "Incorrect value of type '" + Token::typeToString(type) + "', expected '" + Token::typeToString(expected) + "'.";
}

std::string Error::strNoOperatorOverload(ValueType left, ValueType right, NodeID op)
{
    std::string leftStr = Token::typeToString(left);
    std::string rightStr = Token::typeToString(right);

    switch (op) {
        case NodeID::OpAdd:
            return "No operator + overload for types '" + leftStr + "' and '" + rightStr + "'.";
        case NodeID::OpSubtract:
            return "No operator - overload for types '" + leftStr + "' and '" + rightStr + "'.";
        case NodeID::OpMultiply:
            return "No operator * overload for types '" + leftStr + "' and '" + rightStr + "'.";
        case NodeID::OpDivide:
            return "No operator / overload for types '" + leftStr + "' and '" + rightStr + "'.";
        case NodeID::OpEqual:
            return "No operator == overload for types '" + leftStr + "' and '" + rightStr + "'.";
        case NodeID::OpNotEqual:
            return "No operator != overload for types '" + leftStr + "' and '" + rightStr + "'.";
        case NodeID::OpGreaterThan:
            return "No operator > overload for types '" + leftStr + "' and '" + rightStr + "'.";
        case NodeID::OpGreaterThanOrEqual:
            return "No operator >= overload for types '" + leftStr + "' and '" + rightStr + "'.";
        case NodeID::OpLessThan:
            return "No operator < overload for types '" + leftStr + "' and '" + rightStr + "'.";
        case NodeID::OpLessThanOrEqual:
            return "No operator <= overload for types '" + leftStr + "' and '" + rightStr + "'.";
        case NodeID::OpAnd:
            return "No operator 'and' overload for types '" + leftStr + "' and '" + rightStr + "'.";
        case NodeID::OpOr:
            return "No operator 'or' overload for types '" + leftStr + "' and '" + rightStr + "'.";
        case NodeID::OpNot:
            return "No operator 'not' overload for type '" + rightStr + "'.";
        default:
            return "No operator overload for types '" + leftStr + "' and '" + rightStr + "'.";
    }
}

std::string Error::strInvalidArguments(const std::string& s)
{
    return "Invalid arguments for '" + s + "'.";
}

std::string Error::strNoSubscriptOperator(ValueType type)
{
    return "No subscript operator for type '" + Token::typeToString(type) + "'.";
}

std::string Error::strInvalidPosType()
{
    return "Pos type has to be one of the following: '" + std::string{ KW::Full } + "', '" + std::string{ KW::Empty } + "', '" + std::string{ KW::Index } + "', '" + std::string{ KW::Notindex } + "'.";
}

std::string Error::strReadOnlyAssignment()
{
    return "Cannot modify a read only value.";
}

/*
    ErrUnexpectedEof
*/
ErrUnexpectedEof::ErrUnexpectedEof(const Token& t)
{
    m_line = t.line;
    m_err = Error::strUnexpectedEof();
}

/*
    ErrUnexpectedToken
*/
ErrUnexpectedToken::ErrUnexpectedToken(const Token& t)
{
    m_line = t.line;
    m_err = Error::strUnexpectedToken(t.value);
}

ErrUnexpectedToken::ErrUnexpectedToken(const Token& t, std::string_view expected)
{
    m_line = t.line;
    m_err = Error::strUnexpectedToken(t.value, expected);
}

/*
    ErrIncorrectLiteralType
*/
ErrIncorrectLiteralType::ErrIncorrectLiteralType(const Token& t, ValueType expected)
{
    m_line = t.line;
    if (t.cat == TLiteral)
        m_err = Error::strIncorrectLiteralType(t.value, expected);
    else
        m_err = Error::strUnexpectedToken(t.value);
}

/*
    ErrFileNotFound
*/
ErrFileNotFound::ErrFileNotFound(const Token& t)
{
    m_line = t.line;

    std::filesystem::path path = t.value;
    if (std::filesystem::status(path).type() == std::filesystem::file_type::regular)
        m_err = strFileNotFound(t.value);
    else
        m_err = strIncorrectPath(t.value);
}

ErrFileNotFound::ErrFileNotFound(const std::string& path, uint32_t line)
{
    m_line = line;

    std::filesystem::path file_path = path;
    if (std::filesystem::status(file_path).type() == std::filesystem::file_type::regular)
        m_err = strFileNotFound(path);
    else
        m_err = strIncorrectPath(path);
}

/*
    ErrInvalidOutPath
*/
ErrInvalidOutPath::ErrInvalidOutPath(const std::string& path, uint32_t line)
{
    m_line = line;
    m_err = strInvalidOutPath(path);
}

/*
    ErrPreprocNotIdentifier
*/
ErrPreprocNotIdentifier::ErrPreprocNotIdentifier(const Token& t)
{
    m_line = t.line;
    if (t.cat == TIdentifier && !Token::isPreprocIdentifier(t.value))
        m_err = Error::strIncorrectIdentifier(t.value);
    else if (t.cat == TKeyword)
        m_err = Error::strKeywordNotAllowed(t.value);
    else
        m_err = Error::strUnexpectedToken(t.value);
}

/*
    ErrMissingToken
*/
ErrMissingToken::ErrMissingToken(const Token& t, std::string_view missing)
{
    m_line = t.line;
    m_err = Error::strMissingToken(missing);
}

/*
    ErrMissingExpressionFor
*/
ErrMissingExpression::ErrMissingExpression(const std::vector<Token*>& tokens)
{
    m_line = tokens.front()->line;
    std::string expr = formatExpression(tokens);
    m_err = Error::strMissingExpression(expr);
}

/*
    ErrInvalidExpression
*/
ErrInvalidExpression::ErrInvalidExpression(const std::vector<Token*>& tokens)
{
    m_line = tokens.front()->line;
    std::string expr = formatExpression(tokens);
    m_err = Error::strInvalidExpression(expr);
}

/*
    ErrNotAMemberOf
*/
ErrNotAMemberOf::ErrNotAMemberOf(const std::string& member, ValueType type, uint32_t line)
{
    m_line = line;
    m_err = Error::strNotAMemberOf(member, type);
}

ErrNotAMemberOf::ErrNotAMemberOf(std::string_view member, ValueType type, uint32_t line)
{
    m_line = line;
    m_err = Error::strNotAMemberOf(std::string{ member }, type);
}

ErrNotAMemberOf::ErrNotAMemberOf(const std::string& member, std::string_view name, uint32_t line)
{
    m_line = line;
    m_err = Error::strNotAMemberOf(member, std::string{ name });
}

ErrNotAMemberOf::ErrNotAMemberOf(std::string_view member, std::string_view name, uint32_t line)
{
    m_line = line;
    m_err = Error::strNotAMemberOf(std::string{ member }, std::string{ name });
}

/*
    ErrNameCallNotVariable
*/
ErrNameCallNotVariable::ErrNameCallNotVariable(uint32_t line)
{
    m_line = line;
    m_err = Error::strNameCallNotVariable();
}

/*
    ErrRedeclaration
*/
ErrRedeclaration::ErrRedeclaration(const std::string& name, uint32_t line)
{
    m_line = line;
    m_err = Error::strRedeclaration(name);
}

/*
    ErrUndeclared
*/
ErrUndeclared::ErrUndeclared(const std::string& name, uint32_t line)
{
    m_line = line;
    m_err = Error::strUndeclared(name);
}

/*
    ErrUnassignedVariable
*/
ErrUnassignedVariable::ErrUnassignedVariable(const std::string& name, uint32_t line)
{
    m_line = line;
    m_err = Error::strUnassignedVariable(name);
}

/*
    ErrInvalidContext
*/
ErrInvalidContext::ErrInvalidContext(std::string_view keyword, uint32_t line)
{
    m_line = line;
    m_err = Error::strInvalidContext(std::string{ keyword });
}

ErrMissingValue::ErrMissingValue(std::string_view keyword, uint32_t line)
{
    m_line = line;
    m_err = Error::strMissingValue(std::string{ keyword });
}

/*
    ErrFunctionSignatureNotFound
*/
ErrFunctionSignatureNotFound::ErrFunctionSignatureNotFound(const std::string& name, uint32_t line)
{
    m_line = line;
    m_err = Error::strFunctionSignatureNotFound(name);
}

/*
    ErrNestedSignatureNotFound
*/
ErrNestedSignatureNotFound::ErrNestedSignatureNotFound(const std::string& name, uint32_t line)
{
    m_line = line;
    m_err = Error::strNestedSignatureNotFound(name);
}

/*
    ErrPresetSignatureNotFound
*/
ErrPresetSignatureNotFound::ErrPresetSignatureNotFound(const std::string& name, uint32_t line)
{
    m_line = line;
    m_err = Error::strPresetSignatureNotFound(name);
}

/*
    ErrNestedDifferentReturnType
*/
ErrNestedDifferentReturnType::ErrNestedDifferentReturnType(const std::string& name, ValueType expected, uint32_t line)
{
    m_line = line;
    m_err = Error::strNestedDifferentReturnType(name, expected);
}

/*
    ErrReturnInvalidContext
*/
ErrReturnInvalidContext::ErrReturnInvalidContext(uint32_t line)
{
    m_line = line;
    m_err = Error::strReturnInvalidContext();
}

/*
    ErrBreakInvalidContext
*/
ErrBreakInvalidContext::ErrBreakInvalidContext(uint32_t line)
{
    m_line = line;
    m_err = Error::strBreakInvalidContext();
}

/*
    ErrContinueInvalidContext
*/
ErrContinueInvalidContext::ErrContinueInvalidContext(uint32_t line)
{
    m_line = line;
    m_err = Error::strContinueInvalidContext();
}

/*
    ErrInvokeInvalidContext
*/
ErrInvokeInvalidContext::ErrInvokeInvalidContext(uint32_t line)
{
    m_line = line;
    m_err = Error::strInvokeInvalidContext();
}

/*
    ErrMissingProperty
*/
ErrMissingProperty::ErrMissingProperty(std::string_view keyword, uint32_t line)
{
    m_line = line;
    m_err = Error::strMissingProperty(std::string{ keyword });
}

/*
    ErrMissingReturn
*/
ErrMissingReturn::ErrMissingReturn(const std::string& name, uint32_t line)
{
    m_line = line;
    m_err = Error::strMissingReturn(name);
}

/*
    ErrIncorrectValueType
*/
ErrIncorrectValueType::ErrIncorrectValueType(ValueType type, ValueType expected, uint32_t line)
{
    m_line = line;
    m_err = Error::strIncorrectValueType(type, expected);
}

/*
    ErrNoOperatorOverload
*/
ErrNoOperatorOverload::ErrNoOperatorOverload(ValueType left, ValueType right, NodeID op, uint32_t line)
{
    m_line = line;
    m_err = Error::strNoOperatorOverload(left, right, op);
}

/*
    ErrInvalidArguments
*/
ErrInvalidArguments::ErrInvalidArguments(const std::string& name, uint32_t line)
{
    m_line = line;
    m_err = Error::strInvalidArguments(name);
}

/*
    ErrNoSubscriptOperator
*/
ErrNoSubscriptOperator::ErrNoSubscriptOperator(ValueType type, uint32_t line)
{
    m_line = line;
    m_err = Error::strNoSubscriptOperator(type);
}

/*
    ErrInvalidPosType
*/
ErrInvalidPosType::ErrInvalidPosType(uint32_t line)
{
    m_line = line;
    m_err = Error::strInvalidPosType();
}

/*
    ErrReadOnlyAssignment
*/
ErrReadOnlyAssignment::ErrReadOnlyAssignment(uint32_t line)
{
    m_line = line;
    m_err = Error::strReadOnlyAssignment();
}
