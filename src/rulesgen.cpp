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
#include <rulesgen.hpp>
#include <automapper.hpp>
#include <erroroutput.hpp>

/*
    RulesGen
*/
void RulesGen::run(std::vector<AutoMapper>& automappers, const std::filesystem::path& outputFile) {
    if (automappers.empty()) {
        errorOutput::print::stage("No rules to generate");
        return;
    }

    errorOutput::print::stage("Generating rules", outputFile.string());

    std::ofstream rulesFile(outputFile.string());
    if (rulesFile.is_open()) {
        for (auto& automapper : automappers) {
            rulesFile << "[" << automapper.name << "]";
            newLine(rulesFile);
            newLine(rulesFile);

            for (auto& run : automapper.runs) {
                if (run.rules.empty())
                    continue;

                run.rules.erase(util::removeDuplicates(run.rules.begin(), run.rules.end()), run.rules.end());

                for (u32 i = 0; i < run.copies; ++i) {
                    rulesFile << "NewRun";
                    newLine(rulesFile);
                    if (run.overrideLayer) {
                        rulesFile << "NoLayerCopy";
                        newLine(rulesFile);
                    }
                    newLine(rulesFile);

                    for (auto& rule : run.rules) {
                        if (i == 0) // optimize only once
                            optimize(rule);

                        auto vectors = getOrPosRules(rule);
                        Combinator combinator{ vectors };

                        removeOrPosRules(rule);

                        do {
                            rulesFile << "Index " << rule.indexInfo.tileID;
                            if ((rule.indexInfo.rotation & Rotation::V) != Rotation::Default || (rule.indexInfo.rotation & Rotation::X) != Rotation::Default)
                                rulesFile << " XFLIP";
                            if ((rule.indexInfo.rotation & Rotation::H) != Rotation::Default || (rule.indexInfo.rotation & Rotation::Y) != Rotation::Default)
                                rulesFile << " YFLIP";
                            if ((rule.indexInfo.rotation & Rotation::R) != Rotation::Default)
                                rulesFile << " ROTATE";
                            newLine(rulesFile);

                            for (auto& posRule : rule.posRules) {
                                generatePosRule(posRule, i == 0, rulesFile);
                            }

                            for (const auto& it : combinator.combination()) {
                                auto posRule = *it;
                                generatePosRule(posRule, i == 0, rulesFile);
                            }

                            if (rule.random > 1.0f) {
                                rulesFile << "Random " << rule.random;
                                newLine(rulesFile);
                            }
                            if (rule.noDefaultRule) {
                                rulesFile << "NoDefaultRule";
                                newLine(rulesFile);
                            }
                            newLine(rulesFile);

                        } while (combinator.next());
                    }
                }
            }
        }
        m_fileSize = rulesFile.tellp();
    }
}

void RulesGen::generatePosRule(PosRule& rule, bool runOptimize, std::ofstream& rulesFile) {
    if (rule.indexInfos.empty() && rule.ruleType != PosRuleType::FULL && rule.ruleType != PosRuleType::EMPTY)
        return;

    if (runOptimize) // optimize only once
        optimize(rule);

    rulesFile << "Pos " << rule.x << " " << rule.y;
    switch (rule.ruleType) {
        case PosRuleType::INDEX:    rulesFile << " INDEX"; break;
        case PosRuleType::NOTINDEX: rulesFile << " NOTINDEX"; break;
        case PosRuleType::FULL:
            rulesFile << " FULL";
            newLine(rulesFile);
            return;
        case PosRuleType::EMPTY:
            rulesFile << " EMPTY";
            newLine(rulesFile);
            return;
    }

    bool insertOr = false;
    for (const auto& indexInfo : rule.indexInfos) {
        if (insertOr)
            rulesFile << " OR";
        rulesFile << " " << indexInfo.tileID;
        if ((indexInfo.rotation & Rotation::N) != Rotation::Default)
            rulesFile << " NONE";
        else {
            if ((indexInfo.rotation & Rotation::V) != Rotation::Default || (indexInfo.rotation & Rotation::X) != Rotation::Default)
                rulesFile << " XFLIP";
            if ((indexInfo.rotation & Rotation::H) != Rotation::Default || (indexInfo.rotation & Rotation::Y) != Rotation::Default)
                rulesFile << " YFLIP";
            if ((indexInfo.rotation & Rotation::R) != Rotation::Default)
                rulesFile << " ROTATE";
        }
        insertOr = true;
    }
    newLine(rulesFile);
}

void RulesGen::newLine(std::ofstream& rulesFile) {
    rulesFile << '\n';
    ++m_lineCount;
}

void RulesGen::optimize(Rule& rule) const {
    for (usize i = 1; i < rule.posRules.size(); ++i) {
        for (isize j = i - 1; j >= 0; --j) {
            if (rule.posRules[i].ruleType == rule.posRules[j].ruleType
                && rule.posRules[i].x == rule.posRules[j].x
                && rule.posRules[i].y == rule.posRules[j].y
                && rule.posRules[i].op == rule.posRules[j].op
                && rule.posRules[i].group == rule.posRules[j].group) {
                rule.posRules[i].ruleType = PosRuleType::NORULE;
                if (rule.posRules[j].ruleType == PosRuleType::EMPTY || rule.posRules[j].ruleType == PosRuleType::FULL)
                    continue;

                for (const auto& indexInfo : rule.posRules[i].indexInfos)
                    rule.posRules[j].indexInfos.push_back(indexInfo);
            }
        }
    }

    rule.posRules.erase(
        std::remove_if(
            rule.posRules.begin(), rule.posRules.end(),
            [](const PosRule& posRule) {
                return posRule.ruleType == PosRuleType::NORULE;
            }
        ),
        rule.posRules.end()
    );
}

void RulesGen::optimize(PosRule& rule) const {
    std::sort(rule.indexInfos.begin(), rule.indexInfos.end());
    rule.indexInfos.erase(std::unique(rule.indexInfos.begin(), rule.indexInfos.end()), rule.indexInfos.end());
}

std::vector<std::vector<PosRule>> RulesGen::getOrPosRules(Rule& rule) const {
    std::vector<PosRule> orPosRules;
    std::copy_if(rule.posRules.begin(), rule.posRules.end(), std::back_inserter(orPosRules), [](const PosRule& posRule) {
        return posRule.op == Op::Or;
    });
    std::sort(orPosRules.begin(), orPosRules.end(), [](const PosRule& lhs, const PosRule& rhs) {
        return lhs.group < rhs.group;
    });

    if (orPosRules.empty())
        return {};

    std::vector<std::vector<PosRule>> result;
    result.push_back({});
    result.back().push_back(orPosRules.front());
    for (auto it = orPosRules.begin() + 1; it != orPosRules.end(); ++it) {
        if (it->group != (it - 1)->group)
            result.push_back({});
        result.back().push_back(*it);
    }
    return result;
}

void RulesGen::removeOrPosRules(Rule& rule) const {
    rule.posRules.erase(
        std::remove_if(
            rule.posRules.begin(), rule.posRules.end(),
            [](const PosRule& posRule) {
                return posRule.op == Op::Or;
            }
        ),
        rule.posRules.end()
    );
}

/*
    Combinator
*/
Combinator::Combinator(std::vector<std::vector<PosRule>>& vectors)
    : m_vectors(vectors) {
    m_combination.reserve(m_vectors.size());
    for (auto& v : m_vectors)
        m_combination.push_back(v.begin());
}

bool Combinator::next() {
    for (isize i = m_vectors.size() - 1; i >= 0; --i) {
        auto& v  = m_vectors[i];
        auto& it = m_combination[i];

        if (++it != v.end())
            return true;
        it = v.begin();
    }
    return false;
}
