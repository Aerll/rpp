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
#ifndef RPP_PARSETREE_HPP
#define RPP_PARSETREE_HPP

#include <parsetreevisitor.hpp>
#include <tokenstream.hpp>

class TokenH;

class ParseTree final {
    using ptr_stat_v = std::vector<std::unique_ptr<IPTStatementNode>>;
    using ptr_stat   = std::unique_ptr<IPTStatementNode>;
    using ptr_expr_v = std::vector<std::unique_ptr<IPTExpressionNode>>;
    using ptr_expr   = std::unique_ptr<IPTExpressionNode>;

public:
    ParseTree() = default;

    void create(TokenStream& tokenStream);

    ptr_stat_v& getStatements() {
        return m_statements;
    }

    void destroy() {
        ptr_stat_v{}.swap(getStatements());
    }

private:
    StatementID getNodeID(const TokenStream& tokenStream) const noexcept;

    void add(ptr_stat&& statement) {
        m_statements.push_back(std::move(statement));
    }

    ptr_stat getStatementNode(TokenStream& tokenStream, StatementID nodeID) const;
    ptr_stat getExprStatementNode(TokenStream& tokenStream) const;
    ptr_stat getForStatementNode(TokenStream& tokenStream) const;
    ptr_stat getIfStatementNode(TokenStream& tokenStream) const;
    ptr_stat getDeclStatementNode(TokenStream& tokenStream) const;
    ptr_stat getFunctionDefStatementNode(TokenStream& tokenStream) const;
    ptr_stat getFunctionDeclStatementNode(TokenStream& tokenStream) const;
    ptr_stat getNestedFunctionDefStatementNode(TokenStream& tokenStream) const;
    ptr_stat getNestedFunctionDeclStatementNode(TokenStream& tokenStream) const;
    ptr_stat getNestedDeclStatementNode(TokenStream& tokenStream) const;
    ptr_stat getReturnStatementNode(TokenStream& tokenStream) const;
    ptr_stat getBreakStatementNode(TokenStream& tokenStream) const;
    ptr_stat getContinueStatementNode(TokenStream& tokenStream) const;

    ptr_expr getExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const;
    ptr_expr getArrayExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const;
    ptr_expr getFunctionCallExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const;
    ptr_expr getPercentLiteralExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const;
    ptr_expr getCoordLiteralExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const;
    ptr_expr getStringLiteralExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const;
    ptr_expr getReturnTypeExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const;
    ptr_expr getErrorExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const;
    ptr_expr getWarningExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const;
    ptr_expr getAssertExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const;
    ptr_expr getDeclTypeExpressionNode(TokenStream& tokenStream, uint32_t beg, uint32_t end) const;

    template <typename NodeType>
    ptr_expr getUnaryExpressionNode(TokenStream& tokenStream, Order order, uint32_t beg, uint32_t end, const std::vector<TokenH>& tokens) const;
    template <typename NodeType>
    ptr_expr getBinaryExpressionNode(TokenStream& tokenStream, Order order, uint32_t beg, uint32_t end, const std::vector<TokenH>& tokens) const;

    uint32_t findEnd(const TokenStream& tokenStream, uint32_t beg, const TokenH& t) const;
    uint32_t findRange(const TokenStream& tokenStream, uint32_t beg, uint32_t end, const std::vector<TokenH>& tokens) const;
    uint32_t findRange(const TokenStream& tokenStream, uint32_t beg, uint32_t end, int32_t cat) const;
    uint32_t findLastRange(const TokenStream& tokenStream, int32_t beg, int32_t end, const std::vector<TokenH>& tokens) const;

private:
    ptr_stat_v m_statements;
};

template <typename NodeType>
ParseTree::ptr_expr ParseTree::getUnaryExpressionNode(TokenStream& tokenStream, Order order, uint32_t beg, uint32_t end, const std::vector<TokenH>& tokens) const {
    uint32_t found;
    if (order == Order::RightToLeft)
        found = findRange(tokenStream, beg, end, tokens);
    else
        found = findLastRange(tokenStream, beg, end, tokens);

    if (found == end)
        return nullptr;

    NodeType expr;
    expr.template set<1>(&tokenStream.current(found));
    expr.template set<2>(getExpressionNode(tokenStream, found + 1, end));
    return std::make_unique<NodeType>(std::move(expr));
}

template <typename NodeType>
ParseTree::ptr_expr ParseTree::getBinaryExpressionNode(TokenStream& tokenStream, Order order, uint32_t beg, uint32_t end, const std::vector<TokenH>& tokens) const {
    uint32_t found;
    if (order == Order::RightToLeft)
        found = findRange(tokenStream, beg, end, tokens);
    else
        found = findLastRange(tokenStream, beg, end, tokens);

    if (found == end)
        return nullptr;

    NodeType expr;
    expr.template set<1>(getExpressionNode(tokenStream, beg, found));
    expr.template set<2>(&tokenStream.current(found));
    expr.template set<3>(getExpressionNode(tokenStream, found + 1, end));
    return std::make_unique<NodeType>(std::move(expr));
}

#endif // RPP_PARSETREE_HPP
