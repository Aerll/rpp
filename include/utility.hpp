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
#ifndef RPP_UTILITY_HPP
#define RPP_UTILITY_HPP

#include <cstdint>
#include <type_traits>
#include <algorithm>

enum class Rotation;

namespace util {

Rotation toVHR(Rotation rotation) noexcept;

template <typename Type>
    concept _Enum = std::is_enum_v<Type>;

template <_Enum EnumType>
constexpr bool enum_b(EnumType val) noexcept
{
    return static_cast<bool>(val);
}

template <_Enum EnumType>
constexpr int32_t enum_i32(EnumType val) noexcept
{
    return static_cast<int32_t>(val);
}



template <_Enum EnumType>
constexpr EnumType b_enum(bool val) noexcept
{
    return static_cast<EnumType>(val);
}

template <_Enum EnumType>
constexpr EnumType i32_enum(int32_t val) noexcept
{
    return static_cast<EnumType>(val);
}

inline uint32_t digitsCount(uint32_t val) noexcept
{
    if (val < 10u) return 1;
    if (val < 100u) return 2;
    if (val < 1000u) return 3;
    if (val < 10000u) return 4;
    if (val < 100000u) return 5;
    if (val < 1000000u) return 6;
    if (val < 10000000u) return 7;
    if (val < 100000000u) return 8;
    if (val < 1000000000u) return 9;
    else return 10; // maximum value for an uint32_t is 2^32-1 = 4294967295 (10 digits)
}

template <typename Iterator>
Iterator removeDuplicates(Iterator first, Iterator last)
{
    auto new_last = first;

    for (auto it = first; it != last; ++it) {
        if (std::find(first, new_last, *it) == new_last) {
            if (new_last != it)
                *new_last = *it;
            ++new_last;
        }
    }
    return new_last;
}

template <typename Iterator, typename Type>
bool contains(Iterator first, Iterator last, const Type& value)
{
    return std::find(first, last, value) != last;
}

} // namespace util

#endif // RPP_UTILITY_HPP
