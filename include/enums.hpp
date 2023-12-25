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
#ifndef RPP_ENUMS_HPP
#define RPP_ENUMS_HPP

#include <utility.hpp>

enum {
    TInvalid,
    TKeyword,
    TIdentifier,
    TLiteral,
    TPunctuator,
    TOperator,
};

enum class Order {
    LeftToRight,
    RightToLeft,
};

enum class Op {
    And = 0,
    Or  = 1,
};

enum class ValueType {
    Null   = 0,
    Bool   = 1 << 0,
    Int    = 1 << 1,
    Range  = 1 << 2,
    Coord  = 1 << 3,
    Float  = 1 << 4,
    String = 1 << 5,
    Object = 1 << 6,
    Array  = 1 << 7, // array needs to have subtype

    ArrayBool   = Array | Bool,
    ArrayInt    = Array | Int,
    ArrayRange  = Array | Range,
    ArrayCoord  = Array | Coord,
    ArrayFloat  = Array | Float,
    ArrayString = Array | String,
    ArrayObject = Array | Object,
};

inline ValueType operator|(ValueType lhs, ValueType rhs) noexcept {
    return util::i32_enum<ValueType>(util::enum_i32(lhs) | util::enum_i32(rhs));
}

inline ValueType& operator|=(ValueType& lhs, ValueType rhs) noexcept {
    return lhs = lhs | rhs;
}

inline ValueType operator&(ValueType lhs, ValueType rhs) noexcept {
    return util::i32_enum<ValueType>(util::enum_i32(lhs) & util::enum_i32(rhs));
}

inline ValueType operator^(ValueType lhs, ValueType rhs) noexcept {
    return util::i32_enum<ValueType>(util::enum_i32(lhs) ^ util::enum_i32(rhs));
}

enum class StatementID {
    Empty,
    Expr,
    For,
    If,
    Decl,
    FunctionDef,
    FunctionDecl,
    NestedFunctionDef,
    NestedFunctionDecl,
    NestedDecl,
    Return,
    Break,
    Continue,
};

enum class ExpressionID {
    Invalid,
    Empty,
    Literal,
    Identifier,
    Keyword,
    Assignment,
    Arithmetic,
    Comparison,
    Logical,
    UnaryLogical,
    ReturnType,
    FunctionCall,
    ForRange,
    MemberAccess,
    Error,
    Warning,
    Assert,
    ArraySubscript,
    PercentLiteral,
    StringLiteral,
    RangeLiteral,
    CoordLiteral,
    Separator,
    DeclType,
};

enum class NodeID {
    Null,
    Bool,
    Int,
    Range,
    Coord,
    Float,
    String,
    Object,
    Array,
    Declaration,
    Identifier,
    Variable,
    Anchor,
    Count,
    Last,
    X,
    Y,
    Rotation,
    Empty,
    Full,
    Index,
    NotIndex,
    Insert,
    Rotate,
    OpAssign,
    OpAdd,
    OpSubtract,
    OpMultiply,
    OpDivide,
    OpEqual,
    OpNotEqual,
    OpGreaterThan,
    OpGreaterThanOrEqual,
    OpLessThan,
    OpLessThanOrEqual,
    OpAnd,
    OpOr,
    OpNot,
    OpRange,
    OpCoord,
    Error,
    Warning,
    Assert,
    Return,
    Break,
    Continue,
    ForRange,
    ArraySubscript,
    PushCall,
    HasCall,
    UniqueCall,
    StrCall,
    NameCall,
    FindCall,
    FunctionCall,
    NestedCall,
    For,
    If,
    FunctionIdentifier,
    Function,
    NestedIdentifier,
    NestedFunction,
    InvokeNested,
};

enum class Rotation {
    Default = 0,
    V       = 1 << 0, // XFLIP
    H       = 1 << 1, // YFLIP
    R       = 1 << 2, // ROTATE
    N       = 1 << 3, // NONE

    VH  = V | H,
    VR  = V | R,
    HR  = H | R,
    VHR = V | H | R,

    X = 1 << 4, // XFLIP
    Y = 1 << 5, // YFLIP

    XY  = X | Y,
    XR  = X | R,
    YR  = Y | R,
    XYR = X | Y | R,
};

inline Rotation operator|(Rotation lhs, Rotation rhs) noexcept {
    return util::i32_enum<Rotation>(util::enum_i32(lhs) | util::enum_i32(rhs));
}

inline Rotation& operator|=(Rotation& lhs, Rotation rhs) noexcept {
    return lhs = lhs | rhs;
}

inline Rotation operator&(Rotation lhs, Rotation rhs) noexcept {
    return util::i32_enum<Rotation>(util::enum_i32(lhs) & util::enum_i32(rhs));
}

inline Rotation operator^(Rotation lhs, Rotation rhs) noexcept {
    return util::i32_enum<Rotation>(util::enum_i32(lhs) ^ util::enum_i32(rhs));
}

inline Rotation& operator^=(Rotation& lhs, Rotation rhs) noexcept {
    return lhs = lhs ^ rhs;
}

enum class InsertC {
    Default    = 0,
    Insert     = 1 << 0,
    Automapper = 1 << 1,
    Newrun     = 1 << 2,
    Newrule    = 1 << 3,
    Nocopy     = 1 << 4,
    Rule       = 1 << 5,
    Nodefault  = 1 << 6,
    Random     = 1 << 7,
    Pos        = 1 << 8,
    Index      = 1 << 9,
    Type       = 1 << 10,
    Operator   = 1 << 11,
    Group      = 1 << 12,

    InsertAutomapper      = Insert | Automapper,
    InsertNewrun          = Insert | Newrun,
    InsertNewrule         = Insert | Newrule,
    InsertNocopy          = Insert | Nocopy,
    InsertRuleNodefault   = Insert | Rule | Nodefault,
    InsertRuleRandom      = Insert | Rule | Random,
    InsertRulePos         = Insert | Rule | Pos,
    InsertRulePosType     = Insert | Rule | Pos | Type,
    InsertRulePosIndex    = Insert | Rule | Pos | Index,
    InsertRulePosOperator = Insert | Rule | Pos | Operator,
    InsertRulePosGroup    = Insert | Rule | Pos | Group,
    InsertRuleIndex       = Insert | Rule | Index,
};

inline InsertC operator|(InsertC lhs, InsertC rhs) noexcept {
    return util::i32_enum<InsertC>(util::enum_i32(lhs) | util::enum_i32(rhs));
}

inline InsertC& operator|=(InsertC& lhs, InsertC rhs) noexcept {
    return lhs = lhs | rhs;
}

inline InsertC operator&(InsertC lhs, InsertC rhs) noexcept {
    return util::i32_enum<InsertC>(util::enum_i32(lhs) & util::enum_i32(rhs));
}

inline InsertC operator^(InsertC lhs, InsertC rhs) noexcept {
    return util::i32_enum<InsertC>(util::enum_i32(lhs) ^ util::enum_i32(rhs));
}

inline InsertC& operator^=(InsertC& lhs, InsertC rhs) noexcept {
    return lhs = lhs ^ rhs;
}

#endif // RPP_ENUMS_HPP
