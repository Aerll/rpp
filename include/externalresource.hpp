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
#ifndef RPP_EXTERNALPRESET_HPP
#define RPP_EXTERNALPRESET_HPP

#include <filesystem>
#include <vector>

#include <utility.hpp>

class Token;

class ExternalResource final {
    struct Info {
        std::string fileName;
        uint32_t beginLine;
        uint32_t linesCount;
    };
    ExternalResource() = default;

public:
    static ExternalResource& get();

    std::vector<Token> load(const std::filesystem::path& path, uint32_t beg);
    bool isLoaded(const std::filesystem::path& path) const;

    const std::vector<Info>& info() const noexcept
        { return m_info; }

private:
    void addInfo(Info&& info);

private:
    std::vector<Info> m_info;
};

#endif // RPP_EXTERNALPRESET_HPP