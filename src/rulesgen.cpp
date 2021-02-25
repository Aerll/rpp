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
#include <rulesgen.hpp>

#include <fstream>

#include <automapper.hpp>
#include <erroroutput.hpp>

/*
    RulesGen
*/
void RulesGen::exec(std::vector<AutoMapper>& automappers, const std::filesystem::path& outputPath, const std::filesystem::path& tileset)
{
    if (automappers.empty()) {
        errorOutput::print::stage("No rules to generate");
        return;
    }

    std::filesystem::path path = outputPath / tileset;
    errorOutput::print::stage("Generating rules", path.string() + ".rules");

    std::ofstream rulesFile(path.string() + ".rules");
    if (rulesFile.is_open()) {
        for (auto& automapper : automappers) {
            rulesFile << "[" << automapper.name << "]\n\n";

            for (auto& run : automapper.runs) {
                run.rules.erase(util::removeDuplicates(run.rules.begin(), run.rules.end()), run.rules.end());

                for (uint32_t i = 0; i < run.copies; ++i) {
                    rulesFile << "NewRun\n";
                    if (run.overrideLayer)
                        rulesFile << "NoLayerCopy\n";
                    rulesFile << '\n';

                    for (auto& rule : run.rules) {
                        if (i == 0) // optimize only once
                            optimize(rule);

                        rulesFile << "Index " << rule.indexInfo.tileID << " ";
                        if ((rule.indexInfo.rotation & Rotation::V) != Rotation::Default)
                            rulesFile << "XFLIP ";
                        if ((rule.indexInfo.rotation & Rotation::H) != Rotation::Default)
                            rulesFile << "YFLIP ";
                        if ((rule.indexInfo.rotation & Rotation::R) != Rotation::Default)
                            rulesFile << "ROTATE ";
                        rulesFile << '\n';

                        for (auto& posRule : rule.posRules) {
                            if (posRule.indexInfos.empty() && posRule.ruleType != PosRuleType::FULL && posRule.ruleType != PosRuleType::EMPTY)
                                continue;
                            if (posRule.ruleType == PosRuleType::NORULE)
                                continue;

                            if (i == 0) // optimize only once
                                optimize(posRule);

                            rulesFile << "Pos " << posRule.x << " " << posRule.y << " ";
                            switch (posRule.ruleType) {
                                case PosRuleType::INDEX: rulesFile << "INDEX "; break;
                                case PosRuleType::NOTINDEX: rulesFile << "NOTINDEX "; break;
                                case PosRuleType::FULL: rulesFile << "FULL \n"; continue;
                                case PosRuleType::EMPTY: rulesFile << "EMPTY \n"; continue;
                            }

                            bool insertOr = false;
                            for (const auto& indexInfo : posRule.indexInfos) {
                                if (insertOr)
                                    rulesFile << "OR ";
                                rulesFile << indexInfo.tileID << " ";
                                if ((indexInfo.rotation & Rotation::N) != Rotation::Default)
                                    rulesFile << "NONE ";
                                else {
                                    if ((indexInfo.rotation & Rotation::V) != Rotation::Default)
                                        rulesFile << "XFLIP ";
                                    if ((indexInfo.rotation & Rotation::H) != Rotation::Default)
                                        rulesFile << "YFLIP ";
                                    if ((indexInfo.rotation & Rotation::R) != Rotation::Default)
                                        rulesFile << "ROTATE ";
                                }
                                insertOr = true;
                            }
                            rulesFile << '\n';
                        }

                        if (rule.random != 0.0f)
                            rulesFile << "Random " << rule.random << '\n';
                        if (rule.noDefaultRule)
                            rulesFile << "NoDefaultRule\n";
                        rulesFile << '\n';
                    }
                }
            }
        }
    }
}

void RulesGen::optimize(Rule& rule)
{
    for (size_t i = 1; i < rule.posRules.size(); ++i) {
        for (int64_t j = i - 1; j >= 0; --j) {
            if (rule.posRules[i].ruleType == rule.posRules[j].ruleType &&
                rule.posRules[i].x == rule.posRules[j].x &&
                rule.posRules[i].y == rule.posRules[j].y
                ) {
                rule.posRules[i].ruleType = PosRuleType::NORULE;
                if (rule.posRules[i].ruleType == PosRuleType::EMPTY || rule.posRules[i].ruleType == PosRuleType::FULL)
                    continue;

                for (const auto& indexInfo : rule.posRules[i].indexInfos)
                    rule.posRules[j].indexInfos.push_back(indexInfo);
            }
        }
    }
}

void RulesGen::optimize(PosRule& rule)
{
    std::sort(rule.indexInfos.begin(), rule.indexInfos.end());
    rule.indexInfos.erase(std::unique(rule.indexInfos.begin(), rule.indexInfos.end()), rule.indexInfos.end());
}
