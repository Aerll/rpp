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
#ifndef RPP_AUTOMAPPER_HPP
#define RPP_AUTOMAPPER_HPP

#include <vector>
#include <string>

#include <enums.hpp>

enum class PosRuleType {
    NORULE,
    INDEX,
    NOTINDEX,
    EMPTY,
    FULL
};

struct IndexInfo {
    int32_t tileID;
    Rotation rotation;
    
    friend bool operator==(const IndexInfo& lhs, const IndexInfo& rhs)
        { return lhs.tileID == rhs.tileID && lhs.rotation == rhs.rotation; }
    friend bool operator<(const IndexInfo& lhs, const IndexInfo& rhs)
        { return lhs.tileID < rhs.tileID; }
};

struct PosRule {
    int32_t x;
    int32_t y;
    PosRuleType ruleType;
    std::vector<IndexInfo> indexInfos;
    Op op;
    int32_t group;
    
    friend bool operator==(const PosRule& lhs, const PosRule& rhs)
        { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.ruleType == rhs.ruleType && lhs.indexInfos == rhs.indexInfos; }
};

struct Rule {
    IndexInfo indexInfo;
    std::vector<PosRule> posRules;
    float random;
    bool noDefaultRule;
    
    friend bool operator==(const Rule& lhs, const Rule& rhs)
        { return lhs.indexInfo == rhs.indexInfo && lhs.posRules == rhs.posRules && lhs.random == rhs.random && lhs.noDefaultRule == rhs.noDefaultRule; }
};

struct Run {
    std::vector<Rule> rules;
    uint32_t copies;
    bool overrideLayer;
};

struct AutoMapper {
    std::string name;
    std::vector<Run> runs;
};

#endif // RPP_AUTOMAPPER_HPP