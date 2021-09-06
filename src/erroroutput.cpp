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
#include <erroroutput.hpp>

#include <iostream>
#include <iomanip>

namespace errorOutput::print {

void string(std::string_view str, uint32_t width)
{
    std::cout << std::setw(width) << str << std::setw(0);
}

void stage(std::string_view stageName)
{
    std::cout << ">>> " << stageName << '\n';
}

void stage(std::string_view stageName, const std::string& fileName)
{
    std::cout << ">>> " << stageName << ": '" << fileName << "'\n";
}

void summary(uint32_t errorsCount, bool failed)
{
    if (failed)
        std::cout << ">>> failed - errors: " << errorsCount << '\n';
    else
        std::cout << "> \n";
}

void newLine(uint32_t count)
{
    for (uint32_t i = 0; i < count; ++i)
        std::cout << '\n';
}

}