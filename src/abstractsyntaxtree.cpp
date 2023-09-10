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
#include <abstractsyntaxtree.hpp>

#include <tokenliterals.hpp>

/*
    AbstractSyntaxTree
*/
void AbstractSyntaxTree::create(ParseTree& parseTree)
{
    m_scope = -1;
    enterScope();

    m_tree = std::make_unique<ASTNullNode>();
    setCurrentNode(getMainNode());

    convertStatements(std::move(parseTree.getStatements()));
    leaveScope();

    parseTree.destroy();
}

void AbstractSyntaxTree::addNextNode(ptr_node&& node)
{
    IASTNode* previous = getCurrentNode();
    getCurrentNode()->setNextNode(std::move(node));
    setCurrentNode(getCurrentNode()->getNextNode());
    getCurrentNode()->setPreviousNode(previous);
}

void AbstractSyntaxTree::convertStatements(std::vector<std::unique_ptr<IPTStatementNode>>&& statements)
{
    for (auto&& stat : statements) {
        auto node = convertStatement(*stat.get());
        if (node == nullptr)
            continue;
        addNextNode(std::move(node));
    }
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertStatement(IPTStatementNode& statement, NodeID id)
{
    switch (statement.id()) {
        case StatementID::Expr:
            return convertStatement(static_cast<PTExprStatement&>(statement));
        case StatementID::For:
            return convertStatement(static_cast<PTForStatement&>(statement));
        case StatementID::If:
            return convertStatement(static_cast<PTIfStatement&>(statement));
        case StatementID::Decl:
            return convertStatement(static_cast<PTDeclStatement&>(statement));
        case StatementID::FunctionDef:
            return convertStatement(static_cast<PTFunctionDefStatement&>(statement));
        case StatementID::FunctionDecl:
            return convertStatement(static_cast<PTFunctionDeclStatement&>(statement), id);
        case StatementID::NestedFunctionDef:
            return convertStatement(static_cast<PTNestedFunctionDefStatement&>(statement));
        case StatementID::NestedFunctionDecl:
            return convertStatement(static_cast<PTNestedFunctionDeclStatement&>(statement), id);
        case StatementID::PresetDef:
            return convertStatement(static_cast<PTPresetDefStatement&>(statement));
        case StatementID::Return:
            return convertStatement(static_cast<PTReturnStatement&>(statement));
        case StatementID::Break:
            return convertStatement(static_cast<PTBreakStatement&>(statement));
        case StatementID::Continue:
            return convertStatement(static_cast<PTContinueStatement&>(statement));
        default:
            return nullptr;
    }
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertStatement(PTExprStatement& statement)
{
    return convertExpression(*statement.get<1>().get());
}


AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertStatement(PTForStatement& statement)
{
    enterScope();

    auto node = std::make_unique<ASTForNode>();
    node->setLine(statement.get<1>()->line);
    node->setRange(convertExpression(*statement.get<3>()));

    auto branch = std::make_unique<ASTNullNode>();
    branch->setPreviousNode(node.get());
    node->setBranch(std::move(branch));

    setCurrentNode(node->getBranch());
    convertStatements(statement.get<5>());

    leaveScope();
    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertStatement(PTIfStatement& statement)
{
    enterScope();

    auto node = std::make_unique<ASTIfNode>();
    node->setLine(statement.get<1>()->line);
    node->setCondition(convertExpression(*statement.get<3>()));

    auto branch = std::make_unique<ASTNullNode>();
    branch->setPreviousNode(node.get());
    node->setBranch(std::move(branch));

    setCurrentNode(node->getBranch());
    convertStatements(statement.get<5>());

    leaveScope();
    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertStatement(PTDeclStatement& statement)
{
    return convertExpression(*statement.get<1>().get());
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertStatement(PTFunctionDefStatement& statement)
{
    enterScope();

    auto node = std::make_unique<ASTFunctionNode>();
    node->setLine(statement.get<1>()->getLastToken()->line);
    node->setIdentifier(convertStatement(*statement.get<2>(), NodeID::FunctionIdentifier));
    node->setArguments(convertArguments(*statement.get<2>()));
    node->setNestedIdentifiers(convertArguments(*statement.get<3>()));

    auto branch = std::make_unique<ASTNullNode>();
    branch->setPreviousNode(node.get());
    node->setBranch(std::move(branch));

    static_cast<ASTFunctionIdentifierNode*>(node->getIdentifier())->setFunction(node.get());

    auto& returnType = static_cast<PTReturnTypeExpression&>(*statement.get<1>());
    node->setReturnType(Token::stringToType(returnType.get<3>()->value));
    if (returnType.get<4>() != nullptr)
        node->setReturnType(node->getReturnType() | Token::stringToType(returnType.get<4>()->value));

    setCurrentNode(node->getBranch());
    convertStatements(statement.get<4>());

    leaveScope();
    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertStatement(PTFunctionDeclStatement& statement, NodeID id)
{
    if (id == NodeID::FunctionIdentifier) {
        auto node = std::make_unique<ASTFunctionIdentifierNode>();
        node->setName(statement.get<1>()->value);
        node->setLine(statement.get<1>()->line);
        return node;
    }
    else if (id == NodeID::PresetIdentifier) {
        auto node = std::make_unique<ASTPresetIdentifierNode>();
        node->setName(statement.get<1>()->value);
        node->setLine(statement.get<1>()->line);
        return node;
    }
    else
        return nullptr;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertStatement(PTNestedFunctionDefStatement& statement)
{
    enterScope();

    auto node = std::make_unique<ASTNestedFunctionNode>();
    node->setFunctionIdentifier(convertStatement(*statement.get<3>(), NodeID::FunctionIdentifier));
    node->setIdentifier(convertStatement(*statement.get<3>(), NodeID::NestedIdentifier));
    node->setArguments(convertArguments(*statement.get<3>()));

    auto branch = std::make_unique<ASTNullNode>();
    branch->setPreviousNode(node.get());
    node->setBranch(std::move(branch));

    static_cast<ASTNestedIdentifierNode*>(node->getIdentifier())->setNestedFunction(node.get());

    auto& returnType = static_cast<PTReturnTypeExpression&>(*statement.get<2>());
    node->setReturnType(Token::stringToType(returnType.get<3>()->value));
    if (returnType.get<4>() != nullptr)
        node->setReturnType(node->getReturnType() | Token::stringToType(returnType.get<4>()->value));

    setCurrentNode(node->getBranch());
    convertStatements(statement.get<4>());

    leaveScope();
    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertStatement(PTNestedFunctionDeclStatement& statement, NodeID id)
{
    return convertExpression(*statement.get<1>(), id);
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertStatement(PTPresetDefStatement& statement)
{
    enterScope();

    auto node = std::make_unique<ASTPresetNode>();
    node->setLine(statement.get<1>()->line);
    node->setIdentifier(convertStatement(*statement.get<2>(), NodeID::PresetIdentifier));
    node->setArguments(convertArguments(*statement.get<2>()));

    auto branch = std::make_unique<ASTNullNode>();
    branch->setPreviousNode(node.get());
    node->setBranch(std::move(branch));

    static_cast<ASTPresetIdentifierNode*>(node->getIdentifier())->setPreset(node.get());

    setCurrentNode(node->getBranch());
    convertStatements(statement.get<3>());

    leaveScope();
    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertStatement(PTReturnStatement& statement)
{
    auto node = std::make_unique<ASTReturnNode>();
    node->setNode(convertExpression(*statement.get<2>()));
    node->setLine(statement.get<1>()->line);

    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertStatement(PTBreakStatement& statement)
{
    auto node = std::make_unique<ASTBreakNode>();
    node->setLine(statement.get<1>()->line);

    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertStatement(PTContinueStatement& statement)
{
    auto node = std::make_unique<ASTContinueNode>();
    node->setLine(statement.get<1>()->line);

    return node;
}

AbstractSyntaxTree::ptr_node_v AbstractSyntaxTree::convertArguments(IPTStatementNode& statement)
{
    switch (statement.id()) {
        case StatementID::FunctionDecl:
            return convertArguments(static_cast<PTFunctionDeclStatement&>(statement));
        case StatementID::NestedFunctionDecl:
            return convertArguments(static_cast<PTNestedFunctionDeclStatement&>(statement));
        case StatementID::NestedDecl:
            return convertArguments(static_cast<PTNestedDeclStatement&>(statement));
        default:
            return {};
    }
}

AbstractSyntaxTree::ptr_node_v AbstractSyntaxTree::convertArguments(PTFunctionDeclStatement& statement)
{
    if (statement.get<3>()->id() == ExpressionID::Empty)
        return {};

    ptr_node_v args;
    if (statement.get<3>()->id() != ExpressionID::Separator) {
        args.push_back(convertExpression(*statement.get<3>(), NodeID::Function));
        return args;
    }

    PTSeparatorExpression* current = static_cast<PTSeparatorExpression*>(statement.get<3>().get());
    while (true) {
        args.push_back(convertExpression(*current->get<1>(), NodeID::Function));
        if (current->get<3>()->id() != ExpressionID::Separator) {
            args.push_back(convertExpression(*current->get<3>(), NodeID::Function));
            break;
        }

        current = static_cast<PTSeparatorExpression*>(current->get<3>().get());
    }
    return args;
}

AbstractSyntaxTree::ptr_node_v AbstractSyntaxTree::convertArguments(PTNestedFunctionDeclStatement& statement)
{
    if (statement.get<3>()->id() == ExpressionID::Empty)
        return {};

    ptr_node_v args;
    if (statement.get<3>()->id() != ExpressionID::Separator) {
        args.push_back(convertExpression(*statement.get<3>(), NodeID::NestedFunction));
        return args;
    }

    PTSeparatorExpression* current = static_cast<PTSeparatorExpression*>(statement.get<3>().get());
    while (true) {
        args.push_back(convertExpression(*current->get<1>(), NodeID::NestedFunction));
        if (current->get<3>()->id() != ExpressionID::Separator) {
            args.push_back(convertExpression(*current->get<3>(), NodeID::NestedFunction));
            break;
        }

        current = static_cast<PTSeparatorExpression*>(current->get<3>().get());
    }
    return args;
}

AbstractSyntaxTree::ptr_node_v AbstractSyntaxTree::convertArguments(PTNestedDeclStatement& statement)
{
    if (statement.get<3>()->id() == ExpressionID::Empty)
        return {};

    ptr_node_v args;
    if (statement.get<3>()->id() != ExpressionID::Separator) {
        args.push_back(convertExpression(*statement.get<3>(), NodeID::NestedIdentifier));
        return args;
    }
    
    PTSeparatorExpression* current = static_cast<PTSeparatorExpression*>(statement.get<3>().get());
    while (true) {
        args.push_back(convertExpression(*current->get<1>(), NodeID::NestedIdentifier));
        if (current->get<3>()->id() != ExpressionID::Separator) {
            args.push_back(convertExpression(*current->get<3>(), NodeID::NestedIdentifier));
            break;
        }

        current = static_cast<PTSeparatorExpression*>(current->get<3>().get());
    }
    return args;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(IPTExpressionNode& expression, NodeID id)
{
    switch (expression.id()) {
        case ExpressionID::Literal:
            return convertExpression(static_cast<PTLiteralExpression&>(expression));
        case ExpressionID::Identifier:
            return convertExpression(static_cast<PTIdentifierExpression&>(expression), id);
        case ExpressionID::Keyword:
            return convertExpression(static_cast<PTKeywordExpression&>(expression));
        case ExpressionID::Assignment:
            return convertExpression(static_cast<PTAssignmentExpression&>(expression), id);
        case ExpressionID::Arithmetic:
            return convertExpression(static_cast<PTArithmeticExpression&>(expression));
        case ExpressionID::Comparison:
            return convertExpression(static_cast<PTComparisonExpression&>(expression));
        case ExpressionID::Logical:
            return convertExpression(static_cast<PTLogicalExpression&>(expression));
        case ExpressionID::UnaryLogical:
            return convertExpression(static_cast<PTUnaryLogicalExpression&>(expression));
        case ExpressionID::FunctionCall:
            return convertExpression(static_cast<PTFunctionCallExpression&>(expression), id);
        case ExpressionID::ForRange:
            return convertExpression(static_cast<PTForRangeExpression&>(expression));
        case ExpressionID::MemberAccess:
            return convertExpression(static_cast<PTMemberAccessExpression&>(expression), id);
        case ExpressionID::Error:
            return convertExpression(static_cast<PTErrorExpression&>(expression));
        case ExpressionID::Warning:
            return convertExpression(static_cast<PTWarningExpression&>(expression));
        case ExpressionID::Assert:
            return convertExpression(static_cast<PTAssertExpression&>(expression));
        case ExpressionID::ArraySubscript:
            return convertExpression(static_cast<PTArraySubscriptExpression&>(expression));
        case ExpressionID::PercentLiteral:
            return convertExpression(static_cast<PTPercentLiteralExpression&>(expression));
        case ExpressionID::StringLiteral:
            return convertExpression(static_cast<PTStringLiteralExpression&>(expression));
        case ExpressionID::RangeLiteral:
            return convertExpression(static_cast<PTRangeLiteralExpression&>(expression));
        case ExpressionID::CoordLiteral:
            return convertExpression(static_cast<PTCoordLiteralExpression&>(expression));
        case ExpressionID::DeclType:
            return convertExpression(static_cast<PTDeclTypeExpression&>(expression), id);
        default:
            return nullptr;
    }
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTLiteralExpression& expression)
{
    if (expression.get<1>()->type == ValueType::Int)
        return convertValue<ASTIntNode>(std::strtol(expression.get<1>()->value.data(), nullptr, 10), expression.get<1>()->line);
    else if (expression.get<1>()->type == ValueType::Float)
        return convertValue<ASTFloatNode>(std::strtof(expression.get<1>()->value.data(), nullptr), expression.get<1>()->line);
    else
        return nullptr;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTIdentifierExpression& expression, NodeID id)
{
    if (id == NodeID::FunctionIdentifier)
        return convertName<ASTFunctionIdentifierNode>(expression.get<1>()->value, expression.get<1>()->line);
    else if (id == NodeID::NestedIdentifier)
        return convertName<ASTNestedIdentifierNode>(expression.get<1>()->value, expression.get<1>()->line);
    else if (id == NodeID::PresetIdentifier)
        return convertName<ASTPresetIdentifierNode>(expression.get<1>()->value, expression.get<1>()->line);
    else if (id == NodeID::X)
        return convertName<ASTXNode>(expression.get<1>()->value, expression.get<1>()->line);
    else if (id == NodeID::Y)
        return convertName<ASTYNode>(expression.get<1>()->value, expression.get<1>()->line);
    else if (id == NodeID::Rotation)
        return convertName<ASTRotationNode>(expression.get<1>()->value, expression.get<1>()->line);
    else
        return convertName<ASTVariableNode>(expression.get<1>()->value, expression.get<1>()->line);
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTKeywordExpression& expression)
{
    if (expression.get<1>()->value == KW::Anchor)
        return convert<ASTAnchorNode>(expression.get<1>()->line);
    else if (expression.get<1>()->value == KW::Count)
        return convert<ASTCountNode>(expression.get<1>()->line);
    else if (expression.get<1>()->value == KW::Empty)
        return convert<ASTEmptyNode>(expression.get<1>()->line);
    else if (expression.get<1>()->value == KW::False)
        return convertValue<ASTBoolNode>(false, expression.get<1>()->line);
    else if (expression.get<1>()->value == KW::Full)
        return convert<ASTFullNode>(expression.get<1>()->line);
    else if (expression.get<1>()->value == KW::Index)
        return convert<ASTIndexNode>(expression.get<1>()->line);
    else if (expression.get<1>()->value == KW::Last)
        return convert<ASTLastNode>(expression.get<1>()->line);
    else if (expression.get<1>()->value == KW::Notindex)
        return convert<ASTNotIndexNode>(expression.get<1>()->line);
    else if (expression.get<1>()->value == KW::Rotate)
        return convert<ASTRotateNode>(expression.get<1>()->line);
    else if (expression.get<1>()->value == KW::True)
        return convertValue<ASTBoolNode>(true, expression.get<1>()->line);
    else
        return nullptr;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTAssignmentExpression& expression, NodeID id)
{
    if (id == NodeID::ForRange) {
        PTDeclTypeExpression decl;
        Token intType = { TKeyword, KW::Int, expression.get<1>()->getLastToken()->line };
        decl.set<1>(&intType);
        decl.set<3>(expression.get<1>()->getLastToken());

        auto left = convertExpression(decl, NodeID::OpAssign);
        auto right = convertExpression(*expression.get<3>());

        left->as<ASTDeclarationNode*>()->setNode(std::move(right));
        left->setLine(expression.get<1>()->getTokens().front()->line);
        return left;
    }
    else {
        auto left = convertExpression(*expression.get<1>(), NodeID::OpAssign);
        auto right = convertExpression(*expression.get<3>());

        if (left->id() == NodeID::Declaration) {
            left->as<ASTDeclarationNode*>()->setNode(std::move(right));
            left->setLine(expression.get<1>()->getTokens().front()->line);
            return left;
        }
        else if (left->id() == NodeID::Insert) {
            left->as<ASTInsertNode*>()->setNode(std::move(right));
            return left;
        }
        return convertBinaryExpression<ASTOpAssignNode>(std::move(left), std::move(right), expression.get<2>()->line);
    }
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTArithmeticExpression& expression)
{
    auto left = convertExpression(*expression.get<1>());
    auto right = convertExpression(*expression.get<3>());

    ptr_node node;
    if (expression.get<2>()->value == OP::Addition)
        node = convertBinaryExpression<ASTOpAddNode>(std::move(left), std::move(right), expression.get<2>()->line);
    else if (expression.get<2>()->value == OP::Subtraction)
        node = convertBinaryExpression<ASTOpSubtractNode>(std::move(left), std::move(right), expression.get<2>()->line);
    else if (expression.get<2>()->value == OP::Multiplication)
        node = convertBinaryExpression<ASTOpMultiplyNode>(std::move(left), std::move(right), expression.get<2>()->line);
    else if (expression.get<2>()->value == OP::Division)
        node = convertBinaryExpression<ASTOpDivideNode>(std::move(left), std::move(right), expression.get<2>()->line);
    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTComparisonExpression& expression)
{
    auto left = convertExpression(*expression.get<1>());
    auto right = convertExpression(*expression.get<3>());

    ptr_node node;
    if (expression.get<2>()->value == OP::Equal)
        node = convertBinaryExpression<ASTOpEqualNode>(std::move(left), std::move(right), expression.get<2>()->line);
    else if (expression.get<2>()->value == OP::NotEqual)
        node = convertBinaryExpression<ASTOpNotEqualNode>(std::move(left), std::move(right), expression.get<2>()->line);
    else if (expression.get<2>()->value == OP::GreaterThan)
        node = convertBinaryExpression<ASTOpGreaterThanNode>(std::move(left), std::move(right), expression.get<2>()->line);
    else if (expression.get<2>()->value == OP::GreaterThanOrEqual)
        node = convertBinaryExpression<ASTOpGreaterThanOrEqualNode>(std::move(left), std::move(right), expression.get<2>()->line);
    else if (expression.get<2>()->value == OP::LessThan)
        node = convertBinaryExpression<ASTOpLessThanNode>(std::move(left), std::move(right), expression.get<2>()->line);
    else if (expression.get<2>()->value == OP::LessThanOrEqual)
        node = convertBinaryExpression<ASTOpLessThanOrEqualNode>(std::move(left), std::move(right), expression.get<2>()->line);
    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTLogicalExpression& expression)
{
    auto left = convertExpression(*expression.get<1>());
    auto right = convertExpression(*expression.get<3>());
    
    ptr_node node;
    if (expression.get<2>()->value == KW::And)
        node = convertBinaryExpression<ASTOpAndNode>(std::move(left), std::move(right), expression.get<2>()->line);
    else if (expression.get<2>()->value == KW::Or)
        node = convertBinaryExpression<ASTOpOrNode>(std::move(left), std::move(right), expression.get<2>()->line);
    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTUnaryLogicalExpression& expression)
{
    auto expr = convertExpression(*expression.get<2>());
    
    ptr_node node;
    if (expression.get<1>()->value == KW::Not)
        node = convertUnaryExpression<ASTOpNotNode>(std::move(expr), expression.get<1>()->line);
    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTFunctionCallExpression& expression, NodeID id)
{
    if (id == NodeID::NestedCall) {
        auto node = std::make_unique<ASTNestedCallNode>();
        node->setName(expression.get<1>()->value);
        node->setArguments(convertArguments(expression));
        node->setLine(expression.get<1>()->line);
        return node;
    }
    else if (id == NodeID::PresetCall) {
        auto node = std::make_unique<ASTPresetCallNode>();
        node->setName(expression.get<1>()->value);
        node->setArguments(convertArguments(expression));
        node->setLine(expression.get<1>()->line);
        return node;
    }
    else if (id == NodeID::PushCall) {
        auto node = std::make_unique<ASTPushCallNode>();
        node->setArguments(convertArguments(expression));
        node->setLine(expression.get<1>()->line);
        return node;
    }
    else if (id == NodeID::HasCall) {
        auto node = std::make_unique<ASTHasCallNode>();
        node->setArguments(convertArguments(expression));
        node->setLine(expression.get<1>()->line);
        return node;
    }
    else if (id == NodeID::UniqueCall) {
        auto node = std::make_unique<ASTUniqueCallNode>();
        node->setArguments(convertArguments(expression));
        node->setLine(expression.get<1>()->line);
        return node;
    }
    else if (id == NodeID::StrCall) {
        auto node = std::make_unique<ASTStrCallNode>();
        node->setArguments(convertArguments(expression));
        node->setLine(expression.get<1>()->line);
        return node;
    }
    else if (id == NodeID::NameCall) {
        auto node = std::make_unique<ASTNameCallNode>();
        node->setArguments(convertArguments(expression));
        node->setLine(expression.get<1>()->line);
        return node;
    }
    else if (id == NodeID::FindCall) {
        auto node = std::make_unique<ASTFindCallNode>();
        node->setArguments(convertArguments(expression));
        node->setLine(expression.get<1>()->line);
        return node;
    }
    else {
        if (expression.get<1>() == nullptr)
            return convertExpression(*expression.get<3>());
        else if (expression.get<1>()->value == KW::Invoke)
            return convert<ASTInvokeNestedNode>(expression.get<1>()->line);
        else {
            auto node = std::make_unique<ASTFunctionCallNode>();
            node->setName(expression.get<1>()->value);
            node->setArguments(convertArguments(expression));
            node->setLine(expression.get<1>()->line);
            return node;
        }
    }
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTForRangeExpression& expression)
{
    auto node = std::make_unique<ASTForRangeNode>();
    node->setDeclaration(convertExpression(*expression.get<1>(), NodeID::ForRange));
    node->setTo(convertExpression(*expression.get<3>()));

    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTMemberAccessExpression& expression, NodeID id)
{
    if (id == NodeID::FunctionIdentifier)
        return convertExpression(*expression.get<1>(), id);
    else if (id == NodeID::NestedIdentifier)
        return convertExpression(*expression.get<3>(), id);
        
    auto nodes = convertExpressions(expression, id);

    // handle nested calls
    ptr_node result;
    ptr_node functionCall;
    size_t nestedEnd = 0;
    if (nodes.front()->id() == NodeID::FunctionCall) {
        functionCall = std::move(nodes.front());
        nestedEnd = 1;

        ptr_node_v nestedCalls;
        for (size_t i = 1; i < nodes.size(); ++i, ++nestedEnd) {
            if (nodes[i]->id() == NodeID::NestedCall) {
                nodes[i]->as<ASTNestedCallNode*>()->setFunctionCall(functionCall.get());
                nestedCalls.push_back(std::move(nodes[i]));
            }
            else
                break;
        }
        functionCall->as<ASTFunctionCallNode*>()->setNestedCalls(std::move(nestedCalls));
        result = std::move(functionCall);
    }
    else
        result = std::move(nodes[nestedEnd++]);

    for (size_t i = nestedEnd; i < nodes.size(); ++i) {
        auto& current = nodes[i];

        switch (result->id()) {
            case NodeID::Bool :
            case NodeID::HasCall :
            case NodeID::Float :
            case NodeID::String :
            case NodeID::NameCall :
                if (current->id() == NodeID::StrCall)
                    current->as<ASTStrCallNode*>()->setVariable(std::move(result));
                result = std::move(current);
                break;

            case NodeID::Int :
            case NodeID::OpRange :
            case NodeID::Count :
            case NodeID::Last :
            case NodeID::X :
            case NodeID::Y :
            case NodeID::FindCall :
                if (current->id() == NodeID::Rotation)
                    current->as<ASTRotationNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Rotate)
                    current->as<ASTRotateNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::StrCall)
                    current->as<ASTStrCallNode*>()->setVariable(std::move(result));
                result = std::move(current);
                break;
                
            case NodeID::OpCoord :
            case NodeID::Anchor :
                if (current->id() == NodeID::X)
                    current->as<ASTXNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Y)
                    current->as<ASTYNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Rotation)
                    current->as<ASTRotationNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Rotate)
                    current->as<ASTRotateNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::StrCall)
                    current->as<ASTStrCallNode*>()->setVariable(std::move(result));
                result = std::move(current);
                break;

            case NodeID::Object :
                if (current->id() == NodeID::Anchor)
                    current->as<ASTAnchorNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Count)
                    current->as<ASTCountNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Last)
                    current->as<ASTLastNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Rotation)
                    current->as<ASTRotationNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Rotate)
                    current->as<ASTRotateNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::StrCall)
                    current->as<ASTStrCallNode*>()->setVariable(std::move(result));
                result = std::move(current);
                break;

            case NodeID::Array :
            case NodeID::UniqueCall :
                if (current->id() == NodeID::Count)
                    current->as<ASTCountNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Last)
                    current->as<ASTLastNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::PushCall)
                    current->as<ASTPushCallNode*>()->setVariable(std::move(result));
                else if (current->id() == NodeID::HasCall)
                    current->as<ASTHasCallNode*>()->setVariable(std::move(result));
                else if (current->id() == NodeID::UniqueCall)
                    current->as<ASTUniqueCallNode*>()->setVariable(std::move(result));
                else if (current->id() == NodeID::StrCall)
                    current->as<ASTStrCallNode*>()->setVariable(std::move(result));
                else if (current->id() == NodeID::FindCall)
                    current->as<ASTFindCallNode*>()->setVariable(std::move(result));
                result = std::move(current);
                break;

            case NodeID::Variable :
                if (current->id() == NodeID::Anchor)
                    current->as<ASTAnchorNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Count)
                    current->as<ASTCountNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Last)
                    current->as<ASTLastNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::X)
                    current->as<ASTXNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Y)
                    current->as<ASTYNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Rotation)
                    current->as<ASTRotationNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Rotate)
                    current->as<ASTRotateNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::PushCall)
                    current->as<ASTPushCallNode*>()->setVariable(std::move(result));
                else if (current->id() == NodeID::HasCall)
                    current->as<ASTHasCallNode*>()->setVariable(std::move(result));
                else if (current->id() == NodeID::UniqueCall)
                    current->as<ASTUniqueCallNode*>()->setVariable(std::move(result));
                else if (current->id() == NodeID::StrCall)
                    current->as<ASTStrCallNode*>()->setVariable(std::move(result));
                else if (current->id() == NodeID::NameCall)
                    current->as<ASTNameCallNode*>()->setVariable(std::move(result));
                else if (current->id() == NodeID::FindCall)
                    current->as<ASTFindCallNode*>()->setVariable(std::move(result));
                result = std::move(current);
                break;

            case NodeID::Rotation :
                if (current->id() == NodeID::Anchor)
                    current->as<ASTAnchorNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Count)
                    current->as<ASTCountNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Last)
                    current->as<ASTLastNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::X)
                    current->as<ASTXNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Y)
                    current->as<ASTYNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Rotate)
                    current->as<ASTRotateNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::StrCall)
                    current->as<ASTStrCallNode*>()->setVariable(std::move(result));
                result = std::move(current);
                break;

            case NodeID::Rotate :
                if (current->id() == NodeID::Rotation) {
                    result->as<ASTRotateNode*>()->setRotation(current->as<ASTRotationNode*>()->getRotation());
                    break;
                }
                if (current->id() == NodeID::StrCall)
                    current->as<ASTStrCallNode*>()->setVariable(std::move(result));
                result = std::move(current);
                break;        
                
            case NodeID::ArraySubscript :
                if (current->id() == NodeID::Anchor)
                    current->as<ASTAnchorNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Count)
                    current->as<ASTCountNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Last)
                    current->as<ASTLastNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::X)
                    current->as<ASTXNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Y)
                    current->as<ASTYNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Rotation)
                    current->as<ASTRotationNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Rotate)
                    current->as<ASTRotateNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::StrCall)
                    current->as<ASTStrCallNode*>()->setVariable(std::move(result));
                result = std::move(current);
                break;

            case NodeID::FunctionCall :
                if (current->id() == NodeID::Anchor)
                    current->as<ASTAnchorNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Count)
                    current->as<ASTCountNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Last)
                    current->as<ASTLastNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::X)
                    current->as<ASTXNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Y)
                    current->as<ASTYNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Rotation)
                    current->as<ASTRotationNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::Rotate)
                    current->as<ASTRotateNode*>()->setNode(std::move(result));
                else if (current->id() == NodeID::HasCall)
                    current->as<ASTHasCallNode*>()->setVariable(std::move(result));
                else if (current->id() == NodeID::UniqueCall)
                    current->as<ASTUniqueCallNode*>()->setVariable(std::move(result));
                else if (current->id() == NodeID::StrCall)
                    current->as<ASTStrCallNode*>()->setVariable(std::move(result));
                else if (current->id() == NodeID::FindCall)
                    current->as<ASTFindCallNode*>()->setVariable(std::move(result));
                result = std::move(current);
                break;
        }
    }
    return result;
}

AbstractSyntaxTree::ptr_node_v AbstractSyntaxTree::convertExpressions(PTMemberAccessExpression& expression, NodeID id)
{
    ptr_node_v result;
    result.push_back(convertLeft(expression, id));

    if (result.back()->id() == NodeID::Insert)
        return result;

    ptr_node_v nodes;
    if (expression.get<3>()->id() == ExpressionID::MemberAccess) {
        nodes = convertExpressions(static_cast<PTMemberAccessExpression&>(*expression.get<3>()), NodeID::NestedCall);
        result.insert(result.end(), std::make_move_iterator(nodes.begin()), std::make_move_iterator(nodes.end()));
    }
    else if (expression.get<1>()->id() == ExpressionID::FunctionCall && expression.get<3>()->id() == ExpressionID::FunctionCall)
        result.push_back(convertRight(expression, NodeID::NestedCall));
    else {
        if (result.back()->id() != NodeID::PresetCall)
            result.push_back(convertRight(expression, result.back()->id()));
    }
    
    return result;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTErrorExpression& expression)
{
    auto node = std::make_unique<ASTErrorNode>();
    node->setString(convertExpression(*expression.get<3>()));
    node->setLine(expression.get<1>()->line);

    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTWarningExpression& expression)
{
    auto node = std::make_unique<ASTWarningNode>();
    node->setString(convertExpression(*expression.get<3>()));
    node->setLine(expression.get<1>()->line);

    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTAssertExpression& expression)
{
    auto node = std::make_unique<ASTAssertNode>();
    node->setExpr(convertExpression(*expression.get<3>()));
    node->setLine(expression.get<1>()->line);

    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTArraySubscriptExpression& expression)
{
    auto node = std::make_unique<ASTArraySubscriptNode>();
    std::vector<Token*> tokens = expression.get<1>()->getTokens();
    std::string name;
    for (auto&& token : tokens)
        name += token->value;
    node->setName(name);
    node->setLine(tokens.front()->line);
    node->setArray(convertExpression(*expression.get<1>()));
    node->setIndex(convertExpression(*expression.get<3>()));
    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTPercentLiteralExpression& expression)
{
    return convertValue<ASTFloatNode>(100.0f / std::stof(expression.get<1>()->value), expression.get<1>()->line);
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTStringLiteralExpression& expression)
{
    return convertValue<ASTStringNode>(expression.get<2>()->value, expression.get<2>()->line);
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTRangeLiteralExpression& expression)
{
    auto from = convertExpression(*expression.get<1>());
    auto to = convertExpression(*expression.get<3>());

    auto node = std::make_unique<ASTOpRangeNode>();
    node->setLeft(std::move(from));
    node->setRight(std::move(to));
    node->setLine(expression.get<1>()->getTokens().front()->line);

    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTCoordLiteralExpression& expression)
{
    auto x = convertExpression(*static_cast<PTSeparatorExpression&>(*expression.get<2>()).get<1>());
    auto y = convertExpression(*static_cast<PTSeparatorExpression&>(*expression.get<2>()).get<3>());

    auto node = std::make_unique<ASTOpCoordNode>();
    node->setLeft(std::move(x));
    node->setRight(std::move(y));
    node->setLine(expression.get<1>()->line);

    return node;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertExpression(PTDeclTypeExpression& expression, NodeID id)
{
    auto identifier = std::make_unique<ASTIdentifierNode>();
    identifier->setName(expression.get<3>()->value);
    identifier->setLine(expression.get<3>()->line);
    identifier->setType(Token::stringToType(expression.get<1>()->value));

    if (expression.get<2>() != nullptr)
        identifier->setType(identifier->getType() | Token::stringToType(expression.get<2>()->value));

    if (id == NodeID::Function || id == NodeID::NestedFunction || id == NodeID::OpAssign) {
        switch (identifier->getType()) {
            case ValueType::Bool:
                identifier->setValue(std::make_unique<BoolValue>());
                break;
            case ValueType::Int:
                identifier->setValue(std::make_unique<IntValue>());
                break;
            case ValueType::Range:
                identifier->setValue(std::make_unique<RangeValue>());
                break;
            case ValueType::Coord:
                identifier->setValue(std::make_unique<CoordValue>());
                break;
            case ValueType::Float:
                identifier->setValue(std::make_unique<FloatValue>());
                break;
            case ValueType::String:
                identifier->setValue(std::make_unique<StringValue>());
                break;
        }
    }

    if (Token::isArray(identifier->getType())) {
        if (identifier->getType() == ValueType::ArrayBool)
            identifier->setValue(std::make_unique<ArrayValue<BoolValue>>());
        else if (identifier->getType() == ValueType::ArrayInt)
            identifier->setValue(std::make_unique<ArrayValue<IntValue>>());
        else if (identifier->getType() == ValueType::ArrayRange)
            identifier->setValue(std::make_unique<ArrayValue<RangeValue>>());
        else if (identifier->getType() == ValueType::ArrayCoord)
            identifier->setValue(std::make_unique<ArrayValue<CoordValue>>());
        else if (identifier->getType() == ValueType::ArrayFloat)
            identifier->setValue(std::make_unique<ArrayValue<FloatValue>>());
        else if (identifier->getType() == ValueType::ArrayString)
            identifier->setValue(std::make_unique<ArrayValue<StringValue>>());
        else if (identifier->getType() == ValueType::ArrayObject)
            identifier->setValue(std::make_unique<ArrayValue<ObjectValue>>());
    }
    else if (identifier->getType() == ValueType::Object)
        identifier->setValue(std::make_unique<ObjectValue>());

    auto node = std::make_unique<ASTDeclarationNode>();
    node->setIdentifier(std::move(identifier));
    node->setLine(expression.get<1>()->line);

    return node;
}

AbstractSyntaxTree::ptr_node_v AbstractSyntaxTree::convertArguments(IPTExpressionNode& expression)
{
    switch (expression.id()) {
        case ExpressionID::FunctionCall:
            return convertArguments(expression);
        default:
            return {};
    }
}

AbstractSyntaxTree::ptr_node_v AbstractSyntaxTree::convertArguments(PTFunctionCallExpression& expression)
{
    if (expression.get<3>()->id() == ExpressionID::Empty)
        return {};

    ptr_node_v args;
    if (expression.get<3>()->id() != ExpressionID::Separator) {
        args.push_back(convertExpression(*expression.get<3>()));
        return args;
    }

    PTSeparatorExpression* current = static_cast<PTSeparatorExpression*>(expression.get<3>().get());
    while (true) {
        args.push_back(convertExpression(*current->get<1>()));
        if (current->get<3>()->id() != ExpressionID::Separator) {
            args.push_back(convertExpression(*current->get<3>()));
            break;
        }

        current = static_cast<PTSeparatorExpression*>(current->get<3>().get());
    }
    return args;
}

InsertC AbstractSyntaxTree::convertInsertControl(PTMemberAccessExpression& expression)
{
    InsertC control = InsertC::Default;

    Token* left = expression.get<1>()->getLastToken();
    if (left->value == KW::Insert)
        control |= InsertC::Insert;
    else if (left->value == KW::Rule)
        control |= InsertC::Rule;
    else if (left->value == KW::Pos)
        control |= InsertC::Pos;
    else if (left->value == KW::Index)
        control |= InsertC::Index;

    if (expression.get<3>()->id() != ExpressionID::MemberAccess) {
        Token* right = expression.get<3>()->getLastToken();

        if (right->value == KW::Automapper)
            control |= InsertC::Automapper;
        else if (right->value == KW::Newrun)
            control |= InsertC::Newrun;
        else if (right->value == KW::Newrule)
            control |= InsertC::Newrule;
        else if (right->value == KW::Nocopy)
            control |= InsertC::Nocopy;
        else if (right->value == KW::Nodefault)
            control |= InsertC::Nodefault;
        else if (right->value == KW::Random)
            control |= InsertC::Random;
        else if (right->value == KW::Pos)
            control |= InsertC::Pos;
        else if (right->value == KW::Index)
            control |= InsertC::Index;
        else if (right->value == KW::Type)
            control |= InsertC::Type;
        else if (right->value == KW::Operator)
            control |= InsertC::Operator;
        else if (right->value == KW::Group)
            control |= InsertC::Group;
    }
    else
        control |= convertInsertControl(static_cast<PTMemberAccessExpression&>(*expression.get<3>()));

    return control;
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertLeft(PTMemberAccessExpression& expression, NodeID id)
{
    if (expression.get<1>()->getLastToken()->value == KW::Insert) {
        auto insert = std::make_unique<ASTInsertNode>();
        insert->setControl(convertInsertControl(expression));
        insert->setLine(expression.get<1>()->getLastToken()->line);
        return insert;
    }
    
    if (expression.get<1>()->getLastToken()->value == KW::Anchor)
        return convertExpression(*expression.get<1>(), NodeID::Anchor);
    else if (expression.get<1>()->getLastToken()->value == KW::Count)
        return convertExpression(*expression.get<1>(), NodeID::Count);
    else if (expression.get<1>()->getLastToken()->value == KW::Last)
        return convertExpression(*expression.get<1>(), NodeID::Last);
    else if (expression.get<1>()->getLastToken()->value == "x") {
        if (id == NodeID::NestedCall)
            return convertExpression(*expression.get<1>(), NodeID::X);
        else
            return convertExpression(*expression.get<1>(), NodeID::Variable);
    }
    else if (expression.get<1>()->getLastToken()->value == "y") {
        if (id == NodeID::NestedCall)
            return convertExpression(*expression.get<1>(), NodeID::Y);
        else
            return convertExpression(*expression.get<1>(), NodeID::Variable);
    }
    else if (Token::stringToRotation(expression.get<1>()->getTokens().front()->value) != Rotation::Default)
        return convertExpression(*expression.get<1>(), NodeID::Rotation);
    else if (expression.get<1>()->getTokens().front()->value == KW::Rotate)
        return convertExpression(*expression.get<1>(), NodeID::Rotate);
    else if (expression.get<1>()->getLastToken()->value == KW::Preset)
        return convertExpression(*expression.get<3>(), NodeID::PresetCall);
    else if (expression.get<1>()->id() == ExpressionID::FunctionCall) {
        std::string_view functionName = static_cast<PTFunctionCallExpression&>(*expression.get<1>()).get<1>()->value;
        if (Token::isBuiltin(functionName)) {
            if (functionName == "push")
                return convertExpression(*expression.get<1>(), NodeID::PushCall);
            else if (functionName == "has")
                return convertExpression(*expression.get<1>(), NodeID::HasCall);
            else if (functionName == "unique")
                return convertExpression(*expression.get<1>(), NodeID::UniqueCall);
            else if (functionName == "str")
                return convertExpression(*expression.get<1>(), NodeID::StrCall);
            else if (functionName == "name")
                return convertExpression(*expression.get<1>(), NodeID::NameCall);
            else if (functionName == "find")
                return convertExpression(*expression.get<1>(), NodeID::FindCall);
            else
                return nullptr;
        }
        else if (id == NodeID::NestedCall)
            return convertExpression(*expression.get<1>(), NodeID::NestedCall);
        else
            return convertExpression(*expression.get<1>(), NodeID::FunctionCall);
    }
    else
        return convertExpression(*expression.get<1>());
}

AbstractSyntaxTree::ptr_node AbstractSyntaxTree::convertRight(PTMemberAccessExpression& expression, NodeID left_id)
{
    if (expression.get<3>()->id() == ExpressionID::MemberAccess)
        return convertExpression(*expression.get<3>());

    if (expression.get<3>()->getLastToken()->value == KW::Anchor)
        return convertExpression(*expression.get<3>(), NodeID::Anchor);
    else if (expression.get<3>()->getLastToken()->value == KW::Count)
        return convertExpression(*expression.get<3>(), NodeID::Count);
    else if (expression.get<3>()->getLastToken()->value == KW::Last)
        return convertExpression(*expression.get<3>(), NodeID::Last);
    else if (expression.get<3>()->getLastToken()->value == "x")
        return convertExpression(*expression.get<3>(), NodeID::X);
    else if (expression.get<3>()->getLastToken()->value == "y")
        return convertExpression(*expression.get<3>(), NodeID::Y);
    else if (Token::stringToRotation(expression.get<3>()->getTokens().front()->value) != Rotation::Default)
        return convertExpression(*expression.get<3>(), NodeID::Rotation);
    else if (expression.get<3>()->getTokens().front()->value == KW::Rotate)
        return convertExpression(*expression.get<3>(), NodeID::Rotate);
    else if (expression.get<3>()->getLastToken()->value == KW::Preset)
        return convertExpression(*expression.get<3>(), NodeID::PresetCall);
    else if (expression.get<3>()->id() == ExpressionID::FunctionCall) {
        std::string_view functionName = static_cast<PTFunctionCallExpression&>(*expression.get<3>()).get<1>()->value;
        if (Token::isBuiltin(functionName)) {
            if (functionName == "push")
                return convertExpression(*expression.get<3>(), NodeID::PushCall);
            else if (functionName == "has")
                return convertExpression(*expression.get<3>(), NodeID::HasCall);
            else if (functionName == "unique")
                return convertExpression(*expression.get<3>(), NodeID::UniqueCall);
            else if (functionName == "str")
                return convertExpression(*expression.get<3>(), NodeID::StrCall);
            else if (functionName == "name")
                return convertExpression(*expression.get<3>(), NodeID::NameCall);
            else if (functionName == "find")
                return convertExpression(*expression.get<3>(), NodeID::FindCall);
            else
                return nullptr;
        }
        else if (left_id == NodeID::PresetCall)
            return convertExpression(*expression.get<3>(), NodeID::PresetCall);
        else if (left_id == NodeID::NestedCall)
            return convertExpression(*expression.get<3>(), NodeID::NestedCall);
        else
            return convertExpression(*expression.get<3>(), NodeID::FunctionCall);
    }
    else
        return convertExpression(*expression.get<3>());
}
