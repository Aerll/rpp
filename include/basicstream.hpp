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
#ifndef RPP_BASICSTREAM_HPP
#define RPP_BASICSTREAM_HPP

#include <vector>

#include <utility.hpp>

template <typename T>
class BasicStream {
public:
    BasicStream() = delete;
    BasicStream(const BasicStream&) = delete;
    BasicStream& operator=(const BasicStream&) = delete;

    virtual ~BasicStream() = default;

    BasicStream(std::vector<T>&& data)
        : m_data(std::move(data))
        , m_current(0)
    {
        m_data.push_back(T{});
    }

    const T& current(int32_t offset = 0) const
        { return m_current + offset < m_data.size() && m_current + offset >= 0 ? m_data.at(m_current + offset) : m_data.back(); }
    T& current(int32_t offset = 0)
        { return m_current + offset < m_data.size() && m_current + offset >= 0 ? m_data.at(m_current + offset) : m_data.back(); }

    T& next() 
        { return m_current < m_data.size() ? m_data.at(m_current++) : m_data.back(); }

    void skip(uint32_t count = 1) noexcept
        { m_current += count; }

    bool eof() const noexcept
        { return m_current >= m_data.size() - 1; }

    std::vector<T>&& data() noexcept
        { return std::move(m_data); }
    const std::vector<T>& data() const noexcept
        { return m_data; }
    uint32_t currentIndex() const noexcept
        { return m_current; }

    void reset() noexcept
        { m_current = 0; }

protected:
    std::vector<T> m_data;
    uint32_t m_current;
};

#endif // RPP_BASICSTREAM_HPP
