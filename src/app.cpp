///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2020 Aerll - aerlldev@gmail.com
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

#include <filesystem>
#include <fstream>
#include <chrono>
#include <iostream>

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
    long long max_memory = 0;
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

void operator delete(void* data, std::size_t size) {
    memory -= size;
    std::free(data);
}

void operator delete[](void* data, std::size_t size) {
    memory -= size;
    std::free(data);
}



/*
    App
*/
int App::exec(int argc, char** argv) {
    try {
        using namespace std::chrono;
        auto beg = high_resolution_clock::now();

        for (int i = 1; i < argc; ++i) {
            max_memory = 0;

            std::filesystem::path path = argv[i];

            InputStream inputStream(FileR::read(path));

            Tokenizer tokenizer;
            tokenizer.run(inputStream);

            Preprocessor preprocessor(tokenizer.data());
            preprocessor.run(path);
            if (preprocessor.failed())
                continue;

            max_memory = preprocessor.stack(); // in megabytes

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

            RulesGen::exec(translator.automappers(), preprocessor.path(), preprocessor.tileset());
        }

        auto end = high_resolution_clock::now();
        auto time = duration_cast<duration<double>>(end - beg).count();

        std::cout << "\n\n";
        std::cout << "Finished in: " << time << "s\n";

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
