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
#ifndef RPP_ABSTRACTSYNTAXTREE_HPP
#define RPP_ABSTRACTSYNTAXTREE_HPP

#include <abstractsyntaxtreevisitor.hpp>
#include <parsetree.hpp>

class AbstractSyntaxTree final {
    using ptr_node = std::unique_ptr<IASTNode>;
    using ptr_node_v = std::vector<ptr_node>;

public:
    AbstractSyntaxTree() = default;

    void create(ParseTree& parseTree);

    IASTNode* getMainNode() const noexcept
        { return m_tree.get(); }
    IASTNode* getCurrentNode() const
        { return m_currentNode[getScope()]; }

private:
    void enterScope()
        { m_currentNode.push_back(nullptr); ++m_scope; }
    void leaveScope()
        { m_currentNode.pop_back(); --m_scope; }
    int32_t getScope() const noexcept
        { return m_scope; }

    void setCurrentNode(IASTNode* node)
        { m_currentNode[getScope()] = node; }
        
    void addNextNode(ptr_node&& node);

    void convertStatements(std::vector<std::unique_ptr<IPTStatementNode>>&& statements);

    ptr_node convertStatement(IPTStatementNode& statement, NodeID id = NodeID::Null);
    ptr_node convertStatement(PTExprStatement& statement);
    ptr_node convertStatement(PTForStatement& statement);
    ptr_node convertStatement(PTIfStatement& statement);
    ptr_node convertStatement(PTDeclStatement& statement);
    ptr_node convertStatement(PTFunctionDefStatement& statement);
    ptr_node convertStatement(PTFunctionDeclStatement& statement, NodeID id = NodeID::Null);
    ptr_node convertStatement(PTNestedFunctionDefStatement& statement);
    ptr_node convertStatement(PTNestedFunctionDeclStatement& statement, NodeID id = NodeID::Null);
    ptr_node convertStatement(PTPresetDefStatement& statement);
    ptr_node convertStatement(PTReturnStatement& statement);
    ptr_node convertStatement(PTBreakStatement& statement);
    ptr_node convertStatement(PTContinueStatement& statement);

    ptr_node_v convertArguments(IPTStatementNode& statement);
    ptr_node_v convertArguments(PTFunctionDeclStatement& statement);
    ptr_node_v convertArguments(PTNestedFunctionDeclStatement& statement);
    ptr_node_v convertArguments(PTNestedDeclStatement& statement);

    ptr_node convertExpression(IPTExpressionNode& expression, NodeID id = NodeID::Null);
    ptr_node convertExpression(PTLiteralExpression& expression);
    ptr_node convertExpression(PTIdentifierExpression& expression, NodeID id = NodeID::Null);
    ptr_node convertExpression(PTKeywordExpression& expression);
    ptr_node convertExpression(PTAssignmentExpression& expression, NodeID id = NodeID::Null);
    ptr_node convertExpression(PTArithmeticExpression& expression);
    ptr_node convertExpression(PTComparisonExpression& expression);
    ptr_node convertExpression(PTLogicalExpression& expression);
    ptr_node convertExpression(PTUnaryLogicalExpression& expression);
    ptr_node convertExpression(PTFunctionCallExpression& expression, NodeID id);
    ptr_node convertExpression(PTForRangeExpression& expression);
    ptr_node convertExpression(PTMemberAccessExpression& expression, NodeID id = NodeID::Null);
    ptr_node_v convertExpressions(PTMemberAccessExpression& expression, NodeID id = NodeID::Null);
    ptr_node convertExpression(PTErrorExpression& expression);
    ptr_node convertExpression(PTWarningExpression& expression);
    ptr_node convertExpression(PTAssertExpression& expression);
    ptr_node convertExpression(PTArraySubscriptExpression& expression);
    ptr_node convertExpression(PTPercentLiteralExpression& expression);
    ptr_node convertExpression(PTStringLiteralExpression& expression);
    ptr_node convertExpression(PTRangeLiteralExpression& expression);
    ptr_node convertExpression(PTCoordLiteralExpression& expression);
    ptr_node convertExpression(PTDeclTypeExpression& expression, NodeID id = NodeID::Null);

    ptr_node_v convertArguments(IPTExpressionNode& expression);
    ptr_node_v convertArguments(PTFunctionCallExpression& expression);

    InsertC convertInsertControl(PTMemberAccessExpression& expression);
    ptr_node convertLeft(PTMemberAccessExpression& expression, NodeID id = NodeID::Null);
    ptr_node convertRight(PTMemberAccessExpression& expression, NodeID id = NodeID::Null);

    template <typename T>
    ptr_node convert(uint32_t line);

    template <typename T>
    ptr_node convertName(std::string_view name, uint32_t line);
    template <typename T, typename ValT>
    ptr_node convertValue(ValT value, uint32_t line);

    template <typename T>
    ptr_node convertUnaryExpression(ptr_node&& expr, uint32_t line);
    template <typename T>
    ptr_node convertBinaryExpression(ptr_node&& left, ptr_node&& right, uint32_t line);

private:
    ptr_node m_tree;

    std::vector<IASTNode*> m_currentNode;
    int32_t m_scope;
};

template <typename T>
inline AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convert(uint32_t line)
{
    auto node = std::make_unique<T>();
    node->setLine(line);
    return node;
}

template <typename T>
inline AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertName(std::string_view name, uint32_t line)
{
    auto node = std::make_unique<T>();
    if constexpr (
        std::is_same_v<T, ASTFunctionIdentifierNode> ||
        std::is_same_v<T, ASTNestedIdentifierNode> ||
        std::is_same_v<T, ASTPresetIdentifierNode> ||
        std::is_same_v<T, ASTVariableNode>
        ) node->setName(name);
    else if constexpr (
        std::is_same_v<T, ASTRotationNode>
        ) node->setRotation(Token::stringToRotation(name));
    node->setLine(line);
    return node;
}

template <typename T, typename ValT>
inline AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertValue(ValT value, uint32_t line)
{
    auto node = std::make_unique<T>();
    node->setValue(value);
    node->setLine(line);
    return node;
}

template <typename T>
inline AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertUnaryExpression(ptr_node&& expr, uint32_t line)
{
    auto node = std::make_unique<T>();
    node->setExpr(std::move(expr));
    node->setLine(line);
    return node;
}

template <typename T>
inline AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertBinaryExpression(ptr_node&& left, ptr_node&& right, uint32_t line)
{
    auto node = std::make_unique<T>();
    node->setLeft(std::move(left));
    node->setRight(std::move(right));
    node->setLine(line);
    return node;
}

#endif // RPP_ABSTRACTSYNTAXTREE_HPP