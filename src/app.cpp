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
#include <abstractsyntaxtree.hpp>
#include <app.hpp>
#include <automapper.hpp>
#include <externalresource.hpp>
#include <inputstream.hpp>
#include <io.hpp>
#include <parser.hpp>
#include <parsetree.hpp>
#include <preprocessor.hpp>
#include <rulesgen.hpp>
#include <tokenizer.hpp>
#include <tokenstream.hpp>
#include <translator.hpp>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <utility>

namespace {

int64_t memory     = 0;
int64_t max_memory = 0; // in bytes

}

void* operator new(std::size_t size) {
    if (max_memory != 0 && memory + size > max_memory) {
        int64_t tmp_max_memory = max_memory;
        max_memory             = 0; // allow allocating beyond max_memory for the error
        auto err               = std::overflow_error("Memory overflow");
        max_memory             = tmp_max_memory;
        throw err;
    }
    memory += size;
    return std::malloc(size);
}

void* operator new[](std::size_t size) {
    if (max_memory != 0 && memory + size > max_memory) {
        int64_t tmp_max_memory = max_memory;
        max_memory             = 0; // allow allocating beyond max_memory for the error
        auto err               = std::overflow_error("Memory overflow");
        max_memory             = tmp_max_memory;
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
static void showHelp(const char* prog) {
    std::cout << "Usage: " << prog << "[options] file...\n"
              << "      --help               Display the help.\n"
              << "  -o, --output <file>      Write to <file> (same as #tileset).\n"
              << "  -i, --include <file>     A file to include (same as #include).\n"
              << "  -m, --memory <megabytes> Memory limit in <megabytes> (same as #memory).\n"
              << "  -p, --no-pause           Do not pause after execution.\n"
              << "Options -o, -i, -m disable preprocessor stage. All directives will be ignored.\n";
}

static void exitWithError(const char* prog, const char* err) {
    std::cerr << "Error: " << err << "\n\n";
    showHelp(prog);
    std::exit(1);
}

CLI App::parseCLI(int argc, char** argv) {
    CLI cli = {};

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

                cli.output           = argv[++i];
                cli.skipPreprocessor = true;
            }
            else if (arg == "--include" || arg == "-i") {
                if (i + 1 >= argc)
                    exitWithError(argv[0], "missing filename after --include");

                cli.includes.push_back(argv[++i]);
                cli.skipPreprocessor = true;
            }
            else if (arg == "--memory" || arg == "-m") {
                if (i + 1 >= argc)
                    exitWithError(argv[0], "missing value after --memory");

                try {
                    cli.memory           = std::stoll(argv[++i]) * 1024 * 1024;
                    cli.skipPreprocessor = true;
                } catch (...) {
                    exitWithError(argv[0], "--memory: value is not an integer");
                }
            }
            else if (arg == "--no-pause" || arg == "-p") {
                cli.pause = false;
            }
            else {
                std::cerr << "Warning: unrecognized flag: " << arg << '\n';
            }
        }
        else {
            std::filesystem::path input(arg);
            if (!std::filesystem::is_regular_file(input))
                exitWithError(argv[0], "input file not found");

            cli.inputFiles.push_back(arg);
        }
    }

    if (cli.inputFiles.size() > 1 && cli.skipPreprocessor)
        exitWithError(argv[0], "too many input files");

    std::reverse(cli.includes.begin(), cli.includes.end());
    return cli;
}

int App::exec(int argc, char** argv) {
    CLI cli = parseCLI(argc, argv);

    try {
        using namespace std::chrono;
        auto beg = high_resolution_clock::now();

        for (const auto& input : cli.inputFiles) {
            max_memory = 0;
            ExternalResource::get().clear();

            InputStream inputStream(FileR::read(input));

            Tokenizer tokenizer;
            tokenizer.run(inputStream);

            Preprocessor preprocessor(tokenizer.data());
            preprocessor.run(input, cli);
            if (preprocessor.failed())
                continue;

            max_memory = preprocessor.memory();

            AbstractSyntaxTree abstractSyntaxTree;
            {
                TokenStream tokenStream(preprocessor.data());

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

            RulesGen rulesGen;
            rulesGen.run(translator.automappers(), preprocessor.output());

            errorOutput::print::newLine();
            std::cout << "File size (bytes): " << rulesGen.fileSize() << '\n';
            std::cout << "Line count: " << rulesGen.lineCount() << '\n';
        }

        auto end  = high_resolution_clock::now();
        auto time = duration_cast<duration<double>>(end - beg).count();

        std::cout << "\n\n";
        std::cout << "Finished in: " << time << "s\n";

        if (cli.pause)
            pause();
        return 0;
    } catch (const std::overflow_error& error) {
        std::cout << error.what() << '\n';
        pause();
        return 0;
    }
}

void App::pause() {
    errorOutput::print::newLine(2);
    errorOutput::print::string("Press any key to continue...");
    std::cin.get();
}
