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
#include <cli.hpp>
#include <externalresource.hpp>
#include <inputstream.hpp>
#include <io.hpp>
#include <preprocessor.hpp>
#include <tokenizer.hpp>

#include <algorithm>
#include <cstdint>
#include <filesystem>

/*
    ExternalResource
*/
ExternalResource& ExternalResource::get() {
    static ExternalResource instance;
    return instance;
}

std::vector<Token> ExternalResource::load(const std::filesystem::path& path, const CLI& cli) {
    InputStream inputStream(FileR::read(path));
    Tokenizer tokenizer;
    tokenizer.run(inputStream, false);

    Preprocessor preprocessor(tokenizer.data());
    preprocessor.run(path, cli);

    return preprocessor.data();
}

bool ExternalResource::isLoaded(const std::filesystem::path& path) const {
    auto fileName = std::filesystem::canonical(path).string();
    return std::find_if(
               info().begin(), info().end(),
               [&](const Info& i) -> bool {
                   return i.fileName == fileName;
               }
           )
        != info().end();
}

void ExternalResource::addInfo(Info&& info) {
    m_info.push_back(std::move(info));
}
