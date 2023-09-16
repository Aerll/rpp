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
#include <app.hpp>

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <iostream>
#include <utility>

#include <io.hpp>
#include <inputstream.hpp>
#include <tokenizer.hpp>
#include <tokenstream.hpp>
#include <preprocessor.hpp>
#include <parsetree.hpp>
#include <abstractsyntaxtree.hpp>
#include <parser.hpp>
#include <translator.hpp>
#include <automapper.hpp>
#include <rulesgen.hpp>

namespace {
    long long memory = 0;
    long long max_memory = 0; // in megabytes
}

void* operator new(std::size_t size) {
    memory += size;
    if (max_memory != 0 && memory > max_memory)
        throw std::overflow_error("Memory overflow");
    return std::malloc(size);
}

void* operator new[](std::size_t size) {
    memory += size;
    if (max_memory != 0 && memory > max_memory)
        throw std::overflow_error("Memory overflow");
    return std::malloc(size);
}

void operator delete(void* data, std::size_t size) noexcept {
    memory -= size;
    std::free(data);
}

void operator delete[](void* data, std::size_t size) noexcept {
    memory -= size;
    std::free(data);
}

void operator delete(void* data) noexcept {
    std::free(data);
}

void operator delete[](void* data) noexcept {
    std::free(data);
}



/*
    App
*/
static void showHelp(char const* prog) {
    std::cout
        << "Usage: " << prog << " [options] file..." << std::endl
        << "  --help               Display the help." << std::endl
        << "  --output <file>      Write to <file> (override #path and #tileset)." << std::endl
        << "  --stack <megabytes>  Override #stack with <megabytes>." << std::endl
        << "  --include <file>     Additional #include file." << std::endl
        << "  --skip-preprocessor  Skip preprocessor pass." << std::endl
        << "  --silent             Do not write to stdout." << std::endl;
}

static void exitWithError(char const* prog, char const* err) {
    std::cerr << "Error: " << err << std::endl << std::endl;
    showHelp(prog);
    exit(1);
}

Cli App::parseCli(int argc, char** argv) {
    Cli cli{};

    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];

        if (arg[0] == '-') {
            if (arg == "--help") {
                showHelp(argv[0]);
                exit(0);
            }
            else if (arg == "--output" || arg == "-o") {
                if (i + 1 >= argc) {
                    exitWithError(argv[0], "missing filename after --output");
                }
                cli.output = argv[++i];
            }
            else if (arg == "--include") {
                if (i + 1 >= argc) {
                    exitWithError(argv[0], "missing filename after --include");
                }
                cli.includes.push_back(argv[++i]);
            }
            else if (arg == "--stack") {
                if (i + 1 >= argc) {
                    exitWithError(argv[0], "missing value after --stack");
                }
                try {
                    cli.stack = std::stoll(argv[++i]);
                }
                catch (...) {
                    exitWithError(argv[0], "--stack: value is not an integer");
                }
            }
            else if (arg == "--skip-preprocessor") {
                cli.skipPreprocessor = true;
            }
            else if (arg == "--silent") {
                cli.silent = true;
            }
            else {
                std::cerr << "Warning: unrecognized flag: " << arg << std::endl;
            }
        }
        else {
            std::filesystem::path input(arg);
            if (!std::filesystem::is_regular_file(input)) {
                exitWithError(argv[0], "input file not found");
            }
            cli.inputFiles.push_back(arg);
        }
    }

    return cli;
}

int App::exec(const Cli& cli) {
    try {
        using namespace std::chrono;
        auto beg = high_resolution_clock::now();
        bool wait = false;

        for (auto const& input : cli.inputFiles) {
            max_memory = 0;

            InputStream inputStream(FileR::read(input));

            Tokenizer tokenizer;
            tokenizer.run(inputStream);
            std::vector<Token> tokens = tokenizer.data();

            std::filesystem::path outputFile = cli.output.value_or(std::filesystem::current_path() / "tileset.rules");

            if (!cli.skipPreprocessor) {
                Preprocessor preprocessor(std::move(tokens));
                preprocessor.run(input);
                if (preprocessor.failed()) {
                    wait = true;
                    continue;
                }
                tokens = preprocessor.data();
                max_memory = preprocessor.stack();
                outputFile = cli.output.value_or(preprocessor.path() / (preprocessor.tileset() + ".rules"));
            }

            max_memory = cli.stack.value_or(max_memory);

            AbstractSyntaxTree abstractSyntaxTree;
            {
                TokenStream tokenStream(std::move(tokens));

                ParseTree parseTree;
                parseTree.create(tokenStream);

                Parser parser;
                parser.parse(parseTree, tokenStream);
                if (parser.failed()) {
                    wait = true;
                    continue;
                }

                abstractSyntaxTree.create(parseTree);
                parser.parse(abstractSyntaxTree);
                if (parser.failed()) {
                    wait = true;
                    continue;
                }
            }

            Translator translator;
            translator.run(abstractSyntaxTree);
            if (translator.failed()) {
                wait = true;
                continue;
            }
            if (translator.warned())
                wait = true;

            RulesGen::exec(translator.automappers(), outputFile);
        }

        auto end = high_resolution_clock::now();
        auto time = duration_cast<duration<double>>(end - beg).count();

        std::cout << "\n\n";
        std::cout << "Finished in: " << time << "s\n";

        if (wait)
            pause();
        return 0;
    }
    catch (const std::overflow_error& error) {
        std::cout << error.what() << '\n';
        pause();
        return 0;
    }
}

void App::pause()
{
    errorOutput::print::newLine(2);
    errorOutput::print::string("Press any key to continue...");
    std::cin.get();
}
