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
#ifndef RPP_ABSTRACTSYNTAXTREEVISITOR_HPP
#define RPP_ABSTRACTSYNTAXTREEVISITOR_HPP

#include <automapper.hpp>
#include <errorqueue.hpp>
#include <signature.hpp>
#include <tokenliterals.hpp>
#include <valuetypes.hpp>

#include <queue>

class IASTNode;
class IASTNodeParser;
class IASTNodeLinker;
class IASTNodeEvaluator;

class IASTNode {
protected:
    using ptr_node    = std::unique_ptr<IASTNode>;
    using ptr_node_v  = std::vector<ptr_node>;
    using ptr_value   = std::unique_ptr<Value>;
    using ptr_value_v = std::vector<ptr_node>;

public:
    IASTNode(const IASTNode&)            = delete;
    IASTNode& operator=(const IASTNode&) = delete;

    IASTNode(IASTNode&&)            = default;
    IASTNode& operator=(IASTNode&&) = default;

    virtual ~IASTNode() = default;

    IASTNode()
        : m_prev(nullptr)
        , m_next()
        , m_line(0) {}

    virtual bool isDeclared(std::string_view name, NodeID id, IASTNode* caller, const Signature& signature = {}) const;
    virtual bool hasNode(NodeID id, const std::vector<NodeID>& skip_ids = {}) const;
    virtual IASTNode* findNode(const std::vector<NodeID>& ids, const std::vector<NodeID>& skip_ids, bool forward = false);

    virtual IASTNode* getLastNode();
    virtual std::vector<IASTNode*> getDeclaredObjects();
    virtual IASTNode* getNodeByName(std::string_view name, NodeID id);
    virtual IASTNode* getNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName = "");
    virtual IASTNode* getConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName = "");
    virtual IASTNode* getVariadicConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName = "");

    virtual const Signature* getSignature() const;

    virtual ValueType getNodeType();

    virtual void accept(IASTNodeParser& visitor)         = 0;
    virtual void accept(IASTNodeLinker& visitor)         = 0;
    virtual Value* accept(IASTNodeEvaluator& translator) = 0;
    virtual NodeID id() const noexcept                   = 0;

    virtual void attach([[maybe_unused]] IASTNode* previous) {}

    bool hasPreviousNode() const noexcept {
        return m_prev != nullptr;
    }

    bool hasNextNode() const noexcept {
        return m_next != nullptr;
    }

    ptr_node&& moveNextNode() noexcept {
        return std::move(m_next);
    }

    IASTNode* getPreviousNode() const noexcept {
        return m_prev;
    }

    IASTNode* getNextNode() const noexcept {
        return m_next.get();
    }

    uint32_t getLine() const noexcept {
        return m_line;
    }

    void setPreviousNode(IASTNode* prev) noexcept {
        m_prev = prev;
    }

    void setNextNode(ptr_node&& next) noexcept {
        m_next = std::move(next);
    }

    void setLine(uint32_t line) noexcept {
        m_line = line;
    }

public:
    template <typename T>
    constexpr T as() noexcept {
        return static_cast<T>(this);
    }

public:
    IASTNode* m_prev;
    ptr_node m_next;
    uint32_t m_line;
};

class ASTNullNode;
class ASTBoolNode;
class ASTIntNode;
class ASTRangeNode;
class ASTCoordNode;
class ASTFloatNode;
class ASTStringNode;
class ASTObjectNode;
template <typename T>
class ASTArrayNode;
class ASTDeclarationNode;
class ASTIdentifierNode;
class ASTVariableNode;
class ASTAnchorNode;
class ASTCountNode;
class ASTLastNode;
class ASTXNode;
class ASTYNode;
class ASTRotationNode;
class ASTEmptyNode;
class ASTFullNode;
class ASTIndexNode;
class ASTNotIndexNode;
class ASTInsertNode;
class ASTRotateNode;
class ASTOpAssignNode;
class ASTOpAddNode;
class ASTOpSubtractNode;
class ASTOpMultiplyNode;
class ASTOpDivideNode;
class ASTOpEqualNode;
class ASTOpNotEqualNode;
class ASTOpGreaterThanNode;
class ASTOpGreaterThanOrEqualNode;
class ASTOpLessThanNode;
class ASTOpLessThanOrEqualNode;
class ASTOpAndNode;
class ASTOpOrNode;
class ASTOpNotNode;
class ASTOpRangeNode;
class ASTOpCoordNode;
class ASTErrorNode;
class ASTWarningNode;
class ASTAssertNode;
class ASTReturnNode;
class ASTBreakNode;
class ASTContinueNode;
class ASTForRangeNode;
class ASTArraySubscriptNode;
class ASTPushCallNode;
class ASTHasCallNode;
class ASTUniqueCallNode;
class ASTStrCallNode;
class ASTNameCallNode;
class ASTFindCallNode;
class ASTFunctionCallNode;
class ASTNestedCallNode;
class ASTForNode;
class ASTIfNode;
class ASTFunctionIdentifierNode;
class ASTFunctionNode;
class ASTNestedIdentifierNode;
class ASTNestedFunctionNode;
class ASTInvokeNestedNode;

class IASTNodeParser : public ErrorQueue {
public:
    virtual ~IASTNodeParser() = default;

    auto&& errors() noexcept {
        return std::move(m_errors);
    }

    virtual void parse(ASTNullNode* node)                 = 0;
    virtual void parse(ASTBoolNode* node)                 = 0;
    virtual void parse(ASTIntNode* node)                  = 0;
    virtual void parse(ASTRangeNode* node)                = 0;
    virtual void parse(ASTCoordNode* node)                = 0;
    virtual void parse(ASTFloatNode* node)                = 0;
    virtual void parse(ASTStringNode* node)               = 0;
    virtual void parse(ASTObjectNode* node)               = 0;
    virtual void parse(ASTArrayNode<BoolValue>* node)     = 0;
    virtual void parse(ASTArrayNode<IntValue>* node)      = 0;
    virtual void parse(ASTArrayNode<RangeValue>* node)    = 0;
    virtual void parse(ASTArrayNode<CoordValue>* node)    = 0;
    virtual void parse(ASTArrayNode<FloatValue>* node)    = 0;
    virtual void parse(ASTArrayNode<StringValue>* node)   = 0;
    virtual void parse(ASTArrayNode<ObjectValue>* node)   = 0;
    virtual void parse(ASTDeclarationNode* node)          = 0;
    virtual void parse(ASTIdentifierNode* node)           = 0;
    virtual void parse(ASTVariableNode* node)             = 0;
    virtual void parse(ASTAnchorNode* node)               = 0;
    virtual void parse(ASTCountNode* node)                = 0;
    virtual void parse(ASTLastNode* node)                 = 0;
    virtual void parse(ASTXNode* node)                    = 0;
    virtual void parse(ASTYNode* node)                    = 0;
    virtual void parse(ASTRotationNode* node)             = 0;
    virtual void parse(ASTEmptyNode* node)                = 0;
    virtual void parse(ASTFullNode* node)                 = 0;
    virtual void parse(ASTIndexNode* node)                = 0;
    virtual void parse(ASTNotIndexNode* node)             = 0;
    virtual void parse(ASTInsertNode* node)               = 0;
    virtual void parse(ASTRotateNode* node)               = 0;
    virtual void parse(ASTOpAssignNode* node)             = 0;
    virtual void parse(ASTOpAddNode* node)                = 0;
    virtual void parse(ASTOpSubtractNode* node)           = 0;
    virtual void parse(ASTOpMultiplyNode* node)           = 0;
    virtual void parse(ASTOpDivideNode* node)             = 0;
    virtual void parse(ASTOpEqualNode* node)              = 0;
    virtual void parse(ASTOpNotEqualNode* node)           = 0;
    virtual void parse(ASTOpGreaterThanNode* node)        = 0;
    virtual void parse(ASTOpGreaterThanOrEqualNode* node) = 0;
    virtual void parse(ASTOpLessThanNode* node)           = 0;
    virtual void parse(ASTOpLessThanOrEqualNode* node)    = 0;
    virtual void parse(ASTOpAndNode* node)                = 0;
    virtual void parse(ASTOpOrNode* node)                 = 0;
    virtual void parse(ASTOpNotNode* node)                = 0;
    virtual void parse(ASTOpRangeNode* node)              = 0;
    virtual void parse(ASTOpCoordNode* node)              = 0;
    virtual void parse(ASTErrorNode* node)                = 0;
    virtual void parse(ASTWarningNode* node)              = 0;
    virtual void parse(ASTAssertNode* node)               = 0;
    virtual void parse(ASTReturnNode* node)               = 0;
    virtual void parse(ASTBreakNode* node)                = 0;
    virtual void parse(ASTContinueNode* node)             = 0;
    virtual void parse(ASTForRangeNode* node)             = 0;
    virtual void parse(ASTArraySubscriptNode* node)       = 0;
    virtual void parse(ASTPushCallNode* node)             = 0;
    virtual void parse(ASTHasCallNode* node)              = 0;
    virtual void parse(ASTUniqueCallNode* node)           = 0;
    virtual void parse(ASTStrCallNode* node)              = 0;
    virtual void parse(ASTNameCallNode* node)             = 0;
    virtual void parse(ASTFindCallNode* node)             = 0;
    virtual void parse(ASTFunctionCallNode* node)         = 0;
    virtual void parse(ASTNestedCallNode* node)           = 0;
    virtual void parse(ASTForNode* node)                  = 0;
    virtual void parse(ASTIfNode* node)                   = 0;
    virtual void parse(ASTFunctionIdentifierNode* node)   = 0;
    virtual void parse(ASTFunctionNode* node)             = 0;
    virtual void parse(ASTNestedIdentifierNode* node)     = 0;
    virtual void parse(ASTNestedFunctionNode* node)       = 0;
    virtual void parse(ASTInvokeNestedNode* node)         = 0;
};

class IASTNodeLinker : public ErrorQueue {
public:
    virtual ~IASTNodeLinker() = default;

    auto&& errors() noexcept {
        return std::move(m_errors);
    }

    virtual void link(ASTNullNode* node)                 = 0;
    virtual void link(ASTBoolNode* node)                 = 0;
    virtual void link(ASTIntNode* node)                  = 0;
    virtual void link(ASTRangeNode* node)                = 0;
    virtual void link(ASTCoordNode* node)                = 0;
    virtual void link(ASTFloatNode* node)                = 0;
    virtual void link(ASTStringNode* node)               = 0;
    virtual void link(ASTObjectNode* node)               = 0;
    virtual void link(ASTArrayNode<BoolValue>* node)     = 0;
    virtual void link(ASTArrayNode<IntValue>* node)      = 0;
    virtual void link(ASTArrayNode<RangeValue>* node)    = 0;
    virtual void link(ASTArrayNode<CoordValue>* node)    = 0;
    virtual void link(ASTArrayNode<FloatValue>* node)    = 0;
    virtual void link(ASTArrayNode<StringValue>* node)   = 0;
    virtual void link(ASTArrayNode<ObjectValue>* node)   = 0;
    virtual void link(ASTDeclarationNode* node)          = 0;
    virtual void link(ASTIdentifierNode* node)           = 0;
    virtual void link(ASTVariableNode* node)             = 0;
    virtual void link(ASTAnchorNode* node)               = 0;
    virtual void link(ASTCountNode* node)                = 0;
    virtual void link(ASTLastNode* node)                 = 0;
    virtual void link(ASTXNode* node)                    = 0;
    virtual void link(ASTYNode* node)                    = 0;
    virtual void link(ASTRotationNode* node)             = 0;
    virtual void link(ASTEmptyNode* node)                = 0;
    virtual void link(ASTFullNode* node)                 = 0;
    virtual void link(ASTIndexNode* node)                = 0;
    virtual void link(ASTNotIndexNode* node)             = 0;
    virtual void link(ASTInsertNode* node)               = 0;
    virtual void link(ASTRotateNode* node)               = 0;
    virtual void link(ASTOpAssignNode* node)             = 0;
    virtual void link(ASTOpAddNode* node)                = 0;
    virtual void link(ASTOpSubtractNode* node)           = 0;
    virtual void link(ASTOpMultiplyNode* node)           = 0;
    virtual void link(ASTOpDivideNode* node)             = 0;
    virtual void link(ASTOpEqualNode* node)              = 0;
    virtual void link(ASTOpNotEqualNode* node)           = 0;
    virtual void link(ASTOpGreaterThanNode* node)        = 0;
    virtual void link(ASTOpGreaterThanOrEqualNode* node) = 0;
    virtual void link(ASTOpLessThanNode* node)           = 0;
    virtual void link(ASTOpLessThanOrEqualNode* node)    = 0;
    virtual void link(ASTOpAndNode* node)                = 0;
    virtual void link(ASTOpOrNode* node)                 = 0;
    virtual void link(ASTOpNotNode* node)                = 0;
    virtual void link(ASTOpRangeNode* node)              = 0;
    virtual void link(ASTOpCoordNode* node)              = 0;
    virtual void link(ASTErrorNode* node)                = 0;
    virtual void link(ASTWarningNode* node)              = 0;
    virtual void link(ASTAssertNode* node)               = 0;
    virtual void link(ASTReturnNode* node)               = 0;
    virtual void link(ASTBreakNode* node)                = 0;
    virtual void link(ASTContinueNode* node)             = 0;
    virtual void link(ASTForRangeNode* node)             = 0;
    virtual void link(ASTArraySubscriptNode* node)       = 0;
    virtual void link(ASTPushCallNode* node)             = 0;
    virtual void link(ASTHasCallNode* node)              = 0;
    virtual void link(ASTUniqueCallNode* node)           = 0;
    virtual void link(ASTStrCallNode* node)              = 0;
    virtual void link(ASTNameCallNode* node)             = 0;
    virtual void link(ASTFindCallNode* node)             = 0;
    virtual void link(ASTFunctionCallNode* node)         = 0;
    virtual void link(ASTNestedCallNode* node)           = 0;
    virtual void link(ASTForNode* node)                  = 0;
    virtual void link(ASTIfNode* node)                   = 0;
    virtual void link(ASTFunctionIdentifierNode* node)   = 0;
    virtual void link(ASTFunctionNode* node)             = 0;
    virtual void link(ASTNestedIdentifierNode* node)     = 0;
    virtual void link(ASTNestedFunctionNode* node)       = 0;
    virtual void link(ASTInvokeNestedNode* node)         = 0;
};

class IASTNodeEvaluator : public ErrorQueue {
protected:
    using ptr_node    = std::unique_ptr<IASTNode>;
    using ptr_node_v  = std::vector<ptr_node>;
    using ptr_value   = std::unique_ptr<Value>;
    using ptr_value_v = std::vector<ptr_value>;

public:
    virtual ~IASTNodeEvaluator() = default;

    IASTNodeEvaluator()
        : m_automappers()
        , m_calls()
        , m_stack()
        , m_failed(false)
        , m_returned(false)
        , m_warnings(false)
        , m_break(false)
        , m_continue(false) {}

    auto&& errors() noexcept {
        return std::move(m_errors);
    }

    std::vector<AutoMapper>& automappers() noexcept {
        return m_automappers;
    }

    bool failed() const noexcept {
        return m_failed;
    }

    virtual Value* evaluate(ASTNullNode* node)                 = 0;
    virtual Value* evaluate(ASTBoolNode* node)                 = 0;
    virtual Value* evaluate(ASTIntNode* node)                  = 0;
    virtual Value* evaluate(ASTRangeNode* node)                = 0;
    virtual Value* evaluate(ASTCoordNode* node)                = 0;
    virtual Value* evaluate(ASTFloatNode* node)                = 0;
    virtual Value* evaluate(ASTStringNode* node)               = 0;
    virtual Value* evaluate(ASTObjectNode* node)               = 0;
    virtual Value* evaluate(ASTArrayNode<BoolValue>* node)     = 0;
    virtual Value* evaluate(ASTArrayNode<IntValue>* node)      = 0;
    virtual Value* evaluate(ASTArrayNode<RangeValue>* node)    = 0;
    virtual Value* evaluate(ASTArrayNode<CoordValue>* node)    = 0;
    virtual Value* evaluate(ASTArrayNode<FloatValue>* node)    = 0;
    virtual Value* evaluate(ASTArrayNode<StringValue>* node)   = 0;
    virtual Value* evaluate(ASTArrayNode<ObjectValue>* node)   = 0;
    virtual Value* evaluate(ASTDeclarationNode* node)          = 0;
    virtual Value* evaluate(ASTIdentifierNode* node)           = 0;
    virtual Value* evaluate(ASTVariableNode* node)             = 0;
    virtual Value* evaluate(ASTAnchorNode* node)               = 0;
    virtual Value* evaluate(ASTCountNode* node)                = 0;
    virtual Value* evaluate(ASTLastNode* node)                 = 0;
    virtual Value* evaluate(ASTXNode* node)                    = 0;
    virtual Value* evaluate(ASTYNode* node)                    = 0;
    virtual Value* evaluate(ASTRotationNode* node)             = 0;
    virtual Value* evaluate(ASTEmptyNode* node)                = 0;
    virtual Value* evaluate(ASTFullNode* node)                 = 0;
    virtual Value* evaluate(ASTIndexNode* node)                = 0;
    virtual Value* evaluate(ASTNotIndexNode* node)             = 0;
    virtual Value* evaluate(ASTInsertNode* node)               = 0;
    virtual Value* evaluate(ASTRotateNode* node)               = 0;
    virtual Value* evaluate(ASTOpAssignNode* node)             = 0;
    virtual Value* evaluate(ASTOpAddNode* node)                = 0;
    virtual Value* evaluate(ASTOpSubtractNode* node)           = 0;
    virtual Value* evaluate(ASTOpMultiplyNode* node)           = 0;
    virtual Value* evaluate(ASTOpDivideNode* node)             = 0;
    virtual Value* evaluate(ASTOpEqualNode* node)              = 0;
    virtual Value* evaluate(ASTOpNotEqualNode* node)           = 0;
    virtual Value* evaluate(ASTOpGreaterThanNode* node)        = 0;
    virtual Value* evaluate(ASTOpGreaterThanOrEqualNode* node) = 0;
    virtual Value* evaluate(ASTOpLessThanNode* node)           = 0;
    virtual Value* evaluate(ASTOpLessThanOrEqualNode* node)    = 0;
    virtual Value* evaluate(ASTOpAndNode* node)                = 0;
    virtual Value* evaluate(ASTOpOrNode* node)                 = 0;
    virtual Value* evaluate(ASTOpNotNode* node)                = 0;
    virtual Value* evaluate(ASTOpRangeNode* node)              = 0;
    virtual Value* evaluate(ASTOpCoordNode* node)              = 0;
    virtual Value* evaluate(ASTErrorNode* node)                = 0;
    virtual Value* evaluate(ASTWarningNode* node)              = 0;
    virtual Value* evaluate(ASTAssertNode* node)               = 0;
    virtual Value* evaluate(ASTReturnNode* node)               = 0;
    virtual Value* evaluate(ASTBreakNode* node)                = 0;
    virtual Value* evaluate(ASTContinueNode* node)             = 0;
    virtual Value* evaluate(ASTForRangeNode* node)             = 0;
    virtual Value* evaluate(ASTArraySubscriptNode* node)       = 0;
    virtual Value* evaluate(ASTPushCallNode* node)             = 0;
    virtual Value* evaluate(ASTHasCallNode* node)              = 0;
    virtual Value* evaluate(ASTUniqueCallNode* node)           = 0;
    virtual Value* evaluate(ASTStrCallNode* node)              = 0;
    virtual Value* evaluate(ASTNameCallNode* node)             = 0;
    virtual Value* evaluate(ASTFindCallNode* node)             = 0;
    virtual Value* evaluate(ASTFunctionCallNode* node)         = 0;
    virtual Value* evaluate(ASTNestedCallNode* node)           = 0;
    virtual Value* evaluate(ASTForNode* node)                  = 0;
    virtual Value* evaluate(ASTIfNode* node)                   = 0;
    virtual Value* evaluate(ASTFunctionIdentifierNode* node)   = 0;
    virtual Value* evaluate(ASTFunctionNode* node)             = 0;
    virtual Value* evaluate(ASTNestedIdentifierNode* node)     = 0;
    virtual Value* evaluate(ASTNestedFunctionNode* node)       = 0;
    virtual Value* evaluate(ASTInvokeNestedNode* node)         = 0;

protected:
    std::vector<AutoMapper> m_automappers;
    std::vector<ASTFunctionCallNode*> m_calls;
    ptr_value_v m_stack;
    bool m_failed;
    bool m_returned;
    bool m_warnings;
    bool m_break;
    bool m_continue;
};

/*
    Nodes
*/
class ASTNullNode final : public IASTNode {
public:
    ASTNullNode(const ASTNullNode&)            = delete;
    ASTNullNode& operator=(const ASTNullNode&) = delete;

    ASTNullNode(ASTNullNode&&)            = default;
    ASTNullNode& operator=(ASTNullNode&&) = default;

    ASTNullNode() = default;

    bool isDeclared(std::string_view name, NodeID id, IASTNode* caller, const Signature& signature) const final;

    IASTNode* getNodeByName(std::string_view name, NodeID id) final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Null;
    }
};

class ASTBoolNode final : public IASTNode {
public:
    ASTBoolNode(const ASTBoolNode&)            = delete;
    ASTBoolNode& operator=(const ASTBoolNode&) = delete;

    ASTBoolNode(ASTBoolNode&&)            = default;
    ASTBoolNode& operator=(ASTBoolNode&&) = default;

    ASTBoolNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Bool;
    }

    BoolValue* getValue() noexcept {
        return &m_value;
    }

    void setValue(const BoolValue& value) noexcept {
        m_value = value;
    }

    void setValue(BoolValue&& value) noexcept {
        m_value = std::move(value);
    }

private:
    BoolValue m_value;
};

class ASTIntNode final : public IASTNode {
public:
    ASTIntNode(const ASTIntNode&)            = delete;
    ASTIntNode& operator=(const ASTIntNode&) = delete;

    ASTIntNode(ASTIntNode&&)            = default;
    ASTIntNode& operator=(ASTIntNode&&) = default;

    ASTIntNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Int;
    }

    IntValue* getValue() noexcept {
        return &m_value;
    }

    void setValue(const IntValue& value) noexcept {
        m_value = value;
    }

    void setValue(IntValue&& value) noexcept {
        m_value = std::move(value);
    }

private:
    IntValue m_value;
};

class ASTRangeNode final : public IASTNode {
public:
    ASTRangeNode(const ASTRangeNode&)            = delete;
    ASTRangeNode& operator=(const ASTRangeNode&) = delete;

    ASTRangeNode(ASTRangeNode&&)            = default;
    ASTRangeNode& operator=(ASTRangeNode&&) = default;

    ASTRangeNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Range;
    }

    RangeValue* getValue() noexcept {
        return &m_value;
    }

    void setValue(const RangeValue& value) noexcept {
        m_value = value;
    }

    void setValue(RangeValue&& value) noexcept {
        m_value = std::move(value);
    }

private:
    RangeValue m_value;
};

class ASTCoordNode final : public IASTNode {
public:
    ASTCoordNode(const ASTCoordNode&)            = delete;
    ASTCoordNode& operator=(const ASTCoordNode&) = delete;

    ASTCoordNode(ASTCoordNode&&)            = default;
    ASTCoordNode& operator=(ASTCoordNode&&) = default;

    ASTCoordNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Coord;
    }

    CoordValue* getValue() noexcept {
        return &m_value;
    }

    void setValue(const CoordValue& value) noexcept {
        m_value = value;
    }

    void setValue(CoordValue&& value) noexcept {
        m_value = std::move(value);
    }

private:
    CoordValue m_value;
};

class ASTFloatNode final : public IASTNode {
public:
    ASTFloatNode(const ASTFloatNode&)            = delete;
    ASTFloatNode& operator=(const ASTFloatNode&) = delete;

    ASTFloatNode(ASTFloatNode&&)            = default;
    ASTFloatNode& operator=(ASTFloatNode&&) = default;

    ASTFloatNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Float;
    }

    FloatValue* getValue() noexcept {
        return &m_value;
    }

    void setValue(const FloatValue& value) noexcept {
        m_value = value;
    }

    void setValue(FloatValue&& value) noexcept {
        m_value = std::move(value);
    }

private:
    FloatValue m_value;
};

class ASTStringNode final : public IASTNode {
public:
    ASTStringNode(const ASTStringNode&)            = delete;
    ASTStringNode& operator=(const ASTStringNode&) = delete;

    ASTStringNode(ASTStringNode&&)            = default;
    ASTStringNode& operator=(ASTStringNode&&) = default;

    ASTStringNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::String;
    }

    StringValue* getValue() noexcept {
        return &m_value;
    }

    void setValue(const StringValue& value) noexcept {
        m_value = value;
    }

    void setValue(StringValue&& value) noexcept {
        m_value = std::move(value);
    }

private:
    StringValue m_value;
};

class ASTObjectNode final : public IASTNode {
public:
    ASTObjectNode(const ASTObjectNode&)            = delete;
    ASTObjectNode& operator=(const ASTObjectNode&) = delete;

    ASTObjectNode(ASTObjectNode&&)            = default;
    ASTObjectNode& operator=(ASTObjectNode&&) = default;

    ASTObjectNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Object;
    }

    ObjectValue* getValue() noexcept {
        return &m_value;
    }

    void setValue(const ObjectValue& value) noexcept {
        m_value = value;
    }

    void setValue(ObjectValue&& value) noexcept {
        m_value = std::move(value);
    }

private:
    ObjectValue m_value;
};

template <typename T>
class ASTArrayNode final : public IASTNode {
public:
    ASTArrayNode(const ASTArrayNode&)            = delete;
    ASTArrayNode& operator=(const ASTArrayNode&) = delete;

    ASTArrayNode(ASTArrayNode&&)            = default;
    ASTArrayNode& operator=(ASTArrayNode&&) = default;

    ASTArrayNode() = default;

    ValueType getNodeType() final {
        return m_value.type();
    }

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Array;
    }

    ArrayValue<T>* getValue() noexcept {
        return &m_value;
    }

    void setValue(const ArrayValue<T>& value) noexcept {
        m_value = value;
    }

    void setValue(ArrayValue<T>&& value) noexcept {
        m_value = std::move(value);
    }

private:
    ArrayValue<T> m_value;
};

class ASTDeclarationNode final : public IASTNode {
public:
    ASTDeclarationNode(const ASTDeclarationNode&)            = delete;
    ASTDeclarationNode& operator=(const ASTDeclarationNode&) = delete;

    ASTDeclarationNode(ASTDeclarationNode&&)            = default;
    ASTDeclarationNode& operator=(ASTDeclarationNode&&) = default;

    ASTDeclarationNode() = default;

    bool isDeclared(std::string_view name, NodeID id, IASTNode* caller, const Signature& signature = {}) const final;

    IASTNode* getLastNode() final;
    std::vector<IASTNode*> getDeclaredObjects() final;
    IASTNode* getNodeByName(std::string_view name, NodeID id) final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Declaration;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getIdentifier() const noexcept {
        return m_identifier.get();
    }

    IASTNode* getNode() const noexcept {
        return m_node.get();
    }

    void setIdentifier(ptr_node&& identifier) noexcept {
        m_identifier = std::move(identifier);
    }

    void setNode(ptr_node&& node) noexcept {
        m_node = std::move(node);
    }

private:
    ptr_node m_identifier;
    ptr_node m_node;
};

class ASTIdentifierNode final : public IASTNode {
public:
    ASTIdentifierNode(const ASTIdentifierNode&)            = delete;
    ASTIdentifierNode& operator=(const ASTIdentifierNode&) = delete;

    ASTIdentifierNode(ASTIdentifierNode&&)            = default;
    ASTIdentifierNode& operator=(ASTIdentifierNode&&) = default;

    ASTIdentifierNode()
        : IASTNode()
        , m_name()
        , m_type(ValueType::Null)
        , m_value() {}

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Identifier;
    }

    const std::string& getName() const noexcept {
        return m_name;
    }

    ValueType getType() const noexcept {
        return m_type;
    }

    Value* getValue() const noexcept {
        return m_value.get();
    }

    void setName(std::string_view name) {
        m_name = name;
    }

    void setType(ValueType type) noexcept {
        m_type = type;
    }

    void setValue(ptr_value&& value) noexcept {
        m_value = std::move(value);
    }

private:
    std::string m_name;
    ValueType m_type;
    ptr_value m_value;
};

class ASTVariableNode final : public IASTNode {
public:
    ASTVariableNode(const ASTVariableNode&)            = delete;
    ASTVariableNode& operator=(const ASTVariableNode&) = delete;

    ASTVariableNode(ASTVariableNode&&)            = default;
    ASTVariableNode& operator=(ASTVariableNode&&) = default;

    ASTVariableNode()
        : IASTNode()
        , m_name()
        , m_identifier(nullptr) {}

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Variable;
    }

    const std::string& getName() const noexcept {
        return m_name;
    }

    IASTNode* getIdentifier() const noexcept {
        return m_identifier;
    }

    void setName(std::string_view name) {
        m_name = name;
    }

    void setIdentifier(IASTNode* identifier) noexcept {
        m_identifier = identifier;
    }

private:
    std::string m_name;
    IASTNode* m_identifier;
};

class ASTAnchorNode final : public IASTNode {
public:
    ASTAnchorNode(const ASTAnchorNode&)            = delete;
    ASTAnchorNode& operator=(const ASTAnchorNode&) = delete;

    ASTAnchorNode(ASTAnchorNode&&)            = default;
    ASTAnchorNode& operator=(ASTAnchorNode&&) = default;

    ASTAnchorNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Anchor;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getNode() const noexcept {
        return m_node.get();
    }

    void setNode(ptr_node&& node) noexcept {
        m_node = std::move(node);
    }

private:
    ptr_node m_node;
};

class ASTCountNode final : public IASTNode {
public:
    ASTCountNode(const ASTCountNode&)            = delete;
    ASTCountNode& operator=(const ASTCountNode&) = delete;

    ASTCountNode(ASTCountNode&&)            = default;
    ASTCountNode& operator=(ASTCountNode&&) = default;

    ASTCountNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Count;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getNode() const noexcept {
        return m_node.get();
    }

    void setNode(ptr_node&& node) noexcept {
        m_node = std::move(node);
    }

private:
    ptr_node m_node;
};

class ASTLastNode final : public IASTNode {
public:
    ASTLastNode(const ASTLastNode&)            = delete;
    ASTLastNode& operator=(const ASTLastNode&) = delete;

    ASTLastNode(ASTLastNode&&)            = default;
    ASTLastNode& operator=(ASTLastNode&&) = default;

    ASTLastNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Last;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getNode() const noexcept {
        return m_node.get();
    }

    void setNode(ptr_node&& node) noexcept {
        m_node = std::move(node);
    }

private:
    ptr_node m_node;
};

class ASTXNode final : public IASTNode {
public:
    ASTXNode(const ASTXNode&)            = delete;
    ASTXNode& operator=(const ASTXNode&) = delete;

    ASTXNode(ASTXNode&&)            = default;
    ASTXNode& operator=(ASTXNode&&) = default;

    ASTXNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::X;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getNode() const noexcept {
        return m_node.get();
    }

    void setNode(ptr_node&& node) noexcept {
        m_node = std::move(node);
    }

private:
    ptr_node m_node;
};

class ASTYNode final : public IASTNode {
public:
    ASTYNode(const ASTYNode&)            = delete;
    ASTYNode& operator=(const ASTYNode&) = delete;

    ASTYNode(ASTYNode&&)            = default;
    ASTYNode& operator=(ASTYNode&&) = default;

    ASTYNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Y;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getNode() const noexcept {
        return m_node.get();
    }

    void setNode(ptr_node&& node) noexcept {
        m_node = std::move(node);
    }

private:
    ptr_node m_node;
};

class ASTRotationNode final : public IASTNode {
public:
    ASTRotationNode(const ASTRotationNode&)            = delete;
    ASTRotationNode& operator=(const ASTRotationNode&) = delete;

    ASTRotationNode(ASTRotationNode&&)            = default;
    ASTRotationNode& operator=(ASTRotationNode&&) = default;

    ASTRotationNode()
        : m_rotation(Rotation::Default)
        , m_node() {}

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Rotation;
    }

    void attach(IASTNode* previous) final;

    Rotation getRotation() const noexcept {
        return m_rotation;
    }

    IASTNode* getNode() const noexcept {
        return m_node.get();
    }

    void setRotation(Rotation rotation) noexcept {
        m_rotation = rotation;
    }

    void setNode(ptr_node&& node) noexcept {
        m_node = std::move(node);
    }

private:
    Rotation m_rotation;
    ptr_node m_node;
};

class ASTEmptyNode final : public IASTNode {
public:
    ASTEmptyNode(const ASTEmptyNode&)            = delete;
    ASTEmptyNode& operator=(const ASTEmptyNode&) = delete;

    ASTEmptyNode(ASTEmptyNode&&)            = default;
    ASTEmptyNode& operator=(ASTEmptyNode&&) = default;

    ASTEmptyNode() = default;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Empty;
    }
};

class ASTFullNode final : public IASTNode {
public:
    ASTFullNode(const ASTFullNode&)            = delete;
    ASTFullNode& operator=(const ASTFullNode&) = delete;

    ASTFullNode(ASTFullNode&&)            = default;
    ASTFullNode& operator=(ASTFullNode&&) = default;

    ASTFullNode() = default;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Full;
    }
};

class ASTIndexNode final : public IASTNode {
public:
    ASTIndexNode(const ASTIndexNode&)            = delete;
    ASTIndexNode& operator=(const ASTIndexNode&) = delete;

    ASTIndexNode(ASTIndexNode&&)            = default;
    ASTIndexNode& operator=(ASTIndexNode&&) = default;

    ASTIndexNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Index;
    }
};

class ASTNotIndexNode final : public IASTNode {
public:
    ASTNotIndexNode(const ASTNotIndexNode&)            = delete;
    ASTNotIndexNode& operator=(const ASTNotIndexNode&) = delete;

    ASTNotIndexNode(ASTNotIndexNode&&)            = default;
    ASTNotIndexNode& operator=(ASTNotIndexNode&&) = default;

    ASTNotIndexNode() = default;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::NotIndex;
    }
};

class ASTInsertNode final : public IASTNode {
public:
    ASTInsertNode(const ASTInsertNode&)            = delete;
    ASTInsertNode& operator=(const ASTInsertNode&) = delete;

    ASTInsertNode(ASTInsertNode&&)            = default;
    ASTInsertNode& operator=(ASTInsertNode&&) = default;

    ASTInsertNode()
        : m_control(InsertC::Default)
        , m_node() {}

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Insert;
    }

    void attach(IASTNode* previous) final;

    InsertC getControl() const noexcept {
        return m_control;
    }

    IASTNode* getNode() const noexcept {
        return m_node.get();
    }

    void setControl(InsertC control) noexcept {
        m_control = control;
    }

    void setNode(ptr_node&& node) noexcept {
        m_node = std::move(node);
    }

private:
    InsertC m_control;
    ptr_node m_node;
};

class ASTRotateNode final : public IASTNode {
public:
    ASTRotateNode(const ASTRotateNode&)            = delete;
    ASTRotateNode& operator=(const ASTRotateNode&) = delete;

    ASTRotateNode(ASTRotateNode&&)            = default;
    ASTRotateNode& operator=(ASTRotateNode&&) = default;

    ASTRotateNode()
        : IASTNode()
        , m_rotation(Rotation::Default)
        , m_node() {}

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Rotate;
    }

    void attach(IASTNode* previous) final;

    Rotation getRotation() const noexcept {
        return m_rotation;
    }

    IASTNode* getNode() const noexcept {
        return m_node.get();
    }

    void setRotation(Rotation rotation) noexcept {
        m_rotation = rotation;
    }

    void setNode(ptr_node&& node) noexcept {
        m_node = std::move(node);
    }

private:
    Rotation m_rotation;
    ptr_node m_node;
};

class ASTOpAssignNode final : public IASTNode {
public:
    ASTOpAssignNode(const ASTOpAssignNode&)            = delete;
    ASTOpAssignNode& operator=(const ASTOpAssignNode&) = delete;

    ASTOpAssignNode(ASTOpAssignNode&&)            = default;
    ASTOpAssignNode& operator=(ASTOpAssignNode&&) = default;

    ASTOpAssignNode() = default;

    IASTNode* getLastNode() final;
    std::vector<IASTNode*> getDeclaredObjects() final;
    IASTNode* getNodeByName(std::string_view name, NodeID id) final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpAssign;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpAddNode final : public IASTNode {
public:
    ASTOpAddNode(const ASTOpAddNode&)            = delete;
    ASTOpAddNode& operator=(const ASTOpAddNode&) = delete;

    ASTOpAddNode(ASTOpAddNode&&)            = default;
    ASTOpAddNode& operator=(ASTOpAddNode&&) = default;

    ASTOpAddNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpAdd;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpSubtractNode final : public IASTNode {
public:
    ASTOpSubtractNode(const ASTOpSubtractNode&)            = delete;
    ASTOpSubtractNode& operator=(const ASTOpSubtractNode&) = delete;

    ASTOpSubtractNode(ASTOpSubtractNode&&)            = default;
    ASTOpSubtractNode& operator=(ASTOpSubtractNode&&) = default;

    ASTOpSubtractNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpSubtract;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpMultiplyNode final : public IASTNode {
public:
    ASTOpMultiplyNode(const ASTOpMultiplyNode&)            = delete;
    ASTOpMultiplyNode& operator=(const ASTOpMultiplyNode&) = delete;

    ASTOpMultiplyNode(ASTOpMultiplyNode&&)            = default;
    ASTOpMultiplyNode& operator=(ASTOpMultiplyNode&&) = default;

    ASTOpMultiplyNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpMultiply;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpDivideNode final : public IASTNode {
public:
    ASTOpDivideNode(const ASTOpDivideNode&)            = delete;
    ASTOpDivideNode& operator=(const ASTOpDivideNode&) = delete;

    ASTOpDivideNode(ASTOpDivideNode&&)            = default;
    ASTOpDivideNode& operator=(ASTOpDivideNode&&) = default;

    ASTOpDivideNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpDivide;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpEqualNode final : public IASTNode {
public:
    ASTOpEqualNode(const ASTOpEqualNode&)            = delete;
    ASTOpEqualNode& operator=(const ASTOpEqualNode&) = delete;

    ASTOpEqualNode(ASTOpEqualNode&&)            = default;
    ASTOpEqualNode& operator=(ASTOpEqualNode&&) = default;

    ASTOpEqualNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpEqual;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpNotEqualNode final : public IASTNode {
public:
    ASTOpNotEqualNode(const ASTOpNotEqualNode&)            = delete;
    ASTOpNotEqualNode& operator=(const ASTOpNotEqualNode&) = delete;

    ASTOpNotEqualNode(ASTOpNotEqualNode&&)            = default;
    ASTOpNotEqualNode& operator=(ASTOpNotEqualNode&&) = default;

    ASTOpNotEqualNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpNotEqual;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpGreaterThanNode final : public IASTNode {
public:
    ASTOpGreaterThanNode(const ASTOpGreaterThanNode&)            = delete;
    ASTOpGreaterThanNode& operator=(const ASTOpGreaterThanNode&) = delete;

    ASTOpGreaterThanNode(ASTOpGreaterThanNode&&)            = default;
    ASTOpGreaterThanNode& operator=(ASTOpGreaterThanNode&&) = default;

    ASTOpGreaterThanNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpGreaterThan;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpGreaterThanOrEqualNode final : public IASTNode {
public:
    ASTOpGreaterThanOrEqualNode(const ASTOpGreaterThanOrEqualNode&)            = delete;
    ASTOpGreaterThanOrEqualNode& operator=(const ASTOpGreaterThanOrEqualNode&) = delete;

    ASTOpGreaterThanOrEqualNode(ASTOpGreaterThanOrEqualNode&&)            = default;
    ASTOpGreaterThanOrEqualNode& operator=(ASTOpGreaterThanOrEqualNode&&) = default;

    ASTOpGreaterThanOrEqualNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpGreaterThanOrEqual;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpLessThanNode final : public IASTNode {
public:
    ASTOpLessThanNode(const ASTOpLessThanNode&)            = delete;
    ASTOpLessThanNode& operator=(const ASTOpLessThanNode&) = delete;

    ASTOpLessThanNode(ASTOpLessThanNode&&)            = default;
    ASTOpLessThanNode& operator=(ASTOpLessThanNode&&) = default;

    ASTOpLessThanNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpLessThan;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpLessThanOrEqualNode final : public IASTNode {
public:
    ASTOpLessThanOrEqualNode(const ASTOpLessThanOrEqualNode&)            = delete;
    ASTOpLessThanOrEqualNode& operator=(const ASTOpLessThanOrEqualNode&) = delete;

    ASTOpLessThanOrEqualNode(ASTOpLessThanOrEqualNode&&)            = default;
    ASTOpLessThanOrEqualNode& operator=(ASTOpLessThanOrEqualNode&&) = default;

    ASTOpLessThanOrEqualNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpLessThanOrEqual;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpAndNode final : public IASTNode {
public:
    ASTOpAndNode(const ASTOpAndNode&)            = delete;
    ASTOpAndNode& operator=(const ASTOpAndNode&) = delete;

    ASTOpAndNode(ASTOpAndNode&&)            = default;
    ASTOpAndNode& operator=(ASTOpAndNode&&) = default;

    ASTOpAndNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpAnd;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpOrNode final : public IASTNode {
public:
    ASTOpOrNode(const ASTOpOrNode&)            = delete;
    ASTOpOrNode& operator=(const ASTOpOrNode&) = delete;

    ASTOpOrNode(ASTOpOrNode&&)            = default;
    ASTOpOrNode& operator=(ASTOpOrNode&&) = default;

    ASTOpOrNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpOr;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpNotNode final : public IASTNode {
public:
    ASTOpNotNode(const ASTOpNotNode&)            = delete;
    ASTOpNotNode& operator=(const ASTOpNotNode&) = delete;

    ASTOpNotNode(ASTOpNotNode&&)            = default;
    ASTOpNotNode& operator=(ASTOpNotNode&&) = default;

    ASTOpNotNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpNot;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveExpr() noexcept {
        return std::move(m_expr);
    }

    IASTNode* getExpr() const noexcept {
        return m_expr.get();
    }

    void setExpr(ptr_node&& left) noexcept {
        m_expr = std::move(left);
    }

private:
    ptr_node m_expr;
};

class ASTOpRangeNode final : public IASTNode {
public:
    ASTOpRangeNode(const ASTOpRangeNode&)            = delete;
    ASTOpRangeNode& operator=(const ASTOpRangeNode&) = delete;

    ASTOpRangeNode(ASTOpRangeNode&&)            = default;
    ASTOpRangeNode& operator=(ASTOpRangeNode&&) = default;

    ASTOpRangeNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpRange;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTOpCoordNode final : public IASTNode {
public:
    ASTOpCoordNode(const ASTOpCoordNode&)            = delete;
    ASTOpCoordNode& operator=(const ASTOpCoordNode&) = delete;

    ASTOpCoordNode(ASTOpCoordNode&&)            = default;
    ASTOpCoordNode& operator=(ASTOpCoordNode&&) = default;

    ASTOpCoordNode() = default;

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::OpCoord;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveLeft() noexcept {
        return std::move(m_left);
    }

    ptr_node&& moveRight() noexcept {
        return std::move(m_right);
    }

    IASTNode* getLeft() const noexcept {
        return m_left.get();
    }

    IASTNode* getRight() const noexcept {
        return m_right.get();
    }

    void setLeft(ptr_node&& left) noexcept {
        m_left = std::move(left);
    }

    void setRight(ptr_node&& right) noexcept {
        m_right = std::move(right);
    }

private:
    ptr_node m_left;
    ptr_node m_right;
};

class ASTErrorNode final : public IASTNode {
public:
    ASTErrorNode(const ASTErrorNode&)            = delete;
    ASTErrorNode& operator=(const ASTErrorNode&) = delete;

    ASTErrorNode(ASTErrorNode&&)            = default;
    ASTErrorNode& operator=(ASTErrorNode&&) = default;

    ASTErrorNode() = default;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Error;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getString() const noexcept {
        return m_string.get();
    }

    void setString(ptr_node&& string) noexcept {
        m_string = std::move(string);
    }

private:
    ptr_node m_string;
};

class ASTWarningNode final : public IASTNode {
public:
    ASTWarningNode(const ASTWarningNode&)            = delete;
    ASTWarningNode& operator=(const ASTWarningNode&) = delete;

    ASTWarningNode(ASTWarningNode&&)            = default;
    ASTWarningNode& operator=(ASTWarningNode&&) = default;

    ASTWarningNode() = default;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Warning;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getString() const noexcept {
        return m_string.get();
    }

    void setString(ptr_node&& string) noexcept {
        m_string = std::move(string);
    }

private:
    ptr_node m_string;
};

class ASTAssertNode final : public IASTNode {
public:
    ASTAssertNode(const ASTAssertNode&)            = delete;
    ASTAssertNode& operator=(const ASTAssertNode&) = delete;

    ASTAssertNode(ASTAssertNode&&)            = default;
    ASTAssertNode& operator=(ASTAssertNode&&) = default;

    ASTAssertNode() = default;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Assert;
    }

    void attach(IASTNode* previous) final;

    ptr_node&& moveExpr() noexcept {
        return std::move(m_expr);
    }

    IASTNode* getExpr() const noexcept {
        return m_expr.get();
    }

    void setExpr(ptr_node&& left) noexcept {
        m_expr = std::move(left);
    }

private:
    ptr_node m_expr;
};

class ASTReturnNode final : public IASTNode {
public:
    ASTReturnNode(const ASTReturnNode&)            = delete;
    ASTReturnNode& operator=(const ASTReturnNode&) = delete;

    ASTReturnNode(ASTReturnNode&&)            = default;
    ASTReturnNode& operator=(ASTReturnNode&&) = default;

    ASTReturnNode()
        : m_function(nullptr)
        , m_node() {}

    IASTNode* getLastNode() final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Return;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getFunction() const noexcept {
        return m_function;
    }

    IASTNode* getNode() const noexcept {
        return m_node.get();
    }

    void setFunction(IASTNode* function) noexcept {
        m_function = function;
    }

    void setNode(ptr_node&& node) noexcept {
        m_node = std::move(node);
    }

private:
    IASTNode* m_function;
    ptr_node m_node;
};

class ASTBreakNode final : public IASTNode {
public:
    ASTBreakNode(const ASTBreakNode&)            = delete;
    ASTBreakNode& operator=(const ASTBreakNode&) = delete;

    ASTBreakNode(ASTBreakNode&&)            = default;
    ASTBreakNode& operator=(ASTBreakNode&&) = default;

    ASTBreakNode() = default;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Break;
    }
};

class ASTContinueNode final : public IASTNode {
public:
    ASTContinueNode(const ASTContinueNode&)            = delete;
    ASTContinueNode& operator=(const ASTContinueNode&) = delete;

    ASTContinueNode(ASTContinueNode&&)            = default;
    ASTContinueNode& operator=(ASTContinueNode&&) = default;

    ASTContinueNode() = default;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Continue;
    }
};

class ASTForRangeNode final : public IASTNode {
public:
    ASTForRangeNode(const ASTForRangeNode&)            = delete;
    ASTForRangeNode& operator=(const ASTForRangeNode&) = delete;

    ASTForRangeNode(ASTForRangeNode&&)            = default;
    ASTForRangeNode& operator=(ASTForRangeNode&&) = default;

    ASTForRangeNode() = default;

    IASTNode* getLastNode() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::ForRange;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getDeclaration() const noexcept {
        return m_declaration.get();
    }

    IASTNode* getTo() const noexcept {
        return m_to.get();
    }

    void setDeclaration(ptr_node&& declaration) noexcept {
        m_declaration = std::move(declaration);
    }

    void setTo(ptr_node&& to) noexcept {
        m_to = std::move(to);
    }

private:
    ptr_node m_declaration;
    ptr_node m_to;
};

class ASTArraySubscriptNode final : public IASTNode {
public:
    ASTArraySubscriptNode(const ASTArraySubscriptNode&)            = delete;
    ASTArraySubscriptNode& operator=(const ASTArraySubscriptNode&) = delete;

    ASTArraySubscriptNode(ASTArraySubscriptNode&&)            = default;
    ASTArraySubscriptNode& operator=(ASTArraySubscriptNode&&) = default;

    ASTArraySubscriptNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::ArraySubscript;
    }

    void attach(IASTNode* previous) final;

    const std::string& getName() const noexcept {
        return m_name;
    }

    IASTNode* getArray() const noexcept {
        return m_array.get();
    }

    IASTNode* getIndex() const noexcept {
        return m_index.get();
    }

    void setName(const std::string& name) {
        m_name = name;
    }

    void setArray(ptr_node&& array) noexcept {
        m_array = std::move(array);
    }

    void setIndex(ptr_node&& index) noexcept {
        m_index = std::move(index);
    }

private:
    std::string m_name;
    ptr_node m_array;
    ptr_node m_index;
};

class ASTPushCallNode final : public IASTNode {
public:
    ASTPushCallNode(const ASTPushCallNode&)            = delete;
    ASTPushCallNode& operator=(const ASTPushCallNode&) = delete;

    ASTPushCallNode(ASTPushCallNode&&)            = default;
    ASTPushCallNode& operator=(ASTPushCallNode&&) = default;

    ASTPushCallNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::PushCall;
    }

    void attach(IASTNode* previous) final;

    const ptr_node_v& getArguments() const noexcept {
        return m_arguments;
    }

    IASTNode* getVariable() const noexcept {
        return m_variable.get();
    }

    void setArguments(ptr_node_v&& arguments) {
        m_arguments = std::move(arguments);
    }

    void setVariable(ptr_node&& variable) {
        m_variable = std::move(variable);
    }

private:
    ptr_node_v m_arguments;
    ptr_node m_variable;
};

class ASTHasCallNode final : public IASTNode {
public:
    ASTHasCallNode(const ASTHasCallNode&)            = delete;
    ASTHasCallNode& operator=(const ASTHasCallNode&) = delete;

    ASTHasCallNode(ASTHasCallNode&&)            = default;
    ASTHasCallNode& operator=(ASTHasCallNode&&) = default;

    ASTHasCallNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::HasCall;
    }

    void attach(IASTNode* previous) final;

    const ptr_node_v& getArguments() const noexcept {
        return m_arguments;
    }

    IASTNode* getVariable() const noexcept {
        return m_variable.get();
    }

    void setArguments(ptr_node_v&& arguments) {
        m_arguments = std::move(arguments);
    }

    void setVariable(ptr_node&& variable) {
        m_variable = std::move(variable);
    }

private:
    ptr_node_v m_arguments;
    ptr_node m_variable;
};

class ASTUniqueCallNode final : public IASTNode {
public:
    ASTUniqueCallNode(const ASTUniqueCallNode&)            = delete;
    ASTUniqueCallNode& operator=(const ASTUniqueCallNode&) = delete;

    ASTUniqueCallNode(ASTUniqueCallNode&&)            = default;
    ASTUniqueCallNode& operator=(ASTUniqueCallNode&&) = default;

    ASTUniqueCallNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::UniqueCall;
    }

    void attach(IASTNode* previous) final;

    const ptr_node_v& getArguments() const noexcept {
        return m_arguments;
    }

    IASTNode* getVariable() const noexcept {
        return m_variable.get();
    }

    void setArguments(ptr_node_v&& arguments) {
        m_arguments = std::move(arguments);
    }

    void setVariable(ptr_node&& variable) {
        m_variable = std::move(variable);
    }

private:
    ptr_node_v m_arguments;
    ptr_node m_variable;
};

class ASTStrCallNode final : public IASTNode {
public:
    ASTStrCallNode(const ASTStrCallNode&)            = delete;
    ASTStrCallNode& operator=(const ASTStrCallNode&) = delete;

    ASTStrCallNode(ASTStrCallNode&&)            = default;
    ASTStrCallNode& operator=(ASTStrCallNode&&) = default;

    ASTStrCallNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::StrCall;
    }

    void attach(IASTNode* previous) final;

    const ptr_node_v& getArguments() const noexcept {
        return m_arguments;
    }

    IASTNode* getVariable() const noexcept {
        return m_variable.get();
    }

    void setArguments(ptr_node_v&& arguments) {
        m_arguments = std::move(arguments);
    }

    void setVariable(ptr_node&& variable) {
        m_variable = std::move(variable);
    }

private:
    ptr_node_v m_arguments;
    ptr_node m_variable;
};

class ASTNameCallNode final : public IASTNode {
public:
    ASTNameCallNode(const ASTNameCallNode&)            = delete;
    ASTNameCallNode& operator=(const ASTNameCallNode&) = delete;

    ASTNameCallNode(ASTNameCallNode&&)            = default;
    ASTNameCallNode& operator=(ASTNameCallNode&&) = default;

    ASTNameCallNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::NameCall;
    }

    void attach(IASTNode* previous) final;

    const ptr_node_v& getArguments() const noexcept {
        return m_arguments;
    }

    IASTNode* getVariable() const noexcept {
        return m_variable.get();
    }

    void setArguments(ptr_node_v&& arguments) {
        m_arguments = std::move(arguments);
    }

    void setVariable(ptr_node&& variable) {
        m_variable = std::move(variable);
    }

private:
    ptr_node_v m_arguments;
    ptr_node m_variable;
};

class ASTFindCallNode final : public IASTNode {
public:
    ASTFindCallNode(const ASTFindCallNode&)            = delete;
    ASTFindCallNode& operator=(const ASTFindCallNode&) = delete;

    ASTFindCallNode(ASTFindCallNode&&)            = default;
    ASTFindCallNode& operator=(ASTFindCallNode&&) = default;

    ASTFindCallNode() = default;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::FindCall;
    }

    void attach(IASTNode* previous) final;

    const ptr_node_v& getArguments() const noexcept {
        return m_arguments;
    }

    IASTNode* getVariable() const noexcept {
        return m_variable.get();
    }

    void setArguments(ptr_node_v&& arguments) {
        m_arguments = std::move(arguments);
    }

    void setVariable(ptr_node&& variable) {
        m_variable = std::move(variable);
    }

private:
    ptr_node_v m_arguments;
    ptr_node m_variable;
};

class ASTFunctionCallNode final : public IASTNode {
public:
    ASTFunctionCallNode(const ASTFunctionCallNode&)            = delete;
    ASTFunctionCallNode& operator=(const ASTFunctionCallNode&) = delete;

    ASTFunctionCallNode(ASTFunctionCallNode&&)            = default;
    ASTFunctionCallNode& operator=(ASTFunctionCallNode&&) = default;

    ASTFunctionCallNode()
        : IASTNode()
        , m_function(nullptr)
        , m_name()
        , m_signature()
        , m_arguments()
        , m_nestedCalls() {}

    const Signature* getSignature() const final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::FunctionCall;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getFunction() const noexcept {
        return m_function;
    }

    const std::string& getName() const noexcept {
        return m_name;
    }

    const ptr_node_v& getArguments() const noexcept {
        return m_arguments;
    }

    const ptr_node_v& getNestedCalls() const noexcept {
        return m_nestedCalls;
    }

    void setFunction(IASTNode* function) noexcept {
        m_function = function;
    }

    void setName(const std::string& name) {
        m_name = name;
    }

    void setSignature(Signature&& signature) {
        m_signature = std::move(signature);
    }

    void setArguments(ptr_node_v&& arguments) {
        m_arguments = std::move(arguments);
    }

    void setNestedCalls(ptr_node_v&& nestedCalls) {
        m_nestedCalls = std::move(nestedCalls);
    }

private:
    IASTNode* m_function;
    std::string m_name;
    Signature m_signature;
    ptr_node_v m_arguments;
    ptr_node_v m_nestedCalls;
};

class ASTNestedCallNode final : public IASTNode {
public:
    ASTNestedCallNode(const ASTNestedCallNode&)            = delete;
    ASTNestedCallNode& operator=(const ASTNestedCallNode&) = delete;

    ASTNestedCallNode(ASTNestedCallNode&&)            = default;
    ASTNestedCallNode& operator=(ASTNestedCallNode&&) = default;

    ASTNestedCallNode()
        : IASTNode()
        , m_functionCall(nullptr)
        , m_nestedFunction(nullptr)
        , m_name()
        , m_signature()
        , m_arguments() {}

    const Signature* getSignature() const final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::NestedCall;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getFunctionCall() const noexcept {
        return m_functionCall;
    }

    IASTNode* getNestedFunction() const noexcept {
        return m_nestedFunction;
    }

    const std::string& getName() const noexcept {
        return m_name;
    }

    const ptr_node_v& getArguments() const noexcept {
        return m_arguments;
    }

    void setFunctionCall(IASTNode* functionCall) noexcept {
        m_functionCall = functionCall;
    }

    void setNestedFunction(IASTNode* nestedFunction) noexcept {
        m_nestedFunction = nestedFunction;
    }

    void setName(const std::string& name) {
        m_name = name;
    }

    void setSignature(Signature&& signature) {
        m_signature = std::move(signature);
    }

    void setArguments(ptr_node_v&& arguments) noexcept {
        m_arguments = std::move(arguments);
    }

private:
    IASTNode* m_functionCall;
    IASTNode* m_nestedFunction;
    std::string m_name;
    Signature m_signature;
    ptr_node_v m_arguments;
};

class ASTForNode final : public IASTNode {
public:
    ASTForNode(const ASTForNode&)            = delete;
    ASTForNode& operator=(const ASTForNode&) = delete;

    ASTForNode(ASTForNode&&)            = default;
    ASTForNode& operator=(ASTForNode&&) = default;

    ASTForNode() = default;

    bool hasNode(NodeID id, const std::vector<NodeID>& skip_ids = {}) const final;
    IASTNode* findNode(const std::vector<NodeID>& ids, const std::vector<NodeID>& skip_ids, bool forward = false) final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::For;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getRange() const noexcept {
        return m_range.get();
    }

    IASTNode* getBranch() const noexcept {
        return m_branch.get();
    }

    void setRange(ptr_node&& range) noexcept {
        m_range = std::move(range);
    }

    void setBranch(ptr_node&& branch) noexcept {
        m_branch = std::move(branch);
    }

private:
    ptr_node m_range;
    ptr_node m_branch;
};

class ASTIfNode final : public IASTNode {
public:
    ASTIfNode(const ASTIfNode&)            = delete;
    ASTIfNode& operator=(const ASTIfNode&) = delete;

    ASTIfNode(ASTIfNode&&)            = default;
    ASTIfNode& operator=(ASTIfNode&&) = default;

    ASTIfNode() = default;

    bool hasNode(NodeID id, const std::vector<NodeID>& skip_ids = {}) const final;
    IASTNode* findNode(const std::vector<NodeID>& ids, const std::vector<NodeID>& skip_ids, bool forward = false) final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::If;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getCondition() const noexcept {
        return m_condition.get();
    }

    IASTNode* getBranch() const noexcept {
        return m_branch.get();
    }

    void setCondition(ptr_node&& condition) noexcept {
        m_condition = std::move(condition);
    }

    void setBranch(ptr_node&& branch) noexcept {
        m_branch = std::move(branch);
    }

private:
    ptr_node m_condition;
    ptr_node m_branch;
};

class ASTFunctionIdentifierNode final : public IASTNode {
public:
    ASTFunctionIdentifierNode(const ASTFunctionIdentifierNode&)            = delete;
    ASTFunctionIdentifierNode& operator=(const ASTFunctionIdentifierNode&) = delete;

    ASTFunctionIdentifierNode(ASTFunctionIdentifierNode&&)            = default;
    ASTFunctionIdentifierNode& operator=(ASTFunctionIdentifierNode&&) = default;

    ASTFunctionIdentifierNode()
        : IASTNode()
        , m_name()
        , m_function(nullptr) {}

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::FunctionIdentifier;
    }

    const std::string& getName() const noexcept {
        return m_name;
    }

    IASTNode* getFunction() const noexcept {
        return m_function;
    }

    void setName(std::string_view name) {
        m_name = name;
    }

    void setFunction(IASTNode* function) noexcept {
        m_function = function;
    }

private:
    std::string m_name;
    IASTNode* m_function;
};

class ASTFunctionNode final : public IASTNode {
public:
    ASTFunctionNode(const ASTFunctionNode&)            = delete;
    ASTFunctionNode& operator=(const ASTFunctionNode&) = delete;

    ASTFunctionNode(ASTFunctionNode&&)            = default;
    ASTFunctionNode& operator=(ASTFunctionNode&&) = default;

    ASTFunctionNode()
        : IASTNode()
        , m_identifier()
        , m_signature()
        , m_returnType(ValueType::Null)
        , m_arguments()
        , m_nestedIdentifiers()
        , m_branch() {}

    bool isDeclared(std::string_view name, NodeID id, IASTNode* caller, const Signature& signature = {}) const final;
    bool hasNode(NodeID id, const std::vector<NodeID>& skip_ids = {}) const final;
    IASTNode* findNode(const std::vector<NodeID>& ids, const std::vector<NodeID>& skip_ids, bool forward = false) final;

    IASTNode* getNodeByName(std::string_view name, NodeID id) final;
    IASTNode* getNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName = "") final;
    IASTNode* getConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName = "") final;
    IASTNode* getVariadicConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName = "") final;

    const Signature* getSignature() const final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::Function;
    }

    void attach(IASTNode* previous) final;

    bool hasNested(std::string_view name) const;
    IASTNode* getNested(std::string_view name) const;

    IASTNode* getIdentifier() const noexcept {
        return m_identifier.get();
    }

    ValueType getReturnType() const noexcept {
        return m_returnType;
    }

    ptr_node_v& getArguments() noexcept {
        return m_arguments;
    }

    const ptr_node_v& getNestedIdentifiers() const noexcept {
        return m_nestedIdentifiers;
    }

    IASTNode* getBranch() const noexcept {
        return m_branch.get();
    }

    void setIdentifier(ptr_node&& identifier) noexcept {
        m_identifier = std::move(identifier);
    }

    void setSignature(Signature&& signature) {
        m_signature = std::move(signature);
    }

    void setReturnType(ValueType returnType) noexcept {
        m_returnType = returnType;
    }

    void setArguments(ptr_node_v&& arguments) noexcept {
        m_arguments = std::move(arguments);
    }

    void setNestedIdentifiers(ptr_node_v&& identifiers) noexcept {
        m_nestedIdentifiers = std::move(identifiers);
    }

    void setBranch(ptr_node&& branch) noexcept {
        m_branch = std::move(branch);
    }

private:
    ptr_node m_identifier;
    Signature m_signature;
    ValueType m_returnType;
    ptr_node_v m_arguments;
    ptr_node_v m_nestedIdentifiers;
    ptr_node m_branch;
};

class ASTNestedIdentifierNode final : public IASTNode {
public:
    ASTNestedIdentifierNode(const ASTNestedIdentifierNode&)            = delete;
    ASTNestedIdentifierNode& operator=(const ASTNestedIdentifierNode&) = delete;

    ASTNestedIdentifierNode(ASTNestedIdentifierNode&&)            = default;
    ASTNestedIdentifierNode& operator=(ASTNestedIdentifierNode&&) = default;

    ASTNestedIdentifierNode()
        : IASTNode()
        , m_name()
        , m_nestedFunction(nullptr) {}

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::NestedIdentifier;
    }

    const std::string& getName() const noexcept {
        return m_name;
    }

    IASTNode* getNestedFunction() const noexcept {
        return m_nestedFunction;
    }

    void setName(std::string_view name) {
        m_name = name;
    }

    void setNestedFunction(IASTNode* nestedFunction) noexcept {
        m_nestedFunction = nestedFunction;
    }

private:
    std::string m_name;
    IASTNode* m_nestedFunction;
};

class ASTNestedFunctionNode final : public IASTNode {
public:
    ASTNestedFunctionNode(const ASTNestedFunctionNode&)            = delete;
    ASTNestedFunctionNode& operator=(const ASTNestedFunctionNode&) = delete;

    ASTNestedFunctionNode(ASTNestedFunctionNode&&)            = default;
    ASTNestedFunctionNode& operator=(ASTNestedFunctionNode&&) = default;

    ASTNestedFunctionNode()
        : IASTNode()
        , m_functionIdentifier()
        , m_identifier()
        , m_signature()
        , m_returnType(ValueType::Null)
        , m_arguments()
        , m_branch() {}

    bool isDeclared(std::string_view name, NodeID id, IASTNode* caller, const Signature& signature = {}) const final;
    bool hasNode(NodeID id, const std::vector<NodeID>& skip_ids = {}) const final;
    IASTNode* findNode(const std::vector<NodeID>& ids, const std::vector<NodeID>& skip_ids, bool forward = false) final;

    IASTNode* getNodeByName(std::string_view name, NodeID id) final;
    IASTNode* getNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName = "") final;
    IASTNode* getConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName = "") final;
    IASTNode* getVariadicConvertibleNodeBySignature(std::string_view name, NodeID id, const Signature& signature, std::string_view functionName = "") final;

    const Signature* getSignature() const final;

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::NestedFunction;
    }

    void attach(IASTNode* previous) final;

    IASTNode* getFunctionIdentifier() const noexcept {
        return m_functionIdentifier.get();
    }

    IASTNode* getIdentifier() const noexcept {
        return m_identifier.get();
    }

    ValueType getReturnType() const noexcept {
        return m_returnType;
    }

    ptr_node_v& getArguments() noexcept {
        return m_arguments;
    }

    IASTNode* getBranch() const noexcept {
        return m_branch.get();
    }

    void setFunctionIdentifier(ptr_node&& functionIdentifier) noexcept {
        m_functionIdentifier = std::move(functionIdentifier);
    }

    void setIdentifier(ptr_node&& identifier) noexcept {
        m_identifier = std::move(identifier);
    }

    void setSignature(Signature&& signature) {
        m_signature = std::move(signature);
    }

    void setReturnType(ValueType returnType) noexcept {
        m_returnType = returnType;
    }

    void setArguments(ptr_node_v&& arguments) noexcept {
        m_arguments = std::move(arguments);
    }

    void setBranch(ptr_node&& branch) noexcept {
        m_branch = std::move(branch);
    }

private:
    ptr_node m_functionIdentifier;
    ptr_node m_identifier;
    Signature m_signature;
    ValueType m_returnType;
    ptr_node_v m_arguments;
    ptr_node m_branch;
};

class ASTInvokeNestedNode final : public IASTNode {
public:
    ASTInvokeNestedNode(const ASTInvokeNestedNode&)            = delete;
    ASTInvokeNestedNode& operator=(const ASTInvokeNestedNode&) = delete;

    ASTInvokeNestedNode(ASTInvokeNestedNode&&)            = default;
    ASTInvokeNestedNode& operator=(ASTInvokeNestedNode&&) = default;

    ASTInvokeNestedNode()
        : m_function(nullptr) {}

    ValueType getNodeType() final;

    void accept(IASTNodeParser& visitor) final {
        visitor.parse(this);
    }

    void accept(IASTNodeLinker& visitor) final {
        visitor.link(this);
    }

    Value* accept(IASTNodeEvaluator& visitor) final {
        return visitor.evaluate(this);
    }

    NodeID id() const noexcept final {
        return NodeID::InvokeNested;
    }

    IASTNode* getFunction() const noexcept {
        return m_function;
    }

    void setFunction(IASTNode* function) noexcept {
        m_function = function;
    }

private:
    IASTNode* m_function;
};

/*
    ASTNodeParser
*/
class ASTNodeParser final : public IASTNodeParser {
public:
    using IASTNodeParser::IASTNodeParser;

    void parse(ASTNullNode* node) final;
    void parse(ASTBoolNode* node) final;
    void parse(ASTIntNode* node) final;
    void parse(ASTRangeNode* node) final;
    void parse(ASTCoordNode* node) final;
    void parse(ASTFloatNode* node) final;
    void parse(ASTStringNode* node) final;
    void parse(ASTObjectNode* node) final;
    void parse(ASTArrayNode<BoolValue>* node) final;
    void parse(ASTArrayNode<IntValue>* node) final;
    void parse(ASTArrayNode<RangeValue>* node) final;
    void parse(ASTArrayNode<CoordValue>* node) final;
    void parse(ASTArrayNode<FloatValue>* node) final;
    void parse(ASTArrayNode<StringValue>* node) final;
    void parse(ASTArrayNode<ObjectValue>* node) final;
    void parse(ASTDeclarationNode* node) final;
    void parse(ASTIdentifierNode* node) final;
    void parse(ASTVariableNode* node) final;
    void parse(ASTAnchorNode* node) final;
    void parse(ASTCountNode* node) final;
    void parse(ASTLastNode* node) final;
    void parse(ASTXNode* node) final;
    void parse(ASTYNode* node) final;
    void parse(ASTRotationNode* node) final;
    void parse(ASTEmptyNode* node) final;
    void parse(ASTFullNode* node) final;
    void parse(ASTIndexNode* node) final;
    void parse(ASTNotIndexNode* node) final;
    void parse(ASTInsertNode* node) final;
    void parse(ASTRotateNode* node) final;
    void parse(ASTOpAssignNode* node) final;
    void parse(ASTOpAddNode* node) final;
    void parse(ASTOpSubtractNode* node) final;
    void parse(ASTOpMultiplyNode* node) final;
    void parse(ASTOpDivideNode* node) final;
    void parse(ASTOpEqualNode* node) final;
    void parse(ASTOpNotEqualNode* node) final;
    void parse(ASTOpGreaterThanNode* node) final;
    void parse(ASTOpGreaterThanOrEqualNode* node) final;
    void parse(ASTOpLessThanNode* node) final;
    void parse(ASTOpLessThanOrEqualNode* node) final;
    void parse(ASTOpAndNode* node) final;
    void parse(ASTOpOrNode* node) final;
    void parse(ASTOpNotNode* node) final;
    void parse(ASTOpRangeNode* node) final;
    void parse(ASTOpCoordNode* node) final;
    void parse(ASTErrorNode* node) final;
    void parse(ASTWarningNode* node) final;
    void parse(ASTAssertNode* node) final;
    void parse(ASTReturnNode* node) final;
    void parse(ASTBreakNode* node) final;
    void parse(ASTContinueNode* node) final;
    void parse(ASTForRangeNode* node) final;
    void parse(ASTArraySubscriptNode* node) final;
    void parse(ASTPushCallNode* node) final;
    void parse(ASTHasCallNode* node) final;
    void parse(ASTUniqueCallNode* node) final;
    void parse(ASTStrCallNode* node) final;
    void parse(ASTNameCallNode* node) final;
    void parse(ASTFindCallNode* node) final;
    void parse(ASTFunctionCallNode* node) final;
    void parse(ASTNestedCallNode* node) final;
    void parse(ASTForNode* node) final;
    void parse(ASTIfNode* node) final;
    void parse(ASTFunctionIdentifierNode* node) final;
    void parse(ASTFunctionNode* node) final;
    void parse(ASTNestedIdentifierNode* node) final;
    void parse(ASTNestedFunctionNode* node) final;
    void parse(ASTInvokeNestedNode* node) final;

    std::unique_ptr<Error> parseType(ValueType left, ValueType right, uint32_t line) const;
};

/*
    ASTNodeLinker
*/
class ASTNodeLinker final : public IASTNodeLinker {
public:
    using IASTNodeLinker::IASTNodeLinker;

    void link(ASTNullNode* node) final;
    void link(ASTBoolNode* node) final;
    void link(ASTIntNode* node) final;
    void link(ASTRangeNode* node) final;
    void link(ASTCoordNode* node) final;
    void link(ASTFloatNode* node) final;
    void link(ASTStringNode* node) final;
    void link(ASTObjectNode* node) final;
    void link(ASTArrayNode<BoolValue>* node) final;
    void link(ASTArrayNode<IntValue>* node) final;
    void link(ASTArrayNode<RangeValue>* node) final;
    void link(ASTArrayNode<CoordValue>* node) final;
    void link(ASTArrayNode<FloatValue>* node) final;
    void link(ASTArrayNode<StringValue>* node) final;
    void link(ASTArrayNode<ObjectValue>* node) final;
    void link(ASTDeclarationNode* node) final;
    void link(ASTIdentifierNode* node) final;
    void link(ASTVariableNode* node) final;
    void link(ASTAnchorNode* node) final;
    void link(ASTCountNode* node) final;
    void link(ASTLastNode* node) final;
    void link(ASTXNode* node) final;
    void link(ASTYNode* node) final;
    void link(ASTRotationNode* node) final;
    void link(ASTEmptyNode* node) final;
    void link(ASTFullNode* node) final;
    void link(ASTIndexNode* node) final;
    void link(ASTNotIndexNode* node) final;
    void link(ASTInsertNode* node) final;
    void link(ASTRotateNode* node) final;
    void link(ASTOpAssignNode* node) final;
    void link(ASTOpAddNode* node) final;
    void link(ASTOpSubtractNode* node) final;
    void link(ASTOpMultiplyNode* node) final;
    void link(ASTOpDivideNode* node) final;
    void link(ASTOpEqualNode* node) final;
    void link(ASTOpNotEqualNode* node) final;
    void link(ASTOpGreaterThanNode* node) final;
    void link(ASTOpGreaterThanOrEqualNode* node) final;
    void link(ASTOpLessThanNode* node) final;
    void link(ASTOpLessThanOrEqualNode* node) final;
    void link(ASTOpAndNode* node) final;
    void link(ASTOpOrNode* node) final;
    void link(ASTOpNotNode* node) final;
    void link(ASTOpRangeNode* node) final;
    void link(ASTOpCoordNode* node) final;
    void link(ASTErrorNode* node) final;
    void link(ASTWarningNode* node) final;
    void link(ASTAssertNode* node) final;
    void link(ASTReturnNode* node) final;
    void link(ASTBreakNode* node) final;
    void link(ASTContinueNode* node) final;
    void link(ASTForRangeNode* node) final;
    void link(ASTArraySubscriptNode* node) final;
    void link(ASTPushCallNode* node) final;
    void link(ASTHasCallNode* node) final;
    void link(ASTUniqueCallNode* node) final;
    void link(ASTStrCallNode* node) final;
    void link(ASTNameCallNode* node) final;
    void link(ASTFindCallNode* node) final;
    void link(ASTFunctionCallNode* node) final;
    void link(ASTNestedCallNode* node) final;
    void link(ASTForNode* node) final;
    void link(ASTIfNode* node) final;
    void link(ASTFunctionIdentifierNode* node) final;
    void link(ASTFunctionNode* node) final;
    void link(ASTNestedIdentifierNode* node) final;
    void link(ASTNestedFunctionNode* node) final;
    void link(ASTInvokeNestedNode* node) final;
};

/*
    ASTNodeEvaluator
*/
#define _BreakIfFailed \
    if (failed())      \
        return {}
#define _BreakIfFailedVoid \
    if (failed())          \
    return
#define _BreakIfReturned \
    if (m_returned)      \
    return result
#define _BreakIfBreak \
    if (m_break)      \
    return result
#define _BreakIfContinue \
    if (m_continue)      \
    return result

#define _StackTop        m_stack.back().get()
#define _StackTopSafe    (m_stack.empty() ? nullptr : m_stack.back().get())
#define _StackMoveTop    std::move(m_stack.back())
#define _StackInit       Value* top = !m_stack.empty() ? _StackTop : nullptr
#define _StackPush(_Val) m_stack.push_back(std::move(_Val))
#define _StackPop                                \
    while (!m_stack.empty() && _StackTop != top) \
    m_stack.pop_back()
#define _StackPopTop m_stack.pop_back()

#define _TryEvaluateNextNode \
    if (node->hasNextNode()) \
    return node->getNextNode()->accept(*this)
#define _TryEvaluateNextNodeAndClearStack          \
    if (node->hasNextNode()) {                     \
        _StackPop;                                 \
        return node->getNextNode()->accept(*this); \
    }

class ASTNodeEvaluator final : public IASTNodeEvaluator {
public:
    using IASTNodeEvaluator::IASTNodeEvaluator;

    Value* evaluate(ASTNullNode* node) final;
    Value* evaluate(ASTBoolNode* node) final;
    Value* evaluate(ASTIntNode* node) final;
    Value* evaluate(ASTRangeNode* node) final;
    Value* evaluate(ASTCoordNode* node) final;
    Value* evaluate(ASTFloatNode* node) final;
    Value* evaluate(ASTStringNode* node) final;
    Value* evaluate(ASTObjectNode* node) final;
    Value* evaluate(ASTArrayNode<BoolValue>* node) final;
    Value* evaluate(ASTArrayNode<IntValue>* node) final;
    Value* evaluate(ASTArrayNode<RangeValue>* node) final;
    Value* evaluate(ASTArrayNode<CoordValue>* node) final;
    Value* evaluate(ASTArrayNode<FloatValue>* node) final;
    Value* evaluate(ASTArrayNode<StringValue>* node) final;
    Value* evaluate(ASTArrayNode<ObjectValue>* node) final;
    Value* evaluate(ASTDeclarationNode* node) final;
    Value* evaluate(ASTIdentifierNode* node) final;
    Value* evaluate(ASTVariableNode* node) final;
    Value* evaluate(ASTAnchorNode* node) final;
    Value* evaluate(ASTCountNode* node) final;
    Value* evaluate(ASTLastNode* node) final;
    Value* evaluate(ASTXNode* node) final;
    Value* evaluate(ASTYNode* node) final;
    Value* evaluate(ASTRotationNode* node) final;
    Value* evaluate(ASTEmptyNode* node) final;
    Value* evaluate(ASTFullNode* node) final;
    Value* evaluate(ASTIndexNode* node) final;
    Value* evaluate(ASTNotIndexNode* node) final;
    Value* evaluate(ASTInsertNode* node) final;
    Value* evaluate(ASTRotateNode* node) final;
    Value* evaluate(ASTOpAssignNode* node) final;
    Value* evaluate(ASTOpAddNode* node) final;
    Value* evaluate(ASTOpSubtractNode* node) final;
    Value* evaluate(ASTOpMultiplyNode* node) final;
    Value* evaluate(ASTOpDivideNode* node) final;
    Value* evaluate(ASTOpEqualNode* node) final;
    Value* evaluate(ASTOpNotEqualNode* node) final;
    Value* evaluate(ASTOpGreaterThanNode* node) final;
    Value* evaluate(ASTOpGreaterThanOrEqualNode* node) final;
    Value* evaluate(ASTOpLessThanNode* node) final;
    Value* evaluate(ASTOpLessThanOrEqualNode* node) final;
    Value* evaluate(ASTOpAndNode* node) final;
    Value* evaluate(ASTOpOrNode* node) final;
    Value* evaluate(ASTOpNotNode* node) final;
    Value* evaluate(ASTOpRangeNode* node) final;
    Value* evaluate(ASTOpCoordNode* node) final;
    Value* evaluate(ASTErrorNode* node) final;
    Value* evaluate(ASTWarningNode* node) final;
    Value* evaluate(ASTAssertNode* node) final;
    Value* evaluate(ASTReturnNode* node) final;
    Value* evaluate(ASTBreakNode* node) final;
    Value* evaluate(ASTContinueNode* node) final;
    Value* evaluate(ASTForRangeNode* node) final;
    Value* evaluate(ASTArraySubscriptNode* node) final;
    Value* evaluate(ASTPushCallNode* node) final;
    Value* evaluate(ASTHasCallNode* node) final;
    Value* evaluate(ASTUniqueCallNode* node) final;
    Value* evaluate(ASTStrCallNode* node) final;
    Value* evaluate(ASTNameCallNode* node) final;
    Value* evaluate(ASTFindCallNode* node) final;
    Value* evaluate(ASTFunctionCallNode* node) final;
    Value* evaluate(ASTNestedCallNode* node) final;
    Value* evaluate(ASTForNode* node) final;
    Value* evaluate(ASTIfNode* node) final;
    Value* evaluate(ASTFunctionIdentifierNode* node) final;
    Value* evaluate(ASTFunctionNode* node) final;
    Value* evaluate(ASTNestedIdentifierNode* node) final;
    Value* evaluate(ASTNestedFunctionNode* node) final;
    Value* evaluate(ASTInvokeNestedNode* node) final;

    ptr_value cast(Value* value, ValueType to);
    void evaluateArguments(const ptr_node_v& callArgs, ptr_node_v& defArgs);
    void evaluateArgumentsVariadic(const ptr_node_v& callArgs, ASTIdentifierNode* identifier);

    bool hasRotation(Value* value, Rotation rotation) const;
    void rotate(Value* value, Rotation rotation) const;

    void insertPosType(uint32_t line, NodeID id);
    void insert(InsertC control, Value* value, uint32_t line);

    void printError(std::string_view message, uint32_t line);
    void printWarning(std::string_view message, uint32_t line);
    void printAssert(uint32_t line);
};

#endif // RPP_ABSTRACTSYNTAXTREEVISITOR_HPP
