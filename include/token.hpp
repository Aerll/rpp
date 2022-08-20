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
#ifndef RPP_TOKEN_HPP
#define RPP_TOKEN_HPP

#include <string>
#include <string_view>

#include <enums.hpp>
#include <utility.hpp>

class TokenH;

class Token final {
public:
    Token() = default;
    Token(const Token&) = default;
    Token(Token&&) = default;
    Token& operator=(const Token&) = default;
    Token& operator=(Token&&) = default;

    Token(int32_t cat, std::string_view value = {}, uint32_t line = {}, ValueType type = {})
        : value(value)
        , line(line)
        , type(type)
        , cat(cat)
    {
    }

    bool operator==(const Token& rhs) const noexcept
        { return cat == rhs.cat && type == rhs.type && value == rhs.value; }
    bool operator!=(const Token& rhs) const noexcept
        { return !(*this == rhs); }

    bool operator==(const TokenH& rhs) const noexcept;
    bool operator!=(const TokenH& rhs) const noexcept;

    // checks
    static bool isKeyword(const std::string& s) noexcept;
    static bool isIdentifier(const std::string& s) noexcept;
    static bool isPunctuator(const std::string& s) noexcept;
    static bool isPunctuator(char c) noexcept;
    static bool isOperator(const std::string& s) noexcept;
    static bool isOperator(char c) noexcept;
    static bool isBlank(char c) noexcept;
    static bool isDigit(char c) noexcept;
    static bool isLetter(char c) noexcept;
    static bool isNewLine(char c) noexcept;

    static bool isType(const std::string& s) noexcept;
    static bool isSubtype(const std::string& s) noexcept;
    static bool isReturnType(const std::string& s) noexcept;
    static bool isAssignment(const std::string& s) noexcept;
    static bool isArithmetic(const std::string& s) noexcept;
    static bool isComparison(const std::string& s) noexcept;
    static bool isLogical(const std::string& s) noexcept;

    static bool isConvertible(ValueType from, ValueType to) noexcept;
    static bool isVariadic(ValueType type, ValueType variadic) noexcept;

    static bool isSingleRotation(std::string_view s) noexcept;
    static bool isSingleRotation(Rotation rotation) noexcept;
    static bool isRotation(std::string_view s) noexcept;
    static bool isPos(std::string_view s) noexcept;
    static bool isBuiltin(std::string_view s) noexcept;

    static bool isArray(ValueType type) noexcept;
    static bool isArrayOrObject(ValueType type) noexcept;
    static bool isArithmetic(ValueType type) noexcept;

    static ValueType getArithmeticResult(ValueType left, ValueType right) noexcept;

    static Rotation stringToRotation(std::string_view s) noexcept;
    static std::string rotationToString(Rotation rotation) noexcept;

    static ValueType stringToType(std::string_view type);
    static std::string typeToString(ValueType type, bool lowercase = true);

public:
    std::string value;
    uint32_t line;
    ValueType type;
    int32_t cat;
};

#endif // RPP_TOKEN_HPP