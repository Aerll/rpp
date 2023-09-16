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
#ifndef RPP_TOKENLITERALS_HPP
#define RPP_TOKENLITERALS_HPP

#include <string_view>

/*
    Invalid
*/
namespace IN {

constexpr std::string_view Null = "";

}

/* 
    Keywords
*/
namespace KW {

constexpr std::string_view Anchor     = "anchor";
constexpr std::string_view And        = "and";
constexpr std::string_view Array      = "array";
constexpr std::string_view Assert     = "assert";
constexpr std::string_view Automapper = "automapper";
constexpr std::string_view Bool       = "bool";
constexpr std::string_view Break      = "break";
constexpr std::string_view Continue   = "continue";
constexpr std::string_view Coord      = "coord";
constexpr std::string_view Count      = "count";
constexpr std::string_view Empty      = "empty";
constexpr std::string_view End        = "end";
constexpr std::string_view Error      = "error";
constexpr std::string_view False      = "false";
constexpr std::string_view Float      = "float";
constexpr std::string_view For        = "for";
constexpr std::string_view Full       = "full";
constexpr std::string_view Function   = "function";
constexpr std::string_view Group      = "group";
constexpr std::string_view If         = "if";
constexpr std::string_view Index      = "index";
constexpr std::string_view Insert     = "insert";
constexpr std::string_view Int        = "int";
constexpr std::string_view Invoke     = "invoke";
constexpr std::string_view Last       = "last";
constexpr std::string_view Nested     = "nested";
constexpr std::string_view Newrule    = "newrule";
constexpr std::string_view Newrun     = "newrun";
constexpr std::string_view Nocopy     = "nocopy";
constexpr std::string_view Nodefault  = "nodefault";
constexpr std::string_view Not        = "not";
constexpr std::string_view Notindex   = "notindex";
constexpr std::string_view Null       = "null";
constexpr std::string_view Object     = "object";
constexpr std::string_view Operator   = "operator";
constexpr std::string_view Or         = "or";
constexpr std::string_view Pos        = "pos";
constexpr std::string_view Preset     = "preset";
constexpr std::string_view Random     = "random";
constexpr std::string_view Range      = "range";
constexpr std::string_view Return     = "return";
constexpr std::string_view Rotate     = "rotate";
constexpr std::string_view Rule       = "rule";
constexpr std::string_view String     = "string";
constexpr std::string_view To         = "to";
constexpr std::string_view True       = "true";
constexpr std::string_view Type       = "type";
constexpr std::string_view Warning    = "warning";

}
         
/* 
    Identifiers
*/
namespace ID {

constexpr std::string_view Include = "include";
constexpr std::string_view Path    = "path";
constexpr std::string_view Tileset = "tileset";
constexpr std::string_view Memory  = "memory";

}

/*
    Punctuators
*/
namespace PU {

constexpr std::string_view ArraySubscriptClose = "]";
constexpr std::string_view ArraySubscriptOpen  = "[";
constexpr std::string_view DecimalPoint        = ".";
constexpr std::string_view FunctionCallClose   = ")";
constexpr std::string_view FunctionCallOpen    = "(";
constexpr std::string_view MemberAccess        = ".";
constexpr std::string_view Percent             = "%";
constexpr std::string_view Preproc             = "#";
constexpr std::string_view Separator           = ",";
constexpr std::string_view StatementEnd        = ";";
constexpr std::string_view StringLiteral       = "\"";

constexpr char CharArraySubscriptClose = ']';
constexpr char CharArraySubscriptOpen  = '[';
constexpr char CharDecimalPoint        = '.';
constexpr char CharFunctionCallClose   = ')';
constexpr char CharFunctionCallOpen    = '(';
constexpr char CharMemberAccess        = '.';
constexpr char CharPercent             = '%';
constexpr char CharPreproc             = '#';
constexpr char CharSeparator           = ',';
constexpr char CharStatementEnd        = ';';
constexpr char CharStringLiteral       = '\"';

}

/*
    Operators
*/
namespace OP {

constexpr std::string_view Equal              = "==";
constexpr std::string_view GreaterThanOrEqual = ">=";
constexpr std::string_view LessThanOrEqual    = "<=";
constexpr std::string_view NotEqual           = "!=";
constexpr std::string_view ReturnType         = "->";

constexpr std::string_view Addition           = "+";
constexpr std::string_view Assignment         = "=";
constexpr std::string_view Division           = "/";
constexpr std::string_view GreaterThan        = ">";
constexpr std::string_view LessThan           = "<";
constexpr std::string_view Multiplication     = "*";
constexpr std::string_view Range              = "_";
constexpr std::string_view Subtraction        = "-";
constexpr std::string_view UnaryNegation      = "-";

constexpr char CharAddition       = '+';
constexpr char CharAssignment     = '=';
constexpr char CharDivision       = '/';
constexpr char CharGreaterThan    = '>';
constexpr char CharLessThan       = '<';
constexpr char CharLogicalNot     = '!'; // required by tokenizer to read '!=' correctly
constexpr char CharMultiplication = '*';
constexpr char CharRange          = '_';
constexpr char CharSubtraction    = '-';
constexpr char CharUnaryNegation  = '-';

}

#endif // RPP_TOKENLITERALS_HPP
