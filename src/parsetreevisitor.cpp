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
#include <parsetreevisitor.hpp>

#include <tokenliterals.hpp>
#include <token.hpp>

/*
    PTStatementVisitor
*/
std::unique_ptr<Error> PTStatementVisitor::parse([[maybe_unused]] PTEmptyStatement& node)
{
    // statement itself is always valid
    return nullptr;
}

std::unique_ptr<Error> PTStatementVisitor::parse(PTExprStatement& node)
{
    // 1
    if (node.get<1>()->id() == ExpressionID::Keyword) {
        Token* keywordToken = node.get<1>()->getLastToken();
        if ((keywordToken->value == KW::False) ||
            (keywordToken->value == KW::True)
            ) {} // valid
        else {
            return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
        }
    }
    else if (node.get<1>()->id() == ExpressionID::Separator) {
        return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
    }
    else if (node.get<1>()->hasKW(KW::Insert)) {
        if (node.get<1>()->id() == ExpressionID::MemberAccess) {
            if ((node.get<1>()->hasKW(KW::Nocopy)) ||
                (node.get<1>()->hasKW(KW::Newrule) ||
                (node.get<1>()->hasKW(KW::Rule) && node.get<1>()->hasKW(KW::Nodefault))
                )) {} // valid
            else {
                return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
            }
        }
        else if (node.get<1>()->id() == ExpressionID::Assignment) {
            if ((node.get<1>()->hasKW(KW::Automapper)) ||
                (node.get<1>()->hasKW(KW::Newrun)) ||
                (node.get<1>()->hasKW(KW::Rule) && (
                    node.get<1>()->hasKW(KW::Random) ||
                    (node.get<1>()->hasKW(KW::Pos) && (
                        node.get<1>()->hasKW(KW::Type)
                        )) ||
                    (node.get<1>()->hasKW(KW::Pos) && (
                        node.get<1>()->hasKW(KW::Index)
                        )) ||
                    (node.get<1>()->hasKW(KW::Pos) && (
                        node.get<1>()->hasKW(KW::Operator)
                        )) ||
                    (node.get<1>()->hasKW(KW::Pos) && (
                        node.get<1>()->hasKW(KW::Group)
                        )) ||
                    node.get<1>()->hasKW(KW::Pos)
                    )) ||
                    node.get<1>()->hasKW(KW::Index)
                ) {} // valid
            else {
                return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
            }
        }
        else {
            return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
        }
    }

    node.get<1>()->accept(*m_visitor);

    // 2
    if (node.get<2>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::StatementEnd);
    m_visitor->setCurrentToken(node.get<2>());

    return nullptr;
}

std::unique_ptr<Error> PTStatementVisitor::parse(PTForStatement& node)
{
    // 1 always valid
    m_visitor->setCurrentToken(node.get<1>());

    // 2
    if (node.get<2>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::FunctionCallOpen);
    m_visitor->setCurrentToken(node.get<2>());

    // 4
    if (node.get<4>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::FunctionCallClose);

    // 3
    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(std::vector<Token*>{ node.get<1>(), node.get<2>(), node.get<4>() });

    if (node.get<3>()->id() == ExpressionID::ForRange)
        {} // valid
    else
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());

    node.get<3>()->accept(*m_visitor);

    // 5
    m_visitor->setCurrentToken(node.get<4>());
    for (auto&& stat : node.get<5>()) {
        if (stat->id() == StatementID::FunctionDef) 
            return std::make_unique<ErrInvalidExpression>(static_cast<PTFunctionDefStatement*>(stat.get())->get<1>()->getTokens());
        else if (stat->id() == StatementID::NestedFunctionDef)
            return std::make_unique<ErrInvalidExpression>(std::vector<Token*>{ static_cast<PTNestedFunctionDefStatement*>(stat.get())->get<1>() });
        else if (stat->id() == StatementID::PresetDef)
            return std::make_unique<ErrInvalidExpression>(std::vector<Token*>{ static_cast<PTPresetDefStatement*>(stat.get())->get<1>() });

        stat->accept(*this);
    }

    // 6
    if (node.get<6>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), KW::End);
    m_visitor->setCurrentToken(node.get<6>());

    return nullptr;
}

std::unique_ptr<Error> PTStatementVisitor::parse(PTIfStatement& node)
{
    // 1 always valid
    m_visitor->setCurrentToken(node.get<1>());

    // 2
    if (node.get<2>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::FunctionCallOpen);
    m_visitor->setCurrentToken(node.get<2>());

    // 4
    if (node.get<4>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::FunctionCallClose);

    // 3
    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(std::vector<Token*>{ node.get<1>(), node.get<2>(), node.get<4>() });

    Token* exprLastToken = node.get<3>()->getLastToken();

    if ((exprLastToken->cat == TIdentifier) ||
        (exprLastToken->cat == TKeyword && (
            exprLastToken->value == KW::False ||
            exprLastToken->value == KW::True
            )) ||
        (node.get<3>()->id() == ExpressionID::Comparison) ||
        (node.get<3>()->id() == ExpressionID::Logical) ||
        (node.get<3>()->id() == ExpressionID::UnaryLogical) ||
        (node.get<3>()->id() == ExpressionID::FunctionCall) ||
        (node.get<3>()->id() == ExpressionID::MemberAccess) ||
        (node.get<3>()->id() == ExpressionID::ArraySubscript)
        ) {} // valid
    else
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());

    node.get<3>()->accept(*m_visitor);

    // 5
    m_visitor->setCurrentToken(node.get<4>());
    for (auto&& stat : node.get<5>()) {
        if (stat->id() == StatementID::FunctionDef)
            return std::make_unique<ErrInvalidExpression>(static_cast<PTFunctionDefStatement*>(stat.get())->get<1>()->getTokens());
        else if (stat->id() == StatementID::NestedFunctionDef)
            return std::make_unique<ErrInvalidExpression>(std::vector<Token*>{ static_cast<PTNestedFunctionDefStatement*>(stat.get())->get<1>() });
        else if (stat->id() == StatementID::PresetDef)
            return std::make_unique<ErrInvalidExpression>(std::vector<Token*>{ static_cast<PTPresetDefStatement*>(stat.get())->get<1>() });

        stat->accept(*this);
    }

    // 6
    if (node.get<6>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), KW::End);
    m_visitor->setCurrentToken(node.get<6>());

    return nullptr;
}

std::unique_ptr<Error> PTStatementVisitor::parse(PTDeclStatement& node)
{
    // 1
    if (node.get<1>()->id() == ExpressionID::Keyword)
        return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());

    node.get<1>()->accept(*m_visitor);

    // 2
    if (node.get<2>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::StatementEnd);
    m_visitor->setCurrentToken(node.get<2>());

    return nullptr;
}

std::unique_ptr<Error> PTStatementVisitor::parse(PTFunctionDefStatement& node)
{
    // 1
    if (node.get<1>()->id() == ExpressionID::ReturnType)
        {} // valid
    else
        return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
    m_visitor->setCurrentToken(node.get<1>()->getLastToken());

    // 2
    if (node.get<2>()->id() == StatementID::Empty)
        return std::make_unique<ErrMissingExpression>(node.get<1>()->getTokens());
    
    node.get<2>()->accept(*this);

    // 3
    node.get<3>()->accept(*this);

    // 4
    for (auto&& stat : node.get<4>()) {
        if (stat->id() == StatementID::FunctionDef)
            return std::make_unique<ErrInvalidExpression>(static_cast<PTFunctionDefStatement*>(stat.get())->get<1>()->getTokens());
        else if (stat->id() == StatementID::NestedFunctionDef)
            return std::make_unique<ErrInvalidExpression>(std::vector<Token*>{ static_cast<PTNestedFunctionDefStatement*>(stat.get())->get<1>() });
        else if (stat->id() == StatementID::PresetDef)
            return std::make_unique<ErrInvalidExpression>(std::vector<Token*>{ static_cast<PTPresetDefStatement*>(stat.get())->get<1>() });

        stat->accept(*this);
    }

    // 5
    if (node.get<5>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), KW::End);
    m_visitor->setCurrentToken(node.get<5>());

    return nullptr;
}

std::unique_ptr<Error> PTStatementVisitor::parse(PTFunctionDeclStatement& node)
{
    // 1
    if (node.get<1>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), "FunctionName");
    m_visitor->setCurrentToken(node.get<1>());
    
    // 2
    if (node.get<2>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::FunctionCallOpen);
    m_visitor->setCurrentToken(node.get<2>());

    // 4
    if (node.get<4>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::FunctionCallClose);

    // 3
    if ((node.get<3>()->id() == ExpressionID::Empty) ||
        (node.get<3>()->hasOnlyNodes({ ExpressionID::DeclType }, { ExpressionID::Separator }))
        ) {} // valid
    else
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    m_visitor->setCurrentToken(node.get<4>());

    return nullptr;
}

std::unique_ptr<Error> PTStatementVisitor::parse(PTNestedFunctionDefStatement& node)
{
    // 1 always valid
    m_visitor->setCurrentToken(node.get<1>());

    // 2
    if (node.get<2>()->id() == ExpressionID::ReturnType)
        {} // valid
    else if (node.get<2>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(std::vector<Token*>{ m_visitor->getCurrentToken() });
    else
        return std::make_unique<ErrInvalidExpression>(node.get<2>()->getTokens());
    m_visitor->setCurrentToken(node.get<2>()->getLastToken());

    // 3
    if (node.get<3>()->id() == StatementID::Empty)
        return std::make_unique<ErrMissingExpression>(node.get<2>()->getTokens());

    node.get<3>()->accept(*this);

    // 4
    for (auto&& stat : node.get<4>()) {
        if (stat->id() == StatementID::FunctionDef)
            return std::make_unique<ErrInvalidExpression>(static_cast<PTFunctionDefStatement*>(stat.get())->get<1>()->getTokens());
        else if (stat->id() == StatementID::NestedFunctionDef)
            return std::make_unique<ErrInvalidExpression>(std::vector<Token*>{ static_cast<PTNestedFunctionDefStatement*>(stat.get())->get<1>() });
        else if (stat->id() == StatementID::PresetDef)
            return std::make_unique<ErrInvalidExpression>(std::vector<Token*>{ static_cast<PTPresetDefStatement*>(stat.get())->get<1>() });

        stat->accept(*this);
    }

    // 5
    if (node.get<5>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), KW::End);
    m_visitor->setCurrentToken(node.get<5>());

    return nullptr;
}

std::unique_ptr<Error> PTStatementVisitor::parse(PTNestedFunctionDeclStatement& node)
{
    // 1
    if ((node.get<1>()->id() == ExpressionID::MemberAccess) &&
        (node.get<1>()->hasOnlyNodes({ ExpressionID::MemberAccess, ExpressionID::Identifier }, {})) &&
        (static_cast<PTMemberAccessExpression*>(node.get<1>().get())->get<1>()->id() == ExpressionID::Identifier) &&
        (static_cast<PTMemberAccessExpression*>(node.get<1>().get())->get<3>()->id() == ExpressionID::Identifier)
        ) {} // valid
    else if (node.get<1>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(std::vector<Token*>{ m_visitor->getCurrentToken() });
    else
        return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
    m_visitor->setCurrentToken(node.get<1>()->getLastToken());

    // 2
    if (node.get<2>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::FunctionCallOpen);
    m_visitor->setCurrentToken(node.get<2>());

    // 4
    if (node.get<4>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::FunctionCallClose);

    // 3
    if ((node.get<3>()->id() == ExpressionID::Empty) ||
        (node.get<3>()->hasOnlyNodes({ ExpressionID::DeclType }, { ExpressionID::Separator }))
        ) {} // valid
    else
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    m_visitor->setCurrentToken(node.get<4>());

    return nullptr;
}

std::unique_ptr<Error> PTStatementVisitor::parse(PTNestedDeclStatement& node)
{
    // 1
    if (node.get<1>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), "FunctionName");
    m_visitor->setCurrentToken(node.get<1>());

    // 2
    if (node.get<2>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::FunctionCallOpen);
    m_visitor->setCurrentToken(node.get<2>());

    // 4
    if (node.get<4>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::FunctionCallClose);

    // 3
    if ((node.get<3>()->id() == ExpressionID::Empty) ||
        (node.get<3>()->hasOnlyNodes({ ExpressionID::Identifier }, { ExpressionID::Separator }))
        ) {
    } // valid
    else
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    m_visitor->setCurrentToken(node.get<4>());

    return nullptr;
}

std::unique_ptr<Error> PTStatementVisitor::parse(PTPresetDefStatement& node)
{
    // 1 always valid
    m_visitor->setCurrentToken(node.get<1>());

    // 4
    if (node.get<4>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), KW::End);

    // 2
    if (node.get<2>()->id() == StatementID::Empty)
        return std::make_unique<ErrMissingExpression>(std::vector<Token*>{ node.get<1>() });

    node.get<2>()->accept(*this);

    // 3
    for (auto&& stat : node.get<3>()) {
        if (stat->id() == StatementID::FunctionDef)
            return std::make_unique<ErrInvalidExpression>(static_cast<PTFunctionDefStatement*>(stat.get())->get<1>()->getTokens());
        else if (stat->id() == StatementID::NestedFunctionDef)
            return std::make_unique<ErrInvalidExpression>(std::vector<Token*>{ static_cast<PTNestedFunctionDefStatement*>(stat.get())->get<1>() });
        else if (stat->id() == StatementID::PresetDef)
            return std::make_unique<ErrInvalidExpression>(std::vector<Token*>{ static_cast<PTPresetDefStatement*>(stat.get())->get<1>() });

        stat->accept(*this);
    }

    m_visitor->setCurrentToken(node.get<4>());

    return nullptr;
}

std::unique_ptr<Error> PTStatementVisitor::parse(PTReturnStatement& node)
{
    // 1 always valid

    // 2
    Token* exprLastToken = node.get<2>()->getLastToken();

    if ((node.get<2>()->id() == ExpressionID::Empty) ||
        (node.get<2>()->id() == ExpressionID::Literal) ||
        (exprLastToken->cat == TIdentifier) ||
        (exprLastToken->cat == TKeyword && (
            exprLastToken->value == KW::Anchor ||
            exprLastToken->value == KW::Count ||
            exprLastToken->value == KW::False ||
            exprLastToken->value == KW::Last ||
            exprLastToken->value == KW::Pos ||
            exprLastToken->value == KW::True
            )) ||
        (node.get<2>()->id() == ExpressionID::Arithmetic) ||
        (node.get<2>()->id() == ExpressionID::Comparison) ||
        (node.get<2>()->id() == ExpressionID::Logical) ||
        (node.get<2>()->id() == ExpressionID::UnaryLogical) ||
        (node.get<2>()->id() == ExpressionID::FunctionCall && (
            !node.get<2>()->hasKW(KW::Invoke)
            )) ||
        (node.get<2>()->id() == ExpressionID::MemberAccess) ||
        (node.get<2>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<2>()->id() == ExpressionID::PercentLiteral) ||
        (node.get<2>()->id() == ExpressionID::StringLiteral) ||
        (node.get<2>()->id() == ExpressionID::RangeLiteral) ||
        (node.get<2>()->id() == ExpressionID::CoordLiteral)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<2>()->getTokens());
    }

    node.get<2>()->accept(*m_visitor);

    // 3
    if (node.get<3>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::StatementEnd);
    m_visitor->setCurrentToken(node.get<3>());

    return nullptr;
}

std::unique_ptr<Error> PTStatementVisitor::parse(PTBreakStatement& node)
{
    // 1 always valid
    m_visitor->setCurrentToken(node.get<1>());

    // 2
    if (node.get<2>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::StatementEnd);
    m_visitor->setCurrentToken(node.get<2>());

    return nullptr;
}

std::unique_ptr<Error> PTStatementVisitor::parse(PTContinueStatement& node)
{
    // 1 always valid
    m_visitor->setCurrentToken(node.get<1>());

    // 2
    if (node.get<2>() == nullptr)
        return std::make_unique<ErrMissingToken>(*m_visitor->getCurrentToken(), PU::StatementEnd);
    m_visitor->setCurrentToken(node.get<2>());

    return nullptr;
}

void PTStatementVisitor::visit(PTEmptyStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

void PTStatementVisitor::visit(PTExprStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

void PTStatementVisitor::visit(PTForStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

void PTStatementVisitor::visit(PTIfStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

void PTStatementVisitor::visit(PTDeclStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

void PTStatementVisitor::visit(PTFunctionDefStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

void PTStatementVisitor::visit(PTFunctionDeclStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

void PTStatementVisitor::visit(PTNestedFunctionDefStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

void PTStatementVisitor::visit(PTNestedFunctionDeclStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

void PTStatementVisitor::visit(PTNestedDeclStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

void PTStatementVisitor::visit(PTPresetDefStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

void PTStatementVisitor::visit(PTReturnStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

void PTStatementVisitor::visit(PTBreakStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

void PTStatementVisitor::visit(PTContinueStatement& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_visitor->errors().push(std::move(error));
}

/*
    PTExpressionVisitor
*/
std::unique_ptr<Error> PTExpressionVisitor::parse(PTInvalidExpression& node)
{
    return std::make_unique<ErrInvalidExpression>(node.get<1>());
}

std::unique_ptr<Error> PTExpressionVisitor::parse([[maybe_unused]] PTEmptyExpression& node)
{
    // expression itself is always valid
    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse([[maybe_unused]] PTLiteralExpression& node)
{
    // expression itself is always valid
    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse([[maybe_unused]] PTIdentifierExpression& node)
{
    // expression itself is always valid
    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse([[maybe_unused]] PTKeywordExpression& node)
{
    // expression itself is always valid
    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTAssignmentExpression& node)
{
    node.get<1>()->accept(*this);
    node.get<3>()->accept(*this);

    // 1
    Token* leftLastToken = node.get<1>()->getLastToken();

    if (node.get<1>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((leftLastToken->cat == TIdentifier) ||
        (leftLastToken->cat == TKeyword && (
            leftLastToken->value == KW::Automapper ||
            leftLastToken->value == KW::Group ||
            leftLastToken->value == KW::Index ||
            leftLastToken->value == KW::Newrun ||
            leftLastToken->value == KW::Operator ||
            leftLastToken->value == KW::Pos ||
            leftLastToken->value == KW::Random ||
            leftLastToken->value == KW::Type
            )) ||
        (node.get<1>()->id() == ExpressionID::MemberAccess) ||
        (node.get<1>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<1>()->id() == ExpressionID::DeclType)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
    }

    // 2
    setCurrentToken(node.get<2>());

    // 3
    Token* rightLastToken = node.get<3>()->getLastToken();

    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((node.get<3>()->id() == ExpressionID::Literal) ||
        (node.get<3>()->id() == ExpressionID::Keyword && (
            node.get<3>()->getLastToken()->value == KW::Empty ||
            node.get<3>()->getLastToken()->value == KW::False ||
            node.get<3>()->getLastToken()->value == KW::Full ||
            node.get<3>()->getLastToken()->value == KW::Index ||
            node.get<3>()->getLastToken()->value == KW::Notindex ||
            node.get<3>()->getLastToken()->value == KW::True
            )) ||
        (rightLastToken->cat == TIdentifier) ||
        (rightLastToken->cat == TKeyword && (
            rightLastToken->value == KW::Anchor ||
            rightLastToken->value == KW::Count ||
            rightLastToken->value == KW::Last ||
            rightLastToken->value == KW::Pos
            )) ||
        (node.get<3>()->id() == ExpressionID::Assignment) ||
        (node.get<3>()->id() == ExpressionID::Arithmetic) ||
        (node.get<3>()->id() == ExpressionID::Comparison) ||
        (node.get<3>()->id() == ExpressionID::Logical) ||
        (node.get<3>()->id() == ExpressionID::UnaryLogical) ||
        (node.get<3>()->id() == ExpressionID::FunctionCall) ||
        (node.get<3>()->id() == ExpressionID::ForRange) ||
        (node.get<3>()->id() == ExpressionID::MemberAccess) ||
        (node.get<3>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<3>()->id() == ExpressionID::PercentLiteral) ||
        (node.get<3>()->id() == ExpressionID::StringLiteral) ||
        (node.get<3>()->id() == ExpressionID::CoordLiteral) ||
        (node.get<3>()->id() == ExpressionID::RangeLiteral)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    }

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTArithmeticExpression& node)
{
    node.get<1>()->accept(*this);
    node.get<3>()->accept(*this);

    // 1
    Token* leftLastToken = node.get<1>()->getLastToken();

    if (node.get<1>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((node.get<1>()->id() == ExpressionID::Literal) ||
        (leftLastToken->cat == TIdentifier) ||
        (leftLastToken->cat == TKeyword && (
            leftLastToken->value == KW::Anchor ||
            leftLastToken->value == KW::Count ||
            leftLastToken->value == KW::Pos ||
            leftLastToken->value == KW::Last
            )) ||
        (node.get<1>()->id() == ExpressionID::Arithmetic) ||
        (node.get<1>()->id() == ExpressionID::FunctionCall) ||
        (node.get<1>()->id() == ExpressionID::MemberAccess) ||
        (node.get<1>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<1>()->id() == ExpressionID::PercentLiteral) ||
        (node.get<1>()->id() == ExpressionID::StringLiteral) ||
        (node.get<1>()->id() == ExpressionID::RangeLiteral) ||
        (node.get<1>()->id() == ExpressionID::CoordLiteral)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
    }

    // 2
    setCurrentToken(node.get<2>());

    // 3
    Token* rightLastToken = node.get<3>()->getLastToken();

    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((node.get<3>()->id() == ExpressionID::Literal) ||
        (rightLastToken->cat == TIdentifier) ||
        (rightLastToken->cat == TKeyword && (
            rightLastToken->value == KW::Anchor ||
            rightLastToken->value == KW::Count ||
            rightLastToken->value == KW::Pos ||
            rightLastToken->value == KW::Last
            )) ||
        (node.get<3>()->id() == ExpressionID::Arithmetic) ||
        (node.get<3>()->id() == ExpressionID::FunctionCall) ||
        (node.get<3>()->id() == ExpressionID::MemberAccess) ||
        (node.get<3>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<3>()->id() == ExpressionID::PercentLiteral) ||
        (node.get<3>()->id() == ExpressionID::StringLiteral) ||
        (node.get<3>()->id() == ExpressionID::RangeLiteral) ||
        (node.get<3>()->id() == ExpressionID::CoordLiteral)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    }

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTComparisonExpression& node)
{
    node.get<1>()->accept(*this);
    node.get<3>()->accept(*this);

    // 1
    Token* leftLastToken = node.get<1>()->getLastToken();

    if (node.get<1>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((node.get<1>()->id() == ExpressionID::Literal) ||
        (leftLastToken->cat == TIdentifier) ||
        (leftLastToken->cat == TKeyword && (
            leftLastToken->value == KW::Anchor ||
            leftLastToken->value == KW::Count ||
            leftLastToken->value == KW::False ||
            leftLastToken->value == KW::Last ||
            leftLastToken->value == KW::Pos ||
            leftLastToken->value == KW::True
            )) ||
        (node.get<1>()->id() == ExpressionID::Arithmetic) ||
        (node.get<1>()->id() == ExpressionID::FunctionCall) ||
        (node.get<1>()->id() == ExpressionID::MemberAccess) ||
        (node.get<1>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<1>()->id() == ExpressionID::PercentLiteral) ||
        (node.get<1>()->id() == ExpressionID::StringLiteral) ||
        (node.get<1>()->id() == ExpressionID::RangeLiteral) ||
        (node.get<1>()->id() == ExpressionID::CoordLiteral)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
    }

    // 2
    setCurrentToken(node.get<2>());

    // 3
    Token* rightLastToken = node.get<3>()->getLastToken();

    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((node.get<3>()->id() == ExpressionID::Literal) ||
        (rightLastToken->cat == TIdentifier) ||
        (rightLastToken->cat == TKeyword && (
            rightLastToken->value == KW::Anchor ||
            rightLastToken->value == KW::Count ||
            rightLastToken->value == KW::False ||
            rightLastToken->value == KW::Last ||
            rightLastToken->value == KW::Pos ||
            rightLastToken->value == KW::True
            )) ||
        (node.get<3>()->id() == ExpressionID::Arithmetic) ||
        (node.get<3>()->id() == ExpressionID::FunctionCall) ||
        (node.get<3>()->id() == ExpressionID::MemberAccess) ||
        (node.get<3>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<3>()->id() == ExpressionID::PercentLiteral) ||
        (node.get<3>()->id() == ExpressionID::StringLiteral) ||
        (node.get<3>()->id() == ExpressionID::RangeLiteral) ||
        (node.get<3>()->id() == ExpressionID::CoordLiteral)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    }

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTLogicalExpression& node)
{
    node.get<1>()->accept(*this);
    node.get<3>()->accept(*this);

    // 1
    Token* leftLastToken = node.get<1>()->getLastToken();

    if (node.get<1>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((leftLastToken->cat == TIdentifier) ||
        (leftLastToken->cat == TKeyword && (
            leftLastToken->value == KW::False ||
            leftLastToken->value == KW::True
            )) ||
        (node.get<1>()->id() == ExpressionID::Comparison) ||
        (node.get<1>()->id() == ExpressionID::Logical) ||
        (node.get<1>()->id() == ExpressionID::UnaryLogical) ||
        (node.get<1>()->id() == ExpressionID::FunctionCall) ||
        (node.get<1>()->id() == ExpressionID::MemberAccess) ||
        (node.get<1>()->id() == ExpressionID::ArraySubscript)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
    }

    // 2
    setCurrentToken(node.get<2>());

    // 3
    Token* rightLastToken = node.get<3>()->getLastToken();

    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((rightLastToken->cat == TIdentifier) ||
        (rightLastToken->cat == TKeyword && (
            rightLastToken->value == KW::False ||
            rightLastToken->value == KW::True
            )) ||
        (node.get<3>()->id() == ExpressionID::Comparison) ||
        (node.get<3>()->id() == ExpressionID::Logical) ||
        (node.get<3>()->id() == ExpressionID::UnaryLogical) ||
        (node.get<3>()->id() == ExpressionID::FunctionCall) ||
        (node.get<3>()->id() == ExpressionID::MemberAccess) ||
        (node.get<3>()->id() == ExpressionID::ArraySubscript)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    }

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTUnaryLogicalExpression& node)
{
    node.get<2>()->accept(*this);

    // 1
    setCurrentToken(node.get<1>());

    // 2
    Token* exprLastToken = node.get<2>()->getLastToken();

    if (node.get<2>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((exprLastToken->cat == TIdentifier) ||
        (exprLastToken->cat == TKeyword && (
            exprLastToken->value == KW::False ||
            exprLastToken->value == KW::True
            )) ||
        (node.get<2>()->id() == ExpressionID::Comparison) ||
        (node.get<2>()->id() == ExpressionID::Logical) ||
        (node.get<2>()->id() == ExpressionID::UnaryLogical) ||
        (node.get<2>()->id() == ExpressionID::FunctionCall) ||
        (node.get<2>()->id() == ExpressionID::MemberAccess) ||
        (node.get<2>()->id() == ExpressionID::ArraySubscript)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<2>()->getTokens());
    }

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTReturnTypeExpression& node)
{
    // 1 always valid

    // 2
    if (node.get<2>() != nullptr && node.get<2>()->value == OP::ReturnType) 
        {} // valid
    else
        return std::make_unique<ErrInvalidExpression>(node.getTokens());

    // 3
    if (node.get<3>() != nullptr && Token::isReturnType(node.get<3>()->value))
        {} // valid
    else
        return std::make_unique<ErrInvalidExpression>(node.getTokens());

    // 4
    if ((node.get<3>()->value != KW::Array && node.get<4>() == nullptr) || (node.get<3>()->value == KW::Array && Token::isSubtype(node.get<4>()->value)))
        {} // valid
    else
        return std::make_unique<ErrInvalidExpression>(node.getTokens());

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTFunctionCallExpression& node)
{
    node.get<3>()->accept(*this);

    // 1
    // 2 always valid

    // 3
    if (node.get<1>() != nullptr && node.get<1>()->cat == TKeyword) {
        if (node.get<3>()->id() == ExpressionID::Keyword && node.get<3>()->getLastToken()->value == KW::Nested)
            {} // valid
        else
            return std::make_unique<ErrInvalidExpression>(node.getTokens());
        setCurrentToken(node.get<3>()->getLastToken());
    }
    else {
        Token* exprLastToken = node.get<3>()->getLastToken();

        if ((node.get<3>()->id() == ExpressionID::Empty) ||
            (node.get<3>()->id() == ExpressionID::Literal) ||
            (exprLastToken->cat == TIdentifier) ||
            (exprLastToken->cat == TKeyword && (
                exprLastToken->value == KW::Anchor ||
                exprLastToken->value == KW::Count ||
                exprLastToken->value == KW::False ||
                exprLastToken->value == KW::Last ||
                exprLastToken->value == KW::Pos ||
                exprLastToken->value == KW::True
                )) ||
            (node.get<3>()->id() == ExpressionID::Arithmetic) ||
            (node.get<3>()->id() == ExpressionID::Comparison) ||
            (node.get<3>()->id() == ExpressionID::Logical) ||
            (node.get<3>()->id() == ExpressionID::UnaryLogical) ||
            (node.get<3>()->id() == ExpressionID::FunctionCall) ||
            (node.get<3>()->id() == ExpressionID::MemberAccess) ||
            (node.get<3>()->id() == ExpressionID::ArraySubscript) ||
            (node.get<3>()->id() == ExpressionID::PercentLiteral) ||
            (node.get<3>()->id() == ExpressionID::StringLiteral) ||
            (node.get<3>()->id() == ExpressionID::RangeLiteral) ||
            (node.get<3>()->id() == ExpressionID::CoordLiteral) ||
            (node.get<3>()->id() == ExpressionID::Separator && (
                node.get<1>() != nullptr
                ))
            ) {} // valid
        else {
            return std::make_unique<ErrInvalidExpression>(node.getTokens());
        }
    }

    // 4
    if (node.get<4>() == nullptr)
        return std::make_unique<ErrMissingToken>(*getCurrentToken(), PU::FunctionCallClose);

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTForRangeExpression& node)
{
    node.get<1>()->accept(*this);
    node.get<3>()->accept(*this);

    // 1
    if (node.get<1>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((node.get<1>()->id() == ExpressionID::Assignment && (
            !node.get<1>()->hasNode(ExpressionID::DeclType)
            ))
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
    }

    // 2
    setCurrentToken(node.get<2>());

    // 3
    Token* rightLastToken = node.get<3>()->getLastToken();

    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());
    
    if ((node.get<3>()->id() == ExpressionID::Literal) ||
        (rightLastToken->cat == TIdentifier) ||
        (rightLastToken->cat == TKeyword && (
            rightLastToken->value == KW::Count ||
            rightLastToken->value == KW::Last
            )) ||
        (node.get<3>()->id() == ExpressionID::Arithmetic) ||
        (node.get<3>()->id() == ExpressionID::FunctionCall) ||
        (node.get<3>()->id() == ExpressionID::MemberAccess) ||
        (node.get<3>()->id() == ExpressionID::ArraySubscript)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    }

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTMemberAccessExpression& node)
{
    node.get<1>()->accept(*this);
    node.get<3>()->accept(*this);

    // 1
    Token* leftLastToken = node.get<1>()->getLastToken();

    if (node.get<1>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((node.get<1>()->id() == ExpressionID::Literal) ||
        (leftLastToken->cat == TIdentifier) ||
        (leftLastToken->cat == TKeyword && (
            leftLastToken->value == KW::Anchor ||
            leftLastToken->value == KW::Count ||
            leftLastToken->value == KW::False ||
            leftLastToken->value == KW::Index ||
            leftLastToken->value == KW::Insert ||
            leftLastToken->value == KW::Last ||
            leftLastToken->value == KW::Pos ||
            leftLastToken->value == KW::Preset ||
            leftLastToken->value == KW::Rotate ||
            leftLastToken->value == KW::Rule ||
            leftLastToken->value == KW::True
            )) ||
        (node.get<1>()->id() == ExpressionID::FunctionCall) ||
        (node.get<1>()->id() == ExpressionID::MemberAccess) ||
        (node.get<1>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<1>()->id() == ExpressionID::RangeLiteral) ||
        (node.get<1>()->id() == ExpressionID::CoordLiteral) ||
        (node.get<1>()->id() == ExpressionID::StringLiteral)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.getTokens());
    }

    // 2
    setCurrentToken(node.get<2>());

    // 3
    Token* rightLastToken = node.get<3>()->getLastToken();

    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());
    
    if ((rightLastToken->cat == TIdentifier) ||
        (rightLastToken->cat == TKeyword && (
            rightLastToken->value == KW::Anchor ||
            rightLastToken->value == KW::Automapper ||
            rightLastToken->value == KW::Count ||
            rightLastToken->value == KW::Index ||
            rightLastToken->value == KW::Group ||
            rightLastToken->value == KW::Last ||
            rightLastToken->value == KW::Newrule ||
            rightLastToken->value == KW::Newrun ||
            rightLastToken->value == KW::Nocopy ||
            rightLastToken->value == KW::Nodefault ||
            rightLastToken->value == KW::Notindex ||
            rightLastToken->value == KW::Operator ||
            rightLastToken->value == KW::Pos ||
            rightLastToken->value == KW::Random ||
            rightLastToken->value == KW::Rotate ||
            rightLastToken->value == KW::Rule ||
            rightLastToken->value == KW::Type
            )) ||
        (node.get<3>()->id() == ExpressionID::FunctionCall) ||
        (node.get<3>()->id() == ExpressionID::MemberAccess) ||
        (node.get<3>()->id() == ExpressionID::ArraySubscript)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.getTokens());
    }

    /*
    insert -> automapper
           -> newrun
           -> newrule
           -> nocopy
           -> rule -> nodefault
                   -> random
                   -> pos
                   -> index
                   -> pos -> type
                          -> index
                          -> operator
                          -> group
    */
    if (node.get<1>()->id() == ExpressionID::Keyword && leftLastToken->value == KW::Insert) {
        if ((node.get<3>()->id() == ExpressionID::Keyword && (
                rightLastToken->value == KW::Automapper ||
                rightLastToken->value == KW::Newrun ||
                rightLastToken->value == KW::Newrule ||
                rightLastToken->value == KW::Nocopy
                ))
            ) {} // valid
        else if (node.get<3>()->id() == ExpressionID::MemberAccess) {
            auto& right = static_cast<PTMemberAccessExpression&>(*node.get<3>());
            if ((right.get<1>()->id() == ExpressionID::Keyword && (
                    right.get<1>()->getLastToken()->value == KW::Rule
                    ))
                ) {} // valid
            else
                return std::make_unique<ErrInvalidExpression>(node.getTokens());
        }
        else
            return std::make_unique<ErrInvalidExpression>(node.getTokens());

    }
    else if (node.get<1>()->id() == ExpressionID::Keyword && leftLastToken->value == KW::Rule) {
        if ((node.get<3>()->id() == ExpressionID::Keyword && (
                rightLastToken->value == KW::Nodefault ||
                rightLastToken->value == KW::Random ||
                rightLastToken->value == KW::Pos ||
                rightLastToken->value == KW::Index
                ))
            ) {} // valid
        else if (node.get<3>()->id() == ExpressionID::MemberAccess) {
            auto& right = static_cast<PTMemberAccessExpression&>(*node.get<3>());
            if ((right.get<1>()->id() == ExpressionID::Keyword && (
                    right.get<1>()->getLastToken()->value == KW::Pos ||
                    right.get<1>()->getLastToken()->value == KW::Index
                    ))
                ) {} // valid
            else
                return std::make_unique<ErrInvalidExpression>(node.getTokens());
        }
        else
            return std::make_unique<ErrInvalidExpression>(node.getTokens());
    }
    else if (node.get<1>()->id() == ExpressionID::Keyword && leftLastToken->value == KW::Pos) {
        if ((node.get<3>()->id() == ExpressionID::Keyword && (
                rightLastToken->value == KW::Type ||
                rightLastToken->value == KW::Index ||
                rightLastToken->value == KW::Operator ||
                rightLastToken->value == KW::Group
                ))
            ) {} // valid
        else if (node.get<3>()->id() == ExpressionID::MemberAccess) {
            auto& right = static_cast<PTMemberAccessExpression&>(*node.get<3>());
            if ((right.get<1>()->id() == ExpressionID::Keyword && (
                    right.get<1>()->getLastToken()->value == KW::Index
                    ))
                ) {} // valid
            else
                return std::make_unique<ErrInvalidExpression>(node.getTokens());
        }
        else
            return std::make_unique<ErrInvalidExpression>(node.getTokens());
    }

    // preset.Call()
    if ((node.get<1>()->id() == ExpressionID::Keyword && leftLastToken->value == KW::Preset) &&
        (node.get<3>()->id() != ExpressionID::FunctionCall)
        ) return std::make_unique<ErrInvalidExpression>(node.getTokens());

    // nested call
    if ((node.get<1>()->id() == ExpressionID::FunctionCall) &&
        (node.get<3>()->id() == ExpressionID::Identifier)
        ) {
        if (Token::isPos(rightLastToken->value) ||
            Token::isRotation(rightLastToken->value)
            ) {} // valid
        else
            return std::make_unique<ErrInvalidExpression>(node.getTokens());
    }

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTErrorExpression& node)
{
    node.get<3>()->accept(*this);

    // 1
    setCurrentToken(node.get<1>());

    // 2
    if (node.get<2>() == nullptr)
        return std::make_unique<ErrMissingToken>(*getCurrentToken(), PU::FunctionCallOpen);

    // 3
    Token* exprLastToken = node.get<3>()->getLastToken();

    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((exprLastToken->cat == TIdentifier) ||
        (node.get<3>()->id() == ExpressionID::Arithmetic) ||
        (node.get<3>()->id() == ExpressionID::FunctionCall) ||
        (node.get<3>()->id() == ExpressionID::MemberAccess) ||
        (node.get<3>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<3>()->id() == ExpressionID::StringLiteral)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    }
    setCurrentToken(exprLastToken);

    // 4
    if (node.get<4>() == nullptr)
        return std::make_unique<ErrMissingToken>(*getCurrentToken(), PU::FunctionCallClose);

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTWarningExpression& node)
{
    node.get<3>()->accept(*this);

    // 1
    setCurrentToken(node.get<1>());

    // 2
    if (node.get<2>() == nullptr)
        return std::make_unique<ErrMissingToken>(*getCurrentToken(), PU::FunctionCallOpen);

    // 3
    Token* exprLastToken = node.get<3>()->getLastToken();

    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((exprLastToken->cat == TIdentifier) ||
        (node.get<3>()->id() == ExpressionID::Arithmetic) ||
        (node.get<3>()->id() == ExpressionID::FunctionCall) ||
        (node.get<3>()->id() == ExpressionID::MemberAccess) ||
        (node.get<3>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<3>()->id() == ExpressionID::StringLiteral)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    }
    setCurrentToken(exprLastToken);

    // 4
    if (node.get<4>() == nullptr)
        return std::make_unique<ErrMissingToken>(*getCurrentToken(), PU::FunctionCallClose);

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTAssertExpression& node)
{
    node.get<3>()->accept(*this);

    // 1
    setCurrentToken(node.get<1>());

    // 2
    if (node.get<2>() == nullptr)
        return std::make_unique<ErrMissingToken>(*getCurrentToken(), PU::FunctionCallOpen);

    // 3
    Token* exprLastToken = node.get<3>()->getLastToken();

    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((exprLastToken->cat == TIdentifier) ||
        (node.get<3>()->id() == ExpressionID::Keyword && (
            exprLastToken->value == KW::False ||
            exprLastToken->value == KW::True
            )) ||
        (node.get<3>()->id() == ExpressionID::Comparison) ||
        (node.get<3>()->id() == ExpressionID::Logical) ||
        (node.get<3>()->id() == ExpressionID::UnaryLogical) ||
        (node.get<3>()->id() == ExpressionID::FunctionCall) ||
        (node.get<3>()->id() == ExpressionID::MemberAccess) ||
        (node.get<3>()->id() == ExpressionID::ArraySubscript)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    }
    setCurrentToken(exprLastToken);

    // 4
    if (node.get<4>() == nullptr)
        return std::make_unique<ErrMissingToken>(*getCurrentToken(), PU::FunctionCallClose);

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTArraySubscriptExpression& node)
{
    node.get<1>()->accept(*this);
    node.get<3>()->accept(*this);

    // 1
    // 2 always valid

    // 3
    Token* exprLastToken = node.get<3>()->getLastToken();

    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((node.get<3>()->id() == ExpressionID::Literal) ||
        (exprLastToken->cat == TIdentifier) ||
        (exprLastToken->cat == TKeyword && (
            exprLastToken->value == KW::Count ||
            exprLastToken->value == KW::Last
            )) ||
        (node.get<3>()->id() == ExpressionID::Arithmetic) ||
        (node.get<3>()->id() == ExpressionID::FunctionCall) ||
        (node.get<3>()->id() == ExpressionID::MemberAccess) ||
        (node.get<3>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<3>()->id() == ExpressionID::CoordLiteral)
        ) {
    } // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    }
    setCurrentToken(exprLastToken);

    // 4
    if (node.get<4>() == nullptr)
        return std::make_unique<ErrMissingToken>(*getCurrentToken(), PU::FunctionCallClose);

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse([[maybe_unused]] PTPercentLiteralExpression& node)
{
    // expression itself is always valid
    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTStringLiteralExpression& node)
{
    // 1 always valid

    // 2
    if (node.get<2>() == nullptr)
        return std::make_unique<ErrInvalidExpression>(node.getTokens());
    setCurrentToken(node.get<2>());

    // 3
    if (node.get<3>() == nullptr)
        return std::make_unique<ErrMissingToken>(*getCurrentToken(), PU::StringLiteral);

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTRangeLiteralExpression& node)
{
    node.get<1>()->accept(*this);
    node.get<3>()->accept(*this);

    // 1
    Token* leftLastToken = node.get<1>()->getLastToken();

    if (node.get<1>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((node.get<1>()->id() == ExpressionID::Literal) ||
        (leftLastToken->cat == TIdentifier) ||
        (leftLastToken->cat == TKeyword && (
            leftLastToken->value == KW::Count ||
            leftLastToken->value == KW::Last
            )) ||
        (node.get<1>()->id() == ExpressionID::FunctionCall) ||
        (node.get<1>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<1>()->id() == ExpressionID::CoordLiteral)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
    }

    // 2
    setCurrentToken(node.get<2>());

    // 3
    Token* rightLastToken = node.get<3>()->getLastToken();

    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());
    
    if ((node.get<3>()->id() == ExpressionID::Literal) ||
        (rightLastToken->cat == TIdentifier) ||
        (rightLastToken->cat == TKeyword && (
            rightLastToken->value == KW::Count ||
            rightLastToken->value == KW::Last
            )) ||
        (node.get<3>()->id() == ExpressionID::FunctionCall) ||
        (node.get<3>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<3>()->id() == ExpressionID::CoordLiteral)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    }

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTCoordLiteralExpression& node)
{
    node.get<2>()->accept(*this);

    // 1 always valid

    // 2
    if (node.get<2>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());

    if ((node.get<2>()->id() == ExpressionID::Separator && (
            node.get<2>()->hasNode(ExpressionID::Literal) ||
            node.get<2>()->hasNode(ExpressionID::Identifier) ||
            node.get<2>()->hasNode(ExpressionID::Keyword) ||
            node.get<2>()->hasNode(ExpressionID::Arithmetic) ||
            node.get<2>()->hasNode(ExpressionID::FunctionCall) ||
            node.get<2>()->hasNode(ExpressionID::MemberAccess) ||
            node.get<2>()->hasNode(ExpressionID::ArraySubscript)
            )) &&
        (static_cast<PTSeparatorExpression*>(node.get<2>().get())->get<3>()->id() != ExpressionID::Separator)
        ) {} // valid
    else
        return std::make_unique<ErrInvalidExpression>(node.getTokens());

    // 3 always valid

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTSeparatorExpression& node)
{
    node.get<1>()->accept(*this);
    node.get<3>()->accept(*this);

    // 1
    Token* leftLastToken = node.get<1>()->getLastToken();

    if (node.get<1>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());
    
    if ((node.get<1>()->id() == ExpressionID::Literal) ||
        (leftLastToken->cat == TIdentifier) ||
        (leftLastToken->cat == TKeyword && (
            leftLastToken->value == KW::Anchor ||
            leftLastToken->value == KW::Count ||
            leftLastToken->value == KW::False ||
            leftLastToken->value == KW::Last ||
            leftLastToken->value == KW::Pos ||
            leftLastToken->value == KW::True
            )) ||
        (node.get<1>()->id() == ExpressionID::Assignment && (
            node.get<1>()->hasNode(ExpressionID::DeclType)
            )) ||
        (node.get<1>()->id() == ExpressionID::Arithmetic) ||
        (node.get<1>()->id() == ExpressionID::Comparison) ||
        (node.get<1>()->id() == ExpressionID::Logical) ||
        (node.get<1>()->id() == ExpressionID::UnaryLogical) ||
        (node.get<1>()->id() == ExpressionID::FunctionCall) ||
        (node.get<1>()->id() == ExpressionID::MemberAccess) ||
        (node.get<1>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<1>()->id() == ExpressionID::PercentLiteral) ||
        (node.get<1>()->id() == ExpressionID::StringLiteral) ||
        (node.get<1>()->id() == ExpressionID::RangeLiteral) ||
        (node.get<1>()->id() == ExpressionID::CoordLiteral) ||
        (node.get<1>()->id() == ExpressionID::DeclType)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<1>()->getTokens());
    }

    // 2
    setCurrentToken(node.get<2>());

    // 3
    Token* rightLastToken = node.get<3>()->getLastToken();

    if (node.get<3>()->id() == ExpressionID::Empty)
        return std::make_unique<ErrMissingExpression>(node.getTokens());
    
    if ((node.get<3>()->id() == ExpressionID::Literal) ||
        (rightLastToken->cat == TIdentifier) ||
        (rightLastToken->cat == TKeyword && (
            rightLastToken->value == KW::Anchor ||
            rightLastToken->value == KW::Count ||
            rightLastToken->value == KW::False ||
            rightLastToken->value == KW::Last ||
            rightLastToken->value == KW::Pos ||
            rightLastToken->value == KW::True
            )) ||
        (node.get<3>()->id() == ExpressionID::Assignment) ||
        (node.get<3>()->id() == ExpressionID::Arithmetic) ||
        (node.get<3>()->id() == ExpressionID::Comparison) ||
        (node.get<3>()->id() == ExpressionID::Logical) ||
        (node.get<3>()->id() == ExpressionID::UnaryLogical) ||
        (node.get<3>()->id() == ExpressionID::FunctionCall) ||
        (node.get<3>()->id() == ExpressionID::MemberAccess) ||
        (node.get<3>()->id() == ExpressionID::ArraySubscript) ||
        (node.get<3>()->id() == ExpressionID::PercentLiteral) ||
        (node.get<3>()->id() == ExpressionID::StringLiteral) ||
        (node.get<3>()->id() == ExpressionID::RangeLiteral) ||
        (node.get<3>()->id() == ExpressionID::CoordLiteral) ||
        (node.get<3>()->id() == ExpressionID::Separator) ||
        (node.get<3>()->id() == ExpressionID::DeclType)
        ) {} // valid
    else {
        return std::make_unique<ErrInvalidExpression>(node.get<3>()->getTokens());
    }

    return nullptr;
}

std::unique_ptr<Error> PTExpressionVisitor::parse(PTDeclTypeExpression& node)
{
    // 1 always valid

    // 3
    if (node.get<3>() == nullptr)
        return std::make_unique<ErrInvalidExpression>(node.getTokens());

    if ((node.get<1>()->value != KW::Array && (
            node.get<3>()->cat == TIdentifier
            ))
        ) {} // valid
    else {
        // 2
        if (node.get<2>() == nullptr)
            return std::make_unique<ErrInvalidExpression>(node.getTokens());

        if ((Token::isSubtype(node.get<2>()->value)) &&
            (node.get<3>()->cat == TIdentifier)
            ) {} // valid
        else {
            return std::make_unique<ErrInvalidExpression>(node.getTokens());
        }
    }

    return nullptr;
}

void PTExpressionVisitor::visit(PTInvalidExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTEmptyExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTLiteralExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTIdentifierExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTKeywordExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTAssignmentExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTArithmeticExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTComparisonExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTLogicalExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTUnaryLogicalExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTReturnTypeExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTFunctionCallExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTForRangeExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTMemberAccessExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTErrorExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTWarningExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTAssertExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTArraySubscriptExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTPercentLiteralExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTStringLiteralExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTRangeLiteralExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTCoordLiteralExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTSeparatorExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

void PTExpressionVisitor::visit(PTDeclTypeExpression& node)
{
    auto error = parse(node);
    if (error != nullptr)
        m_errors.push(std::move(error));
}

/*
    PTEmptyStatement
*/
bool PTEmptyStatement::hasNode([[maybe_unused]] ExpressionID id) const
{
    return false;
}

/*
    PTExprStatement
*/
bool PTExprStatement::hasNode(ExpressionID id) const
{
    return this->expr->hasNode(id);
}

/*
    PTForStatement
*/
bool PTForStatement::hasNode(ExpressionID id) const
{
    if (this->expr->hasNode(id))
        return true;

    for (auto&& s : this->stats)
        if (s->hasNode(id))
            return true;

    return false;
}

/*
    PTIfStatement
*/
bool PTIfStatement::hasNode(ExpressionID id) const
{
    if (this->expr->hasNode(id))
        return true;

    for (auto&& s : this->stats)
        if (s->hasNode(id))
            return true;

    return false;    
}

/*
    PTDeclStatement
*/
bool PTDeclStatement::hasNode(ExpressionID id) const
{
    return this->expr->hasNode(id);
}

/*
    PTFunctionDefStatement
*/
bool PTFunctionDefStatement::hasNode(ExpressionID id) const
{
    if (this->expr->hasNode(id))
        return true;
    if (this->stat->hasNode(id))
        return true;
    if (this->nested->hasNode(id))
        return true;

    for (auto&& s : this->stats)
        if (s->hasNode(id))
            return true;

    return false;
}

/*
    PTFunctionDeclStatement
*/
bool PTFunctionDeclStatement::hasNode(ExpressionID id) const
{
    return this->expr->hasNode(id);
}

/*
    PTNestedFunctionDefStatement
*/
bool PTNestedFunctionDefStatement::hasNode(ExpressionID id) const
{
    if (this->expr->hasNode(id))
        return true;
    if (this->stat->hasNode(id))
        return true;

    for (auto&& s : this->stats)
        if (s->hasNode(id))
            return true;

    return false;
}

/*
    PTNestedFunctionDeclStatement
*/
bool PTNestedFunctionDeclStatement::hasNode(ExpressionID id) const
{
    if (this->name->hasNode(id))
        return true;
    if (this->expr->hasNode(id))
        return true;

    return false;
}

/*
    PTNestedDeclStatement
*/
bool PTNestedDeclStatement::hasNode(ExpressionID id) const
{
    return this->expr->hasNode(id);
}

/*
    PTPresetDefStatement
*/
bool PTPresetDefStatement::hasNode(ExpressionID id) const
{
    if (this->stat->hasNode(id))
        return true;

    for (auto&& s : stats)
        if (s->hasNode(id))
            return true;

    return false;
}

/*
    PTReturnStatement
*/
bool PTReturnStatement::hasNode(ExpressionID id) const
{
    return this->expr->hasNode(id);
}

/*
    PTBreakStatement
*/
bool PTBreakStatement::hasNode([[maybe_unused]] ExpressionID id) const
{
    return false;
}

/*
    PTContinueStatement
*/
bool PTContinueStatement::hasNode([[maybe_unused]] ExpressionID id) const
{
    return false;
}

/*
    PTInvalidExpression
*/
bool PTInvalidExpression::hasNode(ExpressionID id) const
{
    return this->id() == id;
}

bool PTInvalidExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTInvalidExpression::hasKW([[maybe_unused]] std::string_view kw_name) const
{
    return false;
}

std::vector<Token*> PTInvalidExpression::getTokens() const
{
    return this->tokens;
}

Token* PTInvalidExpression::getLastToken() const
{
    return this->tokens.back();
}

/*
    PTEmptyExpression
*/
bool PTEmptyExpression::hasNode(ExpressionID id) const
{
    return this->id() == id;
}

bool PTEmptyExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTEmptyExpression::hasKW([[maybe_unused]] std::string_view kw_name) const
{
    return false;
}

std::vector<Token*> PTEmptyExpression::getTokens() const
{
    return {};
}

Token* PTEmptyExpression::getLastToken() const
{
    return nullptr;
}

/*
    PTLiteralExpression
*/
bool PTLiteralExpression::hasNode(ExpressionID id) const
{
    return this->id() == id;
}

bool PTLiteralExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTLiteralExpression::hasKW([[maybe_unused]] std::string_view kw_name) const
{
    return false;
}

std::vector<Token*> PTLiteralExpression::getTokens() const
{
    return { this->token };
}

Token* PTLiteralExpression::getLastToken() const
{
    return this->token;
}

/*
    PTIdentifierExpression
*/
bool PTIdentifierExpression::hasNode(ExpressionID id) const
{
    return this->id() == id;
}

bool PTIdentifierExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTIdentifierExpression::hasKW(std::string_view kw_name) const
{
    return this->token->value == kw_name;
}

std::vector<Token*> PTIdentifierExpression::getTokens() const
{
    return { this->token };
}

Token* PTIdentifierExpression::getLastToken() const
{
    return this->token;
}

/*
    PTKeywordExpression
*/
bool PTKeywordExpression::hasNode(ExpressionID id) const
{
    return this->id() == id;
}

bool PTKeywordExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTKeywordExpression::hasKW(std::string_view kw_name) const
{
    return this->token->value == kw_name;
}

std::vector<Token*> PTKeywordExpression::getTokens() const
{
    return { this->token };
}

Token* PTKeywordExpression::getLastToken() const
{
    return this->token;
}

/*
    PTAssignmentExpression
*/
bool PTAssignmentExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    if (this->left->hasNode(id))
        return true;
    if (this->right->hasNode(id))
        return true;

    return false;
}

bool PTAssignmentExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->left->hasOnlyNodes(ids, ignore))
        return false;
    if (!this->right->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTAssignmentExpression::hasKW(std::string_view kw_name) const
{
    if (this->left->hasKW(kw_name))
        return true;
    if (this->right->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTAssignmentExpression::getTokens() const
{
    std::vector<Token*> t;
    
    auto leftV = this->left->getTokens();
    auto rightV = this->right->getTokens();

    t.insert(t.end(), leftV.begin(), leftV.end());
    t.push_back(this->token);
    t.insert(t.end(), rightV.begin(), rightV.end());

    return t;
}

Token* PTAssignmentExpression::getLastToken() const
{
    if (this->right->id() != ExpressionID::Empty)
        return this->right->getLastToken();

    return this->token;
}

/*
    PTArithmeticExpression
*/
bool PTArithmeticExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    if (this->left->hasNode(id))
        return true;
    if (this->right->hasNode(id))
        return true;

    return false;
}

bool PTArithmeticExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->left->hasOnlyNodes(ids, ignore))
        return false;
    if (!this->right->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTArithmeticExpression::hasKW(std::string_view kw_name) const
{
    if (this->left->hasKW(kw_name))
        return true;
    if (this->right->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTArithmeticExpression::getTokens() const
{
    std::vector<Token*> t;

    auto leftV = this->left->getTokens();
    auto rightV = this->right->getTokens();

    t.insert(t.end(), leftV.begin(), leftV.end());
    t.push_back(this->token);
    t.insert(t.end(), rightV.begin(), rightV.end());

    return t;
}

Token* PTArithmeticExpression::getLastToken() const
{
    if (this->right->id() != ExpressionID::Empty)
        return this->right->getLastToken();

    return this->token;
}

/*
    PTComparisonExpression
*/
bool PTComparisonExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    if (this->left->hasNode(id))
        return true;
    if (this->right->hasNode(id))
        return true;

    return false;
}

bool PTComparisonExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->left->hasOnlyNodes(ids, ignore))
        return false;
    if (!this->right->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTComparisonExpression::hasKW(std::string_view kw_name) const
{
    if (this->left->hasKW(kw_name))
        return true;
    if (this->right->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTComparisonExpression::getTokens() const
{
    std::vector<Token*> t;

    auto leftV = this->left->getTokens();
    auto rightV = this->right->getTokens();

    t.insert(t.end(), leftV.begin(), leftV.end());
    t.push_back(this->token);
    t.insert(t.end(), rightV.begin(), rightV.end());

    return t;
}

Token* PTComparisonExpression::getLastToken() const
{
    if (this->right->id() != ExpressionID::Empty)
        return this->right->getLastToken();

    return this->token;
}

/*
    PTLogicalExpression
*/
bool PTLogicalExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    if (this->left->hasNode(id))
        return true;
    if (this->right->hasNode(id))
        return true;

    return false;
}

bool PTLogicalExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->left->hasOnlyNodes(ids, ignore))
        return false;
    if (!this->right->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTLogicalExpression::hasKW(std::string_view kw_name) const
{
    if (this->left->hasKW(kw_name))
        return true;
    if (this->right->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTLogicalExpression::getTokens() const
{
    std::vector<Token*> t;

    auto leftV = this->left->getTokens();
    auto rightV = this->right->getTokens();

    t.insert(t.end(), leftV.begin(), leftV.end());
    t.push_back(this->token);
    t.insert(t.end(), rightV.begin(), rightV.end());

    return t;
}

Token* PTLogicalExpression::getLastToken() const
{
    if (this->right->id() != ExpressionID::Empty)
        return this->right->getLastToken();

    return this->token;
}

/*
    PTUnaryLogicalExpression
*/
bool PTUnaryLogicalExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    if (this->expr->hasNode(id))
        return true;

    return false;
}

bool PTUnaryLogicalExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->expr->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTUnaryLogicalExpression::hasKW(std::string_view kw_name) const
{
    if (this->expr->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTUnaryLogicalExpression::getTokens() const
{
    std::vector<Token*> t;

    auto rightV = this->expr->getTokens();

    t.push_back(this->token);
    t.insert(t.end(), rightV.begin(), rightV.end());

    return t;
}

Token* PTUnaryLogicalExpression::getLastToken() const
{
    if (this->expr->id() != ExpressionID::Empty)
        return this->expr->getLastToken();

    return this->token;
}

/*
    PTReturnTypeExpression
*/
bool PTReturnTypeExpression::hasNode(ExpressionID id) const
{
    return this->id() == id;
}

bool PTReturnTypeExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTReturnTypeExpression::hasKW(std::string_view kw_name) const
{
    if (this->left->value == kw_name)
        return true;
    if (this->type != nullptr && this->type->value == kw_name)
        return true;
    if (this->subtype != nullptr && this->subtype->value == kw_name)
        return true;

    return false;
}

std::vector<Token*> PTReturnTypeExpression::getTokens() const
{
    std::vector<Token*> t;

    t.push_back(this->left);
    if (this->token != nullptr)
        t.push_back(this->token);
    if (this->type != nullptr)
        t.push_back(this->type);
    if (this->subtype != nullptr)
        t.push_back(this->subtype);

    return t;
}

Token* PTReturnTypeExpression::getLastToken() const
{
    if (this->subtype != nullptr)
        return this->subtype;
    if (this->type != nullptr)
        return this->type;
    if (this->token != nullptr)
        return this->token;
    
    return this->left;
}

/*
    PTFunctionCallExpression
*/
bool PTFunctionCallExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    return this->expr->hasNode(id);
}

bool PTFunctionCallExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->expr->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTFunctionCallExpression::hasKW(std::string_view kw_name) const
{
    if (this->name != nullptr && this->name->value == kw_name)
        return true;
    if (this->expr->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTFunctionCallExpression::getTokens() const
{
    std::vector<Token*> t;

    auto exprV = this->expr->getTokens();

    if (this->name != nullptr)
        t.push_back(this->name);
    t.push_back(this->left);
    t.insert(t.end(), exprV.begin(), exprV.end());
    if (this->right != nullptr)
        t.push_back(this->right);

    return t;
}

Token* PTFunctionCallExpression::getLastToken() const
{
    if (this->right != nullptr)
        return this->right;
    if (this->expr->id() != ExpressionID::Empty)
        return this->expr->getLastToken();

    return this->left;
}

/*
    PTForRangeExpression
*/
bool PTForRangeExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    if (this->left->hasNode(id))
        return true;
    if (this->right->hasNode(id))
        return true;

    return false;
}

bool PTForRangeExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->left->hasOnlyNodes(ids, ignore))
        return false;
    if (!this->right->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTForRangeExpression::hasKW(std::string_view kw_name) const
{
    if (this->left->hasKW(kw_name))
        return true;
    if (this->right->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTForRangeExpression::getTokens() const
{
    std::vector<Token*> t;

    auto leftV = this->left->getTokens();
    auto rightV = this->right->getTokens();

    t.insert(t.end(), leftV.begin(), leftV.end());
    t.push_back(this->token);
    t.insert(t.end(), rightV.begin(), rightV.end());

    return t;
}

Token* PTForRangeExpression::getLastToken() const
{
    if (this->right->id() != ExpressionID::Empty)
        return this->right->getLastToken();

    return this->token;
}

/*
    PTMemberAccessExpression
*/
bool PTMemberAccessExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    if (this->left->hasNode(id))
        return true;
    if (this->right->hasNode(id))
        return true;

    return false;
}

bool PTMemberAccessExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->left->hasOnlyNodes(ids, ignore))
        return false;
    if (!this->right->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTMemberAccessExpression::hasKW(std::string_view kw_name) const
{
    if (this->left->hasKW(kw_name))
        return true;
    if (this->right->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTMemberAccessExpression::getTokens() const
{
    std::vector<Token*> t;

    auto leftV = this->left->getTokens();
    auto rightV = this->right->getTokens();

    t.insert(t.end(), leftV.begin(), leftV.end());
    t.push_back(this->token);
    t.insert(t.end(), rightV.begin(), rightV.end());

    return t;
}

Token* PTMemberAccessExpression::getLastToken() const
{
    if (this->right->id() != ExpressionID::Empty)
        return this->right->getLastToken();

    return this->token;
}

/*
    PTErrorExpression
*/
bool PTErrorExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    return this->expr->hasNode(id);
}

bool PTErrorExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->expr->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTErrorExpression::hasKW(std::string_view kw_name) const
{
    if (this->keyword->value == kw_name)
        return true;
    if (this->expr->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTErrorExpression::getTokens() const
{
    std::vector<Token*> t;

    auto exprV = this->expr->getTokens();

    t.push_back(this->keyword);
    if (this->left != nullptr)
        t.push_back(this->left);
    t.insert(t.end(), exprV.begin(), exprV.end());
    if (this->right != nullptr)
        t.push_back(this->right);

    return t;
}

Token* PTErrorExpression::getLastToken() const
{
    if (this->right != nullptr)
        return this->right;
    if (this->expr->id() != ExpressionID::Empty)
        return this->expr->getLastToken();
    if (this->left != nullptr)
        return this->left;

    return this->keyword;
}

/*
    PTWarningExpression
*/
bool PTWarningExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    return this->expr->hasNode(id);
}

bool PTWarningExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->expr->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTWarningExpression::hasKW(std::string_view kw_name) const
{
    if (this->keyword->value == kw_name)
        return true;
    if (this->expr->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTWarningExpression::getTokens() const
{
    std::vector<Token*> t;

    auto exprV = this->expr->getTokens();

    t.push_back(this->keyword);
    if (this->left != nullptr)
        t.push_back(this->left);
    t.insert(t.end(), exprV.begin(), exprV.end());
    if (this->right != nullptr)
        t.push_back(this->right);

    return t;
}

Token* PTWarningExpression::getLastToken() const
{
    if (this->right != nullptr)
        return this->right;
    if (this->expr->id() != ExpressionID::Empty)
        return this->expr->getLastToken();
    if (this->left != nullptr)
        return this->left;

    return this->keyword;
}

/*
    PTAssertExpression
*/
bool PTAssertExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    return this->expr->hasNode(id);
}

bool PTAssertExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->expr->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTAssertExpression::hasKW(std::string_view kw_name) const
{
    if (this->keyword->value == kw_name)
        return true;
    if (this->expr->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTAssertExpression::getTokens() const
{
    std::vector<Token*> t;

    auto exprV = this->expr->getTokens();

    t.push_back(this->keyword);
    if (this->left != nullptr)
        t.push_back(this->left);
    t.insert(t.end(), exprV.begin(), exprV.end());
    if (this->right != nullptr)
        t.push_back(this->right);

    return t;
}

Token* PTAssertExpression::getLastToken() const
{
    if (this->right != nullptr)
        return this->right;
    if (this->expr->id() != ExpressionID::Empty)
        return this->expr->getLastToken();
    if (this->left != nullptr)
        return this->left;

    return this->keyword;
}

/*
    PTArraySubscriptExpression
*/
bool PTArraySubscriptExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    if (this->array->hasNode(id))
        return true;
    if (this->expr->hasNode(id))
        return true;

    return false;
}

bool PTArraySubscriptExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->array->hasOnlyNodes(ids, ignore))
        return false;
    if (!this->expr->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTArraySubscriptExpression::hasKW(std::string_view kw_name) const
{
    if (this->array->hasKW(kw_name))
        return true;
    if (this->expr->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTArraySubscriptExpression::getTokens() const
{
    std::vector<Token*> t;

    auto arrayV = this->array->getTokens();
    auto exprV = this->expr->getTokens();

    t.insert(t.end(), arrayV.begin(), arrayV.end());
    t.push_back(this->left);
    t.insert(t.end(), exprV.begin(), exprV.end());
    if (this->right != nullptr)
        t.push_back(this->right);

    return t;
}

Token* PTArraySubscriptExpression::getLastToken() const
{
    if (this->right != nullptr)
        return this->right;
    if (this->expr->id() != ExpressionID::Empty)
        return this->expr->getLastToken();

    return this->left;
}

/*
    PTPercentLiteralExpression
*/
bool PTPercentLiteralExpression::hasNode(ExpressionID id) const
{
    return this->id() == id;
}

bool PTPercentLiteralExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (ignored) 
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;
    
    return false;
}

bool PTPercentLiteralExpression::hasKW([[maybe_unused]] std::string_view kw_name) const
{
    return false;
}

std::vector<Token*> PTPercentLiteralExpression::getTokens() const
{
    std::vector<Token*> t;

    t.push_back(this->value);
    t.push_back(this->right);

    return t;
}

Token* PTPercentLiteralExpression::getLastToken() const
{
    return this->right;
}

/*
    PTStringLiteralExpression
*/
bool PTStringLiteralExpression::hasNode(ExpressionID id) const
{
    return this->id() == id;
}

bool PTStringLiteralExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTStringLiteralExpression::hasKW([[maybe_unused]] std::string_view kw_name) const
{
    return false;
}

std::vector<Token*> PTStringLiteralExpression::getTokens() const
{
    std::vector<Token*> t;
    
    t.push_back(this->left);
    if (this->value != nullptr)
        t.push_back(this->value);
    if (this->right != nullptr)
        t.push_back(this->right);

    return t;
}

Token* PTStringLiteralExpression::getLastToken() const
{
    if (this->right != nullptr)
        return this->right;
    if (this->value != nullptr)
        return this->value;

    return this->left;
}

/*
    PTRangeLiteralExpression
*/
bool PTRangeLiteralExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    if (this->left->hasNode(id))
        return true;
    if (this->right->hasNode(id))
        return true;

    return false;
}

bool PTRangeLiteralExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->left->hasOnlyNodes(ids, ignore))
        return false;
    if (!this->right->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTRangeLiteralExpression::hasKW(std::string_view kw_name) const
{
    if (this->left->hasKW(kw_name))
        return true;
    if (this->right->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTRangeLiteralExpression::getTokens() const
{
    std::vector<Token*> t;

    auto leftV = this->left->getTokens();
    auto rightV = this->right->getTokens();

    t.insert(t.end(), leftV.begin(), leftV.end());
    t.push_back(this->token);
    t.insert(t.end(), rightV.begin(), rightV.end());

    return t;
}

Token* PTRangeLiteralExpression::getLastToken() const
{
    if (this->right->id() != ExpressionID::Empty)
        return this->right->getLastToken();

    return this->token;
}

/*
    PTCoordLiteralExpression
*/
bool PTCoordLiteralExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    return this->expr->hasNode(id);
}

bool PTCoordLiteralExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->expr->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTCoordLiteralExpression::hasKW(std::string_view kw_name) const
{
    if (this->expr->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTCoordLiteralExpression::getTokens() const
{
    std::vector<Token*> t;

    auto exprV = this->expr->getTokens();

    t.push_back(this->left);
    t.insert(t.end(), exprV.begin(), exprV.end());
    t.push_back(this->right);

    return t;
}

Token* PTCoordLiteralExpression::getLastToken() const
{
    return this->right;
}

/*
    PTSeparatorExpression
*/
bool PTSeparatorExpression::hasNode(ExpressionID id) const
{
    if (this->id() == id)
        return true;

    if (this->left->hasNode(id))
        return true;
    if (this->right->hasNode(id))
        return true;

    return false;
}

bool PTSeparatorExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (!this->left->hasOnlyNodes(ids, ignore))
        return false;
    if (!this->right->hasOnlyNodes(ids, ignore))
        return false;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;

    return false;
}

bool PTSeparatorExpression::hasKW(std::string_view kw_name) const
{
    if (this->left->hasKW(kw_name))
        return true;
    if (this->right->hasKW(kw_name))
        return true;

    return false;
}

std::vector<Token*> PTSeparatorExpression::getTokens() const
{
    std::vector<Token*> t;

    auto leftV = this->left->getTokens();
    auto rightV = this->right->getTokens();

    t.insert(t.end(), leftV.begin(), leftV.end());
    t.push_back(this->sep);
    t.insert(t.end(), rightV.begin(), rightV.end());

    return t;
}

Token* PTSeparatorExpression::getLastToken() const
{
    if (this->right->id() != ExpressionID::Empty)
        return this->right->getLastToken();

    return this->sep;
}

/*
    PTDeclTypeExpression
*/
bool PTDeclTypeExpression::hasNode(ExpressionID id) const
{
    return this->id() == id;
}

bool PTDeclTypeExpression::hasOnlyNodes(const std::vector<ExpressionID>& ids, const std::vector<ExpressionID>& ignore) const
{
    bool ignored = false;
    for (auto id : ignore)
        if (this->id() == id)
            ignored = true;

    if (ignored)
        return true;

    for (auto id : ids)
        if (this->id() == id)
            return true;
    
    return false;
}

bool PTDeclTypeExpression::hasKW(std::string_view kw_name) const
{
    if (this->type->value == kw_name)
        return true;
    if (this->subtype != nullptr && this->subtype->value == kw_name)
        return true;

    return false;
}

std::vector<Token*> PTDeclTypeExpression::getTokens() const
{
    std::vector<Token*> t;

    t.push_back(this->type);
    if (this->subtype != nullptr)
        t.push_back(this->subtype);
    if (this->name != nullptr)
        t.push_back(this->name);

    return t;
}

Token* PTDeclTypeExpression::getLastToken() const
{
    if (this->name != nullptr)
        return this->name;
    if (this->subtype != nullptr)
        return this->subtype;

    return this->type;
}
