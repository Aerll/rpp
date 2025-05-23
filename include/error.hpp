///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2020-2025 Aerll - aerlldev@gmail.com
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
#ifndef RPP_ERROR_HPP
#define RPP_ERROR_HPP

#include <enums.hpp>
#include <erroroutput.hpp>

#include <vector>

class Token;

class Error {
protected:
    static std::string formatExpression(const std::vector<Token*>& tokens);

    static std::string strUnexpectedEof();
    static std::string strUnexpectedToken(const std::string& s);
    static std::string strUnexpectedToken(const std::string& s, std::string_view expected);
    static std::string strKeywordNotAllowed(const std::string& s);
    static std::string strIncorrectIdentifier(const std::string& s);
    static std::string strIncorrectLiteralType(const std::string& s, ValueType expected);
    static std::string strIncorrectPath(const std::string& s);
    static std::string strFileNotFound(const std::string& s);
    static std::string strInvalidOutPath(const std::string& s);
    static std::string strInvalidOutExtension(const std::string& s);
    static std::string strMissingExpression(const std::string& s);
    static std::string strMissingToken(std::string_view missing);
    static std::string strInvalidExpression(const std::string& s);

    // AST
    static std::string strNotAMemberOf(const std::string& s, ValueType type);
    static std::string strNotAMemberOf(const std::string& s, const std::string& of);
    static std::string strNameCallNotVariable();
    static std::string strRedeclaration(const std::string& s);
    static std::string strUndeclared(const std::string& s);
    static std::string strUnassignedVariable(const std::string& s);
    static std::string strInvalidContext(const std::string& s);
    static std::string strMissingValue(const std::string& s);
    static std::string strFunctionSignatureNotFound(const std::string& s);
    static std::string strNestedSignatureNotFound(const std::string& s);
    static std::string strNestedDifferentReturnType(const std::string& s, ValueType expected);
    static std::string strReturnInvalidContext();
    static std::string strBreakInvalidContext();
    static std::string strContinueInvalidContext();
    static std::string strInvokeInvalidContext();
    static std::string strMissingProperty(const std::string& s);
    static std::string strMissingReturn(const std::string& s);
    static std::string strIncorrectValueType(ValueType type, ValueType expected);
    static std::string strNoOperatorOverload(ValueType left, ValueType right, NodeID op);
    static std::string strInvalidArguments(const std::string& s);
    static std::string strNoSubscriptOperator(ValueType type);
    static std::string strInvalidPosType();
    static std::string strReadOnlyAssignment();

protected:
    Error() = default;

public:
    Error(const Error&)            = delete;
    Error& operator=(const Error&) = delete;

    virtual ~Error() = default;

    u32 line() const noexcept {
        return m_line;
    }

    void print() const {
        errorOutput::print::string(m_err);
        errorOutput::print::newLine();
    }

protected:
    std::string m_err;
    u32 m_line;
};

class ErrUnexpectedEof final : public Error {
public:
    ErrUnexpectedEof(const Token& t);
};

class ErrUnexpectedToken final : public Error {
public:
    ErrUnexpectedToken(const Token& t);
    ErrUnexpectedToken(const Token& t, std::string_view expected);
};

class ErrIncorrectLiteralType final : public Error {
public:
    ErrIncorrectLiteralType(const Token& t, ValueType expected);
};

class ErrFileNotFound final : public Error {
public:
    ErrFileNotFound(const Token& t);
    ErrFileNotFound(const std::string& path, u32 line);
};

class ErrInvalidOutPath final : public Error {
public:
    ErrInvalidOutPath(const std::string& path, u32 line);
};

class ErrInvalidOutExtension final : public Error {
public:
    ErrInvalidOutExtension(const std::string& extension, u32 line);
};

class ErrPreprocNotIdentifier final : public Error {
public:
    ErrPreprocNotIdentifier(const Token& t);
};

class ErrMissingToken final : public Error {
public:
    ErrMissingToken(const Token& t, std::string_view missing);
};

class ErrMissingExpression final : public Error {
public:
    ErrMissingExpression(const std::vector<Token*>& tokens);
};

class ErrInvalidExpression final : public Error {
public:
    ErrInvalidExpression(const std::vector<Token*>& tokens);
};

// AST
class ErrNotAMemberOf final : public Error {
public:
    ErrNotAMemberOf(const std::string& member, ValueType type, u32 line);
    ErrNotAMemberOf(std::string_view member, ValueType type, u32 line);
    ErrNotAMemberOf(const std::string& member, std::string_view name, u32 line);
    ErrNotAMemberOf(std::string_view member, std::string_view name, u32 line);
};

class ErrNameCallNotVariable final : public Error {
public:
    ErrNameCallNotVariable(u32 line);
};

class ErrRedeclaration final : public Error {
public:
    ErrRedeclaration(const std::string& name, u32 line);
};

class ErrUndeclared final : public Error {
public:
    ErrUndeclared(const std::string& name, u32 line);
};

class ErrUnassignedVariable final : public Error {
public:
    ErrUnassignedVariable(const std::string& name, u32 line);
};

class ErrInvalidContext final : public Error {
public:
    ErrInvalidContext(std::string_view keyword, u32 line);
};

class ErrMissingValue final : public Error {
public:
    ErrMissingValue(std::string_view keyword, u32 line);
};

class ErrFunctionSignatureNotFound final : public Error {
public:
    ErrFunctionSignatureNotFound(const std::string& name, u32 line);
};

class ErrNestedSignatureNotFound final : public Error {
public:
    ErrNestedSignatureNotFound(const std::string& name, u32 line);
};

class ErrNestedDifferentReturnType final : public Error {
public:
    ErrNestedDifferentReturnType(const std::string& name, ValueType expected, u32 line);
};

class ErrReturnInvalidContext final : public Error {
public:
    ErrReturnInvalidContext(u32 line);
};

class ErrBreakInvalidContext final : public Error {
public:
    ErrBreakInvalidContext(u32 line);
};

class ErrContinueInvalidContext final : public Error {
public:
    ErrContinueInvalidContext(u32 line);
};

class ErrInvokeInvalidContext final : public Error {
public:
    ErrInvokeInvalidContext(u32 line);
};

class ErrMissingProperty final : public Error {
public:
    ErrMissingProperty(std::string_view keyword, u32 line);
};

class ErrMissingReturn final : public Error {
public:
    ErrMissingReturn(const std::string& name, u32 line);
};

class ErrIncorrectValueType final : public Error {
public:
    ErrIncorrectValueType(ValueType type, ValueType expected, u32 line);
};

class ErrNoOperatorOverload final : public Error {
public:
    ErrNoOperatorOverload(ValueType left, ValueType right, NodeID op, u32 line);
};

class ErrInvalidArguments final : public Error {
public:
    ErrInvalidArguments(const std::string& name, u32 line);
};

class ErrNoSubscriptOperator final : public Error {
public:
    ErrNoSubscriptOperator(ValueType type, u32 line);
};

class ErrInvalidPosType final : public Error {
public:
    ErrInvalidPosType(u32 line);
};

class ErrReadOnlyAssignment final : public Error {
public:
    ErrReadOnlyAssignment(u32 line);
};

#endif // RPP_ERROR_HPP
