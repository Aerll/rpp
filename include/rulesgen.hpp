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
#ifndef RPP_RULESGEN_HPP
#define RPP_RULESGEN_HPP

#include <filesystem>
#include <fstream>
#include <vector>

struct AutoMapper;
struct Rule;
struct PosRule;

class RulesGen final {
public:
    static void exec(std::vector<AutoMapper>& automappers, const std::filesystem::path& outputFile);

private:
    static void generatePosRule(PosRule& rule, bool runOptimize, std::ofstream& rulesFile);
    static void optimize(Rule& rule);
    static void optimize(PosRule& rule);
    static std::vector<std::vector<PosRule>> getOrPosRules(Rule& rule);
    static void removeOrPosRules(Rule& rule);
};

class Combinator final {
public:
    Combinator(std::vector<std::vector<PosRule>>& vectors);

    bool next();

    std::vector<std::vector<PosRule>::iterator> combination() const
        { return m_combination; }

private:
    std::vector<std::vector<PosRule>>& m_vectors;
    std::vector<std::vector<PosRule>::iterator> m_combination;
};

#endif // RPP_RULESGEN_HPP