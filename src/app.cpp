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

#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <iostream>
#include <iterator>
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
#include <externalresource.hpp>

namespace {
    int64_t memory = 0;
    int64_t max_memory = 0; // in bytes
}

void* operator new(std::size_t size) {
    if (max_memory != 0 && memory + size > max_memory) {
        int64_t tmp_max_memory = max_memory;
        max_memory = 0; // allow allocating beyond max_memory for the error
        auto err = std::overflow_error("Memory overflow");
        max_memory = tmp_max_memory;
        throw err;
    }
    memory += size;
    return std::malloc(size);
}

void* operator new[](std::size_t size) {
    if (max_memory != 0 && memory + size > max_memory) {
        int64_t tmp_max_memory = max_memory;
        max_memory = 0; // allow allocating beyond max_memory for the error
        auto err = std::overflow_error("Memory overflow");
        max_memory = tmp_max_memory;
        throw err;
    }
    memory += size;
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
        << "Usage: " << prog << " [options] file...\n"
        << "      --help               Display the help.\n"
        << "  -o, --output <file>      Write to <file> (override #path and #tileset).\n"
        << "      --memory <megabytes> Override #memory with <megabytes>.\n"
        << "      --include <file>     Additional #include file.\n"
        << "      --skip-preprocessor  Skip preprocessor pass.\n"
        << "  -p                       Do not pause after execution.\n";
}

static void exitWithError(char const* prog, char const* err) {
    std::cerr << "Error: " << err << "\n\n";
    showHelp(prog);
    std::exit(1);
}

CLI App::parseCLI(int argc, char** argv) {
    CLI cli{};

    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];

        if (arg[0] == '-') {
            if (arg == "--help") {
                showHelp(argv[0]);
                std::exit(0);
            }
            else if (arg == "--output" || arg == "-o") {
                if (i + 1 >= argc)
                    exitWithError(argv[0], "missing filename after --output");

                cli.output = argv[++i];
            }
            else if (arg == "--include") {
                if (i + 1 >= argc)
                    exitWithError(argv[0], "missing filename after --include");

                cli.includes.push_back(argv[++i]);
            }
            else if (arg == "--memory") {
                if (i + 1 >= argc)
                    exitWithError(argv[0], "missing value after --memory");

                try {
                    cli.memory = std::stoll(argv[++i]) * 1024 * 1024;
                }
                catch (...) {
                    exitWithError(argv[0], "--memory: value is not an integer");
                }
            }
            else if (arg == "--skip-preprocessor") {
                cli.skipPreprocessor = true;
            }
            else if (arg == "-p") {
                cli.pause = false;
            }
            else {
                std::cerr << "Warning: unrecognized flag: " << arg << '\n';
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

int App::exec(const CLI& cli) {
    try {
        using namespace std::chrono;
        auto beg = high_resolution_clock::now();

        for (auto const& input : cli.inputFiles) {
            max_memory = 1024 * 1024 * 50;
            ExternalResource::get().clear();
            auto outputFile = cli.output.value_or(std::filesystem::current_path() / "tileset.rules");

            InputStream inputStream(FileR::read(input));

            Tokenizer tokenizer;
            tokenizer.run(inputStream);
            auto tokens = tokenizer.data();

            for (auto const& include : cli.includes) {
                if (ExternalResource::get().isLoaded(include))
                    continue;

                InputStream inputStream(FileR::read(include));

                Tokenizer tokenizer;
                tokenizer.run(inputStream, true);
                auto includeTokens = tokenizer.data();

                if (!cli.skipPreprocessor) {
                    Preprocessor preprocessor(std::move(includeTokens));
                    preprocessor.run(include);
                    if (preprocessor.failed())
                        continue;
                    includeTokens = preprocessor.data();
                }
                
                ExternalResource::get().load(include, 0, includeTokens.back().line);
                tokens.insert(tokens.begin(), std::make_move_iterator(includeTokens.begin()), std::make_move_iterator(includeTokens.end()));
            }

            if (!cli.skipPreprocessor) {
                Preprocessor preprocessor(std::move(tokens));
                preprocessor.run(input);
                if (preprocessor.failed())
                    continue;

                tokens = preprocessor.data();
                max_memory = preprocessor.memory();
                outputFile = cli.output.value_or(preprocessor.path() / (preprocessor.tileset() + ".rules"));
            }

            max_memory = cli.memory.value_or(max_memory);

            AbstractSyntaxTree abstractSyntaxTree;
            {
                TokenStream tokenStream(std::move(tokens));

                ParseTree parseTree;
                parseTree.create(tokenStream);

                Parser parser;
                parser.parse(parseTree, tokenStream);
                if (parser.failed())
                    continue;

                abstractSyntaxTree.create(parseTree);
                parser.parse(abstractSyntaxTree);
                if (parser.failed())
                    continue;
            }

            Translator translator;
            translator.run(abstractSyntaxTree);
            if (translator.failed())
                continue;

            RulesGen::exec(translator.automappers(), outputFile);
        }

        auto end = high_resolution_clock::now();
        auto time = duration_cast<duration<double>>(end - beg).count();

        std::cout << "\n\n";
        std::cout << "Finished in: " << time << "s\n";

        if (cli.pause)
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
