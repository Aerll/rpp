cmake_minimum_required(VERSION 3.10)
project(rpp VERSION 1.0.0 LANGUAGES CXX)

# header files
set(RPP_HEADER_FILES
    "include/abstractsyntaxtree.hpp"
    "include/abstractsyntaxtreevisitor.hpp"
    "include/app.hpp"
    "include/automapper.hpp"
    "include/basicstream.hpp"
    "include/enums.hpp"
    "include/error.hpp"
    "include/erroroutput.hpp"
    "include/errorqueue.hpp"
    "include/expect.hpp"
    "include/externalresource.hpp"
    "include/inputstream.hpp"
    "include/io.hpp"
    "include/iresult.hpp"
    "include/parser.hpp"
    "include/parsetree.hpp"
    "include/parsetreevisitor.hpp"
    "include/preprocessor.hpp"
    "include/rulesgen.hpp"
    "include/signature.hpp"
    "include/token.hpp"
    "include/tokenh.hpp"
    "include/tokenizer.hpp"
    "include/tokenliterals.hpp"
    "include/tokenstream.hpp"
    "include/translator.hpp"
    "include/utility.hpp"
    "include/valuetypes.hpp"
)

# source files
set(RPP_SOURCE_FILES
    "src/abstractsyntaxtree.cpp"
    "src/abstractsyntaxtreevisitor.cpp"
    "src/app.cpp"
    "src/error.cpp"
    "src/erroroutput.cpp"
    "src/errorqueue.cpp"
    "src/expect.cpp"
    "src/externalresource.cpp"
    "src/io.cpp"
    "src/main.cpp"
    "src/parser.cpp"
    "src/parsetree.cpp"
    "src/parsetreevisitor.cpp"
    "src/preprocessor.cpp"
    "src/rulesgen.cpp"
    "src/signature.cpp"
    "src/token.cpp"
    "src/tokenh.cpp"
    "src/tokenizer.cpp"
    "src/translator.cpp"
    "src/valuetypes.cpp"
)

add_executable(rpp ${RPP_SOURCE_FILES} ${RPP_HEADER_FILES})
target_include_directories(rpp PRIVATE "include")

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC") # visual studio
    target_compile_options(rpp PUBLIC /W4 /MT$<$<CONFIG:Debug>:d>)
    source_group(
        TREE ${CMAKE_CURRENT_SOURCE_DIR}
        FILES ${RPP_SOURCE_FILES} ${RPP_HEADER_FILES}
        )
    target_link_options(rpp PRIVATE /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
endif()

set_property(TARGET rpp PROPERTY CXX_STANDARD 23)
set_property(TARGET rpp PROPERTY CXX_STANDARD_REQUIRED On)
set_property(TARGET rpp PROPERTY CXX_EXTENSIONS Off)
target_compile_features(rpp PRIVATE cxx_std_23)
