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
#include <parsetree.hpp>

#include <tokenstream.hpp>
#include <tokenh.hpp>
#include <token.hpp>

/*
    ParseTree
*/
void ParseTree::create(TokenStream& tokenStream)
{
    while (!tokenStream.eof()) {
        add(getStatementNode(tokenStream, getNodeID(tokenStream)));
    }
}

StatementID ParseTree::getNodeID(const TokenStream& tokenStream) const noexcept
{
    if (tokenStream.current().cat == TKeyword && tokenStream.current().value == KW::For)
        return StatementID::For;
    else if (tokenStream.current().cat == TKeyword && tokenStream.current().value == KW::If)
        return StatementID::If;
    else if (tokenStream.current().cat == TKeyword && Token::isType(tokenStream.current().value))
        return StatementID::Decl;
    else if (tokenStream.current().cat == TKeyword && tokenStream.current().value == KW::Function)
        return StatementID::FunctionDef;
    else if (tokenStream.current().cat == TKeyword && tokenStream.current().value == KW::Nested)
        return StatementID::NestedFunctionDef;
    else if (tokenStream.current().cat == TKeyword && tokenStream.current().value == KW::Preset && tokenStream.current(1).value != PU::MemberAccess)
        return StatementID::PresetDef;
    else if (tokenStream.current().cat == TKeyword && tokenStream.current().value == KW::Return)
        return StatementID::Return;
    else if (tokenStream.current().cat == TKeyword && tokenStream.current().value == KW::Break)
        return StatementID::Break;
    else if (tokenStream.current().cat == TKeyword && tokenStream.current().value == KW::Continue)
        return StatementID::Continue;
    else
        return StatementID::Expr;
}

ParseTree::ptr_stat ParseTree::getStatementNode(TokenStream& tokenStream, StatementID nodeID) const
{
    switch (nodeID) {
        case StatementID::Expr:
            return getExprStatementNode(tokenStream);
        case StatementID::For:
            return getForStatementNode(tokenStream);
        case StatementID::If:
            return getIfStatementNode(tokenStream);
        case StatementID::Decl:
            return getDeclStatementNode(tokenStream);
        case StatementID::FunctionDef:
            return getFunctionDefStatementNode(tokenStream);
        case StatementID::NestedFunctionDef:
            return getNestedFunctionDefStatementNode(tokenStream);
        case StatementID::PresetDef:
            return getPresetDefStatementNode(tokenStream);
        case StatementID::Return:
            return getReturnStatementNode(tokenStream);
        case StatementID::Break:
            return getBreakStatementNode(tokenStream);
        default: // StatementID::Continue
            return getContinueStatementNode(tokenStream);
    }
}

ParseTree::ptr_stat ParseTree::getExprStatementNode(TokenStream& tokenStream) const
{
    uint32_t end = findEnd(tokenStream, tokenStream.currentIndex(), TH::StatementEnd);
    uint32_t scope_end = findEnd(tokenStream, tokenStream.currentIndex(), TH::End);
    uint32_t offset = end - tokenStream.currentIndex();

    PTExprStatement stat;
    stat.set<1>(getExpressionNode(tokenStream, 0, offset));

    if (tokenStream.current(offset) != TH::InvalidNull && scope_end > end)
        stat.set<2>(&tokenStream.current(offset));

    tokenStream.skip(offset + 1);
    return std::make_unique<PTExprStatement>(std::move(stat));
}

ParseTree::ptr_stat ParseTree::getForStatementNode(TokenStream& tokenStream) const
{
    uint32_t end = findEnd(tokenStream, tokenStream.currentIndex() + 1, TH::End);
    uint32_t offset = end - tokenStream.currentIndex();
    uint32_t curr = 0;

    PTForStatement stat;
    stat.set<1>(&tokenStream.current(curr++));
    if (tokenStream.current(offset) != TH::InvalidNull)
        stat.set<6>(&tokenStream.current(offset));

    if (tokenStream.current(1) == TH::FunctionCallOpen ||
        tokenStream.current(1).cat == TPunctuator ||
        tokenStream.current(1).cat == TOperator ||
        tokenStream.current(1).cat == TInvalid
        ) stat.set<2>(&tokenStream.current(curr++));

    uint32_t found = findRange(tokenStream, curr, offset, { TH::FunctionCallClose });
    if (found != offset)
        stat.set<4>(&tokenStream.current(found));

    stat.set<3>(getExpressionNode(tokenStream, curr, found));

    tokenStream.skip(found + 1);
    while (tokenStream.currentIndex() < end)
        stat.get<5>().push_back(getStatementNode(tokenStream, getNodeID(tokenStream)));

    tokenStream.skip();
    return std::make_unique<PTForStatement>(std::move(stat));
}

ParseTree::ptr_stat ParseTree::getIfStatementNode(TokenStream& tokenStream) const
{
    uint32_t end = findEnd(tokenStream, tokenStream.currentIndex() + 1, TH::End);
    uint32_t offset = end - tokenStream.currentIndex();
    uint32_t curr = 0;

    PTIfStatement stat;
    stat.set<1>(&tokenStream.current(curr++));
    if (tokenStream.current(offset) != TH::InvalidNull)
        stat.set<6>(&tokenStream.current(offset));

    if (tokenStream.current(1) == TH::FunctionCallOpen ||
        tokenStream.current(1).cat == TPunctuator ||
        tokenStream.current(1).cat == TOperator ||
        tokenStream.current(1).cat == TInvalid
        ) stat.set<2>(&tokenStream.current(curr++));

    uint32_t found = findRange(tokenStream, curr, offset, { TH::FunctionCallClose });
    if (found != offset)
        stat.set<4>(&tokenStream.current(found));

    stat.set<3>(getExpressionNode(tokenStream, curr, found));

    tokenStream.skip(found + 1);
    while (tokenStream.currentIndex() < end)
        stat.get<5>().push_back(getStatementNode(tokenStream, getNodeID(tokenStream)));

    tokenStream.skip();
    return std::make_unique<PTIfStatement>(std::move(stat));
}

ParseTree::ptr_stat ParseTree::getDeclStatementNode(TokenStream& tokenStream) const
{
    uint32_t end = findEnd(tokenStream, tokenStream.currentIndex() + 1, TH::StatementEnd);
    uint32_t scope_end = findEnd(tokenStream, tokenStream.currentIndex(), TH::End);
    uint32_t offset = end - tokenStream.currentIndex();

    PTDeclStatement stat;
    stat.set<1>(getExpressionNode(tokenStream, 0, offset));
    if (tokenStream.current(offset) != TH::InvalidNull && scope_end > end)
        stat.set<2>(&tokenStream.current(offset));

    tokenStream.skip(offset + 1);
    return std::make_unique<PTDeclStatement>(std::move(stat));
}

ParseTree::ptr_stat ParseTree::getFunctionDefStatementNode(TokenStream& tokenStream) const
{
    uint32_t end = findEnd(tokenStream, tokenStream.currentIndex() + 1, TH::End);
    uint32_t offset = end - tokenStream.currentIndex();

    PTFunctionDefStatement stat;
    if (tokenStream.current(offset) != TH::InvalidNull)
        stat.set<5>(&tokenStream.current(offset));
    
    uint32_t found = findRange(tokenStream, 0, offset, TIdentifier);
    stat.set<1>(getExpressionNode(tokenStream, 0, found));

    tokenStream.skip(found);
    if (found != offset)
        stat.set<2>(getFunctionDeclStatementNode(tokenStream));
    else
        stat.set<2>(std::make_unique<PTEmptyStatement>());

    if (tokenStream.current().value == KW::Nested && tokenStream.current(1).value == PU::FunctionCallOpen)
        stat.set<3>(getNestedDeclStatementNode(tokenStream));
    else
        stat.set<3>(std::make_unique<PTEmptyStatement>());

    while (tokenStream.currentIndex() < end)
        stat.get<4>().push_back(getStatementNode(tokenStream, getNodeID(tokenStream)));

    tokenStream.skip();
    return std::make_unique<PTFunctionDefStatement>(std::move(stat));
}

ParseTree::ptr_stat ParseTree::getFunctionDeclStatementNode(TokenStream& tokenStream) const
{
    uint32_t end = findEnd(tokenStream, tokenStream.currentIndex() + 1, TH::FunctionCallClose);
    uint32_t offset = end - tokenStream.currentIndex();

    PTFunctionDeclStatement stat;
    if (tokenStream.current(offset) != TH::InvalidNull)
        stat.set<4>(&tokenStream.current(offset));

    stat.set<1>(&tokenStream.current());
    if (tokenStream.current(1) == TH::FunctionCallOpen ||
        tokenStream.current(1).cat == TPunctuator ||
        tokenStream.current(1).cat == TOperator ||
        tokenStream.current(1).cat == TInvalid
        ) {
        stat.set<2>(&tokenStream.current(1));
        stat.set<3>(getExpressionNode(tokenStream, 2, offset));
    }

    tokenStream.skip(offset + 1);
    return std::make_unique<PTFunctionDeclStatement>(std::move(stat));
}

ParseTree::ptr_stat ParseTree::getNestedFunctionDefStatementNode(TokenStream& tokenStream) const
{
    uint32_t end = findEnd(tokenStream, tokenStream.currentIndex() + 1, TH::End);
    uint32_t offset = end - tokenStream.currentIndex();

    PTNestedFunctionDefStatement stat;
    stat.set<1>(&tokenStream.current());
    if (tokenStream.current(offset) != TH::InvalidNull)
        stat.set<5>(&tokenStream.current(offset));

    uint32_t found = findRange(tokenStream, 1, offset, TIdentifier);
    stat.set<2>(getExpressionNode(tokenStream, 1, found));

    tokenStream.skip(found);
    if (found != offset)
        stat.set<3>(getNestedFunctionDeclStatementNode(tokenStream));
    else
        stat.set<3>(std::make_unique<PTEmptyStatement>());

    while (tokenStream.currentIndex() < end)
        stat.get<4>().push_back(getStatementNode(tokenStream, getNodeID(tokenStream)));

    tokenStream.skip();
    return std::make_unique<PTNestedFunctionDefStatement>(std::move(stat));
}

ParseTree::ptr_stat ParseTree::getNestedFunctionDeclStatementNode(TokenStream& tokenStream) const
{
    uint32_t end = findEnd(tokenStream, tokenStream.currentIndex() + 1, TH::FunctionCallClose);
    uint32_t offset = end - tokenStream.currentIndex();

    PTNestedFunctionDeclStatement stat;
    if (tokenStream.current(offset) != TH::InvalidNull)
        stat.set<4>(&tokenStream.current(offset));

    uint32_t found = findRange(tokenStream, 0, offset, { TH::FunctionCallOpen });
    stat.set<1>(getExpressionNode(tokenStream, 0, found));

    tokenStream.skip(found);
    if (found != offset)
        stat.set<2>(&tokenStream.current());

    offset -= found;
    stat.set<3>(getExpressionNode(tokenStream, 1, std::max(1u, offset)));

    tokenStream.skip(offset + 1);
    return std::make_unique<PTNestedFunctionDeclStatement>(std::move(stat));
}

ParseTree::ptr_stat ParseTree::getNestedDeclStatementNode(TokenStream& tokenStream) const
{
    uint32_t end = findEnd(tokenStream, tokenStream.currentIndex() + 1, TH::FunctionCallClose);
    uint32_t offset = end - tokenStream.currentIndex();

    PTNestedDeclStatement stat;
    if (tokenStream.current(offset) != TH::InvalidNull)
        stat.set<4>(&tokenStream.current(offset));

    stat.set<1>(&tokenStream.current());
    if (tokenStream.current(1) == TH::FunctionCallOpen ||
        tokenStream.current(1).cat == TPunctuator ||
        tokenStream.current(1).cat == TOperator ||
        tokenStream.current(1).cat == TInvalid
        ) {
        stat.set<2>(&tokenStream.current(1));
        stat.set<3>(getExpressionNode(tokenStream, 2, offset));
    }

    tokenStream.skip(offset + 1);
    return std::make_unique<PTNestedDeclStatement>(std::move(stat));
}

ParseTree::ptr_stat ParseTree::getPresetDefStatementNode(TokenStream& tokenStream) const
{
    uint32_t end = findEnd(tokenStream, tokenStream.currentIndex() + 1, TH::End);
    uint32_t offset = end - tokenStream.currentIndex();

    PTPresetDefStatement stat;
    stat.set<1>(&tokenStream.current());
    if (tokenStream.current(offset) != TH::InvalidNull)
        stat.set<4>(&tokenStream.current(offset));

    tokenStream.skip();
    if (tokenStream.current().cat == TIdentifier)
        stat.set<2>(getFunctionDeclStatementNode(tokenStream));
    else
        stat.set<2>(std::make_unique<PTEmptyStatement>());

    while (tokenStream.currentIndex() < end)
        stat.get<3>().push_back(getStatementNode(tokenStream, getNodeID(tokenStream)));

    tokenStream.skip();
    return std::make_unique<PTPresetDefStatement>(std::move(stat));
}

ParseTree::ptr_stat ParseTree::getReturnStatementNode(TokenStream& tokenStream) const
{
    uint32_t end = findEnd(tokenStream, tokenStream.currentIndex() + 1, TH::StatementEnd);
    uint32_t scope_end = findEnd(tokenStream, tokenStream.currentIndex(), TH::End);
    uint32_t offset = end - tokenStream.currentIndex();

    PTReturnStatement stat;
    stat.set<1>(&tokenStream.current());
    stat.set<2>(getExpressionNode(tokenStream, 1, offset));
    if (tokenStream.current(offset) != TH::InvalidNull && scope_end > end)
        stat.set<3>(&tokenStream.current(offset));

    tokenStream.skip(offset + 1);
    return std::make_unique<PTReturnStatement>(std::move(stat));
}

ParseTree::ptr_stat ParseTree::getBreakStatementNode(TokenStream& tokenStream) const
{
    PTBreakStatement stat;
    stat.set<1>(&tokenStream.next());
    if (tokenStream.current() == TH::StatementEnd)
        stat.set<2>(&tokenStream.next());

    return std::make_unique<PTBreakStatement>(std::move(stat));
}

ParseTree::ptr_stat ParseTree::getContinueStatementNode(TokenStream& tokenStream) const
{
    PTContinueStatement stat;
    stat.set<1>(&tokenStream.next());
    if (tokenStream.current() == TH::StatementEnd)
        stat.set<2>(&tokenStream.next());

    return std::make_unique<PTContinueStatement>(std::move(stat));
}

ParseTree::ptr_expr ParseTree::getExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const
{
    if (beg == end)
        return std::make_unique<PTEmptyExpression>();

    if (end - beg == 1)
        switch (tokenStream.current(beg).cat) {
            case TIdentifier:
                return std::make_unique<PTIdentifierExpression>(&tokenStream.current(beg));

            case TKeyword:
                return std::make_unique<PTKeywordExpression>(&tokenStream.current(beg));

            case TLiteral:
                return std::make_unique<PTLiteralExpression>(&tokenStream.current(beg));

            default:
                return std::make_unique<PTInvalidExpression>(std::vector<Token*>{ &tokenStream.current(beg) });
        }

    ptr_expr expr;

    // ','
    expr = getBinaryExpressionNode<PTSeparatorExpression>(tokenStream, Order::RightToLeft, beg, end, { TH::Separator });
    if (expr != nullptr)
        return expr;

    // 'to'
    expr = getBinaryExpressionNode<PTForRangeExpression>(tokenStream, Order::RightToLeft, beg, end, { TH::To });
    if (expr != nullptr)
        return expr;

    // '='
    expr = getBinaryExpressionNode<PTAssignmentExpression>(tokenStream, Order::RightToLeft, beg, end, { TH::Assignment });
    if (expr != nullptr)
        return expr;

    // 'or'
    expr = getBinaryExpressionNode<PTLogicalExpression>(tokenStream, Order::RightToLeft, beg, end, { TH::Or });
    if (expr != nullptr)
        return expr;

    // 'and'
    expr = getBinaryExpressionNode<PTLogicalExpression>(tokenStream, Order::RightToLeft, beg, end, { TH::And });
    if (expr != nullptr)
        return expr;

    // not
    expr = getUnaryExpressionNode<PTUnaryLogicalExpression>(tokenStream, Order::RightToLeft, beg, end, { TH::Not });
    if (expr != nullptr)
        return expr;

    // '==' '!='
    expr = getBinaryExpressionNode<PTComparisonExpression>(tokenStream, Order::RightToLeft, beg, end, { TH::Equal, TH::NotEqual });
    if (expr != nullptr)
        return expr;

    // '>=' '>' '<=' '<'
    expr = getBinaryExpressionNode<PTComparisonExpression>(tokenStream, Order::RightToLeft, beg, end, { TH::GreaterThanOrEqual, TH::GreaterThan, TH::LessThanOrEqual, TH::LessThan });
    if (expr != nullptr)
        return expr;

    // '+' '-'
    expr = getBinaryExpressionNode<PTArithmeticExpression>(tokenStream, Order::LeftToRight, beg, end, { TH::Addition, TH::Subtraction });
    if (expr != nullptr)
        return expr;

    // '*' '/'
    expr = getBinaryExpressionNode<PTArithmeticExpression>(tokenStream, Order::LeftToRight, beg, end, { TH::Multiplication, TH::Division });
    if (expr != nullptr)
        return expr;

    // '.'
    expr = getBinaryExpressionNode<PTMemberAccessExpression>(tokenStream, Order::RightToLeft, beg, end, { TH::MemberAccess });
    if (expr != nullptr)
        return expr;

    // '_'
    expr = getBinaryExpressionNode<PTRangeLiteralExpression>(tokenStream, Order::RightToLeft, beg, end, { TH::Range });
    if (expr != nullptr)
        return expr;

    // array
    expr = getArrayExpressionNode(tokenStream, beg, end);
    if (expr != nullptr)
        return expr;

    // function call
    expr = getFunctionCallExpressionNode(tokenStream, beg, end);
    if (expr != nullptr)
        return expr;

    // percent
    expr = getPercentLiteralExpressionNode(tokenStream, beg, end);
    if (expr != nullptr)
        return expr;

    // coord
    expr = getCoordLiteralExpressionNode(tokenStream, beg, end);
    if (expr != nullptr)
        return expr;

    // string
    expr = getStringLiteralExpressionNode(tokenStream, beg, end);
    if (expr != nullptr)
        return expr;

    // return type
    expr = getReturnTypeExpressionNode(tokenStream, beg, end);
    if (expr != nullptr)
        return expr;

    // decl type
    expr = getDeclTypeExpressionNode(tokenStream, beg, end);
    if (expr != nullptr)
        return expr;

    // error
    expr = getErrorExpressionNode(tokenStream, beg, end);
    if (expr != nullptr)
        return expr;

    // warning
    expr = getWarningExpressionNode(tokenStream, beg, end);
    if (expr != nullptr)
        return expr;

    // assert
    expr = getAssertExpressionNode(tokenStream, beg, end);
    if (expr != nullptr)
        return expr;

    // invalid
    std::vector<Token*> tokens;
    tokens.reserve(end - beg);
    for (uint32_t i = beg; i < end; ++i)
        tokens.push_back(&tokenStream.current(i));

    return std::make_unique<PTInvalidExpression>(std::move(tokens));
}

ParseTree::ptr_expr ParseTree::getArrayExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const
{
    if (tokenStream.current(beg).cat != TIdentifier)
        return nullptr;

    uint32_t found = findLastRange(tokenStream, beg + 1, end, { TH::ArraySubscriptOpen });
    if (found == end)
        return nullptr;

    PTArraySubscriptExpression expr;
    expr.set<1>(getExpressionNode(tokenStream, beg, found));
    expr.set<2>(&tokenStream.current(found));

    beg = found + 1;
    found = findLastRange(tokenStream, beg, end, { TH::ArraySubscriptClose });
    expr.set<3>(getExpressionNode(tokenStream, beg, found));
    if (found != end)
        expr.set<4>(&tokenStream.current(found));

    return std::make_unique<PTArraySubscriptExpression>(std::move(expr));
}

ParseTree::ptr_expr ParseTree::getFunctionCallExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const
{
    bool hasIdentifier = tokenStream.current(beg).cat == TIdentifier || 
        (tokenStream.current(beg).value == KW::Invoke && tokenStream.current(beg).cat == TKeyword);

    if (!hasIdentifier && tokenStream.current(beg).value != PU::FunctionCallOpen)
        return nullptr;
    if (hasIdentifier && tokenStream.current(beg + 1).value != PU::FunctionCallOpen)
        return nullptr;

    uint32_t curr = beg;

    PTFunctionCallExpression expr;
    if (hasIdentifier)
        expr.set<1>(&tokenStream.current(curr++));

    expr.set<2>(&tokenStream.current(curr++));

    uint32_t found = findLastRange(tokenStream, curr, end, { TH::FunctionCallClose });
    expr.set<3>(getExpressionNode(tokenStream, curr, found));
    if (found != end)
        expr.set<4>(&tokenStream.current(found));

    return std::make_unique<PTFunctionCallExpression>(std::move(expr));
}

ParseTree::ptr_expr ParseTree::getPercentLiteralExpressionNode(TokenStream& tokenStream, uint32_t beg, [[maybe_unused]] uint32_t end) const
{
    if (tokenStream.current(beg).cat != TLiteral &&
        tokenStream.current(beg).type != ValueType::Int &&
        tokenStream.current(beg).type != ValueType::Float
        ) return nullptr;
    if (tokenStream.current(beg + 1).value != PU::Percent)
        return nullptr;

    PTPercentLiteralExpression expr;
    expr.set<1>(&tokenStream.current(beg));
    expr.set<2>(&tokenStream.current(beg + 1));

    return std::make_unique<PTPercentLiteralExpression>(std::move(expr));
}

ParseTree::ptr_expr ParseTree::getCoordLiteralExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const
{
    if (tokenStream.current(beg).value != PU::ArraySubscriptOpen)
        return nullptr;
    if (tokenStream.current(end - 1).value != PU::ArraySubscriptClose)
        return nullptr;

    PTCoordLiteralExpression expr;
    expr.set<1>(&tokenStream.current(beg));
    expr.set<2>(getExpressionNode(tokenStream, beg + 1, end - 1));
    expr.set<3>(&tokenStream.current(end - 1));

    return std::make_unique<PTCoordLiteralExpression>(std::move(expr));
}

ParseTree::ptr_expr ParseTree::getStringLiteralExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const
{
    if (tokenStream.current(beg) != TH::StringLiteral)
        return nullptr;

    PTStringLiteralExpression expr;
    expr.set<1>(&tokenStream.current(beg));
    if (tokenStream.current(beg + 1).type == ValueType::String)
        expr.set<2>(&tokenStream.current(beg + 1));
    if (tokenStream.current(end - 1) == TH::StringLiteral)
        expr.set<3>(&tokenStream.current(end - 1));

    return std::make_unique<PTStringLiteralExpression>(std::move(expr));
}

ParseTree::ptr_expr ParseTree::getReturnTypeExpressionNode(TokenStream& tokenStream, uint32_t beg, [[maybe_unused]] uint32_t end) const
{
    if (tokenStream.current(beg).value != KW::Function)
        return nullptr;

    PTReturnTypeExpression expr;
    expr.set<1>(&tokenStream.current(beg));

    if (tokenStream.current(beg + 1) == TH::ReturnType ||
        tokenStream.current(beg + 1).cat == TOperator ||
        tokenStream.current(beg + 1).cat == TPunctuator
        ) expr.set<2>(&tokenStream.current(beg + 1));

    if (tokenStream.current(beg + 2) != TH::InvalidNull)
        expr.set<3>(&tokenStream.current(beg + 2));

    if (tokenStream.current(beg + 3) != TH::InvalidNull &&
        tokenStream.current(beg + 3).cat != TIdentifier &&
        tokenStream.current(beg + 2) == TH::Array
        ) expr.set<4>(&tokenStream.current(beg + 3));

    return std::make_unique<PTReturnTypeExpression>(std::move(expr));
}

ParseTree::ptr_expr ParseTree::getErrorExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const
{
    if (tokenStream.current(beg).value != KW::Error)
        return nullptr;

    PTErrorExpression expr;
    expr.set<1>(&tokenStream.current(beg));

    if (tokenStream.current(beg + 1).value == PU::FunctionCallOpen)
        expr.set<2>(&tokenStream.current(beg + 1));

    if (tokenStream.current(end - 1).value == PU::FunctionCallClose)
        expr.set<4>(&tokenStream.current(end - 1));

    expr.set<3>(getExpressionNode(tokenStream, beg + 2, end - 1));

    return std::make_unique<PTErrorExpression>(std::move(expr));
}

ParseTree::ptr_expr ParseTree::getWarningExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const
{
    if (tokenStream.current(beg).value != KW::Warning)
        return nullptr;

    PTWarningExpression expr;
    expr.set<1>(&tokenStream.current(beg));

    if (tokenStream.current(beg + 1).value == PU::FunctionCallOpen)
        expr.set<2>(&tokenStream.current(beg + 1));

    if (tokenStream.current(end - 1).value == PU::FunctionCallClose)
        expr.set<4>(&tokenStream.current(end - 1));

    expr.set<3>(getExpressionNode(tokenStream, beg + 2, end - 1));

    return std::make_unique<PTWarningExpression>(std::move(expr));
}

ParseTree::ptr_expr ParseTree::getAssertExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const
{
    if (tokenStream.current(beg).value != KW::Assert)
        return nullptr;

    PTAssertExpression expr;
    expr.set<1>(&tokenStream.current(beg));

    if (tokenStream.current(beg + 1).value == PU::FunctionCallOpen)
        expr.set<2>(&tokenStream.current(beg + 1));

    if (tokenStream.current(end - 1).value == PU::FunctionCallClose)
        expr.set<4>(&tokenStream.current(end - 1));

    expr.set<3>(getExpressionNode(tokenStream, beg + 2, end - 1));

    return std::make_unique<PTAssertExpression>(std::move(expr));
}

ParseTree::ptr_expr ParseTree::getDeclTypeExpressionNode(TokenStream& tokenStream, uint32_t beg, [[maybe_unused]] uint32_t end) const
{
    if (!Token::isType(tokenStream.current(beg).value))
        return nullptr;

    PTDeclTypeExpression expr;
    expr.set<1>(&tokenStream.current(beg));

    if (tokenStream.current(beg) == TH::Array &&
        tokenStream.current(beg + 1).cat != TOperator &&
        tokenStream.current(beg + 1).cat != TPunctuator
        ) {
        expr.set<2>(&tokenStream.current(beg + 1));

        if (tokenStream.current(beg + 2).cat != TOperator &&
            tokenStream.current(beg + 2).cat != TPunctuator
            ) expr.set<3>(&tokenStream.current(beg + 2));
    }
    else if (
        tokenStream.current(beg + 1).cat != TOperator &&
        tokenStream.current(beg + 1).cat != TPunctuator
        ) expr.set<3>(&tokenStream.current(beg + 1));

    return std::make_unique<PTDeclTypeExpression>(std::move(expr));
}

uint32_t ParseTree::findEnd(const TokenStream& tokenStream, uint32_t beg, const TokenH& t) const
{
    int32_t scope = 0;
    for (uint32_t i = beg; i < tokenStream.data().size(); ++i) {
        const Token* curr = &tokenStream.data()[i];
        if (*curr == t && scope <= 0)
            return i;
        else if (*curr == TH::If || *curr == TH::For)
            ++scope;
        else if (*curr == TH::End)
            --scope;
    }
    return static_cast<uint32_t>(tokenStream.data().size());
}

uint32_t ParseTree::findRange(const TokenStream& tokenStream, uint32_t beg, uint32_t end, const std::vector<TokenH>& tokens) const
{
    bool has_funcCall = false;
    bool has_arraySub = false;
    for (const auto& t : tokens) {
        if (t == TH::FunctionCallClose)
            has_funcCall = true;
        if (t == TH::ArraySubscriptClose)
            has_arraySub = true;
    }

    int32_t funcCall = 1;
    int32_t arraySub = 1;
    for (uint32_t i = beg; i < end; ++i) {
        const Token* curr = &tokenStream.current(i);
        for (const auto& t : tokens) {
            if (*curr == TH::FunctionCallOpen && t != TH::FunctionCallOpen)
                ++funcCall;
            else if (*curr == TH::FunctionCallClose)
                --funcCall;
            else if (*curr == TH::ArraySubscriptOpen && t != TH::ArraySubscriptOpen)
                ++arraySub;
            else if (*curr == TH::ArraySubscriptClose)
                --arraySub;

            if (*curr == t) {
                if (!has_funcCall && !has_arraySub) {
                    if (funcCall <= 1 && arraySub <= 1)
                        return i;
                }
                else {
                    if (t == TH::FunctionCallClose && funcCall <= 0 && arraySub <= 1)
                        return i;
                    if (t == TH::ArraySubscriptClose && arraySub <= 0 && funcCall <= 1)
                        return i;
                }
            }
        }
    }
    return end;
}

uint32_t ParseTree::findRange(const TokenStream& tokenStream, uint32_t beg, uint32_t end, int32_t cat) const
{
    for (uint32_t i = beg; i < end; ++i)
        if (tokenStream.current(i).cat == cat)
            return i;
    return end;
}

uint32_t ParseTree::findLastRange(const TokenStream& tokenStream, int32_t beg, int32_t end, const std::vector<TokenH>& tokens) const
{
    int32_t funcCall = 0;
    int32_t arraySub = 0;
    for (int32_t i = end - 1; i >= beg; --i) {
        const Token* curr = &tokenStream.current(i);
        for (const auto& t : tokens) {
            if (*curr == TH::FunctionCallClose && t != TH::FunctionCallClose)
                ++funcCall;
            else if (*curr == TH::FunctionCallOpen)
                --funcCall;
            else if (*curr == TH::ArraySubscriptClose && t != TH::ArraySubscriptClose)
                ++arraySub;
            else if (*curr == TH::ArraySubscriptOpen)
                --arraySub;

            if (*curr == t && funcCall <= 0 && arraySub <= 0)
                return i;
        }
    }
    return end;
}
