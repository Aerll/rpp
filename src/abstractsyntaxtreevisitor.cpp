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
#include <abstractsyntaxtreevisitor.hpp>

#include <algorithm>

#include <abstractsyntaxtree.hpp>

/*
    ASTNodeParser
*/
void ASTNodeParser::parse(ASTNullNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTBoolNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTIntNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTRangeNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTCoordNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTFloatNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTStringNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTObjectNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTArrayNode<BoolValue>* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTArrayNode<IntValue>* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTArrayNode<RangeValue>* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTArrayNode<CoordValue>* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTArrayNode<FloatValue>* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTArrayNode<StringValue>* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTArrayNode<ObjectValue>* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTDeclarationNode* node)
{
    node->getIdentifier()->accept(*this);

    std::unique_ptr<Error> error;
    if (node->getNode() != nullptr) {
        node->getNode()->accept(*this);
        error = parseType(node->getNodeType(), node->getNode()->getNodeType(), node->getLine());
    }

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTIdentifierNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getValue() != nullptr)
        error = parseType(node->getNodeType(), node->getValue()->type(), node->getLine());
    else
        error = std::make_unique<ErrUnassignedVariable>(node->getName(), node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTVariableNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTAnchorNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTCountNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTLastNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTXNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTYNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTRotationNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTEmptyNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTFullNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTIndexNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTNotIndexNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTInsertNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNode() != nullptr) {
        node->getNode()->accept(*this);
        if (node->getControl() == InsertC::InsertRulePosType) {
            if (node->getNode()->id() == NodeID::Empty ||
                node->getNode()->id() == NodeID::Full || 
                node->getNode()->id() == NodeID::Index ||
                node->getNode()->id() == NodeID::NotIndex
                ) {} // valid
            else
                error = std::make_unique<ErrInvalidPosType>(node->getLine());
        }
        else
            error = parseType(node->getNodeType(), node->getNode()->getNodeType(), node->getLine());
    }

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTRotateNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpAssignNode* node)
{
    node->getRight()->accept(*this);

    std::unique_ptr<Error> error;
    if (node->getLeft()->id() == NodeID::ArraySubscript) {
        if (node->getLeft()->as<ASTArraySubscriptNode*>()->getArray()->getNodeType() == ValueType::Object) {
            error = std::make_unique<ErrReadOnlyAssignment>(node->getLine());
        }
    }
    else
        error = parseType(node->getLeft()->getNodeType(), node->getRight()->getNodeType(), node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpAddNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() == ValueType::Null)
        error = std::make_unique<ErrNoOperatorOverload>(node->getLeft()->getNodeType(), node->getRight()->getNodeType(), NodeID::OpAdd, node->getLine());
        
    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpSubtractNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() == ValueType::Null)
        error = std::make_unique<ErrNoOperatorOverload>(node->getLeft()->getNodeType(), node->getRight()->getNodeType(), NodeID::OpSubtract, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpMultiplyNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() == ValueType::Null)
        error = std::make_unique<ErrNoOperatorOverload>(node->getLeft()->getNodeType(), node->getRight()->getNodeType(), NodeID::OpMultiply, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpDivideNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() == ValueType::Null)
        error = std::make_unique<ErrNoOperatorOverload>(node->getLeft()->getNodeType(), node->getRight()->getNodeType(), NodeID::OpDivide, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpEqualNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() == ValueType::Null)
        error = std::make_unique<ErrNoOperatorOverload>(node->getLeft()->getNodeType(), node->getRight()->getNodeType(), NodeID::OpEqual, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpNotEqualNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() == ValueType::Null)
        error = std::make_unique<ErrNoOperatorOverload>(node->getLeft()->getNodeType(), node->getRight()->getNodeType(), NodeID::OpNotEqual, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpGreaterThanNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() == ValueType::Null)
        error = std::make_unique<ErrNoOperatorOverload>(node->getLeft()->getNodeType(), node->getRight()->getNodeType(), NodeID::OpGreaterThan, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpGreaterThanOrEqualNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() == ValueType::Null)
        error = std::make_unique<ErrNoOperatorOverload>(node->getLeft()->getNodeType(), node->getRight()->getNodeType(), NodeID::OpGreaterThanOrEqual, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpLessThanNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() == ValueType::Null)
        error = std::make_unique<ErrNoOperatorOverload>(node->getLeft()->getNodeType(), node->getRight()->getNodeType(), NodeID::OpLessThan, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpLessThanOrEqualNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() == ValueType::Null)
        error = std::make_unique<ErrNoOperatorOverload>(node->getLeft()->getNodeType(), node->getRight()->getNodeType(), NodeID::OpLessThanOrEqual, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpAndNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() == ValueType::Null)
        error = std::make_unique<ErrNoOperatorOverload>(node->getLeft()->getNodeType(), node->getRight()->getNodeType(), NodeID::OpAnd, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpOrNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() == ValueType::Null)
        error = std::make_unique<ErrNoOperatorOverload>(node->getLeft()->getNodeType(), node->getRight()->getNodeType(), NodeID::OpOr, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpNotNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() == ValueType::Null)
        error = std::make_unique<ErrNoOperatorOverload>(ValueType::Null, node->getExpr()->getNodeType(), NodeID::OpNot, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTOpRangeNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getLeft()->getNodeType() != ValueType::Int)
        error = std::make_unique<ErrIncorrectValueType>(node->getLeft()->getNodeType(), ValueType::Int, node->getLeft()->getLine());
    else if (node->getRight()->getNodeType() != ValueType::Int)
        error = std::make_unique<ErrIncorrectValueType>(node->getRight()->getNodeType(), ValueType::Int, node->getRight()->getLine());

    if (error != nullptr)
        errors().push(std::move(error));
}

void ASTNodeParser::parse(ASTOpCoordNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getLeft()->getNodeType() != ValueType::Int)
        error = std::make_unique<ErrIncorrectValueType>(node->getLeft()->getNodeType(), ValueType::Int, node->getLeft()->getLine());
    else if (node->getRight()->getNodeType() != ValueType::Int)
        error = std::make_unique<ErrIncorrectValueType>(node->getRight()->getNodeType(), ValueType::Int, node->getRight()->getLine());

    if (error != nullptr)
        errors().push(std::move(error));
}

void ASTNodeParser::parse(ASTErrorNode* node)
{
    node->getString()->accept(*this);

    std::unique_ptr<Error> error;
    if (node->getString()->getNodeType() != ValueType::String)
        error = std::make_unique<ErrIncorrectValueType>(node->getString()->getNodeType(), ValueType::String, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTWarningNode* node)
{
    node->getString()->accept(*this);

    std::unique_ptr<Error> error;
    if (node->getString()->getNodeType() != ValueType::String)
        error = std::make_unique<ErrIncorrectValueType>(node->getString()->getNodeType(), ValueType::String, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTAssertNode* node)
{
    node->getExpr()->accept(*this);

    std::unique_ptr<Error> error;
    if (node->getExpr()->getNodeType() != ValueType::Bool)
        error = std::make_unique<ErrIncorrectValueType>(node->getExpr()->getNodeType(), ValueType::Bool, node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTReturnNode* node)
{
    std::unique_ptr<Error> error;
    auto inside = node->findNode({ NodeID::Function, NodeID::NestedFunction, NodeID::Preset }, {});
    if (inside->getNodeType() == ValueType::Null && node->getNode() == nullptr)
        {} // valid
    else if (
        (node->getNode() != nullptr && (
            inside->getNodeType() == node->getNode()->getNodeType() ||
            Token::isConvertible(inside->getNodeType(), node->getNode()->getNodeType())
            ))
        ) {} // valid
    else {
        if (node->getNode() != nullptr)
            error = std::make_unique<ErrIncorrectValueType>(node->getNode()->getNodeType(), inside->getNodeType(), node->getLine());
        else
            error = std::make_unique<ErrIncorrectValueType>(ValueType::Null, inside->getNodeType(), node->getLine());
    }

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTBreakNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTContinueNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTForRangeNode* node)
{
    std::unique_ptr<Error> error;
    auto identifier = node->getDeclaration()->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
    if (identifier->getValue()->type() != ValueType::Int)
        error = std::make_unique<ErrIncorrectValueType>(identifier->getNodeType(), ValueType::Int, identifier->getLine());
    else if (node->getTo()->getNodeType() != ValueType::Int)
        error = std::make_unique<ErrIncorrectValueType>(node->getTo()->getNodeType(), ValueType::Int, identifier->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    node->getTo()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTArraySubscriptNode* node)
{
    std::unique_ptr<Error> error;

    if (!Token::isArrayOrObject(node->getArray()->getNodeType()))
        error = std::make_unique<ErrNoSubscriptOperator>(node->getArray()->getNodeType(), node->getArray()->getLine());
    else if (node->getIndex()->getNodeType() != ValueType::Int)
        error = std::make_unique<ErrIncorrectValueType>(node->getIndex()->getNodeType(), ValueType::Int, node->getIndex()->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTPushCallNode* node)
{
    node->getVariable()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTHasCallNode* node)
{
    node->getVariable()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTUniqueCallNode* node)
{
    node->getVariable()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTStrCallNode* node)
{
    node->getVariable()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTNameCallNode* node)
{
    node->getVariable()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTFindCallNode* node)
{
    node->getVariable()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTFunctionCallNode* node)
{
    for (auto&& arg : node->getArguments())
        arg->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTNestedCallNode* node)
{
    for (auto&& arg : node->getArguments())
        arg->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTPresetCallNode* node)
{
    for (auto&& arg : node->getArguments())
        arg->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTForNode* node)
{
    node->getRange()->accept(*this);
    node->getBranch()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeParser::parse(ASTIfNode* node)
{
    std::unique_ptr<Error> error;

    if (node->getCondition()->getNodeType() != ValueType::Bool)
        error = std::make_unique<ErrIncorrectValueType>(node->getCondition()->getNodeType(), ValueType::Bool, node->getCondition()->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    node->getCondition()->accept(*this);
    node->getBranch()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTFunctionIdentifierNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTFunctionNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() != ValueType::Null && !node->getBranch()->hasNode(NodeID::Return))
        error = std::make_unique<ErrMissingReturn>(node->getIdentifier()->as<ASTFunctionIdentifierNode*>()->getName(), node->getLine());
    else if (node->getNestedIdentifiers().empty() && node->getBranch()->hasNode(NodeID::InvokeNested))
        error = std::make_unique<ErrInvokeInvalidContext>(node->getBranch()->findNode({ NodeID::InvokeNested }, {}, true)->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    node->getBranch()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTNestedIdentifierNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTNestedFunctionNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() != ValueType::Null && !node->getBranch()->hasNode(NodeID::Return))
        error = std::make_unique<ErrMissingReturn>(node->getIdentifier()->as<ASTNestedIdentifierNode*>()->getName(), node->getLine());
    else if (node->getBranch()->hasNode(NodeID::InvokeNested))
        error = std::make_unique<ErrInvokeInvalidContext>(node->getBranch()->findNode({ NodeID::InvokeNested }, {}, true)->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    node->getBranch()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTPresetIdentifierNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTPresetNode* node)
{
    std::unique_ptr<Error> error;
    if (node->getNodeType() != ValueType::Null && !node->getBranch()->hasNode(NodeID::Return))
        error = std::make_unique<ErrMissingReturn>(node->getIdentifier()->as<ASTPresetIdentifierNode*>()->getName(), node->getLine());
    else if (node->getBranch()->hasNode(NodeID::InvokeNested))
        error = std::make_unique<ErrInvokeInvalidContext>(node->getBranch()->findNode({ NodeID::InvokeNested }, {}, true)->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    node->getBranch()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);    
}

void ASTNodeParser::parse(ASTInvokeNestedNode* node)
{
    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

/*
    ASTNodeLinker
*/
void ASTNodeLinker::link(ASTNullNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTBoolNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTIntNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTRangeNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTCoordNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTFloatNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTStringNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTObjectNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTArrayNode<BoolValue>* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTArrayNode<IntValue>* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTArrayNode<RangeValue>* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTArrayNode<CoordValue>* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTArrayNode<FloatValue>* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTArrayNode<StringValue>* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTArrayNode<ObjectValue>* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTDeclarationNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->getNode() != nullptr)
        node->getNode()->accept(*this);

    std::unique_ptr<Error> error;
    auto identifier = node->getIdentifier()->as<ASTIdentifierNode*>();
    if (node->isDeclared(identifier->getName(), NodeID::Identifier, node))
        error = std::make_unique<ErrRedeclaration>(identifier->getName(), identifier->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTIdentifierNode* node)
{
    node->attach(node->getPreviousNode());    

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTVariableNode* node)
{
    node->attach(node->getPreviousNode());

    std::unique_ptr<Error> error;
    node->setIdentifier(node->getNodeByName(node->getName(), NodeID::Identifier));
    if (node->getIdentifier() == nullptr)
        error = std::make_unique<ErrUndeclared>(node->getName(), node->getLine());
    else {
        auto identifier = node->getIdentifier()->as<ASTIdentifierNode*>();
        if ((identifier->getValue() == nullptr) &&
            (identifier->getType() != ValueType::Object) &&
            (identifier->getType() & ValueType::Array) == ValueType::Null
            ) error = std::make_unique<ErrUnassignedVariable>(node->getName(), node->getLine());
    }

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTAnchorNode* node)
{
    node->attach(node->getPreviousNode());

    node->getNode()->accept(*this);

    std::unique_ptr<Error> error;
    if (node->getNode()->getNodeType() != ValueType::Object)
        error = std::make_unique<ErrNotAMemberOf>(KW::Anchor, node->getNode()->getNodeType(), node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTCountNode* node)
{
    node->attach(node->getPreviousNode());

    node->getNode()->accept(*this);

    std::unique_ptr<Error> error;
    if (!Token::isArrayOrObject(node->getNode()->getNodeType()))
        error = std::make_unique<ErrNotAMemberOf>(KW::Count, node->getNode()->getNodeType(), node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTLastNode* node)
{
    node->attach(node->getPreviousNode());

    node->getNode()->accept(*this);

    std::unique_ptr<Error> error;
    if (!Token::isArrayOrObject(node->getNode()->getNodeType()))
        error = std::make_unique<ErrNotAMemberOf>(KW::Last, node->getNode()->getNodeType(), node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTXNode* node)
{
    node->attach(node->getPreviousNode());

    node->getNode()->accept(*this);

    std::unique_ptr<Error> error;
    if (node->getNode()->getNodeType() != ValueType::Coord)
        error = std::make_unique<ErrNotAMemberOf>(std::string_view{ "x" }, node->getNode()->getNodeType(), node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTYNode* node)
{
    node->attach(node->getPreviousNode());

    node->getNode()->accept(*this);

    std::unique_ptr<Error> error;
    if (node->getNode()->getNodeType() != ValueType::Coord)
        error = std::make_unique<ErrNotAMemberOf>(std::string_view{ "y" }, node->getNode()->getNodeType(), node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTRotationNode* node)
{
    node->attach(node->getPreviousNode());

    node->getNode()->accept(*this);

    std::unique_ptr<Error> error;
    if (node->getNode()->getNodeType() != ValueType::Int &&
        node->getNode()->getNodeType() != ValueType::Range &&
        node->getNode()->getNodeType() != ValueType::Coord &&
        node->getNode()->getNodeType() != ValueType::Object
        ) error = std::make_unique<ErrNotAMemberOf>(Token::rotationToString(node->getRotation()), node->getNode()->getNodeType(), node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTEmptyNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTFullNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTIndexNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTNotIndexNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTInsertNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->getNode() != nullptr)
        node->getNode()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTRotateNode* node)
{
    node->attach(node->getPreviousNode());

    node->getNode()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpAssignNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpAddNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpSubtractNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpMultiplyNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpDivideNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpEqualNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpNotEqualNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpGreaterThanNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpGreaterThanOrEqualNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpLessThanNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpLessThanOrEqualNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpAndNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpOrNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpNotNode* node)
{
    node->attach(node->getPreviousNode());

    node->getExpr()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpRangeNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTOpCoordNode* node)
{
    node->attach(node->getPreviousNode());

    node->getLeft()->accept(*this);
    node->getRight()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTErrorNode* node)
{
    node->attach(node->getPreviousNode());

    node->getString()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTWarningNode* node)
{
    node->attach(node->getPreviousNode());

    node->getString()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTAssertNode* node)
{
    node->attach(node->getPreviousNode());

    node->getExpr()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTReturnNode* node)
{
    node->attach(node->getPreviousNode());

    node->setFunction(node->findNode({ NodeID::Function, NodeID::NestedFunction, NodeID::Preset }, {}));

    if (node->getNode() != nullptr)
        node->getNode()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTBreakNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTContinueNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTForRangeNode* node)
{
    node->attach(node->getPreviousNode());

    node->getDeclaration()->accept(*this);
    node->getTo()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTArraySubscriptNode* node)
{
    node->attach(node->getPreviousNode());

    node->getArray()->accept(*this);
    node->getIndex()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTPushCallNode* node)
{
    node->attach(node->getPreviousNode());

    node->getVariable()->accept(*this);
    for (auto&& arg : node->getArguments())
        arg->accept(*this);

    Signature signature;
    for (auto&& arg : node->getArguments())
        signature.addType(arg->getNodeType());

    std::unique_ptr<Error> error;
    Signature signaturePush;
    signaturePush.addType(node->getVariable()->getNodeType());
    if (signaturePush.isVariadicConvertible(signature))
        {} // valid
    else if (!Token::isArray(node->getVariable()->getNodeType()))
        error = std::make_unique<ErrNotAMemberOf>(std::string_view{ "push" }, node->getVariable()->getNodeType(), node->getLine());
    else
        error = std::make_unique<ErrInvalidArguments>("push", node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTHasCallNode* node)
{
    node->attach(node->getPreviousNode());

    node->getVariable()->accept(*this);
    for (auto&& arg : node->getArguments())
        arg->accept(*this);

    Signature signature;
    for (auto&& arg : node->getArguments())
        signature.addType(arg->getNodeType());

    std::unique_ptr<Error> error;
    if ((node->getArguments().size() == 1 && (
            (node->getVariable()->getNodeType() ^ ValueType::Array) == signature.getTypes().front() ||
            Token::isConvertible(node->getVariable()->getNodeType() ^ ValueType::Array, signature.getTypes().front())
            ))
        ) {} // valid
    else if (!Token::isArray(node->getVariable()->getNodeType()))
        error = std::make_unique<ErrNotAMemberOf>(std::string_view{ "has" }, node->getVariable()->getNodeType(), node->getLine());
    else
        error = std::make_unique<ErrInvalidArguments>("has", node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTUniqueCallNode* node)
{
    node->attach(node->getPreviousNode());

    node->getVariable()->accept(*this);

    std::unique_ptr<Error> error;
    if (!node->getArguments().empty())
        error = std::make_unique<ErrInvalidArguments>("unique", node->getLine());
    else if (!Token::isArray(node->getVariable()->getNodeType()))
        error = std::make_unique<ErrNotAMemberOf>(std::string_view{ "unique" }, node->getVariable()->getNodeType(), node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTStrCallNode* node)
{
    node->attach(node->getPreviousNode());

    node->getVariable()->accept(*this);

    std::unique_ptr<Error> error;
    if (!node->getArguments().empty())
        error = std::make_unique<ErrInvalidArguments>("str", node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTNameCallNode* node)
{
    node->attach(node->getPreviousNode());

    node->getVariable()->accept(*this);

    std::unique_ptr<Error> error;
    if (!node->getArguments().empty())
        error = std::make_unique<ErrInvalidArguments>("name", node->getLine());
    else if (node->getVariable()->id() != NodeID::Variable)
        error = std::make_unique<ErrNameCallNotVariable>(node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTFindCallNode* node)
{
    node->attach(node->getPreviousNode());

    node->getVariable()->accept(*this);
    for (auto&& arg : node->getArguments())
        arg->accept(*this);

    Signature signature;
    for (auto&& arg : node->getArguments())
        signature.addType(arg->getNodeType());

    std::unique_ptr<Error> error;
    Signature signatureFind;
    signatureFind.addType(node->getVariable()->getNodeType());
    if (signatureFind.isVariadicConvertible(signature))
        {} // valid
    else if (!Token::isArray(node->getVariable()->getNodeType()))
        error = std::make_unique<ErrNotAMemberOf>(std::string_view{ "find" }, node->getVariable()->getNodeType(), node->getLine());
    else
        error = std::make_unique<ErrInvalidArguments>("find", node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTFunctionCallNode* node)
{
    node->attach(node->getPreviousNode());

    for (auto&& arg : node->getArguments())
        arg->accept(*this);
    
    Signature signature;
    for (auto&& arg : node->getArguments())
        signature.addType(arg->getNodeType());
    node->setSignature(std::move(signature));

    std::unique_ptr<Error> error;
    auto function = node->getNodeBySignature(node->getName(), NodeID::Function, *node->getSignature());
    if (function != nullptr)
        node->setFunction(function);
    else {
        function = node->getConvertibleNodeBySignature(node->getName(), NodeID::Function, *node->getSignature());
        if (function != nullptr)
            node->setFunction(function);
        else {
            function = node->getVariadicConvertibleNodeBySignature(node->getName(), NodeID::Function, *node->getSignature());
            if (function != nullptr)
                node->setFunction(function);
            else
                error = std::make_unique<ErrFunctionSignatureNotFound>(node->getName(), node->getLine());
        }
    }

    for (auto&& nestedCall : node->getNestedCalls())
        nestedCall->accept(*this);

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTNestedCallNode* node)
{
    node->attach(node->getPreviousNode());

    for (auto&& arg : node->getArguments())
        arg->accept(*this);

    Signature signature;
    for (auto&& arg : node->getArguments())
        signature.addType(arg->getNodeType());
    node->setSignature(std::move(signature));

    std::unique_ptr<Error> error;
    auto functionCall = node->getFunctionCall()->as<ASTFunctionCallNode*>();
    if (functionCall->getFunction() != nullptr) {
        auto nested = node->getNodeBySignature(node->getName(), NodeID::NestedFunction, *node->getSignature(), functionCall->getName());
        if (nested != nullptr) {
            auto function = functionCall->getFunction()->as<ASTFunctionNode*>();
            if (function->hasNested(node->getName()))
                node->setNestedFunction(nested);
            else
                error = std::make_unique<ErrNotAMemberOf>(node->getName(), functionCall->getName(), node->getLine());
        }
        else {
            nested = node->getConvertibleNodeBySignature(node->getName(), NodeID::NestedFunction, *node->getSignature(), functionCall->getName());
            if (nested != nullptr)
                node->setNestedFunction(nested);
            else {
                nested = node->getVariadicConvertibleNodeBySignature(node->getName(), NodeID::NestedFunction, *node->getSignature(), functionCall->getName());
                if (nested != nullptr)
                    node->setNestedFunction(nested);
                else
                    error = std::make_unique<ErrNestedSignatureNotFound>(node->getName(), node->getLine());
            }
        }
    }
    else
        error = std::make_unique<ErrNotAMemberOf>(node->getName(), functionCall->getName(), node->getLine());

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTPresetCallNode* node)
{
    node->attach(node->getPreviousNode());

    for (auto&& arg : node->getArguments())
        arg->accept(*this);

    Signature signature;
    for (auto&& arg : node->getArguments())
        signature.addType(arg->getNodeType());
    node->setSignature(std::move(signature));

    std::unique_ptr<Error> error;
    auto preset = node->getNodeBySignature(node->getName(), NodeID::Preset, *node->getSignature());
    if (preset != nullptr)
        node->setPreset(preset);
    else {
        preset = node->getConvertibleNodeBySignature(node->getName(), NodeID::Preset, *node->getSignature());
        if (preset != nullptr)
            node->setPreset(preset);
        else {
            preset = node->getVariadicConvertibleNodeBySignature(node->getName(), NodeID::Preset, *node->getSignature());
            if (preset != nullptr)
                node->setPreset(preset);
            else
                error = std::make_unique<ErrPresetSignatureNotFound>(node->getName(), node->getLine());
        }
    }

    if (error != nullptr)
        errors().push(std::move(error));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTForNode* node)
{
    node->attach(node->getPreviousNode());

    node->getRange()->accept(*this);
    node->getBranch()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTIfNode* node)
{
    node->attach(node->getPreviousNode());

    node->getCondition()->accept(*this);
    node->getBranch()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTFunctionIdentifierNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTFunctionNode* node)
{
    node->attach(node->getPreviousNode());

    Signature signature;
    for (auto&& arg : node->getArguments())
        signature.addType(arg->getNodeType());
    node->setSignature(std::move(signature));

    std::unique_ptr<Error> error;
    auto identifier = node->getIdentifier()->as<ASTFunctionIdentifierNode*>();
    if (node->isDeclared(identifier->getName(), NodeID::Function, node, *node->getSignature()))
        error = std::make_unique<ErrRedeclaration>(identifier->getName(), identifier->getLine());

    if (error == nullptr) {
        if (!node->getArguments().empty()) {
            std::vector<std::string> arguments;
            for (auto&& arg : node->getArguments())
                arguments.push_back(arg->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>()->getName());

            std::sort(arguments.begin(), arguments.end());
            auto duplicate = std::adjacent_find(arguments.begin(), arguments.end());
            if (duplicate == arguments.end()) {
                for (auto&& arg : node->getArguments())
                    arg->accept(*this);
            }
            else
                error = std::make_unique<ErrRedeclaration>(*duplicate, node->getArguments()[std::distance(arguments.begin(), duplicate)]->as<ASTDeclarationNode*>()->getIdentifier()->getLine());
        }
    }

    if (error == nullptr) {
        if (!node->getNestedIdentifiers().empty()) {
            std::vector<std::string> nestedIdentifiers;
            for (auto&& nested_identifier : node->getNestedIdentifiers())
                nestedIdentifiers.push_back(nested_identifier->as<ASTNestedIdentifierNode*>()->getName());

            std::sort(nestedIdentifiers.begin(), nestedIdentifiers.end());
            auto duplicate = std::adjacent_find(nestedIdentifiers.begin(), nestedIdentifiers.end());
            if (duplicate != nestedIdentifiers.end())
                error = std::make_unique<ErrRedeclaration>(*duplicate, node->getNestedIdentifiers()[std::distance(nestedIdentifiers.begin(), duplicate)]->getLine());
        }
    }

    if (error != nullptr)
        errors().push(std::move(error));
    else
        node->getBranch()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTNestedIdentifierNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTNestedFunctionNode* node)
{
    node->attach(node->getPreviousNode());

    Signature signature;
    for (auto&& arg : node->getArguments())
        signature.addType(arg->getNodeType());
    node->setSignature(std::move(signature));

    std::unique_ptr<Error> error;
    auto identifier = node->getIdentifier()->as<ASTNestedIdentifierNode*>();
    if (node->isDeclared(identifier->getName(), NodeID::NestedFunction, node))
        error = std::make_unique<ErrRedeclaration>(identifier->getName(), identifier->getLine());
    else {
        auto functionIdentifier = node->getFunctionIdentifier()->as<ASTFunctionIdentifierNode*>();
        auto function = node->getNodeByName(functionIdentifier->getName(), NodeID::Function)->as<ASTFunctionNode*>();
        if (function != nullptr) {
            functionIdentifier->setFunction(function);
            if (!function->hasNested(identifier->getName()))
                error = std::make_unique<ErrNotAMemberOf>(identifier->getName(), functionIdentifier->getName(), identifier->getLine());
            else if (function->getReturnType() != node->getReturnType())
                error = std::make_unique<ErrNestedDifferentReturnType>(identifier->getName(), function->getReturnType(), identifier->getLine());
            else
                function->getNested(identifier->getName())->as<ASTNestedIdentifierNode*>()->setNestedFunction(node);
        }
        else
            error = std::make_unique<ErrUndeclared>(functionIdentifier->getName(), functionIdentifier->getLine());

        if (error == nullptr) {
            if (!node->getArguments().empty()) {
                std::vector<std::string> arguments;
                for (auto&& arg : node->getArguments())
                    arguments.push_back(arg->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>()->getName());

                std::sort(arguments.begin(), arguments.end());
                auto duplicate = std::adjacent_find(arguments.begin(), arguments.end());
                if (duplicate == arguments.end()) {
                    for (auto&& arg : node->getArguments())
                        arg->accept(*this);
                }
                else
                    error = std::make_unique<ErrRedeclaration>(*duplicate, node->getArguments()[std::distance(arguments.begin(), duplicate)]->as<ASTDeclarationNode*>()->getIdentifier()->getLine());
            }
        }
    }

    if (error != nullptr)
        errors().push(std::move(error));
    else
        node->getBranch()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTPresetIdentifierNode* node)
{
    node->attach(node->getPreviousNode());

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTPresetNode* node)
{
    node->attach(node->getPreviousNode());

    Signature signature;
    for (auto&& arg : node->getArguments())
        signature.addType(arg->getNodeType());
    node->setSignature(std::move(signature));

    std::unique_ptr<Error> error;
    auto identifier = node->getIdentifier()->as<ASTPresetIdentifierNode*>();
    if (node->isDeclared(identifier->getName(), NodeID::Preset, node, *node->getSignature()))
        error = std::make_unique<ErrRedeclaration>(identifier->getName(), identifier->getLine());

    if (error == nullptr) {
        if (!node->getArguments().empty()) {
            std::vector<std::string> arguments;
            for (auto&& arg : node->getArguments())
                arguments.push_back(arg->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>()->getName());

            std::sort(arguments.begin(), arguments.end());
            auto duplicate = std::adjacent_find(arguments.begin(), arguments.end());
            if (duplicate == arguments.end()) {
                for (auto&& arg : node->getArguments())
                    arg->accept(*this);
            }
            else
                error = std::make_unique<ErrRedeclaration>(*duplicate, node->getArguments()[std::distance(arguments.begin(), duplicate)]->as<ASTDeclarationNode*>()->getIdentifier()->getLine());
        }
    }

    if (error != nullptr)
        errors().push(std::move(error));
    else 
        node->getBranch()->accept(*this);

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

void ASTNodeLinker::link(ASTInvokeNestedNode* node)
{
    node->attach(node->getPreviousNode());

    node->setFunction(node->findNode({ NodeID::Function }, {}));

    if (node->hasNextNode())
        node->getNextNode()->accept(*this);
}

std::unique_ptr<Error> ASTNodeParser::parseType(ValueType left, ValueType right, uint32_t line) const
{
    if (right == ValueType::Null)
        return std::make_unique<ErrIncorrectValueType>(right, left, line);
    else if (right != left && !Token::isConvertible(right, left))
        return std::make_unique<ErrIncorrectValueType>(right, left, line);
    return nullptr;
}

/*
    ASTNodeEvaluator
*/
Value* ASTNodeEvaluator::evaluate(ASTNullNode* node)
{
    _TryEvaluateNextNode;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTBoolNode* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTIntNode* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTRangeNode* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTCoordNode* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTFloatNode* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTStringNode* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTObjectNode* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTArrayNode<BoolValue>* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTArrayNode<IntValue>* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTArrayNode<RangeValue>* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTArrayNode<CoordValue>* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTArrayNode<FloatValue>* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTArrayNode<StringValue>* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTArrayNode<ObjectValue>* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTDeclarationNode* node)
{
    if (node->getNode() != nullptr) {
        _StackInit;
        auto value = node->getNode()->accept(*this); _BreakIfFailed;
        auto identifier = node->getIdentifier()->as<ASTIdentifierNode*>();
        identifier->setValue(cast(value, identifier->getNodeType()));

        _StackPop;
    }
    else
        node->getIdentifier()->as<ASTIdentifierNode*>()->getValue()->reset();

    _TryEvaluateNextNode;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTIdentifierNode* node)
{
    _TryEvaluateNextNode;
    return node->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTVariableNode* node)
{
    _TryEvaluateNextNode;
    return node->getIdentifier()->as<ASTIdentifierNode*>()->getValue();
}

Value* ASTNodeEvaluator::evaluate(ASTAnchorNode* node)
{
    _StackInit;
    ObjectValue* object = node->getNode()->accept(*this)->as<ObjectValue*>(); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    return &object->anchor;
}

Value* ASTNodeEvaluator::evaluate(ASTCountNode* node)
{
    _StackInit;
    Value* value = node->getNode()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    return &value->as<Container*>()->count;
}

Value* ASTNodeEvaluator::evaluate(ASTLastNode* node)
{
    _StackInit;
    Value* value = node->getNode()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    return &value->as<Container*>()->last;
}

Value* ASTNodeEvaluator::evaluate(ASTXNode* node)
{
    _StackInit;
    Value* value = node->getNode()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    return &value->as<CoordValue*>()->x;
}

Value* ASTNodeEvaluator::evaluate(ASTYNode* node)
{
    _StackInit;
    Value* value = node->getNode()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    return &value->as<CoordValue*>()->y;
}

Value* ASTNodeEvaluator::evaluate(ASTRotationNode* node)
{
    _StackInit;
    Value* value = node->getNode()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;    
    ptr_value result = value->clone();
    rotate(result.get(), node->getRotation());

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate([[maybe_unused]] ASTEmptyNode* node)
{
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate([[maybe_unused]] ASTFullNode* node)
{
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate([[maybe_unused]] ASTIndexNode* node)
{
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate([[maybe_unused]] ASTNotIndexNode* node)
{
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTInsertNode* node)
{
    _StackInit;
    auto control = node->getControl();
    auto valueNode = node->getNode();

    if (valueNode != nullptr) {
        if (control == InsertC::InsertRulePosType)
            insertPosType(node->getLine(), valueNode->id());
        else {
            Value* value = valueNode->accept(*this); _BreakIfFailed;
            insert(control, value, node->getLine());
        }
    }
    else
        insert(control, nullptr, node->getLine());


    _TryEvaluateNextNodeAndClearStack;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTRotateNode* node)
{
    _StackInit;
    Value* value = node->getNode()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result = std::make_unique<BoolValue>(hasRotation(value, node->getRotation()));

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpAssignNode* node)
{
    _StackInit;
    auto leftID = node->getLeft()->id();

    Value* left;
    Value* right = node->getRight()->accept(*this); _BreakIfFailed;

    if (leftID == NodeID::Variable) {
        auto identifier = node->getLeft()->as<ASTVariableNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
        identifier->setValue(cast(right, identifier->getNodeType()));
    }
    else if (leftID == NodeID::ArraySubscript && node->getLeft()->as<ASTArraySubscriptNode*>()->getArray()->id() == NodeID::Variable) {
        left = node->getLeft()->accept(*this); _BreakIfFailed;

        ptr_value value = cast(right, left->type());
        if (left->type() == ValueType::Bool) {
            left->as<BoolValue*>()->value = value->as<BoolValue*>()->value;
        }
        else if (left->type() == ValueType::Int) {
            left->as<IntValue*>()->value = value->as<IntValue*>()->value;
            left->as<IntValue*>()->rotation = value->as<IntValue*>()->rotation;
        }
        else if (left->type() == ValueType::Range) {
            left->as<RangeValue*>()->from = value->as<RangeValue*>()->from;
            left->as<RangeValue*>()->to = value->as<RangeValue*>()->to;
            left->as<RangeValue*>()->rotation = value->as<RangeValue*>()->rotation;
        }
        else if (left->type() == ValueType::Coord) {
            left->as<CoordValue*>()->x = value->as<CoordValue*>()->x;
            left->as<CoordValue*>()->y = value->as<CoordValue*>()->y;
            left->as<CoordValue*>()->rotation = value->as<CoordValue*>()->rotation;
        }
        else if (left->type() == ValueType::Float) {
            left->as<FloatValue*>()->value = value->as<FloatValue*>()->value;
        }
        else if (left->type() == ValueType::String) {
            left->as<StringValue*>()->value = value->as<StringValue*>()->value;
        }
        else { // left->type() == ValueType::Object
            left->as<ObjectValue*>()->value = value->as<ObjectValue*>()->value;
            left->as<ObjectValue*>()->rotation = value->as<ObjectValue*>()->rotation;
            left->as<ObjectValue*>()->anchor = value->as<ObjectValue*>()->anchor;
            left->as<ObjectValue*>()->count = value->as<ObjectValue*>()->count;
            left->as<ObjectValue*>()->last = value->as<ObjectValue*>()->last;
        }
    }
    else {
        if (leftID == NodeID::X || leftID == NodeID::Y) {
            auto value = cast(right, ValueType::Int)->as<IntValue*>()->value;

            left = node->getLeft()->accept(*this); _BreakIfFailed;
            left->as<IntValue*>()->value = value;
        }
        else {
            left = node->getLeft()->accept(*this); _BreakIfFailed;
        }
    }

    _TryEvaluateNextNodeAndClearStack;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTOpAddNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;
    Value* right = node->getRight()->accept(*this); _BreakIfFailed;

    auto leftType = left->type();
    auto rightType = right->type();

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result;
    if (leftType == ValueType::Int && rightType == ValueType::Int)
        result = std::make_unique<IntValue>(*left->as<IntValue*>() + *right->as<IntValue*>());
    else if (leftType == ValueType::String)
        result = std::make_unique<StringValue>(*left->as<StringValue*>() + *right->as<StringValue*>());
    else {
        if (leftType == ValueType::Int)
            result = std::make_unique<FloatValue>(left->as<IntValue*>()->toFloat() + *right->as<FloatValue*>());
        else if (rightType == ValueType::Int)
            result = std::make_unique<FloatValue>(*left->as<FloatValue*>() + right->as<IntValue*>()->toFloat());
        else
            result = std::make_unique<FloatValue>(*left->as<FloatValue*>() + *right->as<FloatValue*>());
    }

    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpSubtractNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;
    Value* right = node->getRight()->accept(*this); _BreakIfFailed;

    auto leftType = left->type();
    auto rightType = right->type();

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result;
    if (leftType == ValueType::Int && rightType == ValueType::Int)
        result = std::make_unique<IntValue>(*left->as<IntValue*>() - *right->as<IntValue*>());
    else {
        if (leftType == ValueType::Int)
            result = std::make_unique<FloatValue>(left->as<IntValue*>()->toFloat() - *right->as<FloatValue*>());
        else if (rightType == ValueType::Int)
            result = std::make_unique<FloatValue>(*left->as<FloatValue*>() - right->as<IntValue*>()->toFloat());
        else
            result = std::make_unique<FloatValue>(*left->as<FloatValue*>() - *right->as<FloatValue*>());
    }
    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpMultiplyNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;
    Value* right = node->getRight()->accept(*this); _BreakIfFailed;

    auto leftType = left->type();
    auto rightType = right->type();

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result;
    if (leftType == ValueType::Int && rightType == ValueType::Int)
        result = std::make_unique<IntValue>(*left->as<IntValue*>() * *right->as<IntValue*>());
    else {
        if (leftType == ValueType::Int)
            result = std::make_unique<FloatValue>(left->as<IntValue*>()->toFloat() * *right->as<FloatValue*>());
        else if (rightType == ValueType::Int)
            result = std::make_unique<FloatValue>(*left->as<FloatValue*>() * right->as<IntValue*>()->toFloat());
        else
            result = std::make_unique<FloatValue>(*left->as<FloatValue*>() * *right->as<FloatValue*>());
    }
    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpDivideNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;
    Value* right = node->getRight()->accept(*this); _BreakIfFailed;

    auto leftType = left->type();
    auto rightType = right->type();

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result;
    if (leftType == ValueType::Int && rightType == ValueType::Int)
        result = std::make_unique<IntValue>(*left->as<IntValue*>() / *right->as<IntValue*>());
    else {
        if (leftType == ValueType::Int)
            result = std::make_unique<FloatValue>(left->as<IntValue*>()->toFloat() / *right->as<FloatValue*>());
        else if (rightType == ValueType::Int)
            result = std::make_unique<FloatValue>(*left->as<FloatValue*>() / right->as<IntValue*>()->toFloat());
        else
            result = std::make_unique<FloatValue>(*left->as<FloatValue*>() / *right->as<FloatValue*>());
    }
    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpEqualNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;
    Value* right = node->getRight()->accept(*this); _BreakIfFailed;

    auto leftType = left->type();
    auto rightType = right->type();

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result;
    if (leftType == ValueType::Bool)
        result = std::make_unique<BoolValue>(*left->as<BoolValue*>() == *right->as<BoolValue*>());
    else if (leftType == ValueType::Int) {
        if (rightType == ValueType::Int)
            result = std::make_unique<BoolValue>(*left->as<IntValue*>() == *right->as<IntValue*>());
        else if (rightType == ValueType::Float)
            result = std::make_unique<BoolValue>(*cast(left, ValueType::Float)->as<FloatValue*>() == *right->as<FloatValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<IntValue*>() == *cast(right, ValueType::Int)->as<IntValue*>());
    }
    else if (leftType == ValueType::Range) {
        if (rightType == ValueType::Range)
            result = std::make_unique<BoolValue>(*left->as<RangeValue*>() == *right->as<RangeValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<RangeValue*>() == *cast(right, ValueType::Range)->as<RangeValue*>());
    }
    else if (leftType == ValueType::Coord) {
        if (rightType == ValueType::Coord)
            result = std::make_unique<BoolValue>(*left->as<CoordValue*>() == *right->as<CoordValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<CoordValue*>() == *cast(right, ValueType::Coord)->as<CoordValue*>());
    }
    else if (leftType == ValueType::Float) {
        if (rightType == ValueType::Float)
            result = std::make_unique<BoolValue>(*left->as<FloatValue*>() == *right->as<FloatValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<FloatValue*>() == *cast(right, ValueType::Float)->as<FloatValue*>());
    }
    else if (leftType == ValueType::String)
        result = std::make_unique<BoolValue>(*left->as<StringValue*>() == *right->as<StringValue*>());
    else if (leftType == ValueType::Object) {
        if (rightType == ValueType::Object)
            result = std::make_unique<BoolValue>(*left->as<ObjectValue*>() == *right->as<ObjectValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<ObjectValue*>() == *cast(right, ValueType::Object)->as<ObjectValue*>());
    }
    else if (leftType == ValueType::ArrayBool)
        result = std::make_unique<BoolValue>(*left->as<ArrayValue<BoolValue>*>() == *right->as<ArrayValue<BoolValue>*>());
    else if (leftType == ValueType::ArrayInt)
        result = std::make_unique<BoolValue>(*left->as<ArrayValue<IntValue>*>() == *right->as<ArrayValue<IntValue>*>());
    else if (leftType == ValueType::ArrayRange)
        result = std::make_unique<BoolValue>(*left->as<ArrayValue<RangeValue>*>() == *right->as<ArrayValue<RangeValue>*>());
    else if (leftType == ValueType::ArrayCoord)
        result = std::make_unique<BoolValue>(*left->as<ArrayValue<CoordValue>*>() == *right->as<ArrayValue<CoordValue>*>());
    else if (leftType == ValueType::ArrayFloat)
        result = std::make_unique<BoolValue>(*left->as<ArrayValue<FloatValue>*>() == *right->as<ArrayValue<FloatValue>*>());
    else if (leftType == ValueType::ArrayString)
        result = std::make_unique<BoolValue>(*left->as<ArrayValue<StringValue>*>() == *right->as<ArrayValue<StringValue>*>());
    else
        result = std::make_unique<BoolValue>(*left->as<ArrayValue<ObjectValue>*>() == *right->as<ArrayValue<ObjectValue>*>());

    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpNotEqualNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;
    Value* right = node->getRight()->accept(*this); _BreakIfFailed;

    auto leftType = left->type();
    auto rightType = right->type();

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result;
    if (leftType == ValueType::Bool)
        result = std::make_unique<BoolValue>(*left->as<BoolValue*>() != *right->as<BoolValue*>());
    else if (leftType == ValueType::Int) {
        if (rightType == ValueType::Int)
            result = std::make_unique<BoolValue>(*left->as<IntValue*>() != *right->as<IntValue*>());
        else if (rightType == ValueType::Float)
            result = std::make_unique<BoolValue>(*cast(left, ValueType::Float)->as<FloatValue*>() != *right->as<FloatValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<IntValue*>() != *cast(right, ValueType::Int)->as<IntValue*>());
    }
    else if (leftType == ValueType::Range) {
        if (rightType == ValueType::Range)
            result = std::make_unique<BoolValue>(*left->as<RangeValue*>() != *right->as<RangeValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<RangeValue*>() != *cast(right, ValueType::Range)->as<RangeValue*>());
    }
    else if (leftType == ValueType::Coord) {
        if (rightType == ValueType::Coord)
            result = std::make_unique<BoolValue>(*left->as<CoordValue*>() != *right->as<CoordValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<CoordValue*>() != *cast(right, ValueType::Coord)->as<CoordValue*>());
    }
    else if (leftType == ValueType::Float) {
        if (rightType == ValueType::Float)
            result = std::make_unique<BoolValue>(*left->as<FloatValue*>() != *right->as<FloatValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<FloatValue*>() != *cast(right, ValueType::Float)->as<FloatValue*>());
    }
    else if (leftType == ValueType::String)
        result = std::make_unique<BoolValue>(*left->as<StringValue*>() != *right->as<StringValue*>());
    else if (leftType == ValueType::Object) {
        if (rightType == ValueType::Object)
            result = std::make_unique<BoolValue>(*left->as<ObjectValue*>() != *right->as<ObjectValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<ObjectValue*>() != *cast(right, ValueType::Object)->as<ObjectValue*>());
    }
    else if (leftType == ValueType::ArrayBool)
        result = std::make_unique<BoolValue>(*left->as<ArrayValue<BoolValue>*>() != *right->as<ArrayValue<BoolValue>*>());
    else if (leftType == ValueType::ArrayInt)
        result = std::make_unique<BoolValue>(*left->as<ArrayValue<IntValue>*>() != *right->as<ArrayValue<IntValue>*>());
    else if (leftType == ValueType::ArrayRange)
        result = std::make_unique<BoolValue>(*left->as<ArrayValue<RangeValue>*>() != *right->as<ArrayValue<RangeValue>*>());
    else if (leftType == ValueType::ArrayCoord)
        result = std::make_unique<BoolValue>(*left->as<ArrayValue<CoordValue>*>() != *right->as<ArrayValue<CoordValue>*>());
    else if (leftType == ValueType::ArrayFloat)

        result = std::make_unique<BoolValue>(*left->as<ArrayValue<FloatValue>*>() != *right->as<ArrayValue<FloatValue>*>());
    else if (leftType == ValueType::ArrayString)
        result = std::make_unique<BoolValue>(*left->as<ArrayValue<StringValue>*>() != *right->as<ArrayValue<StringValue>*>());
    else
        result = std::make_unique<BoolValue>(*left->as<ArrayValue<ObjectValue>*>() != *right->as<ArrayValue<ObjectValue>*>());

    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpGreaterThanNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;
    Value* right = node->getRight()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result;
    if (left->type() == ValueType::Int) {
        if (right->type() == ValueType::Int)
            result = std::make_unique<BoolValue>(*left->as<IntValue*>() > *right->as<IntValue*>());
        else
            result = std::make_unique<BoolValue>(*cast(left, ValueType::Float)->as<FloatValue*>() > *right->as<FloatValue*>());
    }
    else {
        if (right->type() == ValueType::Float)
            result = std::make_unique<BoolValue>(*left->as<FloatValue*>() > *right->as<FloatValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<FloatValue*>() > *cast(right, ValueType::Float)->as<FloatValue*>());
    }
    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpGreaterThanOrEqualNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;
    Value* right = node->getRight()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result;
    if (left->type() == ValueType::Int) {
        if (right->type() == ValueType::Int)
            result = std::make_unique<BoolValue>(*left->as<IntValue*>() >= *right->as<IntValue*>());
        else
            result = std::make_unique<BoolValue>(*cast(left, ValueType::Float)->as<FloatValue*>() >= *right->as<FloatValue*>());
    }
    else {
        if (right->type() == ValueType::Float)
            result = std::make_unique<BoolValue>(*left->as<FloatValue*>() >= *right->as<FloatValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<FloatValue*>() >= *cast(right, ValueType::Float)->as<FloatValue*>());
    }
    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpLessThanNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;
    Value* right = node->getRight()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result;
    if (left->type() == ValueType::Int) {
        if (right->type() == ValueType::Int)
            result = std::make_unique<BoolValue>(*left->as<IntValue*>() < *right->as<IntValue*>());
        else
            result = std::make_unique<BoolValue>(*cast(left, ValueType::Float)->as<FloatValue*>() < *right->as<FloatValue*>());
    }
    else {
        if (right->type() == ValueType::Float)
            result = std::make_unique<BoolValue>(*left->as<FloatValue*>() < *right->as<FloatValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<FloatValue*>() < *cast(right, ValueType::Float)->as<FloatValue*>());
    }
    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpLessThanOrEqualNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;
    Value* right = node->getRight()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result;
    if (left->type() == ValueType::Int) {
        if (right->type() == ValueType::Int)
            result = std::make_unique<BoolValue>(*left->as<IntValue*>() <= *right->as<IntValue*>());
        else
            result = std::make_unique<BoolValue>(*cast(left, ValueType::Float)->as<FloatValue*>() <= *right->as<FloatValue*>());
    }
    else {
        if (right->type() == ValueType::Float)
            result = std::make_unique<BoolValue>(*left->as<FloatValue*>() <= *right->as<FloatValue*>());
        else
            result = std::make_unique<BoolValue>(*left->as<FloatValue*>() <= *cast(right, ValueType::Float)->as<FloatValue*>());
    }
    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpAndNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;

    ptr_value result;
    if (left->as<BoolValue*>()->value) {
        Value* right = node->getRight()->accept(*this); _BreakIfFailed;
        if (right->as<BoolValue*>()->value)
            result = std::make_unique<BoolValue>(true);
        else
            result = std::make_unique<BoolValue>(false);
    }
    else
        result = std::make_unique<BoolValue>(false);

    _TryEvaluateNextNodeAndClearStack;
    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpOrNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;

    ptr_value result;
    if (!left->as<BoolValue*>()->value) {
        Value* right = node->getRight()->accept(*this); _BreakIfFailed;
        if (right->as<BoolValue*>()->value)
            result = std::make_unique<BoolValue>(true);
        else
            result = std::make_unique<BoolValue>(false);
    }
    else
        result = std::make_unique<BoolValue>(true);

    _TryEvaluateNextNodeAndClearStack;
    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpNotNode* node)
{
    _StackInit;
    Value* value = node->getExpr()->accept(*this); _BreakIfFailed;

    ptr_value result = std::make_unique<BoolValue>(!value->as<BoolValue*>()->value);

    _TryEvaluateNextNodeAndClearStack;
    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpRangeNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;
    Value* right = node->getRight()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result = std::make_unique<RangeValue>(left->as<IntValue*>()->value, right->as<IntValue*>()->value);
    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTOpCoordNode* node)
{
    _StackInit;
    Value* left = node->getLeft()->accept(*this); _BreakIfFailed;
    Value* right = node->getRight()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result = std::make_unique<CoordValue>(left->as<IntValue*>()->value, right->as<IntValue*>()->value);
    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTErrorNode* node)
{
    _StackInit;
    Value* message = node->getString()->accept(*this); _BreakIfFailed;
    printError(message->as<StringValue*>()->value, node->getLine());

    _StackPop;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTWarningNode* node)
{
    _StackInit;
    Value* message = node->getString()->accept(*this); _BreakIfFailed;
    printWarning(message->as<StringValue*>()->value, node->getLine());

    _TryEvaluateNextNodeAndClearStack;
    _StackPop;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTAssertNode* node)
{
    _StackInit;
    Value* result = node->getExpr()->accept(*this); _BreakIfFailed;
    
    if (!result->as<BoolValue*>()->value)
        printAssert(node->getLine());
    else {
        _TryEvaluateNextNodeAndClearStack;
    }

    _StackPop;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTReturnNode* node)
{
    if (node->getNode() == nullptr) {
        m_returned = true;
        return nullptr;
    }

    Value* returnValue = node->getNode()->accept(*this); _BreakIfFailed;

    m_returned = true;

    ptr_value result = cast(returnValue, node->getNodeType());

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate([[maybe_unused]] ASTBreakNode* node)
{
    m_break = true;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate([[maybe_unused]] ASTContinueNode* node)
{
    m_continue = true;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTForRangeNode* node)
{
    _StackInit;
    node->getDeclaration()->accept(*this); _BreakIfFailed;

    Value* forFrom = node->getDeclaration()->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>()->getValue();
    Value* forTo = node->getTo()->accept(*this); _BreakIfFailed;

    ptr_value result = std::make_unique<RangeValue>(forFrom->as<IntValue*>()->value, forTo->as<IntValue*>()->value);
    _StackPop;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTArraySubscriptNode* node)
{
    _StackInit;
    Value* array = node->getArray()->accept(*this); _BreakIfFailed;
    Value* index = node->getIndex()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    return array->as<Array*>()->at(index->as<IntValue*>()->value);
}

Value* ASTNodeEvaluator::evaluate(ASTPushCallNode* node)
{
    _StackInit;
    auto identifier = node->getVariable()->as<ASTVariableNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
    auto tempIdentifier = std::make_unique<ASTIdentifierNode>();
    tempIdentifier->setType(identifier->getType());
    tempIdentifier->setValue(identifier->getValue()->makeNew());

    evaluateArgumentsVariadic(node->getArguments(), tempIdentifier.get()); _BreakIfFailed;

    auto value = identifier->getValue();
    ValueType type = value->type();
    if (type == ValueType::ArrayBool)
        value->as<ArrayValue<BoolValue>*>()->push(tempIdentifier->getValue()->as<ArrayValue<BoolValue>*>());
    else if (type == ValueType::ArrayInt)
        value->as<ArrayValue<IntValue>*>()->push(tempIdentifier->getValue()->as<ArrayValue<IntValue>*>());
    else if (type == ValueType::ArrayRange)
        value->as<ArrayValue<RangeValue>*>()->push(tempIdentifier->getValue()->as<ArrayValue<RangeValue>*>());
    else if (type == ValueType::ArrayCoord)
        value->as<ArrayValue<CoordValue>*>()->push(tempIdentifier->getValue()->as<ArrayValue<CoordValue>*>());
    else if (type == ValueType::ArrayFloat)
        value->as<ArrayValue<FloatValue>*>()->push(tempIdentifier->getValue()->as<ArrayValue<FloatValue>*>());
    else if (type == ValueType::ArrayString)
        value->as<ArrayValue<StringValue>*>()->push(tempIdentifier->getValue()->as<ArrayValue<StringValue>*>());
    else
        value->as<ArrayValue<ObjectValue>*>()->push(tempIdentifier->getValue()->as<ArrayValue<ObjectValue>*>());

    _TryEvaluateNextNodeAndClearStack;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTHasCallNode* node)
{
    _StackInit;
    auto identifierValue = node->getVariable()->as<ASTVariableNode*>()->getIdentifier()->as<ASTIdentifierNode*>()->getValue();
    auto value = node->getArguments().front()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;

    auto type = identifierValue->type();

    ptr_value result;
    if (type == ValueType::ArrayBool)
        result = std::make_unique<BoolValue>(identifierValue->as<ArrayValue<BoolValue>*>()->has(*value->as<BoolValue*>()));
    else if (type == ValueType::ArrayInt)
        result = std::make_unique<BoolValue>(identifierValue->as<ArrayValue<IntValue>*>()->has(*value->as<IntValue*>()));
    else if (type == ValueType::ArrayRange)
        result = std::make_unique<BoolValue>(identifierValue->as<ArrayValue<RangeValue>*>()->has(*value->as<RangeValue*>()));
    else if (type == ValueType::ArrayCoord)
        result = std::make_unique<BoolValue>(identifierValue->as<ArrayValue<CoordValue>*>()->has(*value->as<CoordValue*>()));
    else if (type == ValueType::ArrayFloat)
        result = std::make_unique<BoolValue>(identifierValue->as<ArrayValue<FloatValue>*>()->has(*value->as<FloatValue*>()));
    else if (type == ValueType::ArrayString)
        result = std::make_unique<BoolValue>(identifierValue->as<ArrayValue<StringValue>*>()->has(*value->as<StringValue*>()));
    else
        result = std::make_unique<BoolValue>(identifierValue->as<ArrayValue<ObjectValue>*>()->has(*value->as<ObjectValue*>()));

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTUniqueCallNode* node)
{
    _StackInit;
    auto value = node->getVariable()->accept(*this); _BreakIfFailed;
    
    _TryEvaluateNextNodeAndClearStack;
    ptr_value result = value->clone();
    result->as<Array*>()->unique();

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTStrCallNode* node)
{
    _StackInit;
    auto value = node->getVariable()->accept(*this); _BreakIfFailed;

    _TryEvaluateNextNodeAndClearStack;
    ptr_value result = std::make_unique<StringValue>(value->str());

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTNameCallNode* node)
{
    _StackInit;

    ptr_value result = std::make_unique<StringValue>(node->getVariable()->as<ASTVariableNode*>()->getName());
    _TryEvaluateNextNodeAndClearStack;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTFindCallNode* node)
{
    _StackInit;
    auto identifier = node->getVariable()->as<ASTVariableNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
    auto tempIdentifier = std::make_unique<ASTIdentifierNode>();
    tempIdentifier->setType(identifier->getType());
    tempIdentifier->setValue(identifier->getValue()->makeNew());

    evaluateArgumentsVariadic(node->getArguments(), tempIdentifier.get()); _BreakIfFailed;

    auto value = identifier->getValue();
    ptr_value result;
    ValueType type = value->type();
    if (type == ValueType::ArrayBool)
        result = std::make_unique<IntValue>(value->as<ArrayValue<BoolValue>*>()->find(tempIdentifier->getValue()->as<ArrayValue<BoolValue>*>()));
    else if (type == ValueType::ArrayInt)
        result = std::make_unique<IntValue>(value->as<ArrayValue<IntValue>*>()->find(tempIdentifier->getValue()->as<ArrayValue<IntValue>*>()));
    else if (type == ValueType::ArrayRange)
        result = std::make_unique<IntValue>(value->as<ArrayValue<RangeValue>*>()->find(tempIdentifier->getValue()->as<ArrayValue<RangeValue>*>()));
    else if (type == ValueType::ArrayCoord)
        result = std::make_unique<IntValue>(value->as<ArrayValue<CoordValue>*>()->find(tempIdentifier->getValue()->as<ArrayValue<CoordValue>*>()));
    else if (type == ValueType::ArrayFloat)
        result = std::make_unique<IntValue>(value->as<ArrayValue<FloatValue>*>()->find(tempIdentifier->getValue()->as<ArrayValue<FloatValue>*>()));
    else if (type == ValueType::ArrayString)
        result = std::make_unique<IntValue>(value->as<ArrayValue<StringValue>*>()->find(tempIdentifier->getValue()->as<ArrayValue<StringValue>*>()));
    else
        result = std::make_unique<IntValue>(value->as<ArrayValue<ObjectValue>*>()->find(tempIdentifier->getValue()->as<ArrayValue<ObjectValue>*>()));

    _TryEvaluateNextNodeAndClearStack;

    _StackPush(result);
    return _StackTop;
}

Value* ASTNodeEvaluator::evaluate(ASTFunctionCallNode* node)
{
    _StackInit;
    auto function = node->getFunction()->as<ASTFunctionNode*>();
    bool hasNestedCalls = !node->getNestedCalls().empty();
    if (hasNestedCalls)
        m_calls.push_back(node);

    if (!function->getArguments().empty()) {
        if (function->getSignature()->isVariadic()) {
            auto identifier = function->getArguments().front()->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
            evaluateArgumentsVariadic(node->getArguments(), identifier); _BreakIfFailed;
        }
        else {
            evaluateArguments(node->getArguments(), function->getArguments()); _BreakIfFailed;
        }
    }
    _StackPop;

    Value* result = nullptr;
    if (function->getBranch()->hasNextNode()) {
        result = function->getBranch()->getNextNode()->accept(*this); m_returned = false; _BreakIfFailed;
    }

    if (hasNestedCalls)
        m_calls.pop_back();
    _TryEvaluateNextNodeAndClearStack;

    return result;
}

Value* ASTNodeEvaluator::evaluate(ASTNestedCallNode* node)
{
    _StackInit;
    auto nested = node->getNestedFunction()->as<ASTNestedFunctionNode*>();

    if (!nested->getArguments().empty()) {
        if (nested->getSignature()->isVariadic()) {
            auto identifier = nested->getArguments().front()->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
            evaluateArgumentsVariadic(node->getArguments(), identifier); _BreakIfFailed;
        }
        else {
            evaluateArguments(node->getArguments(), nested->getArguments()); _BreakIfFailed;
        }
    }
    _StackPop;

    Value* result = nullptr;
    if (nested->getBranch()->hasNextNode()) {
        result = nested->getBranch()->getNextNode()->accept(*this); m_returned = false; _BreakIfFailed;
    }
    _TryEvaluateNextNodeAndClearStack;

    return result;
}

Value* ASTNodeEvaluator::evaluate(ASTPresetCallNode* node)
{
    _StackInit;
    IntValue value = 1;
    insert(InsertC::InsertNewrun, &value, node->getLine());

    auto preset = node->getPreset()->as<ASTPresetNode*>();

    if (!preset->getArguments().empty()) {
        if (preset->getSignature()->isVariadic()) {
            auto identifier = preset->getArguments().front()->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
            evaluateArgumentsVariadic(node->getArguments(), identifier); _BreakIfFailed;
        }
        else {
            evaluateArguments(node->getArguments(), preset->getArguments()); _BreakIfFailed;
        }
    }
    _StackPop;

    Value* result = nullptr;
    if (preset->getBranch()->hasNextNode()) {
        result = preset->getBranch()->getNextNode()->accept(*this); m_returned = false; _BreakIfFailed;
    }
    _TryEvaluateNextNodeAndClearStack;

    return result;
}

Value* ASTNodeEvaluator::evaluate(ASTForNode* node)
{
    _StackInit;
    RangeValue* range = node->getRange()->accept(*this)->as<RangeValue*>(); _BreakIfFailed;
    int32_t from = range->from;
    int32_t to = range->to;

    Value* result = nullptr;
    bool increment = from <= to;
    for (int32_t i = from; increment ? i <= to : i >= to; ) {
        if (node->getBranch()->hasNextNode()) {
            result = node->getBranch()->getNextNode()->accept(*this); _BreakIfFailed; _BreakIfReturned;
            if (m_break) {
                m_break = false;
                _StackPop;
                break;
            }
        }
        IntValue* forFrom = node->getRange()->as<ASTForRangeNode*>()->getDeclaration()->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>()->getValue()->as<IntValue*>();
        increment ? ++forFrom->value : --forFrom->value;
        i = forFrom->value;
        _StackPop;
    }

    _TryEvaluateNextNodeAndClearStack;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTIfNode* node)
{
    _StackInit;
    Value* result = nullptr;

    Value* condition = node->getCondition()->accept(*this); _BreakIfFailed;
    if (condition->as<BoolValue*>()->value && node->getBranch()->hasNextNode()) {
        result = node->getBranch()->getNextNode()->accept(*this); _BreakIfFailed; _BreakIfReturned; _BreakIfBreak; _BreakIfContinue;
    }

    _TryEvaluateNextNodeAndClearStack;
    _StackPop;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTFunctionIdentifierNode* node)
{
    _TryEvaluateNextNode;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTFunctionNode* node)
{
    _TryEvaluateNextNode;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTNestedIdentifierNode* node)
{
    _TryEvaluateNextNode;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTNestedFunctionNode* node)
{
    _TryEvaluateNextNode;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTPresetIdentifierNode* node)
{
    _TryEvaluateNextNode;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTPresetNode* node)
{
    _TryEvaluateNextNode;
    return nullptr;
}

Value* ASTNodeEvaluator::evaluate(ASTInvokeNestedNode* node)
{
    if (m_calls.empty()) {
        _TryEvaluateNextNode;
        return nullptr;
    }

    _StackInit;
    Value* result = nullptr;

    for (auto& nestedCall : m_calls.back()->getNestedCalls())
        nestedCall->accept(*this);

    _TryEvaluateNextNodeAndClearStack;
    return result;
}

ASTNodeEvaluator::ptr_value ASTNodeEvaluator::cast(Value* value, ValueType to)
{
    auto type = value->type();
    if (value == nullptr)
        return nullptr;
    else if (type == to) {
        if (value != _StackTopSafe)
            return value->clone();
        else
            return _StackMoveTop;
    }

    ptr_value result;
    if (type == ValueType::Int) {
        if (to == ValueType::Float)
            result = std::make_unique<FloatValue>(value->as<IntValue*>()->toFloat());
        else
            result = std::make_unique<CoordValue>(value->as<IntValue*>()->toCoord());
    }
    else if (type == ValueType::Range)
        result = std::make_unique<ObjectValue>(value->as<RangeValue*>()->toObject());
    else if (type == ValueType::Coord)
        result = std::make_unique<IntValue>(value->as<CoordValue*>()->toInt());
    else if (type == ValueType::Float)
        result = std::make_unique<IntValue>(value->as<FloatValue*>()->toInt());
    else if (type == ValueType::Object)
        result = std::make_unique<ArrayValue<IntValue>>(value->as<ObjectValue*>()->toArray());
    else
        result = std::make_unique<ObjectValue>(value->as<ArrayValue<IntValue>*>()->toObject());

    return result;
}

void ASTNodeEvaluator::evaluateArguments(const ptr_node_v& callArgs, ptr_node_v& defArgs)
{
    for (size_t i = 0; i < callArgs.size(); ++i) {
        auto identifier = defArgs[i]->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
        identifier->setValue(cast(callArgs[i].get()->accept(*this), identifier->getNodeType())); _BreakIfFailedVoid;
    }
}

void ASTNodeEvaluator::evaluateArgumentsVariadic(const ptr_node_v& callArgs, ASTIdentifierNode* identifier)
{
    auto type = identifier->getNodeType();

    if (type == ValueType::ArrayBool) {
        auto array = std::make_unique<ArrayValue<BoolValue>>();
        for (const auto& arg : callArgs) {
            auto value = arg->accept(*this); _BreakIfFailedVoid;
            if (value->type() == ValueType::Bool)
                array->value.push_back(*value->as<BoolValue*>());
            else {
                for (const auto& elem : value->as<ArrayValue<BoolValue>*>()->value)
                    array->value.push_back(elem);
            }
        }
        array->update();
        identifier->setValue(std::move(array));
    }
    else if (type == ValueType::ArrayInt) {
        auto array = std::make_unique<ArrayValue<IntValue>>();
        for (const auto& arg : callArgs) {
            auto value = arg->accept(*this); _BreakIfFailedVoid;
            if (value->type() == ValueType::Int)
                array->value.push_back(*value->as<IntValue*>());
            else if (value->type() == ValueType::Range) {
                RangeValue* range = value->as<RangeValue*>();

                bool increment = range->from <= range->to;
                for (int32_t i = range->from; increment ? i <= range->to : i >= range->to; increment ? ++i : --i)
                    array->value.push_back({ i, range->rotation });
            }
            else if (value->type() == ValueType::Coord)
                array->value.push_back(value->as<CoordValue*>()->toInt());
            else if (value->type() == ValueType::Float)
                array->value.push_back(value->as<FloatValue*>()->toInt());
            else if (value->type() == ValueType::Object) {
                for (auto elem : value->as<ObjectValue*>()->value)
                    array->value.push_back(elem);
            }
            else {
                for (const auto& elem : value->as<ArrayValue<IntValue>*>()->value)
                    array->value.push_back(elem);
            }
        }
        array->update();
        identifier->setValue(std::move(array));
    }
    else if (type == ValueType::ArrayRange) {
        auto array = std::make_unique<ArrayValue<RangeValue>>();
        for (const auto& arg : callArgs) {
            auto value = arg->accept(*this); _BreakIfFailedVoid;
            if (value->type() == ValueType::Range)
                array->value.push_back(*value->as<RangeValue*>());
            else {
                for (const auto& elem : value->as<ArrayValue<RangeValue>*>()->value)
                    array->value.push_back(elem);
            }
        }
        array->update();
        identifier->setValue(std::move(array));
    }
    else if (type == ValueType::ArrayCoord) {
        auto array = std::make_unique<ArrayValue<CoordValue>>();
        for (const auto& arg : callArgs) {
            auto value = arg->accept(*this); _BreakIfFailedVoid;
            if (value->type() == ValueType::Int)
                array->value.push_back(value->as<IntValue*>()->toCoord());
            else if (value->type() == ValueType::Coord)
                array->value.push_back(*value->as<CoordValue*>());
            else {
                for (const auto& elem : value->as<ArrayValue<CoordValue>*>()->value)
                    array->value.push_back(elem);
            }
        }
        array->update();
        identifier->setValue(std::move(array));
    }
    else if (type == ValueType::ArrayFloat) {
        auto array = std::make_unique<ArrayValue<FloatValue>>();
        for (const auto& arg : callArgs) {
            auto value = arg->accept(*this); _BreakIfFailedVoid;
            if (value->type() == ValueType::Int)
                array->value.push_back(value->as<IntValue*>()->toFloat());
            else if (value->type() == ValueType::Float)
                array->value.push_back(*value->as<FloatValue*>());
            else {
                for (const auto& elem : value->as<ArrayValue<FloatValue>*>()->value)
                    array->value.push_back(elem);
            }
        }
        array->update();
        identifier->setValue(std::move(array));
    }
    else if (type == ValueType::ArrayString) {
        auto array = std::make_unique<ArrayValue<StringValue>>();
        for (const auto& arg : callArgs) {
            auto value = arg->accept(*this); _BreakIfFailedVoid;
            if (value->type() == ValueType::String)
                array->value.push_back(*value->as<StringValue*>());
            else {
                for (const auto& elem : value->as<ArrayValue<StringValue>*>()->value)
                    array->value.push_back(elem);
            }
        }
        array->update();
        identifier->setValue(std::move(array));
    }
    else {
        auto array = std::make_unique<ArrayValue<ObjectValue>>();
        for (const auto& arg : callArgs) {
            auto value = arg->accept(*this); _BreakIfFailedVoid;
            if (value->type() == ValueType::Object)
                array->value.push_back(*value->as<ObjectValue*>());
            else if (value->type() == ValueType::Range)
                array->value.push_back(value->as<RangeValue*>()->toObject());
            else if (value->type() == ValueType::ArrayInt)
                array->value.push_back(value->as<ArrayValue<IntValue>*>()->toObject());
            else {
                for (const auto& elem : value->as<ArrayValue<ObjectValue>*>()->value)
                    array->value.push_back(elem);
            }
        }
        array->update();
        identifier->setValue(std::move(array));
    }
}

bool ASTNodeEvaluator::hasRotation(Value* value, Rotation rotation)
{
    auto type = value->type();

    if (type == ValueType::Int)
        return (util::enum_b(value->as<IntValue*>()->rotation & rotation));
    else if (type == ValueType::Range)
        return (util::enum_b(value->as<RangeValue*>()->rotation & rotation));
    else if (type == ValueType::Coord)
        return (util::enum_b(value->as<CoordValue*>()->rotation & rotation));
    else
        return (util::enum_b(value->as<ObjectValue*>()->rotation & rotation));
}

void ASTNodeEvaluator::rotate(Value* value, Rotation rotation)
{
    auto type = value->type();

    if (type == ValueType::Int)
        value->as<IntValue*>()->rotation = rotation;
    else if (type == ValueType::Range)
        value->as<RangeValue*>()->rotation = rotation;
    else if (type == ValueType::Coord)
        value->as<CoordValue*>()->rotation = rotation;
    else {
        value->as<ObjectValue*>()->rotation = rotation;
        value->as<ObjectValue*>()->update(false);
    }
}

void ASTNodeEvaluator::insertPosType(uint32_t line, NodeID id)
{
    if (automappers().empty())
        printError("Cannot evaluate 'insert.rule.pos.type'. No automapper found.", line);
    else if (automappers().back().runs.empty())
        printError("Cannot evaluate 'insert.rule.pos.type'. No run found.", line);
    else if (automappers().back().runs.back().rules.empty())
        printError("Cannot evaluate 'insert.rule.pos.type'. No rule found.", line);
    else if (automappers().back().runs.back().rules.back().posRules.empty())
        printError("Cannot evaluate 'insert.rule.pos.type'. No posrule found.", line);
    else {
        if (id == NodeID::Index)
            automappers().back().runs.back().rules.back().posRules.back().ruleType = PosRuleType::INDEX;
        else if (id == NodeID::NotIndex)
            automappers().back().runs.back().rules.back().posRules.back().ruleType = PosRuleType::NOTINDEX;
        else if (id == NodeID::Full)
            automappers().back().runs.back().rules.back().posRules.back().ruleType = PosRuleType::FULL;
        else if (id == NodeID::Empty)
            automappers().back().runs.back().rules.back().posRules.back().ruleType = PosRuleType::EMPTY;
    }
}

void ASTNodeEvaluator::insert(InsertC control, Value* value, uint32_t line)
{
    if (control == InsertC::InsertAutomapper) {
        AutoMapper automapper;
        automapper.name = value->as<StringValue*>()->value;
        automappers().push_back(std::move(automapper));
    }
    else if (control == InsertC::InsertNewrun) {
        if (value->as<IntValue*>()->value <= 0)
            printError("Invalid value for 'insert.newrun', must be greater than 0.", line);
        else if (automappers().empty())
            printError("Cannot evaluate 'insert.newrun'. No automapper found.", line);
        else {
            Run run = {};
            run.copies = value->as<IntValue*>()->value;
            automappers().back().runs.push_back(std::move(run));
        }
    }
    else if (control == InsertC::InsertNewrule) {
        if (automappers().empty())
            printError("Cannot evaluate 'insert.newrule'. No automapper found.", line);
        else if (automappers().back().runs.empty())
            printError("Cannot evaluate 'insert.newrule'. No run found.", line);
        else
            automappers().back().runs.back().rules.push_back({});
    }
    else if (control == InsertC::InsertNocopy) {
        if (automappers().empty())
            printError("Cannot evaluate 'insert.nocopy'. No automapper found.", line);
        else if (automappers().back().runs.empty())
            printError("Cannot evaluate 'insert.nocopy'. No run found.", line);
        else
            automappers().back().runs.back().overrideLayer = true;
    }
    else if (control == InsertC::InsertRuleNodefault) {
        if (automappers().empty())
            printError("Cannot evaluate 'insert.nodefault'. No automapper found.", line);
        else if (automappers().back().runs.empty())
            printError("Cannot evaluate 'insert.nodefault'. No run found.", line);
        else if (automappers().back().runs.back().rules.empty())
            printError("Cannot evaluate 'insert.nodefault'. No rule found.", line);
        else
            automappers().back().runs.back().rules.back().noDefaultRule = true;
    }
    else if (control == InsertC::InsertRuleRandom) {
        if (automappers().empty())
            printError("Cannot evaluate 'insert.rule.random'. No automapper found.", line);
        else if (automappers().back().runs.empty())
            printError("Cannot evaluate 'insert.rule.random'. No run found.", line);
        else if (automappers().back().runs.back().rules.empty())
            printError("Cannot evaluate 'insert.rule.random'. No rule found.", line);
        else {
            if (value->type() == ValueType::Float)
                automappers().back().runs.back().rules.back().random = value->as<FloatValue*>()->value;
            else
                automappers().back().runs.back().rules.back().random = cast(value, ValueType::Float)->as<FloatValue*>()->value;
        }
    }
    else if (control == InsertC::InsertRulePos) {
        if (automappers().empty())
            printError("Cannot evaluate 'insert.rule.pos'. No automapper found.", line);
        else if (automappers().back().runs.empty())
            printError("Cannot evaluate 'insert.rule.pos'. No run found.", line);
        else if (automappers().back().runs.back().rules.empty())
            printError("Cannot evaluate 'insert.rule.pos'. No rule found.", line);
        else {
            if (value->type() == ValueType::Coord) {
                PosRule posRule = {};
                posRule.x = value->as<CoordValue*>()->x.value;
                posRule.y = value->as<CoordValue*>()->y.value;
                automappers().back().runs.back().rules.back().posRules.push_back(std::move(posRule));
            }
            else
                printError("Type '" + Token::typeToString(value->type()) + "' was assigned to 'insert.rule.pos'. Use 'coord' type instead.", line);
        }
    }
    else if (control == InsertC::InsertRulePosIndex) {
        if (automappers().empty())
            printError("Cannot evaluate 'insert.rule.pos.index'. No automapper found.", line);
        else if (automappers().back().runs.empty())
            printError("Cannot evaluate 'insert.rule.pos.index'. No run found.", line);
        else if (automappers().back().runs.back().rules.empty())
            printError("Cannot evaluate 'insert.rule.pos.index'. No rule found.", line);
        else if (automappers().back().runs.back().rules.back().posRules.empty())
            printError("Cannot evaluate 'insert.rule.pos.index'. No posrule found.", line);
        else {
            IndexInfo ii;
            if (value->type() == ValueType::Int) {
                ii.tileID = value->as<IntValue*>()->value;
                ii.rotation = value->as<IntValue*>()->rotation;
            }
            else {
                ptr_value intValue = cast(value, ValueType::Int);
                ii.tileID = intValue->as<IntValue*>()->value;
                ii.rotation = intValue->as<IntValue*>()->rotation;
            }

            if (ii.tileID < -1 || ii.tileID > 255)
                printError("Invalid value for 'insert.rule.pos.index', must be in range [-1,255].", line);
            else
                automappers().back().runs.back().rules.back().posRules.back().indexInfos.push_back(ii);
        }
    }
    else if (control == InsertC::InsertRulePosOperator) {
        if (automappers().empty())
            printError("Cannot evaluate 'insert.rule.pos.operator'. No automapper found.", line);
        else if (automappers().back().runs.empty())
            printError("Cannot evaluate 'insert.rule.pos.operator'. No run found.", line);
        else if (automappers().back().runs.back().rules.empty())
            printError("Cannot evaluate 'insert.rule.pos.operator'. No rule found.", line);
        else if (automappers().back().runs.back().rules.back().posRules.empty())
            printError("Cannot evaluate 'insert.rule.pos.operator'. No posrule found.", line);
        else {
            int32_t op = value->as<IntValue*>()->value;
            if (op != util::enum_i32(Op::And) && op != util::enum_i32(Op::Or))
                printError("Invalid value for 'insert.rule.pos.operator', must be either 0 or 1.", line);
            else
                automappers().back().runs.back().rules.back().posRules.back().op = util::i32_enum<Op>(op);
        }
    }
    else if (control == InsertC::InsertRulePosGroup) {
        if (automappers().empty())
            printError("Cannot evaluate 'insert.rule.pos.group'. No automapper found.", line);
        else if (automappers().back().runs.empty())
            printError("Cannot evaluate 'insert.rule.pos.group'. No run found.", line);
        else if (automappers().back().runs.back().rules.empty())
            printError("Cannot evaluate 'insert.rule.pos.group'. No rule found.", line);
        else if (automappers().back().runs.back().rules.back().posRules.empty())
            printError("Cannot evaluate 'insert.rule.pos.group'. No posrule found.", line);
        else {
            int32_t group = value->as<IntValue*>()->value;
            automappers().back().runs.back().rules.back().posRules.back().group = group;
        }
    }
    else {
        if (automappers().empty())
            printError("Cannot evaluate 'insert.rule.index'. No automapper found.", line);
        else if (automappers().back().runs.empty())
            printError("Cannot evaluate 'insert.rule.index'. No run found.", line);
        else if (automappers().back().runs.back().rules.empty())
            printError("Cannot evaluate 'insert.rule.index'. No rule found.", line);
        else {
            IndexInfo ii;
            if (value->type() == ValueType::Int) {
                ii.tileID = value->as<IntValue*>()->value;
                ii.rotation = value->as<IntValue*>()->rotation;
            }
            else {
                ptr_value intValue = cast(value, ValueType::Int);
                ii.tileID = intValue->as<IntValue*>()->value;
                ii.rotation = intValue->as<IntValue*>()->rotation;
            }

            if (ii.tileID < 0 || ii.tileID > 255)
                printError("Invalid value for 'insert.rule.index', must be in range [0,255].", line);
            else
                automappers().back().runs.back().rules.back().indexInfo = ii;
        }
    }
}

void ASTNodeEvaluator::printError(std::string_view message, uint32_t line)
{
    m_failed = true;
    errorOutput::print::string("> ");
    errorOutput::print::string(std::to_string(line));
    errorOutput::print::string(": Error: ");
    errorOutput::print::string(message); errorOutput::print::newLine();
    errorOutput::print::stage("... Execution stopped"); errorOutput::print::newLine();
}

void ASTNodeEvaluator::printWarning(std::string_view message, uint32_t line)
{
    m_warnings = true;
    errorOutput::print::string("> ");
    errorOutput::print::string(std::to_string(line));
    errorOutput::print::string(": Warning: ");
    errorOutput::print::string(message); errorOutput::print::newLine();
}

void ASTNodeEvaluator::printAssert(uint32_t line)
{
    m_failed = true;
    errorOutput::print::string("> ");
    errorOutput::print::string(std::to_string(line));
    errorOutput::print::string(": Assertion failed! "); errorOutput::print::newLine();
    errorOutput::print::stage("... Execution stopped"); errorOutput::print::newLine();
}

/*
    IASTNode
*/
bool IASTNode::isDeclared(std::string_view name, NodeID id, IASTNode* caller, const Signature& signature) const
{
    if (hasPreviousNode())
        return getPreviousNode()->isDeclared(name, id, caller, signature);
    return false;
}

bool IASTNode::hasNode(NodeID id, const std::vector<NodeID>& skip_ids) const
{
    bool skip = util::contains(skip_ids.begin(), skip_ids.end(), this->id());
    if (!skip) {
        if (this->id() == id)
            return true;
    }

    if (hasNextNode())
        return getNextNode()->hasNode(id, skip_ids);
    return false;
}

IASTNode* IASTNode::findNode(const std::vector<NodeID>& ids, const std::vector<NodeID>& skip_ids, bool forward)
{
    bool skip = util::contains(skip_ids.begin(), skip_ids.end(), this->id());
    if (!skip) {
        for (auto id : ids)
            if (this->id() == id)
                return this;
    }

    if (forward && hasNextNode())
        return getNextNode()->findNode(ids, skip_ids, forward);
    else if (!forward && hasPreviousNode())
        return getPreviousNode()->findNode(ids, skip_ids, forward);
    return nullptr;
}

IASTNode* IASTNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return this;
}

std::vector<IASTNode*> IASTNode::getDeclaredObjects()
{
    if (hasPreviousNode())
        return getPreviousNode()->getDeclaredObjects();
    return {};
}

IASTNode* IASTNode::getNodeByName(std::string_view name, NodeID id)
{
    if (hasPreviousNode())
        return getPreviousNode()->getNodeByName(name, id);
    return nullptr;
}

IASTNode* IASTNode::getNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName)
{
    if (hasPreviousNode())
        return getPreviousNode()->getNodeBySignature(name, id, signature, functionName);
    return nullptr;
}

IASTNode* IASTNode::getConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName)
{
    if (hasPreviousNode())
        return getPreviousNode()->getConvertibleNodeBySignature(name, id, signature, functionName);
    return nullptr;
}

IASTNode* IASTNode::getVariadicConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName)
{
    if (hasPreviousNode())
        return getPreviousNode()->getVariadicConvertibleNodeBySignature(name, id, signature, functionName);
    return nullptr;
}

const Signature* IASTNode::getSignature() const
{
    return nullptr;
}

ValueType IASTNode::getNodeType()
{
    return ValueType::Null;
}

/*
    ASTNullNode
*/
bool ASTNullNode::isDeclared(std::string_view name, NodeID id, IASTNode* caller, const Signature& signature) const
{
    if (hasPreviousNode()) {
        auto prev = getPreviousNode();
        if (prev->id() == NodeID::For) {
            if (id == NodeID::Identifier) {
                auto declaration = prev->as<ASTForNode*>()->getRange()->as<ASTForRangeNode*>()->getDeclaration();
                if (declaration->isDeclared(name, id, caller, signature))
                    return true;
            }
        }
        else if (prev->id() == NodeID::Function) {
            if (id == NodeID::Identifier) {
                for (auto&& declaration : prev->as<ASTFunctionNode*>()->getArguments()) {
                    auto identifier = declaration->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
                    if (identifier->getName() == name)
                        return true;
                }
            }
        }
        else if (prev->id() == NodeID::NestedFunction) {
            if (id == NodeID::Identifier) {
                for (auto&& declaration : prev->as<ASTNestedFunctionNode*>()->getArguments()) {
                    auto identifier = declaration->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
                    if (identifier->getName() == name)
                        return true;
                }
            }
        }
        else if (prev->id() == NodeID::Preset) {
            if (id == NodeID::Identifier) {
                for (auto&& declaration : prev->as<ASTPresetNode*>()->getArguments()) {
                    auto identifier = declaration->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
                    if (identifier->getName() == name)
                        return true;
                }
            }
        }
        return prev->isDeclared(name, id, caller, signature);
    }
    return false;
}

IASTNode* ASTNullNode::getNodeByName(std::string_view name, NodeID id)
{
    if (hasPreviousNode()) {
        auto prev = getPreviousNode();
        if (prev->id() == NodeID::For) {
            if (id == NodeID::Identifier) {
                auto declaration = prev->as<ASTForNode*>()->getRange()->as<ASTForRangeNode*>()->getDeclaration();
                auto node = declaration->getNodeByName(name, id);
                if (node != nullptr)
                    return node;
            }
        }
        else if (prev->id() == NodeID::Function) {
            if (id == NodeID::Identifier) {
                for (auto&& declaration : prev->as<ASTFunctionNode*>()->getArguments()) {
                    auto identifier = declaration->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
                    if (identifier->getName() == name)
                        return identifier;
                }
            }
        }
        else if (prev->id() == NodeID::NestedFunction) {
            if (id == NodeID::Identifier) {
                for (auto&& declaration : prev->as<ASTNestedFunctionNode*>()->getArguments()) {
                    auto identifier = declaration->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
                    if (identifier->getName() == name)
                        return identifier;
                }
            }
        }
        else if (prev->id() == NodeID::Preset) {
            if (id == NodeID::Identifier) {
                for (auto&& declaration : prev->as<ASTPresetNode*>()->getArguments()) {
                    auto identifier = declaration->as<ASTDeclarationNode*>()->getIdentifier()->as<ASTIdentifierNode*>();
                    if (identifier->getName() == name)
                        return identifier;
                }
            }
        }
        return prev->getNodeByName(name, id);
    }
    return nullptr;
}

/*
    ASTBoolNode
*/
ValueType ASTBoolNode::getNodeType()
{
    return m_value.type();
}

/*
    ASTIntNode
*/
ValueType ASTIntNode::getNodeType()
{
    return m_value.type();
}

/*
    ASTRangeNode
*/
ValueType ASTRangeNode::getNodeType()
{
    return m_value.type();
}

/*
    ASTCoordNode
*/
ValueType ASTCoordNode::getNodeType()
{
    return m_value.type();
}

/*
    ASTFloatNode
*/
ValueType ASTFloatNode::getNodeType()
{
    return m_value.type();
}

/*
    ASTStringNode
*/
ValueType ASTStringNode::getNodeType()
{
    return m_value.type();
}

/*
    ASTObjectNode
*/
ValueType ASTObjectNode::getNodeType()
{
    return m_value.type();
}

/*
    ASTDeclarationNode
*/
bool ASTDeclarationNode::isDeclared(std::string_view name, NodeID id, IASTNode* caller, const Signature& signature) const
{
    if (id == NodeID::Identifier && this != caller)
        if (getIdentifier()->as<ASTIdentifierNode*>()->getName() == name)
            return true;

    if (hasPreviousNode())
        return getPreviousNode()->isDeclared(name, id, caller, signature);
    return false;
}

IASTNode* ASTDeclarationNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_identifier.get();
}

std::vector<IASTNode*> ASTDeclarationNode::getDeclaredObjects()
{
    std::vector<IASTNode*> result;
    if (getNodeType() == ValueType::Object || getNodeType() == ValueType::ArrayObject)
        result.push_back(getIdentifier());
    if (hasPreviousNode()) {
        auto objects = getPreviousNode()->getDeclaredObjects();
        result.insert(result.end(), objects.begin(), objects.end());
    }
    return result;
}

IASTNode* ASTDeclarationNode::getNodeByName(std::string_view name, NodeID id)
{
    if (id == NodeID::Identifier) {
        auto node = static_cast<ASTIdentifierNode*>(getIdentifier());
        if (node->getName() == name)
            return node;
    }

    if (hasPreviousNode())
        return getPreviousNode()->getNodeByName(name, id);
    return nullptr;
}

ValueType ASTDeclarationNode::getNodeType()
{
    return getIdentifier()->as<ASTIdentifierNode*>()->getType();
}

void ASTDeclarationNode::attach(IASTNode* previous)
{
    m_identifier->setPreviousNode(previous);
    if (m_node != nullptr)
        m_node->setPreviousNode(previous);
}

/*
    ASTIdentifierNode
*/
ValueType ASTIdentifierNode::getNodeType()
{
    return getType();
}

/*
    ASTVariableNode
*/
ValueType ASTVariableNode::getNodeType()
{
    if (getIdentifier() == nullptr)
        return ValueType::Null;

    auto node = static_cast<ASTIdentifierNode*>(getIdentifier());
    return node->getType();
}

/*
    ASTAnchorNode
*/
ValueType ASTAnchorNode::getNodeType()
{
    return ValueType::Coord;
}

void ASTAnchorNode::attach(IASTNode* previous)
{
    getNode()->setPreviousNode(previous);
}

/*
    ASTCountNode
*/
ValueType ASTCountNode::getNodeType()
{
    return ValueType::Int;
}

void ASTCountNode::attach(IASTNode* previous)
{
    getNode()->setPreviousNode(previous);
}

/*
    ASTLastNode
*/
ValueType ASTLastNode::getNodeType()
{
    return ValueType::Int;
}

void ASTLastNode::attach(IASTNode* previous)
{
    getNode()->setPreviousNode(previous);
}

/*
    ASTXNode
*/
ValueType ASTXNode::getNodeType()
{
    return ValueType::Int;
}

void ASTXNode::attach(IASTNode* previous)
{
    getNode()->setPreviousNode(previous);
}

/*
    ASTYNode
*/
ValueType ASTYNode::getNodeType()
{
    return ValueType::Int;
}

void ASTYNode::attach(IASTNode* previous)
{
    getNode()->setPreviousNode(previous);
}

/*
    ASTRotationNode
*/
ValueType ASTRotationNode::getNodeType()
{
    return getNode()->getNodeType();
}

void ASTRotationNode::attach(IASTNode* previous)
{
    getNode()->setPreviousNode(previous);
}

/*
    ASTIndexNode
*/
ValueType ASTIndexNode::getNodeType()
{
    return ValueType::Int;
}

/*
    ASTInsertNode
*/
ValueType ASTInsertNode::getNodeType()
{
    if (getControl() == InsertC::InsertAutomapper)
        return ValueType::String;
    else if (getControl() == InsertC::InsertRulePos)
        return ValueType::Coord;
    else if (getControl() == InsertC::InsertRuleIndex)
        return ValueType::Int;
    else if (getControl() == InsertC::InsertRulePosIndex)
        return ValueType::Int;
    else if (getControl() == InsertC::InsertRulePosOperator)
        return ValueType::Int;
    else if (getControl() == InsertC::InsertRulePosGroup)
        return ValueType::Int;
    else if (getControl() == InsertC::InsertNewrun)
        return ValueType::Int;
    else if (getControl() == InsertC::InsertRuleRandom)
        return ValueType::Float;
    else
        return ValueType::Null;
}

void ASTInsertNode::attach(IASTNode* previous)
{
    if (getNode() != nullptr)
        getNode()->setPreviousNode(previous);
}

/*
    ASTRotateNode
*/
ValueType ASTRotateNode::getNodeType()
{
    return ValueType::Bool;
}

void ASTRotateNode::attach(IASTNode* previous)
{
    getNode()->setPreviousNode(previous);
}

/*
    ASTOpAssignNode
*/
IASTNode* ASTOpAssignNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

std::vector<IASTNode*> ASTOpAssignNode::getDeclaredObjects()
{
    if (getLeft()->id() == NodeID::Declaration)
        return getLeft()->getDeclaredObjects();
    else if (hasPreviousNode())
        return getPreviousNode()->getDeclaredObjects();
    return {};
}

IASTNode* ASTOpAssignNode::getNodeByName(std::string_view name, NodeID id)
{
    if (getLeft()->id() == NodeID::Declaration)
        return getLeft()->getNodeByName(name, id);
    else if (hasPreviousNode())
        return getPreviousNode()->getNodeByName(name, id);
    return {};
}

void ASTOpAssignNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpAddNode
*/
IASTNode* ASTOpAddNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpAddNode::getNodeType()
{
    if (getLeft()->getNodeType() == ValueType::String && getRight()->getNodeType() == ValueType::String)
        return ValueType::String;
    return Token::getArithmeticResult(getLeft()->getNodeType(), getRight()->getNodeType());
}

void ASTOpAddNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpSubtractNode
*/
IASTNode* ASTOpSubtractNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpSubtractNode::getNodeType()
{
    return Token::getArithmeticResult(getLeft()->getNodeType(), getRight()->getNodeType());
}

void ASTOpSubtractNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpMultiplyNode
*/
IASTNode* ASTOpMultiplyNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpMultiplyNode::getNodeType()
{
    return Token::getArithmeticResult(getLeft()->getNodeType(), getRight()->getNodeType());
}

void ASTOpMultiplyNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpDivideNode
*/
IASTNode* ASTOpDivideNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpDivideNode::getNodeType()
{
    return Token::getArithmeticResult(getLeft()->getNodeType(), getRight()->getNodeType());
}

void ASTOpDivideNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpEqualNode
*/
IASTNode* ASTOpEqualNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpEqualNode::getNodeType()
{
    if (getLeft()->getNodeType() == getRight()->getNodeType())
        return ValueType::Bool;
    if (Token::isConvertible(getLeft()->getNodeType(), getRight()->getNodeType()))
        return ValueType::Bool;
    if (Token::isConvertible(getRight()->getNodeType(), getLeft()->getNodeType()))
        return ValueType::Bool;
    return ValueType::Null;
}

void ASTOpEqualNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpNotEqualNode
*/
IASTNode* ASTOpNotEqualNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpNotEqualNode::getNodeType()
{
    if (getLeft()->getNodeType() == getRight()->getNodeType())
        return ValueType::Bool;
    if (Token::isConvertible(getLeft()->getNodeType(), getRight()->getNodeType()))
        return ValueType::Bool;
    if (Token::isConvertible(getRight()->getNodeType(), getLeft()->getNodeType()))
        return ValueType::Bool;
    return ValueType::Null;
}

void ASTOpNotEqualNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpGreaterThanNode
*/
IASTNode* ASTOpGreaterThanNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpGreaterThanNode::getNodeType()
{
    if (Token::isArithmetic(getLeft()->getNodeType()) && Token::isArithmetic(getRight()->getNodeType()))
        return ValueType::Bool;
    return ValueType::Null;
}

void ASTOpGreaterThanNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpGreaterThanOrEqualNode
*/
IASTNode* ASTOpGreaterThanOrEqualNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpGreaterThanOrEqualNode::getNodeType()
{
    if (Token::isArithmetic(getLeft()->getNodeType()) && Token::isArithmetic(getRight()->getNodeType()))
        return ValueType::Bool;
    return ValueType::Null;
}

void ASTOpGreaterThanOrEqualNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpLessThanNode
*/
IASTNode* ASTOpLessThanNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpLessThanNode::getNodeType()
{
    if (Token::isArithmetic(getLeft()->getNodeType()) && Token::isArithmetic(getRight()->getNodeType()))
        return ValueType::Bool;
    return ValueType::Null;
}

void ASTOpLessThanNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpLessThanOrEqualNode
*/
IASTNode* ASTOpLessThanOrEqualNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpLessThanOrEqualNode::getNodeType()
{
    if (Token::isArithmetic(getLeft()->getNodeType()) && Token::isArithmetic(getRight()->getNodeType()))
        return ValueType::Bool;
    return ValueType::Null;
}

void ASTOpLessThanOrEqualNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpAndNode
*/
IASTNode* ASTOpAndNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpAndNode::getNodeType()
{
    if (getLeft()->getNodeType() == ValueType::Bool && getRight()->getNodeType() == ValueType::Bool)
        return ValueType::Bool;
    return ValueType::Null;
}

void ASTOpAndNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpOrNode
*/
IASTNode* ASTOpOrNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpOrNode::getNodeType()
{
    if (getLeft()->getNodeType() == ValueType::Bool && getRight()->getNodeType() == ValueType::Bool)
        return ValueType::Bool;
    return ValueType::Null;
}

void ASTOpOrNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpNotNode
*/
IASTNode* ASTOpNotNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_expr->getLastNode();
}

ValueType ASTOpNotNode::getNodeType()
{
    if (getExpr()->getNodeType() == ValueType::Bool)
        return ValueType::Bool;
    return ValueType::Null;
}

void ASTOpNotNode::attach(IASTNode* previous)
{
    m_expr->setPreviousNode(previous);
}

/*
    ASTOpRangeNode
*/
IASTNode* ASTOpRangeNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpRangeNode::getNodeType()
{
    return ValueType::Range;
}

void ASTOpRangeNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTOpCoordNode
*/
IASTNode* ASTOpCoordNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_right->getLastNode();
}

ValueType ASTOpCoordNode::getNodeType()
{
    return ValueType::Coord;
}

void ASTOpCoordNode::attach(IASTNode* previous)
{
    m_left->setPreviousNode(previous);
    m_right->setPreviousNode(previous);
}

/*
    ASTErrorNode
*/
void ASTErrorNode::attach(IASTNode* previous)
{
    m_string->setPreviousNode(previous);
}

/*
    ASTWarningNode
*/
void ASTWarningNode::attach(IASTNode* previous)
{
    m_string->setPreviousNode(previous);
}

/*
    ASTAssertNode
*/
void ASTAssertNode::attach(IASTNode* previous)
{
    m_expr->setPreviousNode(previous);
}

/*
    ASTReturnNode
*/
IASTNode* ASTReturnNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_node->getLastNode();
}

ValueType ASTReturnNode::getNodeType()
{
    if (getFunction() != nullptr)
        return getFunction()->getNodeType();
    return ValueType::Null;
}

void ASTReturnNode::attach(IASTNode* previous)
{
    if (m_node != nullptr)
        m_node->setPreviousNode(previous);
}

/*
    ASTForRangeNode
*/
IASTNode* ASTForRangeNode::getLastNode()
{
    if (hasNextNode())
        return getNextNode()->getLastNode();
    return m_to->getLastNode();
}

void ASTForRangeNode::attach(IASTNode* previous)
{
    m_declaration->setPreviousNode(previous);
    m_to->setPreviousNode(previous);
}

/*
    ASTArraySubscriptNode
*/
ValueType ASTArraySubscriptNode::getNodeType()
{
    if (getArray()->getNodeType() == ValueType::Object)
        return ValueType::Int;
    else if ((getArray()->getNodeType() & ValueType::Array) == ValueType::Null)
        return ValueType::Null;
    return getArray()->getNodeType() ^ ValueType::Array;
}

void ASTArraySubscriptNode::attach(IASTNode* previous)
{
    m_array->setPreviousNode(previous);
    m_index->setPreviousNode(previous);
}

/*
    ASTPushCallNode
*/
ValueType ASTPushCallNode::getNodeType()
{
    return ValueType::Null;
}

void ASTPushCallNode::attach(IASTNode* previous)
{
    for (auto&& arg : m_arguments)
        arg->setPreviousNode(previous);
    m_variable->setPreviousNode(previous);
}

/*
    ASTHasCallNode
*/
ValueType ASTHasCallNode::getNodeType()
{
    return ValueType::Bool;
}

void ASTHasCallNode::attach(IASTNode* previous)
{
    for (auto&& arg : m_arguments)
        arg->setPreviousNode(previous);
    m_variable->setPreviousNode(previous);
}

/*
    ASTUniqueCallNode
*/
ValueType ASTUniqueCallNode::getNodeType()
{
    return getVariable()->getNodeType();
}

void ASTUniqueCallNode::attach(IASTNode* previous)
{
    for (auto&& arg : m_arguments)
        arg->setPreviousNode(previous);
    m_variable->setPreviousNode(previous);
}

/*
    ASTStrCallNode
*/
ValueType ASTStrCallNode::getNodeType()
{
    return ValueType::String;
}

void ASTStrCallNode::attach(IASTNode* previous)
{
    for (auto&& arg : m_arguments)
        arg->setPreviousNode(previous);
    m_variable->setPreviousNode(previous);
}

/*
    ASTNameCallNode
*/
ValueType ASTNameCallNode::getNodeType()
{
    return ValueType::String;
}

void ASTNameCallNode::attach(IASTNode* previous)
{
    for (auto&& arg : m_arguments)
        arg->setPreviousNode(previous);
    m_variable->setPreviousNode(previous);
}

/*
    ASTFindCallNode
*/
ValueType ASTFindCallNode::getNodeType()
{
    return ValueType::Int;
}

void ASTFindCallNode::attach(IASTNode* previous)
{
    for (auto&& arg : m_arguments)
        arg->setPreviousNode(previous);
    m_variable->setPreviousNode(previous);
}

/*
    ASTFunctionCallNode
*/
const Signature* ASTFunctionCallNode::getSignature() const
{
    return &m_signature;
}

ValueType ASTFunctionCallNode::getNodeType()
{
    if (getFunction() != nullptr)
        return getFunction()->getNodeType();
    return ValueType::Null;
}

void ASTFunctionCallNode::attach(IASTNode* previous)
{
    for (auto&& arg : m_arguments)
        arg->setPreviousNode(previous);
    for (auto&& nestedCall : m_nestedCalls)
        nestedCall->setPreviousNode(previous);
}

/*
    ASTNestedCallNode
*/
const Signature* ASTNestedCallNode::getSignature() const
{
    return &m_signature;
}

ValueType ASTNestedCallNode::getNodeType()
{
    if (getNestedFunction() != nullptr)
        return getNestedFunction()->getNodeType();
    return ValueType::Null;
}

void ASTNestedCallNode::attach(IASTNode* previous)
{
    for (auto&& arg : m_arguments)
        arg->setPreviousNode(previous);
}

/*
    ASTPresetCallNode
*/
const Signature* ASTPresetCallNode::getSignature() const
{
    return &m_signature;
}

void ASTPresetCallNode::attach(IASTNode* previous)
{
    for (auto&& arg : m_arguments)
        arg->setPreviousNode(previous);
}

/*
    ASTForNode
*/
bool ASTForNode::hasNode(NodeID id, const std::vector<NodeID>& skip_ids) const
{
    bool skip = util::contains(skip_ids.begin(), skip_ids.end(), this->id());
    if (!skip) {
        if (this->id() == id)
            return true;

        bool branchHasNode = getBranch()->hasNode(id, skip_ids);
        if (branchHasNode)
            return true;
    }

    if (hasNextNode())
        return getNextNode()->hasNode(id, skip_ids);
    return false;
}

IASTNode* ASTForNode::findNode(const std::vector<NodeID>& ids, const std::vector<NodeID>& skip_ids, bool forward)
{
    bool skip = util::contains(skip_ids.begin(), skip_ids.end(), this->id());
    if (!skip) {
        for (auto id : ids)
            if (this->id() == id)
                return this;

        IASTNode* found = forward ? getBranch()->findNode(ids, skip_ids, forward) : nullptr;
        if (found != nullptr)
            return found;
    }

    if (forward && hasNextNode())
        return getNextNode()->findNode(ids, skip_ids, forward);
    else if (!forward && hasPreviousNode())
        return getPreviousNode()->findNode(ids, skip_ids, forward);
    return nullptr;
}

void ASTForNode::attach(IASTNode* previous)
{
    m_range->setPreviousNode(previous);
}

/*
    ASTIfNode
*/
bool ASTIfNode::hasNode(NodeID id, const std::vector<NodeID>& skip_ids) const
{
    bool skip = util::contains(skip_ids.begin(), skip_ids.end(), this->id());
    if (!skip) {
        if (this->id() == id)
            return true;

        bool branchHasNode = getBranch()->hasNode(id, skip_ids);
        if (branchHasNode)
            return true;
    }

    if (hasNextNode())
        return getNextNode()->hasNode(id, skip_ids);
    return false;
}

IASTNode* ASTIfNode::findNode(const std::vector<NodeID>& ids, const std::vector<NodeID>& skip_ids, bool forward)
{
    bool skip = util::contains(skip_ids.begin(), skip_ids.end(), this->id());
    if (!skip) {
        for (auto id : ids)
            if (this->id() == id)
                return this;

        IASTNode* found = forward ? getBranch()->findNode(ids, skip_ids, forward) : nullptr;
        if (found != nullptr)
            return found;
    }

    if (forward && hasNextNode())
        return getNextNode()->findNode(ids, skip_ids, forward);
    else if (!forward && hasPreviousNode())
        return getPreviousNode()->findNode(ids, skip_ids, forward);
    return nullptr;
}

void ASTIfNode::attach(IASTNode* previous)
{
    m_condition->setPreviousNode(previous);
}

/*
    ASTFunctionIdentifierNode
*/
ValueType ASTFunctionIdentifierNode::getNodeType()
{
    return getFunction()->getNodeType();
}

/*
    ASTFunctionNode
*/
bool ASTFunctionNode::isDeclared(std::string_view name, NodeID id, IASTNode* caller, const Signature& signature) const
{
    if (id == NodeID::Function && this != caller) {
        auto identifier = static_cast<ASTFunctionIdentifierNode*>(getIdentifier());
        auto callerFunction = caller->as<ASTFunctionNode*>();
        if (identifier->getName() == name && getSignature()->isSame(signature))
            return true;
        if (identifier->getName() == name && !getNestedIdentifiers().empty() && !callerFunction->getNestedIdentifiers().empty())
            return true;
    }

    if (hasPreviousNode())
        return getPreviousNode()->isDeclared(name, id, caller, signature);
    return false;
}

bool ASTFunctionNode::hasNode(NodeID id, const std::vector<NodeID>& skip_ids) const
{
    bool skip = util::contains(skip_ids.begin(), skip_ids.end(), this->id());
    if (!skip) {
        if (this->id() == id)
            return true;

        bool branchHasNode = getBranch()->hasNode(id, skip_ids);
        if (branchHasNode)
            return true;
    }

    if (hasNextNode())
        return getNextNode()->hasNode(id, skip_ids);
    return false;
}

IASTNode* ASTFunctionNode::findNode(const std::vector<NodeID>& ids, const std::vector<NodeID>& skip_ids, bool forward)
{
    bool skip = util::contains(skip_ids.begin(), skip_ids.end(), this->id());
    if (!skip) {
        for (auto id : ids)
            if (this->id() == id)
                return this;

        IASTNode* found = forward ? getBranch()->findNode(ids, skip_ids, forward) : nullptr;
        if (found != nullptr)
            return found;
    }

    if (forward && hasNextNode())
        return getNextNode()->findNode(ids, skip_ids, forward);
    else if (!forward && hasPreviousNode())
        return getPreviousNode()->findNode(ids, skip_ids, forward);
    return nullptr;
}

IASTNode* ASTFunctionNode::getNodeByName(std::string_view name, NodeID id)
{
    if (id == NodeID::Function) {
        auto identifier = static_cast<ASTFunctionIdentifierNode*>(getIdentifier());
        if (identifier->getName() == name)
            return this;
    }

    if (hasPreviousNode())
        return getPreviousNode()->getNodeByName(name, id);
    return nullptr;
}

IASTNode* ASTFunctionNode::getNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName)
{
    if (id == NodeID::Function) {
        auto identifier = static_cast<ASTFunctionIdentifierNode*>(getIdentifier());
        if (identifier->getName() == name && getSignature()->isSame(signature))
            return this;
    }

    if (hasPreviousNode())
        return getPreviousNode()->getNodeBySignature(name, id, signature, functionName);
    return nullptr;
}

IASTNode* ASTFunctionNode::getConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName)
{
    if (id == NodeID::Function) {
        auto identifier = static_cast<ASTFunctionIdentifierNode*>(getIdentifier());
        if (identifier->getName() == name && getSignature()->isConvertible(signature))
            return this;
    }

    if (hasPreviousNode())
        return getPreviousNode()->getConvertibleNodeBySignature(name, id, signature, functionName);
    return nullptr;
}

IASTNode* ASTFunctionNode::getVariadicConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName)
{
    if (id == NodeID::Function) {
        auto functionSignature = getSignature();
        if (functionSignature->getTypes().size() == 1 && Token::isArray(functionSignature->getTypes().front())) {
            auto identifier = static_cast<ASTFunctionIdentifierNode*>(getIdentifier());
            if (identifier->getName() == name && functionSignature->isVariadicConvertible(signature))
                return this;
        }
    }

    if (hasPreviousNode())
        return getPreviousNode()->getVariadicConvertibleNodeBySignature(name, id, signature, functionName);
    return nullptr;
}

const Signature* ASTFunctionNode::getSignature() const
{
    return &m_signature;
}

ValueType ASTFunctionNode::getNodeType()
{
    return getReturnType();
}

void ASTFunctionNode::attach(IASTNode* previous)
{
    m_identifier->setPreviousNode(previous);
    for (auto&& arg : m_arguments)
        arg->setPreviousNode(previous);
    for (auto&& nested : m_nestedIdentifiers)
        nested->setPreviousNode(previous);
}

bool ASTFunctionNode::hasNested(std::string_view name) const
{
    for (auto&& nested : getNestedIdentifiers())
        if (nested->as<ASTNestedIdentifierNode*>()->getName() == name)
            return true;
    return false;
}

IASTNode* ASTFunctionNode::getNested(std::string_view name) const
{
    for (auto&& nested : getNestedIdentifiers())
        if (nested->as<ASTNestedIdentifierNode*>()->getName() == name)
            return nested.get();
    return nullptr;
}

/*
    ASTNestedIdentifierNode
*/
ValueType ASTNestedIdentifierNode::getNodeType()
{
    return getNestedFunction()->getNodeType();
}

/*
    ASTNestedFunctionNode
*/
bool ASTNestedFunctionNode::isDeclared(std::string_view name, NodeID id, IASTNode* caller, const Signature& signature) const
{
    if (id == NodeID::NestedFunction && this != caller) {
        auto identifier = static_cast<ASTNestedIdentifierNode*>(getIdentifier());
        auto functionIdentifier = static_cast<ASTFunctionIdentifierNode*>(getFunctionIdentifier());
        auto callerFunctionIdentifier = caller->as<ASTNestedFunctionNode*>()->getFunctionIdentifier()->as< ASTFunctionIdentifierNode*>();
        if (identifier->getName() == name && functionIdentifier->getName() == callerFunctionIdentifier->getName())
            return true;
    }

    if (hasPreviousNode())
        return getPreviousNode()->isDeclared(name, id, caller, signature);
    return false;
}

bool ASTNestedFunctionNode::hasNode(NodeID id, const std::vector<NodeID>& skip_ids) const
{
    bool skip = util::contains(skip_ids.begin(), skip_ids.end(), this->id());
    if (!skip) {
        if (this->id() == id)
            return true;

        bool branchHasNode = getBranch()->hasNode(id, skip_ids);
        if (branchHasNode)
            return true;
    }

    if (hasNextNode())
        return getNextNode()->hasNode(id, skip_ids);
    return false;
}

IASTNode* ASTNestedFunctionNode::findNode(const std::vector<NodeID>& ids, const std::vector<NodeID>& skip_ids, bool forward)
{
    bool skip = util::contains(skip_ids.begin(), skip_ids.end(), this->id());
    if (!skip) {
        for (auto id : ids)
            if (this->id() == id)
                return this;

        IASTNode* found = forward ? getBranch()->findNode(ids, skip_ids, forward) : nullptr;
        if (found != nullptr)
            return found;
    }

    if (forward && hasNextNode())
        return getNextNode()->findNode(ids, skip_ids, forward);
    else if (!forward && hasPreviousNode())
        return getPreviousNode()->findNode(ids, skip_ids, forward);
    return nullptr;
}

IASTNode* ASTNestedFunctionNode::getNodeByName(std::string_view name, NodeID id)
{
    if (id == NodeID::NestedFunction) {
        auto identifier = static_cast<ASTNestedIdentifierNode*>(getIdentifier());
        if (identifier->getName() == name)
            return this;
    }

    if (hasPreviousNode())
        return getPreviousNode()->getNodeByName(name, id);
    return nullptr;
}

IASTNode* ASTNestedFunctionNode::getNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName)
{
    if (id == NodeID::NestedFunction) {
        auto identifier = static_cast<ASTNestedIdentifierNode*>(getIdentifier());
        auto functionIdentifier = static_cast<ASTFunctionIdentifierNode*>(getFunctionIdentifier());
        if (identifier->getName() == name && functionIdentifier->getName() == functionName && getSignature()->isSame(signature))
            return this;
    }

    if (hasPreviousNode())
        return getPreviousNode()->getNodeBySignature(name, id, signature, functionName);
    return nullptr;
}

IASTNode* ASTNestedFunctionNode::getConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName)
{
    if (id == NodeID::NestedFunction) {
        auto identifier = static_cast<ASTNestedIdentifierNode*>(getIdentifier());
        auto functionIdentifier = static_cast<ASTFunctionIdentifierNode*>(getFunctionIdentifier());
        if (identifier->getName() == name && functionIdentifier->getName() == functionName && getSignature()->isConvertible(signature))
            return this;
    }

    if (hasPreviousNode())
        return getPreviousNode()->getConvertibleNodeBySignature(name, id, signature, functionName);
    return nullptr;
}

IASTNode* ASTNestedFunctionNode::getVariadicConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName)
{
    if (id == NodeID::NestedFunction) {
        auto nestedSignature = getSignature();
        if (nestedSignature->getTypes().size() == 1 && Token::isArray(nestedSignature->getTypes().front())) {
            auto identifier = static_cast<ASTNestedIdentifierNode*>(getIdentifier());
            auto functionIdentifier = static_cast<ASTFunctionIdentifierNode*>(getFunctionIdentifier());
            if (identifier->getName() == name && functionIdentifier->getName() == functionName && nestedSignature->isVariadicConvertible(signature))
                return this;
        }
    }

    if (hasPreviousNode())
        return getPreviousNode()->getVariadicConvertibleNodeBySignature(name, id, signature, functionName);
    return nullptr;
}

const Signature* ASTNestedFunctionNode::getSignature() const
{
    return &m_signature;
}

ValueType ASTNestedFunctionNode::getNodeType()
{
    return getReturnType();
}

void ASTNestedFunctionNode::attach(IASTNode* previous)
{
    m_functionIdentifier->setPreviousNode(previous);
    m_identifier->setPreviousNode(previous);
    for (auto&& arg : m_arguments)
        arg->setPreviousNode(previous);
}

/*
    ASTPresetIdentifierNode
*/
ValueType ASTPresetIdentifierNode::getNodeType()
{
    return getPreset()->getNodeType();
}

/*
    ASTPresetNode
*/
bool ASTPresetNode::isDeclared(std::string_view name, NodeID id, IASTNode* caller, const Signature& signature) const
{
    if (id == NodeID::Preset && this != caller) {
        auto identifier = static_cast<ASTPresetIdentifierNode*>(getIdentifier());
        if (identifier->getName() == name && getSignature()->isSame(signature))
            return true;
    }

    if (hasPreviousNode())
        return getPreviousNode()->isDeclared(name, id, caller, signature);
    return false;
}

bool ASTPresetNode::hasNode(NodeID id, const std::vector<NodeID>& skip_ids) const
{
    bool skip = util::contains(skip_ids.begin(), skip_ids.end(), this->id());
    if (!skip) {
        if (this->id() == id)
            return true;

        bool branchHasNode = getBranch()->hasNode(id, skip_ids);
        if (branchHasNode)
            return true;
    }

    if (hasNextNode())
        return getNextNode()->hasNode(id, skip_ids);
    return false;
}

IASTNode* ASTPresetNode::findNode(const std::vector<NodeID>& ids, const std::vector<NodeID>& skip_ids, bool forward)
{
    bool skip = util::contains(skip_ids.begin(), skip_ids.end(), this->id());
    if (!skip) {
        for (auto id : ids)
            if (this->id() == id)
                return this;

        IASTNode* found = forward ? getBranch()->findNode(ids, skip_ids, forward) : nullptr;
        if (found != nullptr)
            return found;
    }

    if (forward && hasNextNode())
        return getNextNode()->findNode(ids, skip_ids, forward);
    else if (!forward && hasPreviousNode())
        return getPreviousNode()->findNode(ids, skip_ids, forward);
    return nullptr;
}

IASTNode* ASTPresetNode::getNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName)
{
    if (id == NodeID::Preset) {
        auto identifier = static_cast<ASTPresetIdentifierNode*>(getIdentifier());
        if (identifier->getName() == name && getSignature()->isSame(signature))
            return this;
    }

    if (hasPreviousNode())
        return getPreviousNode()->getNodeBySignature(name, id, signature, functionName);
    return nullptr;
}

IASTNode* ASTPresetNode::getConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName)
{
    if (id == NodeID::Preset) {
        auto identifier = static_cast<ASTPresetIdentifierNode*>(getIdentifier());
        if (identifier->getName() == name && getSignature()->isConvertible(signature))
            return this;
    }

    if (hasPreviousNode())
        return getPreviousNode()->getConvertibleNodeBySignature(name, id, signature, functionName);
    return nullptr;
}

IASTNode* ASTPresetNode::getVariadicConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName)
{
    if (id == NodeID::Preset) {
        auto presetSignature = getSignature();
        if (presetSignature->getTypes().size() == 1 && Token::isArray(presetSignature->getTypes().front())) {
            auto identifier = static_cast<ASTPresetIdentifierNode*>(getIdentifier());
            if (identifier->getName() == name && presetSignature->isVariadicConvertible(signature))
                return this;
        }
    }

    if (hasPreviousNode())
        return getPreviousNode()->getVariadicConvertibleNodeBySignature(name, id, signature, functionName);
    return nullptr;
}

const Signature* ASTPresetNode::getSignature() const
{
    return &m_signature;
}

void ASTPresetNode::attach(IASTNode* previous)
{
    m_identifier->setPreviousNode(previous);
    for (auto&& arg : m_arguments)
        arg->setPreviousNode(previous);
}

/*
    ASTInvokeNestedNode
*/
ValueType ASTInvokeNestedNode::getNodeType()
{
    if (getFunction() != nullptr)
        return getFunction()->getNodeType();
    return ValueType::Null;
}
