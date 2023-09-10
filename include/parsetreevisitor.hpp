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
#ifndef RPP_PARSETREEVISITOR_HPP
#define RPP_PARSETREEVISITOR_HPP

#include <memory>
#include <vector>
#include <queue>

#include <errorqueue.hpp>
#include <enums.hpp>

class Token;

class IPTStatementNodeVisitor;
class IPTExpressionNodeVisitor;
class IPTStatementNode;
class IPTExpressionNode;

class IPTStatementNode {
protected:
    using ptr_stat_v = std::vector<std::unique_ptr<IPTStatementNode>>;
    using ptr_stat = std::unique_ptr<IPTStatementNode>;
    using ptr_expr_v = std::vector<std::unique_ptr<IPTExpressionNode>>;
    using ptr_expr = std::unique_ptr<IPTExpressionNode>;

public:
    virtual ~IPTStatementNode() = default;

    virtual bool hasNode(ExpressionID id) const = 0;

    virtual void accept(IPTStatementNodeVisitor& visitor) = 0;
    virtual StatementID id() const noexcept = 0;
};

class IPTExpressionNode {
protected:
    using ptr_expr_v = std::vector<std::unique_ptr<IPTExpressionNode>>;
    using ptr_expr = std::unique_ptr<IPTExpressionNode>;

public:
    virtual ~IPTExpressionNode() = default;

    virtual bool hasNode(ExpressionID id) const = 0;
    virtual bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const = 0;
    virtual bool hasKW(std::string_view kw_name) const = 0;
    virtual std::vector<Token*> getTokens() const = 0;
    virtual Token* getLastToken() const = 0;

    virtual void accept(IPTExpressionNodeVisitor& visitor) = 0;
    virtual ExpressionID id() const noexcept = 0;
};



class PTEmptyStatement;
class PTExprStatement;
class PTForStatement;
class PTIfStatement;
class PTDeclStatement;
class PTFunctionDefStatement;
class PTFunctionDeclStatement;
class PTNestedFunctionDefStatement;
class PTNestedFunctionDeclStatement;
class PTNestedDeclStatement;
class PTPresetDefStatement;
class PTReturnStatement;
class PTBreakStatement;
class PTContinueStatement;

class IPTStatementNodeVisitor {
public:
    virtual ~IPTStatementNodeVisitor() = default;

    void setExpressionVisitor(IPTExpressionNodeVisitor* visitor) noexcept
        { m_visitor = visitor; }

    virtual std::unique_ptr<Error> parse(PTEmptyStatement& node) = 0;
    virtual std::unique_ptr<Error> parse(PTExprStatement& node) = 0;
    virtual std::unique_ptr<Error> parse(PTForStatement& node) = 0;
    virtual std::unique_ptr<Error> parse(PTIfStatement& node) = 0;
    virtual std::unique_ptr<Error> parse(PTDeclStatement& node) = 0;
    virtual std::unique_ptr<Error> parse(PTFunctionDefStatement& node) = 0;
    virtual std::unique_ptr<Error> parse(PTFunctionDeclStatement& node) = 0;
    virtual std::unique_ptr<Error> parse(PTNestedFunctionDefStatement& node) = 0;
    virtual std::unique_ptr<Error> parse(PTNestedFunctionDeclStatement& node) = 0;
    virtual std::unique_ptr<Error> parse(PTNestedDeclStatement& node) = 0;
    virtual std::unique_ptr<Error> parse(PTPresetDefStatement& node) = 0;
    virtual std::unique_ptr<Error> parse(PTReturnStatement& node) = 0;
    virtual std::unique_ptr<Error> parse(PTBreakStatement& node) = 0;
    virtual std::unique_ptr<Error> parse(PTContinueStatement& node) = 0;

    virtual void visit(PTEmptyStatement& node) = 0;
    virtual void visit(PTExprStatement& node) = 0;
    virtual void visit(PTForStatement& node) = 0;
    virtual void visit(PTIfStatement& node) = 0;
    virtual void visit(PTDeclStatement& node) = 0;
    virtual void visit(PTFunctionDefStatement& node) = 0;
    virtual void visit(PTFunctionDeclStatement& node) = 0;
    virtual void visit(PTNestedFunctionDefStatement& node) = 0;
    virtual void visit(PTNestedFunctionDeclStatement& node) = 0;
    virtual void visit(PTNestedDeclStatement& node) = 0;
    virtual void visit(PTPresetDefStatement& node) = 0;
    virtual void visit(PTReturnStatement& node) = 0;
    virtual void visit(PTBreakStatement& node) = 0;
    virtual void visit(PTContinueStatement& node) = 0;

protected:
    IPTExpressionNodeVisitor* m_visitor;
};



class PTInvalidExpression;
class PTEmptyExpression;
class PTLiteralExpression;
class PTIdentifierExpression;
class PTKeywordExpression;
class PTAssignmentExpression;
class PTArithmeticExpression;
class PTComparisonExpression;
class PTLogicalExpression;
class PTUnaryLogicalExpression;
class PTReturnTypeExpression;
class PTFunctionCallExpression;
class PTForRangeExpression;
class PTMemberAccessExpression;
class PTErrorExpression;
class PTWarningExpression;
class PTAssertExpression;
class PTArraySubscriptExpression;
class PTPercentLiteralExpression;
class PTStringLiteralExpression;
class PTRangeLiteralExpression;
class PTCoordLiteralExpression;
class PTSeparatorExpression;
class PTDeclTypeExpression;

class IPTExpressionNodeVisitor : public ErrorQueue {
public:
    virtual ~IPTExpressionNodeVisitor() = default;

    auto&& errors() noexcept
        { return std::move(m_errors); }

    Token* getCurrentToken() noexcept
        { return m_currToken; }
    void setCurrentToken(Token* t) noexcept
        { m_currToken = t; }

    virtual std::unique_ptr<Error> parse(PTInvalidExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTEmptyExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTLiteralExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTIdentifierExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTKeywordExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTAssignmentExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTArithmeticExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTComparisonExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTLogicalExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTUnaryLogicalExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTReturnTypeExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTFunctionCallExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTForRangeExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTMemberAccessExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTErrorExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTWarningExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTAssertExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTArraySubscriptExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTPercentLiteralExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTStringLiteralExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTRangeLiteralExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTCoordLiteralExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTSeparatorExpression& node) = 0;
    virtual std::unique_ptr<Error> parse(PTDeclTypeExpression& node) = 0;

    virtual void visit(PTInvalidExpression& node) = 0;
    virtual void visit(PTEmptyExpression& node) = 0;
    virtual void visit(PTLiteralExpression& node) = 0;
    virtual void visit(PTIdentifierExpression& node) = 0;
    virtual void visit(PTKeywordExpression& node) = 0;
    virtual void visit(PTAssignmentExpression& node) = 0;
    virtual void visit(PTArithmeticExpression& node) = 0;
    virtual void visit(PTComparisonExpression& node) = 0;
    virtual void visit(PTLogicalExpression& node) = 0;
    virtual void visit(PTUnaryLogicalExpression& node) = 0;
    virtual void visit(PTReturnTypeExpression& node) = 0;
    virtual void visit(PTFunctionCallExpression& node) = 0;
    virtual void visit(PTForRangeExpression& node) = 0;
    virtual void visit(PTMemberAccessExpression& node) = 0;
    virtual void visit(PTErrorExpression& node) = 0;
    virtual void visit(PTWarningExpression& node) = 0;
    virtual void visit(PTAssertExpression& node) = 0;
    virtual void visit(PTArraySubscriptExpression& node) = 0;
    virtual void visit(PTPercentLiteralExpression& node) = 0;
    virtual void visit(PTStringLiteralExpression& node) = 0;
    virtual void visit(PTRangeLiteralExpression& node) = 0;
    virtual void visit(PTCoordLiteralExpression& node) = 0;
    virtual void visit(PTSeparatorExpression& node) = 0;
    virtual void visit(PTDeclTypeExpression& node) = 0;

protected:
    Token* m_currToken;
};



/*
    Statements
*/
class PTEmptyStatement final : public IPTStatementNode {
public:
    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final  
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::Empty; }
};

class PTExprStatement final : public IPTStatementNode {
public:
    PTExprStatement(const PTExprStatement&) = delete;
    PTExprStatement& operator=(const PTExprStatement&) = delete;

    PTExprStatement(PTExprStatement&&) = default;
    PTExprStatement& operator=(PTExprStatement&&) = default;

    PTExprStatement()
        : expr()
        , end(nullptr)
    {
    }
    PTExprStatement(ptr_expr&& expr, Token* end)
        : expr(std::move(expr))
        , end(end)
    {
    }

    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final  
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::Expr; }

    template <uint32_t I> requires (I == 1)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return end; }

    template <uint32_t I> requires (I == 1)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 2)
    void set(Token* end) noexcept
        { this->end = end; }

private:
    ptr_expr expr;
    Token* end;
};

class PTForStatement final : public IPTStatementNode {
public:
    PTForStatement(const PTForStatement&) = delete;
    PTForStatement& operator=(const PTForStatement&) = delete;

    PTForStatement(PTForStatement&&) = default;
    PTForStatement& operator=(PTForStatement&&) = default;

    PTForStatement()
        : keyword(nullptr)
        , left(nullptr)
        , expr()
        , right(nullptr)
        , stats()
        , end(nullptr)
    {
    }
    PTForStatement(Token* keyword, Token* left, ptr_expr&& expr, Token* right, ptr_stat_v&& stats, Token* end)
        : keyword(keyword)
        , left(left)
        , expr(std::move(expr))
        , right(right)
        , stats(std::move(stats))
        , end(end)
    {
    }

    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::For; }

    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return keyword; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return left; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 4)
    Token* get() noexcept
        { return right; }
    template <uint32_t I> requires (I == 5)
    ptr_stat_v&& get() noexcept
        { return std::move(stats); }
    template <uint32_t I> requires (I == 6)
    Token* get() noexcept
        { return end; }

    template <uint32_t I> requires (I == 1)
    void set(Token* keyword) noexcept
        { this->keyword = keyword; }
    template <uint32_t I> requires (I == 2)
    void set(Token* left) noexcept
        { this->left = left; }
    template <uint32_t I> requires (I == 3) 
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 4)
    void set(Token* right) noexcept
        { this->right = right; }
    template <uint32_t I> requires (I == 5)
    void set(ptr_stat_v&& stats) noexcept
        { this->stats = std::move(stats); }
    template <uint32_t I> requires (I == 6)
    void set(Token* end) noexcept
        { this->end = end; }

private:
    Token* keyword;
    Token* left;
    ptr_expr expr;
    Token* right;
    ptr_stat_v stats;
    Token* end;
};

class PTIfStatement final : public IPTStatementNode {
public:
    PTIfStatement(const PTIfStatement&) = delete;
    PTIfStatement& operator=(const PTIfStatement&) = delete;

    PTIfStatement(PTIfStatement&&) = default;
    PTIfStatement& operator=(PTIfStatement&&) = default;

    PTIfStatement()
        : keyword(nullptr)
        , left(nullptr)
        , expr()
        , right(nullptr)
        , stats()
        , end(nullptr)
    {
    }
    PTIfStatement(Token* keyword, Token* left, ptr_expr&& expr, Token* right, ptr_stat_v&& stats, Token* end)
        : keyword(keyword)
        , left(left)
        , expr(std::move(expr))
        , right(right)
        , stats(std::move(stats))
        , end(end)
    {
    }

    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::If; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return keyword; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return left; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 4)
    Token* get() noexcept
        { return right; }
    template <uint32_t I> requires (I == 5)
    ptr_stat_v&& get() noexcept
        { return std::move(stats); }
    template <uint32_t I> requires (I == 6)
    Token* get() noexcept
        { return end; }

    template <uint32_t I> requires (I == 1)
    void set(Token* keyword) noexcept
        { this->keyword = keyword; }
    template <uint32_t I> requires (I == 2)
    void set(Token* left) noexcept
        { this->left = left; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 4)
    void set(Token* right) noexcept
        { this->right = right; }
    template <uint32_t I> requires (I == 5)
    void set(ptr_stat_v&& stats) noexcept
        { this->stats = std::move(stats); }
    template <uint32_t I> requires (I == 6)
    void set(Token* end) noexcept
        { this->end = end; }

private:
    Token* keyword;
    Token* left;
    ptr_expr expr;
    Token* right;
    ptr_stat_v stats;
    Token* end;
};

class PTDeclStatement final : public IPTStatementNode {
public:
    PTDeclStatement(const PTDeclStatement&) = delete;
    PTDeclStatement& operator=(const PTDeclStatement&) = delete;

    PTDeclStatement(PTDeclStatement&&) = default;
    PTDeclStatement& operator=(PTDeclStatement&&) = default;

    PTDeclStatement()
        : expr()
        , end(nullptr)
    {
    }
    PTDeclStatement(ptr_expr&& expr, Token* end)
        : expr(std::move(expr))
        , end(end)
    {
    }

    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::Decl; }
    
    template <uint32_t I> requires (I == 1)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return end; }

    template <uint32_t I> requires (I == 1)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 2)
    void set(Token* end) noexcept
        { this->end = end; }

private:
    ptr_expr expr;
    Token* end;
};

class PTFunctionDefStatement final : public IPTStatementNode {
public:
    PTFunctionDefStatement(const PTFunctionDefStatement&) = delete;
    PTFunctionDefStatement& operator=(const PTFunctionDefStatement&) = delete;

    PTFunctionDefStatement(PTFunctionDefStatement&&) = default;
    PTFunctionDefStatement& operator=(PTFunctionDefStatement&&) = default;

    PTFunctionDefStatement()
        : expr()
        , stat()
        , nested()
        , stats()
        , end(nullptr)
    {
    }
    PTFunctionDefStatement(ptr_expr&& expr, ptr_stat&& stat, ptr_stat&& nested, ptr_stat_v&& stats, Token* end)
        : expr(std::move(expr))
        , stat(std::move(stat))
        , nested(std::move(nested))
        , stats(std::move(stats))
        , end(end)
    {
    }

    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::FunctionDef; }
    
    template <uint32_t I> requires (I == 1)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 2)
    ptr_stat&& get() noexcept
        { return std::move(stat); }
    template <uint32_t I> requires (I == 3)
    ptr_stat&& get() noexcept
        { return std::move(nested); }
    template <uint32_t I> requires (I == 4)
    ptr_stat_v&& get() noexcept
        { return std::move(stats); }
    template <uint32_t I> requires (I == 5)
    Token* get() noexcept
        { return end; }

    template <uint32_t I> requires (I == 1)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 2)
    void set(ptr_stat&& stat) noexcept
        { this->stat = std::move(stat); }
    template <uint32_t I> requires (I == 3)
    void set(ptr_stat&& nested) noexcept
        { this->nested = std::move(nested); }
    template <uint32_t I> requires (I == 4)
    void set(ptr_stat_v&& stats) noexcept
        { this->stats = std::move(stats); }
    template <uint32_t I> requires (I == 5)
    void set(Token* end) noexcept
        { this->end = end; }

private:
    ptr_expr expr;
    ptr_stat stat;
    ptr_stat nested;
    ptr_stat_v stats;
    Token* end;
};

class PTFunctionDeclStatement final : public IPTStatementNode {
public:
    PTFunctionDeclStatement(const PTFunctionDeclStatement&) = delete;
    PTFunctionDeclStatement& operator=(const PTFunctionDeclStatement&) = delete;

    PTFunctionDeclStatement(PTFunctionDeclStatement&&) = default;
    PTFunctionDeclStatement& operator=(PTFunctionDeclStatement&&) = default;

    PTFunctionDeclStatement()
        : name(nullptr)
        , left(nullptr)
        , expr()
        , right(nullptr)
    {
    }
    PTFunctionDeclStatement(Token* name, Token* left, ptr_expr&& expr, Token* right)
        : name(name)
        , left(left)
        , expr(std::move(expr))
        , right(right)
    {
    }

    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::FunctionDecl; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return name; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return left; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 4)
    Token* get() noexcept
        { return right; }

    template <uint32_t I> requires (I == 1)
    void set(Token* name) noexcept
        { this->name = name; }
    template <uint32_t I> requires (I == 2)
    void set(Token* left) noexcept
        { this->left = left; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 4)
    void set(Token* right) noexcept
        { this->right = right; }

private:
    Token* name;
    Token* left;
    ptr_expr expr;
    Token* right;
};

class PTNestedFunctionDefStatement final : public IPTStatementNode {
public:
    PTNestedFunctionDefStatement(const PTNestedFunctionDefStatement&) = delete;
    PTNestedFunctionDefStatement& operator=(const PTNestedFunctionDefStatement&) = delete;

    PTNestedFunctionDefStatement(PTNestedFunctionDefStatement&&) = default;
    PTNestedFunctionDefStatement& operator=(PTNestedFunctionDefStatement&&) = default;

    PTNestedFunctionDefStatement()
        : keyword()
        , expr()
        , stat()
        , stats()
        , end(nullptr)
    {
    }
    PTNestedFunctionDefStatement(Token* keyword, ptr_expr&& expr, ptr_stat&& stat, ptr_stat_v&& stats, Token* end)
        : keyword(keyword)
        , expr(std::move(expr))
        , stat(std::move(stat))
        , stats(std::move(stats))
        , end(end)
    {
    }

    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::NestedFunctionDef; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return keyword; }
    template <uint32_t I> requires (I == 2)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 3)
    ptr_stat&& get() noexcept
        { return std::move(stat); }
    template <uint32_t I> requires (I == 4)
    ptr_stat_v&& get() noexcept
        { return std::move(stats); }
    template <uint32_t I> requires (I == 5)
    Token* get() noexcept
        { return end; }
    
    template <uint32_t I> requires (I == 1)
    void set(Token* keyword) noexcept
        { this->keyword = keyword; }
    template <uint32_t I> requires (I == 2)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 3)
    void set(ptr_stat&& stat) noexcept
        { this->stat = std::move(stat); }
    template <uint32_t I> requires (I == 4)
    void set(ptr_stat_v&& stats) noexcept
        { this->stats = std::move(stats); }
    template <uint32_t I> requires (I == 5)
    void set(Token* end) noexcept
        { this->end = end; }

private:
    Token* keyword;
    ptr_expr expr;
    ptr_stat stat;
    ptr_stat_v stats;
    Token* end;
};

class PTNestedFunctionDeclStatement final : public IPTStatementNode {
public:
    PTNestedFunctionDeclStatement(const PTNestedFunctionDeclStatement&) = delete;
    PTNestedFunctionDeclStatement& operator=(const PTNestedFunctionDeclStatement&) = delete;

    PTNestedFunctionDeclStatement(PTNestedFunctionDeclStatement&&) = default;
    PTNestedFunctionDeclStatement& operator=(PTNestedFunctionDeclStatement&&) = default;

    PTNestedFunctionDeclStatement()
        : name()
        , left(nullptr)
        , expr()
        , right(nullptr)
    {
    }
    PTNestedFunctionDeclStatement(ptr_expr&& name, Token* left, ptr_expr&& expr, Token* right)
        : name(std::move(name))
        , left(left)
        , expr(std::move(expr))
        , right(right)
    {
    }

    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::NestedFunctionDecl; }
    
    template <uint32_t I> requires (I == 1)
    ptr_expr&& get() noexcept
        { return std::move(name); }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return left; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 4)
    Token* get() noexcept
        { return right; }

    template <uint32_t I> requires (I == 1)
    void set(ptr_expr&& name) noexcept
        { this->name = std::move(name); }
    template <uint32_t I> requires (I == 2)
    void set(Token* left) noexcept
        { this->left = left; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 4)
    void set(Token* right) noexcept
        { this->right = right; }

private:
    ptr_expr name;
    Token* left;
    ptr_expr expr;
    Token* right;
};

class PTNestedDeclStatement final : public IPTStatementNode {
public:
    PTNestedDeclStatement(const PTNestedDeclStatement&) = delete;
    PTNestedDeclStatement& operator=(const PTNestedDeclStatement&) = delete;

    PTNestedDeclStatement(PTNestedDeclStatement&&) = default;
    PTNestedDeclStatement& operator=(PTNestedDeclStatement&&) = default;

    PTNestedDeclStatement()
        : keyword(nullptr)
        , left(nullptr)
        , expr()
        , right(nullptr)
    {
    }
    PTNestedDeclStatement(Token* keyword, Token* left, ptr_expr&& expr, Token* right)
        : keyword(keyword)
        , left(left)
        , expr(std::move(expr))
        , right(right)
    {
    }

    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::NestedDecl; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return keyword; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return left; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 4)
    Token* get() noexcept
        { return right; }

    template <uint32_t I> requires (I == 1)
    void set(Token* keyword) noexcept
        { this->keyword = keyword; }
    template <uint32_t I> requires (I == 2)
    void set(Token* left) noexcept
        { this->left = left; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 4)
    void set(Token* right) noexcept
        { this->right = right; }

private:
    Token* keyword;
    Token* left;
    ptr_expr expr;
    Token* right;
};

class PTPresetDefStatement final : public IPTStatementNode {
public:
    PTPresetDefStatement(const PTPresetDefStatement&) = delete;
    PTPresetDefStatement& operator=(const PTPresetDefStatement&) = delete;

    PTPresetDefStatement(PTPresetDefStatement&&) = default;
    PTPresetDefStatement& operator=(PTPresetDefStatement&&) = default;

    PTPresetDefStatement()
        : keyword(nullptr)
        , stat()
        , stats()
        , end(nullptr)
    {
    }
    PTPresetDefStatement(Token* keyword, ptr_stat&& stat, ptr_stat_v&& stats, Token* end)
        : keyword(keyword)
        , stat(std::move(stat))
        , stats(std::move(stats))
        , end(end)
    {
    }

    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::PresetDef; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return keyword; }
    template <uint32_t I> requires (I == 2)
    ptr_stat&& get() noexcept
        { return std::move(stat); }
    template <uint32_t I> requires (I == 3)
    ptr_stat_v&& get() noexcept
        { return std::move(stats); }
    template <uint32_t I> requires (I == 4)
    Token* get() noexcept
        { return end; }

    template <uint32_t I> requires (I == 1)
    void set(Token* keyword) noexcept
        { this->keyword = keyword; }
    template <uint32_t I> requires (I == 2)
    void set(ptr_stat&& stat) noexcept
        { this->stat = std::move(stat); }
    template <uint32_t I> requires (I == 3)
    void set(ptr_stat_v&& stats) noexcept
        { this->stats = std::move(stats); }
    template <uint32_t I> requires (I == 4)
    void set(Token* end) noexcept
        { this->end = end; }

private:
    Token* keyword;
    ptr_stat stat;
    ptr_stat_v stats;
    Token* end;
};

class PTReturnStatement final : public IPTStatementNode {
public:
    PTReturnStatement(const PTReturnStatement&) = delete;
    PTReturnStatement& operator=(const PTReturnStatement&) = delete;

    PTReturnStatement(PTReturnStatement&&) = default;
    PTReturnStatement& operator=(PTReturnStatement&&) = default;

    PTReturnStatement()
        : keyword(nullptr)
        , expr()
        , end(nullptr)
    {
    }
    PTReturnStatement(Token* keyword, ptr_expr&& expr, Token* end)
        : keyword(keyword)
        , expr(std::move(expr))
        , end(end)
    {
    }

    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::Return; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return keyword; }
    template <uint32_t I> requires (I == 2)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 3)
    Token* get() noexcept
        { return end; }

    template <uint32_t I> requires (I == 1)
    void set(Token* keyword) noexcept
        { this->keyword = keyword; }
    template <uint32_t I> requires (I == 2)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 3)
    void set(Token* end) noexcept
        { this->end = end; }

private:
    Token* keyword;
    ptr_expr expr;
    Token* end;
};

class PTBreakStatement final : public IPTStatementNode {
public:
    PTBreakStatement(const PTBreakStatement&) = delete;
    PTBreakStatement& operator=(const PTBreakStatement&) = delete;

    PTBreakStatement(PTBreakStatement&&) = default;
    PTBreakStatement& operator=(PTBreakStatement&&) = default;

    PTBreakStatement()
        : keyword(nullptr)
        , end(nullptr)
    {
    }
    PTBreakStatement(Token* keyword, Token* end)
        : keyword(keyword)
        , end(end)
    {
    }

    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::Break; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return keyword; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return end; }

    template <uint32_t I> requires (I == 1)
    void set(Token* keyword) noexcept
        { this->keyword = keyword; }
    template <uint32_t I> requires (I == 2)
    void set(Token* end) noexcept
        { this->end = end; }

private:
    Token* keyword;
    Token* end;
};

class PTContinueStatement final : public IPTStatementNode {
public:
    PTContinueStatement(const PTContinueStatement&) = delete;
    PTContinueStatement& operator=(const PTContinueStatement&) = delete;

    PTContinueStatement(PTContinueStatement&&) = default;
    PTContinueStatement& operator=(PTContinueStatement&&) = default;

    PTContinueStatement()
        : keyword(nullptr)
        , end(nullptr)
    {
    }
    PTContinueStatement(Token* keyword, Token* end)
        : keyword(keyword)
        , end(end)
    {
    }

    bool hasNode(ExpressionID id) const final;

    void accept(IPTStatementNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    StatementID id() const noexcept final
        { return StatementID::Continue; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return keyword; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return end; }

    template <uint32_t I> requires (I == 1)
    void set(Token* keyword) noexcept
        { this->keyword = keyword; }
    template <uint32_t I> requires (I == 2)
    void set(Token* end) noexcept
        { this->end = end; }

private:
    Token* keyword;
    Token* end;
};



/*
    Expressions
*/
class PTInvalidExpression final : public IPTExpressionNode {
public:
    PTInvalidExpression(const PTInvalidExpression&) = delete;
    PTInvalidExpression& operator=(const PTInvalidExpression&) = delete;

    PTInvalidExpression(PTInvalidExpression&&) = default;
    PTInvalidExpression& operator=(PTInvalidExpression&&) = default;

    PTInvalidExpression()
        : tokens()
    {
    }
    PTInvalidExpression(std::vector<Token*>&& tokens)
        : tokens(std::move(tokens))
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::Invalid; }
    
    template <uint32_t I> requires (I == 1)
    std::vector<Token*>&& get() noexcept
        { return std::move(tokens); }

    template <uint32_t I> requires (I == 1)
    void set(std::vector<Token*>&& tokens) noexcept
        { this->tokens = std::move(tokens); }

private:
    std::vector<Token*> tokens;
};

class PTEmptyExpression final : public IPTExpressionNode {
public:
    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::Empty; }
};

class PTLiteralExpression final : public IPTExpressionNode {
public:
    PTLiteralExpression(const PTLiteralExpression&) = delete;
    PTLiteralExpression& operator=(const PTLiteralExpression&) = delete;

    PTLiteralExpression(PTLiteralExpression&&) = default;
    PTLiteralExpression& operator=(PTLiteralExpression&&) = default;

    PTLiteralExpression()
        : token(nullptr)
    {
    }
    PTLiteralExpression(Token* token)
        : token(token)
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::Literal; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return token; }

    template <uint32_t I> requires (I == 1)
    void set(Token* token) noexcept
        { this->token = token; }

private:
    Token* token;
};

class PTIdentifierExpression final : public IPTExpressionNode {
public:
    PTIdentifierExpression(const PTIdentifierExpression&) = delete;
    PTIdentifierExpression& operator=(const PTIdentifierExpression&) = delete;

    PTIdentifierExpression(PTIdentifierExpression&&) = default;
    PTIdentifierExpression& operator=(PTIdentifierExpression&&) = default;

    PTIdentifierExpression()
        : token(nullptr)
    {
    }
    PTIdentifierExpression(Token* token)
        : token(token)
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::Identifier; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return token; }

    template <uint32_t I> requires (I == 1)
    void set(Token* token) noexcept
        { this->token = token; }

private:
    Token* token;
};

class PTKeywordExpression final : public IPTExpressionNode {
public:
    PTKeywordExpression(const PTKeywordExpression&) = delete;
    PTKeywordExpression& operator=(const PTKeywordExpression&) = delete;

    PTKeywordExpression(PTKeywordExpression&&) = default;
    PTKeywordExpression& operator=(PTKeywordExpression&&) = default;

    PTKeywordExpression()
        : token(nullptr)
    {
    }
    PTKeywordExpression(Token* token)
        : token(token)
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::Keyword; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return token; }

    template <uint32_t I> requires (I == 1)
    void set(Token* token) noexcept
        { this->token = token; }

private:
    Token* token;
};

class PTAssignmentExpression final : public IPTExpressionNode {
public:
    PTAssignmentExpression(const PTAssignmentExpression&) = delete;
    PTAssignmentExpression& operator=(const PTAssignmentExpression&) = delete;

    PTAssignmentExpression(PTAssignmentExpression&&) = default;
    PTAssignmentExpression& operator=(PTAssignmentExpression&&) = default;

    PTAssignmentExpression()
        : left()
        , token(nullptr)
        , right()
    {
    }
    PTAssignmentExpression(ptr_expr&& left, Token* token, ptr_expr&& right)
        : left(std::move(left))
        , token(token)
        , right(std::move(right))
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::Assignment; }
    
    template <uint32_t I> requires (I == 1)
    ptr_expr&& get() noexcept
        { return std::move(left); }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return token; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(right); }

    template <uint32_t I> requires (I == 1)
    void set(ptr_expr&& left) noexcept
        { this->left = std::move(left); }
    template <uint32_t I> requires (I == 2)
    void set(Token* token) noexcept
        { this->token = token; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& right) noexcept
        { this->right = std::move(right); }

private:
    ptr_expr left;
    Token* token;
    ptr_expr right;
};

class PTArithmeticExpression final : public IPTExpressionNode {
public:
    PTArithmeticExpression(const PTArithmeticExpression&) = delete;
    PTArithmeticExpression& operator=(const PTArithmeticExpression&) = delete;

    PTArithmeticExpression(PTArithmeticExpression&&) = default;
    PTArithmeticExpression& operator=(PTArithmeticExpression&&) = default;

    PTArithmeticExpression()
        : left()
        , token(nullptr)
        , right()
    {
    }
    PTArithmeticExpression(ptr_expr&& left, Token* token, ptr_expr&& right)
        : left(std::move(left))
        , token(token)
        , right(std::move(right))
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::Arithmetic; }
    
    template <uint32_t I> requires (I == 1)
    ptr_expr&& get() noexcept
        { return std::move(left); }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return token; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(right); }

    template <uint32_t I> requires (I == 1)
    void set(ptr_expr&& left) noexcept
        { this->left = std::move(left); }
    template <uint32_t I> requires (I == 2)
    void set(Token* token) noexcept
        { this->token = token; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& right) noexcept
        { this->right = std::move(right); }

private:
    ptr_expr left;
    Token* token;
    ptr_expr right;
};

class PTComparisonExpression final : public IPTExpressionNode {
public:
    PTComparisonExpression(const PTComparisonExpression&) = delete;
    PTComparisonExpression& operator=(const PTComparisonExpression&) = delete;

    PTComparisonExpression(PTComparisonExpression&&) = default;
    PTComparisonExpression& operator=(PTComparisonExpression&&) = default;

    PTComparisonExpression()
        : left()
        , token(nullptr)
        , right()
    {
    }
    PTComparisonExpression(ptr_expr&& left, Token* token, ptr_expr&& right)
        : left(std::move(left))
        , token(token)
        , right(std::move(right))
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::Comparison; }
    
    template <uint32_t I> requires (I == 1)
    ptr_expr&& get() noexcept
        { return std::move(left); }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return token; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(right); }

    template <uint32_t I> requires (I == 1)
    void set(ptr_expr&& left) noexcept
        { this->left = std::move(left); }
    template <uint32_t I> requires (I == 2)
    void set(Token* token) noexcept
        { this->token = token; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& right) noexcept
        { this->right = std::move(right); }

private:
    ptr_expr left;
    Token* token;
    ptr_expr right;
};

class PTLogicalExpression final : public IPTExpressionNode {
public:
    PTLogicalExpression(const PTLogicalExpression&) = delete;
    PTLogicalExpression& operator=(const PTLogicalExpression&) = delete;

    PTLogicalExpression(PTLogicalExpression&&) = default;
    PTLogicalExpression& operator=(PTLogicalExpression&&) = default;

    PTLogicalExpression()
        : left()
        , token(nullptr)
        , right()
    {
    }
    PTLogicalExpression(ptr_expr&& left, Token* token, ptr_expr&& right)
        : left(std::move(left))
        , token(token)
        , right(std::move(right))
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::Logical; }
    
    template <uint32_t I> requires (I == 1)
    ptr_expr&& get() noexcept
        { return std::move(left); }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return token; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(right); }

    template <uint32_t I> requires (I == 1)
    void set(ptr_expr&& left) noexcept
        { this->left = std::move(left); }
    template <uint32_t I> requires (I == 2)
    void set(Token* token) noexcept
        { this->token = token; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& right) noexcept
        { this->right = std::move(right); }

private:
    ptr_expr left;
    Token* token;
    ptr_expr right;
};

class PTUnaryLogicalExpression final : public IPTExpressionNode {
public:
    PTUnaryLogicalExpression(const PTUnaryLogicalExpression&) = delete;
    PTUnaryLogicalExpression& operator=(const PTUnaryLogicalExpression&) = delete;

    PTUnaryLogicalExpression(PTUnaryLogicalExpression&&) = default;
    PTUnaryLogicalExpression& operator=(PTUnaryLogicalExpression&&) = default;

    PTUnaryLogicalExpression()
        : token(nullptr)
        , expr()
    {
    }
    PTUnaryLogicalExpression(Token* token, ptr_expr&& expr)
        : token(token)
        , expr(std::move(expr))
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::UnaryLogical; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return token; }
    template <uint32_t I> requires (I == 2)
    ptr_expr&& get() noexcept
        { return std::move(expr); }

    template <uint32_t I> requires (I == 1)
    void set(Token* token) noexcept
        { this->token = token; }
    template <uint32_t I> requires (I == 2)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }

private:
    Token* token;
    ptr_expr expr;
};

class PTReturnTypeExpression final : public IPTExpressionNode {
public:
    PTReturnTypeExpression(const PTReturnTypeExpression&) = delete;
    PTReturnTypeExpression& operator=(const PTReturnTypeExpression&) = delete;

    PTReturnTypeExpression(PTReturnTypeExpression&&) = default;
    PTReturnTypeExpression& operator=(PTReturnTypeExpression&&) = default;

    PTReturnTypeExpression()
        : left(nullptr)
        , token(nullptr)
        , type(nullptr)
        , subtype(nullptr)
    {
    }
    PTReturnTypeExpression(Token* left, Token* token, Token* type, Token* subtype)
        : left(left)
        , token(token)
        , type(type)
        , subtype(subtype)
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::ReturnType; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return left; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return token; }
    template <uint32_t I> requires (I == 3)
    Token* get() noexcept
        { return type; }
    template <uint32_t I> requires (I == 4)
    Token* get() noexcept
        { return subtype; }

    template <uint32_t I> requires (I == 1)
    void set(Token* left) noexcept
        { this->left = left; }
    template <uint32_t I> requires (I == 2)
    void set(Token* token) noexcept
        { this->token = token; }
    template <uint32_t I> requires (I == 3)
    void set(Token* type) noexcept
        { this->type = type; }
    template <uint32_t I> requires (I == 4)
    void set(Token* subtype) noexcept
        { this->subtype = subtype; }

private:
    Token* left; 
    Token* token; 
    Token* type; 
    Token* subtype;
};

class PTFunctionCallExpression final : public IPTExpressionNode {
public:
    PTFunctionCallExpression(const PTFunctionCallExpression&) = delete;
    PTFunctionCallExpression& operator=(const PTFunctionCallExpression&) = delete;

    PTFunctionCallExpression(PTFunctionCallExpression&&) = default;
    PTFunctionCallExpression& operator=(PTFunctionCallExpression&&) = default;

    PTFunctionCallExpression()
        : name(nullptr)
        , left(nullptr)
        , expr()
        , right(nullptr)
    {
    }
    PTFunctionCallExpression(Token* name, Token* left, ptr_expr&& expr, Token* right)
        : name(name)
        , left(left)
        , expr(std::move(expr))
        , right(right)
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::FunctionCall; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return name; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return left; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 4)
    Token* get() noexcept
        { return right; }

    template <uint32_t I> requires (I == 1)
    void set(Token* name) noexcept
        { this->name = name; }
    template <uint32_t I> requires (I == 2)
    void set(Token* left) noexcept
        { this->left = left; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 4)
    void set(Token* right) noexcept
        { this->right = right; }

private:
    Token* name;
    Token* left;
    ptr_expr expr;
    Token* right;
};

class PTForRangeExpression final : public IPTExpressionNode {
public:
    PTForRangeExpression(const PTForRangeExpression&) = delete;
    PTForRangeExpression& operator=(const PTForRangeExpression&) = delete;

    PTForRangeExpression(PTForRangeExpression&&) = default;
    PTForRangeExpression& operator=(PTForRangeExpression&&) = default;

    PTForRangeExpression()
        : left()
        , token(nullptr)
        , right()
    {
    }
    PTForRangeExpression(ptr_expr&& left, Token* token, ptr_expr&& right)
        : left(std::move(left))
        , token(token)
        , right(std::move(right))
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::ForRange; }
    
    template <uint32_t I> requires (I == 1)
    ptr_expr&& get() noexcept
        { return std::move(left); }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return token; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(right); }

    template <uint32_t I> requires (I == 1)
    void set(ptr_expr&& left) noexcept
        { this->left = std::move(left); }
    template <uint32_t I> requires (I == 2)
    void set(Token* token) noexcept
        { this->token = token; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& right) noexcept
        { this->right = std::move(right); }

private:
    ptr_expr left;
    Token* token;
    ptr_expr right;
};

class PTMemberAccessExpression final : public IPTExpressionNode {
public:
    PTMemberAccessExpression(const PTMemberAccessExpression&) = delete;
    PTMemberAccessExpression& operator=(const PTMemberAccessExpression&) = delete;

    PTMemberAccessExpression(PTMemberAccessExpression&&) = default;
    PTMemberAccessExpression& operator=(PTMemberAccessExpression&&) = default;

    PTMemberAccessExpression()
        : left()
        , token(nullptr)
        , right()
    {
    }
    PTMemberAccessExpression(ptr_expr&& left, Token* token, ptr_expr&& right)
        : left(std::move(left))
        , token(token)
        , right(std::move(right))
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::MemberAccess; }
    
    template <uint32_t I> requires (I == 1)
    ptr_expr&& get() noexcept
        { return std::move(left); }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return token; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(right); }

    template <uint32_t I> requires (I == 1)
    void set(ptr_expr&& left) noexcept
        { this->left = std::move(left); }
    template <uint32_t I> requires (I == 2)
    void set(Token* token) noexcept
        { this->token = token; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& right) noexcept
        { this->right = std::move(right); }

private:
    ptr_expr left;
    Token* token;
    ptr_expr right;
};

class PTErrorExpression final : public IPTExpressionNode {
public:
    PTErrorExpression(const PTErrorExpression&) = delete;
    PTErrorExpression& operator=(const PTErrorExpression&) = delete;

    PTErrorExpression(PTErrorExpression&&) = default;
    PTErrorExpression& operator=(PTErrorExpression&&) = default;

    PTErrorExpression()
        : keyword(nullptr)
        , left(nullptr)
        , expr()
        , right(nullptr)
    {
    }
    PTErrorExpression(Token* keyword, Token* left, ptr_expr&& expr, Token* right)
        : keyword(keyword)
        , left(left)
        , expr(std::move(expr))
        , right(right)
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::Error; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return keyword; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return left; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 4)
    Token* get() noexcept
        { return right; }
    
    template <uint32_t I> requires (I == 1)
    void set(Token* keyword) noexcept
        { this->keyword = keyword; }
    template <uint32_t I> requires (I == 2)
    void set(Token* left) noexcept
        { this->left = left; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 4)
    void set(Token* right) noexcept
        { this->right = right; }

private:
    Token* keyword;
    Token* left;
    ptr_expr expr;
    Token* right;
};

class PTWarningExpression final : public IPTExpressionNode {
public:
    PTWarningExpression(const PTWarningExpression&) = delete;
    PTWarningExpression& operator=(const PTWarningExpression&) = delete;

    PTWarningExpression(PTWarningExpression&&) = default;
    PTWarningExpression& operator=(PTWarningExpression&&) = default;

    PTWarningExpression()
        : keyword(nullptr)
        , left(nullptr)
        , expr()
        , right(nullptr)
    {
    }
    PTWarningExpression(Token* keyword, Token* left, ptr_expr&& expr, Token* right)
        : keyword(keyword)
        , left(left)
        , expr(std::move(expr))
        , right(right)
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::Warning; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return keyword; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return left; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 4)
    Token* get() noexcept
        { return right; }
    
    template <uint32_t I> requires (I == 1)
    void set(Token* keyword) noexcept
        { this->keyword = keyword; }
    template <uint32_t I> requires (I == 2)
    void set(Token* left) noexcept
        { this->left = left; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 4)
    void set(Token* right) noexcept
        { this->right = right; }

private:
    Token* keyword;
    Token* left;
    ptr_expr expr;
    Token* right;
};

class PTAssertExpression final : public IPTExpressionNode {
public:
    PTAssertExpression(const PTAssertExpression&) = delete;
    PTAssertExpression& operator=(const PTAssertExpression&) = delete;

    PTAssertExpression(PTAssertExpression&&) = default;
    PTAssertExpression& operator=(PTAssertExpression&&) = default;

    PTAssertExpression()
        : keyword(nullptr)
        , left(nullptr)
        , expr()
        , right(nullptr)
    {
    }
    PTAssertExpression(Token* keyword, Token* left, ptr_expr&& expr, Token* right)
        : keyword(keyword)
        , left(left)
        , expr(std::move(expr))
        , right(right)
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::Assert; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return keyword; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return left; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 4)
    Token* get() noexcept
        { return right; }
    
    template <uint32_t I> requires (I == 1)
    void set(Token* keyword) noexcept
        { this->keyword = keyword; }
    template <uint32_t I> requires (I == 2)
    void set(Token* left) noexcept
        { this->left = left; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 4)
    void set(Token* right) noexcept
        { this->right = right; }

private:
    Token* keyword;
    Token* left;
    ptr_expr expr;
    Token* right;
};

class PTArraySubscriptExpression final : public IPTExpressionNode {
public:
    PTArraySubscriptExpression(const PTArraySubscriptExpression&) = delete;
    PTArraySubscriptExpression& operator=(const PTArraySubscriptExpression&) = delete;

    PTArraySubscriptExpression(PTArraySubscriptExpression&&) = default;
    PTArraySubscriptExpression& operator=(PTArraySubscriptExpression&&) = default;

    PTArraySubscriptExpression()
        : array()
        , left(nullptr)
        , expr()
        , right(nullptr)
    {
    }
    PTArraySubscriptExpression(ptr_expr&& array, Token* left, ptr_expr&& expr, Token* right)
        : array(std::move(array))
        , left(left)
        , expr(std::move(expr))
        , right(right)
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::ArraySubscript; }
    
    template <uint32_t I> requires (I == 1)
    ptr_expr&& get() noexcept
        { return std::move(array); }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return left; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 4)
    Token* get() noexcept
        { return right; }
    
    template <uint32_t I> requires (I == 1)
    void set(ptr_expr&& array) noexcept
        { this->array = std::move(array); }
    template <uint32_t I> requires (I == 2)
    void set(Token* left) noexcept
        { this->left = left; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 4)
    void set(Token* right) noexcept
        { this->right = right; }

private:
    ptr_expr array;
    Token* left;
    ptr_expr expr;
    Token* right;
};

class PTPercentLiteralExpression final : public IPTExpressionNode {
public:
    PTPercentLiteralExpression(const PTPercentLiteralExpression&) = delete;
    PTPercentLiteralExpression& operator=(const PTPercentLiteralExpression&) = delete;

    PTPercentLiteralExpression(PTPercentLiteralExpression&&) = default;
    PTPercentLiteralExpression& operator=(PTPercentLiteralExpression&&) = default;

    PTPercentLiteralExpression()
        : value(nullptr)
        , right(nullptr)
    {
    }
    PTPercentLiteralExpression(Token* value, Token* right)
        : value(value)
        , right(right)
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::PercentLiteral; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return value; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return right; }

    template <uint32_t I> requires (I == 1)
    void set(Token* value) noexcept
        { this->value = value; }
    template <uint32_t I> requires (I == 2)
    void set(Token* right) noexcept
        { this->right = right; }

private:
    Token* value;
    Token* right;
};

class PTStringLiteralExpression final : public IPTExpressionNode {
public:
    PTStringLiteralExpression(const PTStringLiteralExpression&) = delete;
    PTStringLiteralExpression& operator=(const PTStringLiteralExpression&) = delete;

    PTStringLiteralExpression(PTStringLiteralExpression&&) = default;
    PTStringLiteralExpression& operator=(PTStringLiteralExpression&&) = default;

    PTStringLiteralExpression()
        : left(nullptr)
        , value(nullptr)
        , right(nullptr)
    {
    }
    PTStringLiteralExpression(Token* left, Token* value, Token* right)
        : left(left)
        , value(value)
        , right(right)
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::StringLiteral; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return left; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return value; }
    template <uint32_t I> requires (I == 3)
    Token* get() noexcept
        { return right; }

    template <uint32_t I> requires (I == 1)
    void set(Token* left) noexcept
        { this->left = left; }
    template <uint32_t I> requires (I == 2)
    void set(Token* value) noexcept
        { this->value = value; }
    template <uint32_t I> requires (I == 3)
    void set(Token* right) noexcept
        { this->right = right; }

private:
    Token* left;
    Token* value;
    Token* right;
};

class PTRangeLiteralExpression final : public IPTExpressionNode {
public:
    PTRangeLiteralExpression(const PTRangeLiteralExpression&) = delete;
    PTRangeLiteralExpression& operator=(const PTRangeLiteralExpression&) = delete;

    PTRangeLiteralExpression(PTRangeLiteralExpression&&) = default;
    PTRangeLiteralExpression& operator=(PTRangeLiteralExpression&&) = default;

    PTRangeLiteralExpression()
        : left()
        , token(nullptr)
        , right()
    {
    }
    PTRangeLiteralExpression(ptr_expr&& left, Token* token, ptr_expr&& right)
        : left(std::move(left))
        , token(token)
        , right(std::move(right))
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::RangeLiteral; }
    
    template <uint32_t I> requires (I == 1)
    ptr_expr&& get() noexcept
        { return std::move(left); }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return token; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(right); }

    template <uint32_t I> requires (I == 1)
    void set(ptr_expr&& left) noexcept
        { this->left = std::move(left); }
    template <uint32_t I> requires (I == 2)
    void set(Token* token) noexcept
        { this->token = token; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& right) noexcept
        { this->right = std::move(right); }

private:
    ptr_expr left;
    Token* token;
    ptr_expr right;
};

class PTCoordLiteralExpression final : public IPTExpressionNode {
public:
    PTCoordLiteralExpression(const PTCoordLiteralExpression&) = delete;
    PTCoordLiteralExpression& operator=(const PTCoordLiteralExpression&) = delete;

    PTCoordLiteralExpression(PTCoordLiteralExpression&&) = default;
    PTCoordLiteralExpression& operator=(PTCoordLiteralExpression&&) = default;

    PTCoordLiteralExpression()
        : left(nullptr)
        , expr()
        , right(nullptr)
    {
    }
    PTCoordLiteralExpression(Token* left, ptr_expr&& expr, Token* right)
        : left(left)
        , expr(std::move(expr))
        , right(right)
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::CoordLiteral; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return left; }
    template <uint32_t I> requires (I == 2)
    ptr_expr&& get() noexcept
        { return std::move(expr); }
    template <uint32_t I> requires (I == 3)
    Token* get() noexcept
        { return right; }

    template <uint32_t I> requires (I == 1)
    void set(Token* left) noexcept
        { this->left = left; }
    template <uint32_t I> requires (I == 2)
    void set(ptr_expr&& expr) noexcept
        { this->expr = std::move(expr); }
    template <uint32_t I> requires (I == 3)
    void set(Token* right) noexcept
        { this->right = right; }

private:
    Token* left;
    ptr_expr expr;
    Token* right;
};

class PTSeparatorExpression final : public IPTExpressionNode {
public:
    PTSeparatorExpression(const PTSeparatorExpression&) = delete;
    PTSeparatorExpression& operator=(const PTSeparatorExpression&) = delete;

    PTSeparatorExpression(PTSeparatorExpression&&) = default;
    PTSeparatorExpression& operator=(PTSeparatorExpression&&) = default;

    PTSeparatorExpression()
        : left()
        , sep(nullptr)
        , right()
    {
    }
    PTSeparatorExpression(ptr_expr&& left, Token* sep, ptr_expr&& right)
        : left(std::move(left))
        , sep(sep)
        , right(std::move(right))
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::Separator; }
    
    template <uint32_t I> requires (I == 1)
    ptr_expr&& get() noexcept
        { return std::move(left); }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return sep; }
    template <uint32_t I> requires (I == 3)
    ptr_expr&& get() noexcept
        { return std::move(right); }

    template <uint32_t I> requires (I == 1)
    void set(ptr_expr&& left) noexcept
        { this->left = std::move(left); }
    template <uint32_t I> requires (I == 2)
    void set(Token* sep) noexcept
        { this->sep = sep; }
    template <uint32_t I> requires (I == 3)
    void set(ptr_expr&& right) noexcept
        { this->right = std::move(right); }

private:
    ptr_expr left;
    Token* sep;
    ptr_expr right;
};

class PTDeclTypeExpression final : public IPTExpressionNode {
public:
    PTDeclTypeExpression(const PTDeclTypeExpression&) = delete;
    PTDeclTypeExpression& operator=(const PTDeclTypeExpression&) = delete;

    PTDeclTypeExpression(PTDeclTypeExpression&&) = default;
    PTDeclTypeExpression& operator=(PTDeclTypeExpression&&) = default;

    PTDeclTypeExpression()
        : type(nullptr)
        , subtype(nullptr)
        , name(nullptr)
    {
    }
    PTDeclTypeExpression(Token* type, Token* subtype, Token* name)
        : type(type)
        , subtype(subtype)
        , name(name)
    {
    }

    bool hasNode(ExpressionID id) const final;
    bool hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const final;
    bool hasKW(std::string_view kw_name) const final;
    std::vector<Token*> getTokens() const final;
    Token* getLastToken() const final;

    void accept(IPTExpressionNodeVisitor& visitor) final 
        { visitor.visit(*this); }
    ExpressionID id() const noexcept final
        { return ExpressionID::DeclType; }
    
    template <uint32_t I> requires (I == 1)
    Token* get() noexcept
        { return type; }
    template <uint32_t I> requires (I == 2)
    Token* get() noexcept
        { return subtype; }
    template <uint32_t I> requires (I == 3)
    Token* get() noexcept
        { return name; }

    template <uint32_t I> requires (I == 1)
    void set(Token* type) noexcept
        { this->type = type; }
    template <uint32_t I> requires (I == 2)
    void set(Token* subtype) noexcept
        { this->subtype = subtype; }
    template <uint32_t I> requires (I == 3)
    void set(Token* name) noexcept
        { this->name = name; }

private:
    Token* type;
    Token* subtype;
    Token* name;
};



/*
    Visitors
*/
class PTStatementVisitor final : public IPTStatementNodeVisitor {
public:
    using IPTStatementNodeVisitor::IPTStatementNodeVisitor;

    std::unique_ptr<Error> parse(PTEmptyStatement& node) final;
    std::unique_ptr<Error> parse(PTExprStatement& node) final;
    std::unique_ptr<Error> parse(PTForStatement& node) final;
    std::unique_ptr<Error> parse(PTIfStatement& node) final;
    std::unique_ptr<Error> parse(PTDeclStatement& node) final;
    std::unique_ptr<Error> parse(PTFunctionDefStatement& node) final;
    std::unique_ptr<Error> parse(PTFunctionDeclStatement& node) final;
    std::unique_ptr<Error> parse(PTNestedFunctionDefStatement& node) final;
    std::unique_ptr<Error> parse(PTNestedFunctionDeclStatement& node) final;
    std::unique_ptr<Error> parse(PTNestedDeclStatement& node) final;
    std::unique_ptr<Error> parse(PTPresetDefStatement& node) final;
    std::unique_ptr<Error> parse(PTReturnStatement& node) final;
    std::unique_ptr<Error> parse(PTBreakStatement& node) final;
    std::unique_ptr<Error> parse(PTContinueStatement& node) final;

    void visit(PTEmptyStatement& node) final;
    void visit(PTExprStatement& node) final;
    void visit(PTForStatement& node) final;
    void visit(PTIfStatement& node) final;
    void visit(PTDeclStatement& node) final;
    void visit(PTFunctionDefStatement& node) final;
    void visit(PTFunctionDeclStatement& node) final;
    void visit(PTNestedFunctionDefStatement& node) final;
    void visit(PTNestedFunctionDeclStatement& node) final;
    void visit(PTNestedDeclStatement& node) final;
    void visit(PTPresetDefStatement& node) final;
    void visit(PTReturnStatement& node) final;
    void visit(PTBreakStatement& node) final;
    void visit(PTContinueStatement& node) final;
};

class PTExpressionVisitor final : public IPTExpressionNodeVisitor {
public:
    using IPTExpressionNodeVisitor::IPTExpressionNodeVisitor;

    std::unique_ptr<Error> parse(PTInvalidExpression& node) final;
    std::unique_ptr<Error> parse(PTEmptyExpression& node) final;
    std::unique_ptr<Error> parse(PTLiteralExpression& node) final;
    std::unique_ptr<Error> parse(PTIdentifierExpression& node) final;
    std::unique_ptr<Error> parse(PTKeywordExpression& node) final;
    std::unique_ptr<Error> parse(PTAssignmentExpression& node) final;
    std::unique_ptr<Error> parse(PTArithmeticExpression& node) final;
    std::unique_ptr<Error> parse(PTComparisonExpression& node) final;
    std::unique_ptr<Error> parse(PTLogicalExpression& node) final;
    std::unique_ptr<Error> parse(PTUnaryLogicalExpression& node) final;
    std::unique_ptr<Error> parse(PTReturnTypeExpression& node) final;
    std::unique_ptr<Error> parse(PTFunctionCallExpression& node) final;
    std::unique_ptr<Error> parse(PTForRangeExpression& node) final;
    std::unique_ptr<Error> parse(PTMemberAccessExpression& node) final;
    std::unique_ptr<Error> parse(PTErrorExpression& node) final;
    std::unique_ptr<Error> parse(PTWarningExpression& node) final;
    std::unique_ptr<Error> parse(PTAssertExpression& node) final;
    std::unique_ptr<Error> parse(PTArraySubscriptExpression& node) final;
    std::unique_ptr<Error> parse(PTPercentLiteralExpression& node) final;
    std::unique_ptr<Error> parse(PTStringLiteralExpression& node) final;
    std::unique_ptr<Error> parse(PTRangeLiteralExpression& node) final;
    std::unique_ptr<Error> parse(PTCoordLiteralExpression& node) final;
    std::unique_ptr<Error> parse(PTSeparatorExpression& node) final;
    std::unique_ptr<Error> parse(PTDeclTypeExpression& node) final;

    void visit(PTInvalidExpression& node) final;
    void visit(PTEmptyExpression& node) final;
    void visit(PTLiteralExpression& node) final;
    void visit(PTIdentifierExpression& node) final;
    void visit(PTKeywordExpression& node) final;
    void visit(PTAssignmentExpression& node) final;
    void visit(PTArithmeticExpression& node) final;
    void visit(PTComparisonExpression& node) final;
    void visit(PTLogicalExpression& node) final;
    void visit(PTUnaryLogicalExpression& node) final;
    void visit(PTReturnTypeExpression& node) final;
    void visit(PTFunctionCallExpression& node) final;
    void visit(PTForRangeExpression& node) final;
    void visit(PTMemberAccessExpression& node) final;
    void visit(PTErrorExpression& node) final;
    void visit(PTWarningExpression& node) final;
    void visit(PTAssertExpression& node) final;
    void visit(PTArraySubscriptExpression& node) final;
    void visit(PTPercentLiteralExpression& node) final;
    void visit(PTStringLiteralExpression& node) final;
    void visit(PTRangeLiteralExpression& node) final;
    void visit(PTCoordLiteralExpression& node) final;
    void visit(PTSeparatorExpression& node) final;
    void visit(PTDeclTypeExpression& node) final;
};

#endif // RPP_PARSETREEVISITOR_HPP