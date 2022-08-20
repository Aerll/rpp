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
#include <token.hpp>

#include <tokenh.hpp>

/*
    Token
*/
bool Token::operator==(const TokenH& rhs) const noexcept
{
    return cat == rhs.cat && value == rhs.value;
}

bool Token::operator!=(const TokenH& rhs) const noexcept
{
    return !(*this == rhs);
}

bool Token::isKeyword(const std::string& s) noexcept
{
    switch (s.size()) {
        case 2:
            if (s == KW::If ||
                s == KW::Or ||
                s == KW::To
                ) return true;

        case 3:
            if (s == KW::And ||
                s == KW::End ||
                s == KW::For ||
                s == KW::Int ||
                s == KW::Not ||
                s == KW::Pos
                ) return true;

        case 4:
            if (s == KW::Bool ||
                s == KW::Full ||
                s == KW::Last ||
                s == KW::Null ||
                s == KW::Rule ||
                s == KW::True ||
                s == KW::Type
                ) return true;

        case 5:
            if (s == KW::Array ||
                s == KW::Break ||
                s == KW::Coord ||
                s == KW::Count ||
                s == KW::Empty ||
                s == KW::Error ||
                s == KW::False ||
                s == KW::Float ||
                s == KW::Group ||
                s == KW::Index ||
                s == KW::Range
                ) return true;

        case 6:
            if (s == KW::Anchor ||
                s == KW::Insert ||
                s == KW::Invoke ||
                s == KW::Nested ||
                s == KW::Newrun ||
                s == KW::Nocopy ||
                s == KW::Object ||
                s == KW::Preset ||
                s == KW::Random ||
                s == KW::Return ||
                s == KW::Rotate ||
                s == KW::String
                ) return true;

        case 7:
            if (s == KW::Newrule ||
                s == KW::Warning
                ) return true;

        case 8:
            if (s == KW::Continue ||
                s == KW::Function ||
                s == KW::Notindex ||
                s == KW::Operator
                ) return true;

        case 9:
            if (s == KW::Nodefault)
                return true;

        case 10:
            if (s == KW::Automapper) 
                return true;
    }
    return false;
}

bool Token::isIdentifier(const std::string& s) noexcept
{
    if (s == ID::Include ||
        s == ID::Path ||
        s == ID::Tileset
        ) return true;

    return false;
}

bool Token::isPunctuator(const std::string& s) noexcept
{
    if (s == PU::ArraySubscriptClose ||
        s == PU::ArraySubscriptOpen ||
        //s == PU::DecimalPoint ||
        s == PU::FunctionCallClose ||
        s == PU::FunctionCallOpen ||
        s == PU::MemberAccess ||
        s == PU::Percent ||
        s == PU::Preproc ||
        s == PU::Separator ||
        s == PU::StatementEnd ||
        s == PU::StringLiteral
        ) return true;

    return false;
}

bool Token::isPunctuator(char c) noexcept
{
    if (c == PU::CharArraySubscriptClose ||
        c == PU::CharArraySubscriptOpen ||
        //c == PU::CharDecimalPoint ||
        c == PU::CharFunctionCallClose ||
        c == PU::CharFunctionCallOpen ||
        c == PU::CharMemberAccess ||
        c == PU::CharPercent ||
        c == PU::CharPreproc ||
        c == PU::CharSeparator ||
        c == PU::CharStatementEnd ||
        c == PU::CharStringLiteral
        ) return true;

    return false;
}

bool Token::isOperator(const std::string& s) noexcept
{
    if (s == OP::Addition ||
        s == OP::Assignment ||
        s == OP::Division ||
        s == OP::Equal ||
        s == OP::GreaterThan ||
        s == OP::GreaterThanOrEqual ||
        s == OP::LessThan ||
        s == OP::LessThanOrEqual ||
        s == OP::Multiplication ||
        s == OP::NotEqual ||
        s == OP::Range ||
        s == OP::ReturnType ||
        //s == OP::Subtraction ||
        s == OP::UnaryNegation
        ) return true;

    return false;
}

bool Token::isOperator(char c) noexcept
{
    if (c == OP::CharAddition ||
        c == OP::CharAssignment ||
        c == OP::CharDivision ||
        c == OP::CharGreaterThan ||
        c == OP::CharLessThan ||
        c == OP::CharLogicalNot ||
        c == OP::CharMultiplication ||
        c == OP::CharRange ||
        //c == OP::CharSubtraction ||
        c == OP::CharUnaryNegation
        ) return true;

    return false;
}

bool Token::isBlank(char c) noexcept
{
    return c == ' ' || (c >= '\t' && c <= '\r') || c == char{};
}

bool Token::isDigit(char c) noexcept
{
    return c >= '0' && c <= '9';
}

bool Token::isLetter(char c) noexcept
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ':';
}

bool Token::isNewLine(char c) noexcept
{
    return c == '\n' || c == '\r';
}

bool Token::isType(const std::string& s) noexcept
{
    if (s == KW::Array ||
        s == KW::Bool ||
        s == KW::Coord ||
        s == KW::Float ||
        s == KW::Int ||
        s == KW::Object ||
        s == KW::Range ||
        s == KW::String
        ) return true;

    return false;
}

bool Token::isSubtype(const std::string& s) noexcept
{
    if (s == KW::Bool ||
        s == KW::Coord ||
        s == KW::Float ||
        s == KW::Int ||
        s == KW::Object ||
        s == KW::Range ||
        s == KW::String
        ) return true;

    return false;
}

bool Token::isReturnType(const std::string& s) noexcept
{
    if (s == KW::Array ||
        s == KW::Bool ||
        s == KW::Coord ||
        s == KW::Float ||
        s == KW::Int ||
        s == KW::Null ||
        s == KW::Object ||
        s == KW::Range ||
        s == KW::String
        ) return true;

    return false;
}

bool Token::isAssignment(const std::string& s) noexcept
{
    return s == OP::Assignment;
}

bool Token::isArithmetic(const std::string& s) noexcept
{
    if (s == OP::Addition ||
        s == OP::Subtraction ||
        s == OP::Multiplication ||
        s == OP::Division
        ) return true;

    return false;
}

bool Token::isComparison(const std::string& s) noexcept
{
    if (s == OP::Equal ||
        s == OP::NotEqual ||
        s == OP::GreaterThanOrEqual ||
        s == OP::LessThanOrEqual ||
        s == OP::GreaterThan ||
        s == OP::LessThan
        ) return true;

    return false;
}

bool Token::isLogical(const std::string& s) noexcept
{
    if (s == KW::And ||
        s == KW::Not ||
        s == KW::Or
        ) return true;

    return false;
}

bool Token::isConvertible(ValueType from, ValueType to) noexcept
{
    switch (from) {
        case ValueType::Int:
            return to == ValueType::Coord || to == ValueType::Float;
        case ValueType::Range:
            return to == ValueType::Object;
        case ValueType::Coord:
            return to == ValueType::Int;
        case ValueType::Float:
            return to == ValueType::Int;
        case ValueType::Object:
            return to == ValueType::ArrayInt;
        case ValueType::ArrayInt:
            return to == ValueType::Object;
    }
    return false;
}

bool Token::isVariadic(ValueType type, ValueType variadic) noexcept
{
    switch (type) {
        case ValueType::Bool:
            return variadic == ValueType::ArrayBool;
        case ValueType::Int:
            return variadic == ValueType::ArrayInt || variadic == ValueType::ArrayCoord || variadic == ValueType::ArrayFloat;
        case ValueType::Range:
            return variadic == ValueType::ArrayRange || variadic == ValueType::ArrayInt || variadic == ValueType::ArrayObject;
        case ValueType::Coord:
            return variadic == ValueType::ArrayCoord || variadic == ValueType::ArrayInt;
        case ValueType::Float:
            return variadic == ValueType::ArrayFloat || variadic == ValueType::ArrayInt;
        case ValueType::String:
            return variadic == ValueType::ArrayString;
        case ValueType::Object:
            return variadic == ValueType::ArrayObject || variadic == ValueType::ArrayInt;
        case ValueType::ArrayInt:
            return variadic == ValueType::ArrayObject;
    }
    return false;
}

bool Token::isSingleRotation(std::string_view s) noexcept
{
    return s == "N" || s == "V" || s == "H" || s == "R";
}

bool Token::isSingleRotation(Rotation rotation) noexcept
{
    return rotation == Rotation::N || rotation == Rotation::V || rotation == Rotation::H || rotation == Rotation::R;
}

bool Token::isRotation(std::string_view s) noexcept
{
    return s == "N" || s == "V" || s == "H" || s == "R" || s == "VH" || s == "VR" || s == "HR" || s == "VHR";
}

bool Token::isPos(std::string_view s) noexcept
{
    return s == "x" || s == "y";
}

bool Token::isBuiltin(std::string_view s) noexcept
{
    return s == "has" || s == "push" || s == "unique" || s == "str";
}

bool Token::isArray(ValueType type) noexcept
{
    return (type & ValueType::Array) != ValueType::Null;
}

bool Token::isArrayOrObject(ValueType type) noexcept
{
    return isArray(type) || type == ValueType::Object;
}

bool Token::isArithmetic(ValueType type) noexcept
{
    return type == ValueType::Int || type == ValueType::Float;
}

ValueType Token::getArithmeticResult(ValueType left, ValueType right) noexcept
{
    switch (left) {
        case ValueType::Int:
            if (Token::isArithmetic(right))
                return right;
            break;

        case ValueType::Float:
            if (Token::isArithmetic(right))
                return left;
            break;
    }
    return ValueType::Null;
}

Rotation Token::stringToRotation(std::string_view s) noexcept
{
    if (s == "N")
        return Rotation::N;
    else if (s == "V")
        return Rotation::V;
    else if (s == "H")
        return Rotation::H;
    else if (s == "R")
        return Rotation::R;
    else if (s == "VH")
        return Rotation::VH;
    else if (s == "VR")
        return Rotation::VR;
    else if (s == "HR")
        return Rotation::HR;
    else if (s == "VHR")
        return Rotation::VHR;
    else
        return Rotation::Default;
}

std::string Token::rotationToString(Rotation rotation) noexcept
{
    switch (rotation) {
        case Rotation::N:
            return "N";
        case Rotation::V:
            return "V";
        case Rotation::H:
            return "H";
        case Rotation::R:
            return "R";
        case Rotation::VH:
            return "VH";
        case Rotation::VR:
            return "VR";
        case Rotation::HR:
            return "HR";
        case Rotation::VHR:
            return "VHR";
        default:
            return "";
    }
}

ValueType Token::stringToType(std::string_view type)
{
    if (type == KW::Bool)
        return ValueType::Bool;
    else if (type == KW::Int)
        return ValueType::Int;
    else if (type == KW::Range)
        return ValueType::Range;
    else if (type == KW::Coord)
        return ValueType::Coord;
    else if (type == KW::Float)
        return ValueType::Float;
    else if (type == KW::String)
        return ValueType::String;
    else if (type == KW::Object)
        return ValueType::Object;
    else if (type == KW::Array)
        return ValueType::Array;
    else
        return ValueType::Null;
}

std::string Token::typeToString(ValueType type, bool lowercase)
{
    switch (type) {
        case ValueType::Null:
            return lowercase ? "null" : "Null";

        case ValueType::Bool:
            return lowercase ? "bool" : "Bool";

        case ValueType::Int:
            return lowercase ? "int" : "Int";

        case ValueType::Range:
            return lowercase ? "range" : "Range";

        case ValueType::Coord:
            return lowercase ? "coord" : "Coord";

        case ValueType::Float:
            return lowercase ? "float" : "Float";

        case ValueType::String:
            return lowercase ? "string" : "String";

        case ValueType::Object:
            return lowercase ? "object" : "Object";

        case ValueType::ArrayBool:
            return lowercase ? "array bool" : "Array Bool";

        case ValueType::ArrayInt:
            return lowercase ? "array int" : "Array Int";

        case ValueType::ArrayRange:
            return lowercase ? "array range" : "Array Range";

        case ValueType::ArrayCoord:
            return lowercase ? "array coord" : "Array Coord";

        case ValueType::ArrayFloat:
            return lowercase ? "array float" : "Array Float";

        case ValueType::ArrayString:
            return lowercase ? "array string" : "Array String";

        case ValueType::ArrayObject:
            return lowercase ? "array object" : "Array Object";

        default:
            return {};
    }
}
