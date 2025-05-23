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
#ifndef RPP_ERRORQUEUE_HPP
#define RPP_ERRORQUEUE_HPP

#include <error.hpp>
#include <utility.hpp>

#include <memory>
#include <queue>

class ErrorQueue {
protected:
    ErrorQueue()                             = default;
    ErrorQueue(const ErrorQueue&)            = delete;
    ErrorQueue& operator=(const ErrorQueue&) = delete;

public:
    virtual ~ErrorQueue() = default;

protected:
    void pushError(std::unique_ptr<Error>&& err) {
        m_errors.push(std::move(err));
        ++m_count;
    }

    bool hasErrors() const {
        return !m_errors.empty();
    }

    void resetCount() noexcept {
        m_count = 0;
    }

    u32 totalCount() const noexcept {
        return m_count;
    }

    void printErrors(u32 lineWidth);

protected:
    std::queue<std::unique_ptr<Error>> m_errors;
    u32 m_count = 0;
};

#endif // RPP_ERRORQUEUE_HPP
