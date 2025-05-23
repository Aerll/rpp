///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2020-2025 Aerll - aerlldev@gmail.com
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
#include <parser.hpp>
#include <abstractsyntaxtree.hpp>
#include <parsetree.hpp>
#include <tokenstream.hpp>

/*
    Parser
*/
void Parser::parse(ParseTree& parseTree, TokenStream& ts) {
    errorOutput::print::stage("... Syntax check:");

    PTExpressionVisitor ex_visitor;
    PTStatementVisitor visitor;
    ex_visitor.setCurrentToken(&ts.data().front());
    visitor.setExpressionVisitor(&ex_visitor);
    for (const auto& stat : parseTree.getStatements())
        stat->accept(visitor);

    m_errors = std::move(ex_visitor.errors());
    m_count  = static_cast<u32>(m_errors.size());
    if (hasErrors()) {
        m_failed = true;
        printErrors(util::digitsCount(m_errors.back()->line()));
        errorOutput::print::summary(totalCount(), failed());
        resetCount();
    }
}

void Parser::parse(AbstractSyntaxTree& abstractTree) {
    errorOutput::print::stage("... Linking:");

    if (abstractTree.getMainNode()->hasNode(NodeID::Return, { NodeID::Function, NodeID::NestedFunction }))
        m_errors.push(
            std::make_unique<ErrReturnInvalidContext>(abstractTree.getMainNode()
                                                          ->findNode({ NodeID::Return }, { NodeID::Function, NodeID::NestedFunction }, true)
                                                          ->getLine())
        );
    if (abstractTree.getMainNode()->hasNode(NodeID::Break, { NodeID::For }))
        m_errors.push(
            std::make_unique<ErrBreakInvalidContext>(
                abstractTree.getMainNode()->findNode({ NodeID::Break }, { NodeID::For }, true)->getLine()
            )
        );
    if (abstractTree.getMainNode()->hasNode(NodeID::Continue, { NodeID::For }))
        m_errors.push(
            std::make_unique<ErrContinueInvalidContext>(
                abstractTree.getMainNode()->findNode({ NodeID::Continue }, { NodeID::For }, true)->getLine()
            )
        );
    if (abstractTree.getMainNode()->hasNode(NodeID::InvokeNested, { NodeID::Function }))
        m_errors.push(
            std::make_unique<ErrInvokeInvalidContext>(
                abstractTree.getMainNode()->findNode({ NodeID::InvokeNested }, { NodeID::Function }, true)->getLine()
            )
        );

    m_count = static_cast<u32>(m_errors.size());

    if (!hasErrors()) {
        ASTNodeLinker linker;
        abstractTree.getMainNode()->accept(linker);

        m_errors = std::move(linker.errors());
        m_count  = static_cast<u32>(m_errors.size());
        if (!hasErrors()) {
            errorOutput::print::stage("... Type check:");

            ASTNodeParser parser;
            abstractTree.getMainNode()->accept(parser);

            m_errors = std::move(parser.errors());
            m_count  = static_cast<u32>(m_errors.size());
        }
    }

    if (hasErrors()) {
        m_failed = true;
        printErrors(util::digitsCount(m_errors.back()->line()));
        errorOutput::print::summary(totalCount(), failed());
        resetCount();
    }
}
