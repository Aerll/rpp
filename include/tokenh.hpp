///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2020-2023 Aerll - aerlldev@gmail.com
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
#ifndef RPP_TOKENH_HPP
#define RPP_TOKENH_HPP

#include <enums.hpp>
#include <tokenliterals.hpp>
#include <utility.hpp>

class Token;

class TokenH final {
public:
    TokenH() = delete;

    constexpr TokenH(const int32_t cat, const std::string_view& value)
        : value(value)
        , cat(cat) {}

    bool operator==(const TokenH& rhs) const noexcept {
        return cat == rhs.cat && value == rhs.value;
    }

    bool operator!=(const TokenH& rhs) const noexcept {
        return !(*this == rhs);
    }

    bool operator==(const Token& rhs) const noexcept;
    bool operator!=(const Token& rhs) const noexcept;

public:
    const std::string_view& value;
    const int cat;
};

namespace TH {

constexpr TokenH InvalidNull{ TInvalid, IN::Null };

constexpr TokenH End{ TKeyword, KW::End };
constexpr TokenH StatementEnd{ TPunctuator, PU::StatementEnd };

constexpr TokenH If{ TKeyword, KW::If };
constexpr TokenH For{ TKeyword, KW::For };
constexpr TokenH Array{ TKeyword, KW::Array };

constexpr TokenH FunctionCallOpen{ TPunctuator, PU::FunctionCallOpen };
constexpr TokenH FunctionCallClose{ TPunctuator, PU::FunctionCallClose };
constexpr TokenH ArraySubscriptOpen{ TPunctuator, PU::ArraySubscriptOpen };
constexpr TokenH ArraySubscriptClose{ TPunctuator, PU::ArraySubscriptClose };

constexpr TokenH Separator{ TPunctuator, PU::Separator };
constexpr TokenH To{ TKeyword, KW::To };
constexpr TokenH Assignment{ TOperator, OP::Assignment };
constexpr TokenH Or{ TKeyword, KW::Or };
constexpr TokenH And{ TKeyword, KW::And };
constexpr TokenH Not{ TKeyword, KW::Not };
constexpr TokenH Equal{ TOperator, OP::Equal };
constexpr TokenH NotEqual{ TOperator, OP::NotEqual };
constexpr TokenH GreaterThanOrEqual{ TOperator, OP::GreaterThanOrEqual };
constexpr TokenH GreaterThan{ TOperator, OP::GreaterThan };
constexpr TokenH LessThanOrEqual{ TOperator, OP::LessThanOrEqual };
constexpr TokenH LessThan{ TOperator, OP::LessThan };
constexpr TokenH Addition{ TOperator, OP::Addition };
constexpr TokenH Subtraction{ TOperator, OP::Subtraction };
constexpr TokenH Multiplication{ TOperator, OP::Multiplication };
constexpr TokenH Division{ TOperator, OP::Division };
constexpr TokenH Range{ TOperator, OP::Range };
constexpr TokenH MemberAccess{ TPunctuator, PU::MemberAccess };
constexpr TokenH StringLiteral{ TPunctuator, PU::StringLiteral };
constexpr TokenH ReturnType{ TOperator, OP::ReturnType };

}

#endif // RPP_TOKENH_HPP
