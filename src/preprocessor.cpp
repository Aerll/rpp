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
#include <preprocessor.hpp>

#include <algorithm>
#include <iterator>

#include <cli.hpp>
#include <enums.hpp>
#include <error.hpp>
#include <tokenliterals.hpp>
#include <token.hpp>
#include <expect.hpp>
#include <externalresource.hpp>
#include <io.hpp>
#include <inputstream.hpp>
#include <tokenizer.hpp>

/*
    Preprocessor
*/
void Preprocessor::run(const std::filesystem::path& path, const CLI& cli)
{
    errorOutput::print::stage("Preprocessing file", path.filename().string());
    
    ExternalResource::Info info;
    info.fileName = std::filesystem::canonical(path.filename()).string();
    info.lineCount = m_data.back().line;
    ExternalResource::get().addInfo(std::move(info));

    if (!cli.skipPreprocessor) {
        auto lastPreproc = std::find_if(m_data.rbegin(), m_data.rend(), 
            [](const Token& token) {
                return token.cat == TPunctuator && token.value == PU::Preproc;
            }
        );
        if (lastPreproc == m_data.rend())
            return;

        while (m_curr != m_data.end()) {
            auto line = getLine();

            if (!line.empty()) {
                m_curr = m_data.erase(m_curr, std::next(m_curr, 5));

                if (line.at(1).value == ID::Output) {
                    m_output = getPath(line.at(3).value);
                    if (!std::filesystem::exists(m_output.parent_path()))
                        pushError(std::make_unique<ErrInvalidOutPath>(m_output.parent_path().string(), line.at(3).line));
                }
                else if (line.at(1).value == ID::Memory) {
                    try {
                        m_memory = std::stoll(line.at(3).value) * 1024 * 1024;
                    }
                    catch (...) {
                        pushError(std::make_unique<ErrIncorrectValueType>(ValueType::String, ValueType::Int, line.at(3).line));
                    }
                }
                else if (line.at(1).value == ID::Include) {
                    auto currentLine = line.back().line - 1;
                    auto filePath = getPath(line.at(3).value);

                    if (std::filesystem::exists(filePath) && 
                        std::filesystem::status(filePath).type() == std::filesystem::file_type::regular &&
                        !ExternalResource::get().isLoaded(filePath)
                        ) {
                        auto tokens = ExternalResource::get().load(filePath, cli);

                        m_curr = m_data.insert(m_curr, std::make_move_iterator(tokens.begin()), std::make_move_iterator(tokens.end()));
                        for (auto it = m_curr; it != m_data.end(); ++it) {
                            if (it < m_curr + tokens.size())
                                it->line += currentLine;
                            else
                                it->line += ExternalResource::get().info().back().lineCount - 1;
                        }
                    }
                    else if (!ExternalResource::get().isLoaded(filePath))
                        pushError(std::make_unique<ErrFileNotFound>(line.at(3)));
                }
            }
        }

        if (hasErrors()) {
            m_failed = true;
            printErrors(util::digitsCount(m_errors.back()->line()));
            errorOutput::print::summary(totalCount(), failed());
            resetCount();
        }
    }
    else {
        while (m_curr != m_data.end()) {
            auto line = getLine();
            if (!line.empty())
                m_curr = m_data.erase(m_curr, std::next(m_curr, 5));
        }

        if (cli.output.has_value()) {
            m_output = cli.output.value();
            if (m_output.has_parent_path() && !std::filesystem::exists(m_output.parent_path()))
                pushError(std::make_unique<ErrInvalidOutPath>(m_output.parent_path().string(), 0));
        }
        if (cli.memory.has_value())
            m_memory = cli.memory.value();

        for (const auto& include : cli.includes) {
            if (std::filesystem::exists(include) && 
                std::filesystem::status(include).type() == std::filesystem::file_type::regular &&
                !ExternalResource::get().isLoaded(include)
                ) {
                auto tokens = ExternalResource::get().load(include, cli);
                
                m_curr = m_data.insert(m_data.begin(), std::make_move_iterator(tokens.begin()), std::make_move_iterator(tokens.end()));
                for (auto it = m_curr; it != m_data.end(); ++it)
                    it->line += ExternalResource::get().info().back().lineCount - 1;
            }
            else if (!ExternalResource::get().isLoaded(include))
                pushError(std::make_unique<ErrFileNotFound>(include.string(), 0));
        }
    }
}

std::filesystem::path Preprocessor::getPath(const std::string& value) const
{
    std::filesystem::path path = value;
    if (path.is_absolute()) {}
    else if (path.empty())
        path = std::filesystem::current_path();
    else
        path = std::filesystem::current_path() / value;

    return path;
}

std::vector<Token> Preprocessor::getLine()
{
    m_curr = std::find_if(m_curr, m_data.end(), 
        [](const Token& token) {
            return token.cat == TPunctuator && token.value == PU::Preproc;
        }
    );
    if (m_curr == m_data.end())
        return {};

    for (int32_t i = 1; i <= 4; ++i) {
        if (std::next(m_curr, i) == m_data.end()) {
            pushError(std::make_unique<ErrUnexpectedEof>(*(m_data.end() - 1)));
            m_curr = m_data.end(); // to terminate loop
            return {};
        }
    }

    Token t1 = *std::next(m_curr, 1);
    Token t2 = *std::next(m_curr, 2);
    Token t3 = *std::next(m_curr, 3);
    Token t4 = *std::next(m_curr, 4);

    auto prevTotalCount = totalCount();
    if (!Expect::identifierTPreproc(t1))
        pushError(std::make_unique<ErrPreprocNotIdentifier>(t1));
    else if (!Expect::punctuatorT(t2, PU::CharStringLiteral))
        pushError(std::make_unique<ErrUnexpectedToken>(t2, std::string(1, PU::CharStringLiteral)));
    else if (!Expect::literalT(t3, { ValueType::String }))
        pushError(std::make_unique<ErrIncorrectLiteralType>(t3, ValueType::String));
    else if (!Expect::punctuatorT(t4, PU::CharStringLiteral))
        pushError(std::make_unique<ErrMissingToken>(t3, PU::StringLiteral));

    if (prevTotalCount != totalCount()) {
        std::advance(m_curr, 1);
        return {};
    }
    
    return { *m_curr, t1, t2, t3, t4 };
}