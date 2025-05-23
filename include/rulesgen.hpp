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
#ifndef RPP_RULESGEN_HPP
#define RPP_RULESGEN_HPP

#include <aliases.hpp>

#include <filesystem>
#include <fstream>
#include <vector>

struct AutoMapper;
struct Rule;
struct PosRule;

class RulesGen final {
public:
    RulesGen() = default;

    void run(std::vector<AutoMapper>& automappers, const std::filesystem::path& outputFile);

    std::streamoff fileSize() const noexcept {
        return m_fileSize;
    }

    u32 lineCount() const noexcept {
        return m_lineCount;
    }

private:
    void newLine(std::ofstream& rulesFile);
    void generatePosRule(PosRule& rule, bool runOptimize, std::ofstream& rulesFile);
    void optimize(Rule& rule) const;
    void optimize(PosRule& rule) const;
    std::vector<std::vector<PosRule>> getOrPosRules(Rule& rule) const;
    void removeOrPosRules(Rule& rule) const;

private:
    std::streamoff m_fileSize = 0;
    u32 m_lineCount      = 1;
};

class Combinator final {
public:
    Combinator(std::vector<std::vector<PosRule>>& vectors);

    bool next();

    std::vector<std::vector<PosRule>::iterator> combination() const {
        return m_combination;
    }

private:
    std::vector<std::vector<PosRule>>& m_vectors;
    std::vector<std::vector<PosRule>::iterator> m_combination;
};

#endif // RPP_RULESGEN_HPP
