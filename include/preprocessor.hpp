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
#ifndef RPP_PREPROCESSOR_HPP
#define RPP_PREPROCESSOR_HPP

#include <vector>
#include <filesystem>

#include <iresult.hpp>
#include <errorqueue.hpp>
#include <token.hpp>

struct CLI;

class Preprocessor final : public ErrorQueue, public IResult {
    using iterator = std::vector<Token>::iterator;

public:
    Preprocessor() = delete;
    Preprocessor(const Preprocessor&) = delete;
    Preprocessor& operator=(const Preprocessor&) = delete;

    Preprocessor(std::vector<Token>&& data)
        : IResult()
        , m_data(std::move(data))
        , m_curr(m_data.begin())
        , m_output(std::filesystem::current_path() / "tileset.rules")
        , m_memory(1024 * 1024 * 50)
    {
    }

    void run(const std::filesystem::path& path, const CLI& cli);

    std::vector<Token>&& data() noexcept
        { return std::move(m_data); }

    const std::filesystem::path& output() const noexcept
        { return m_output; }
    int64_t memory() const noexcept
        { return m_memory; }

private:
    std::filesystem::path getPath(const std::string& value) const;
    std::vector<Token> getLine();

private:
    std::vector<Token> m_data;
    iterator m_curr;

    std::filesystem::path m_output;
    int64_t m_memory;
};

#endif // RPP_PREPROCESSOR_HPP
