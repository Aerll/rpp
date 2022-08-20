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
#ifndef RPP_SIGNATURE_HPP
#define RPP_SIGNATURE_HPP

#include <vector>

#include <enums.hpp>

class Signature final {
public:
    Signature() = default;

    bool isSame(const Signature& call) const;
    bool isConvertible(const Signature& call) const;
    bool isVariadicConvertible(const Signature& call) const;

    bool isVariadic() const;

    const std::vector<ValueType>& getTypes() const noexcept
        { return m_types; }
    void setTypes(std::vector<ValueType>&& types) noexcept
        { m_types = std::move(types); }
    void addType(ValueType type)
        { m_types.push_back(type); }

private:
    std::vector<ValueType> m_types;
};

#endif // RPP_SIGNATURE_HPP