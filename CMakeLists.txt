cmake_minimum_required(VERSION 3.28)
project(bugguette)

set(CMAKE_CXX_STANDARD 17)

add_executable(bugguette main.cpp
        lexer
        starter.cpp
        lexer/lexer.cpp
        globalVariables.h
        structures/trie/Trie.h
        structures/trie/Trie.cpp
        globalVariables.cpp
        syntax_analizator/SyntaxAnalizator.cpp
        syntax_analizator/SyntaxAnalizator.h
        syntax_analizator/syntax_error/SyntaxError.cpp
        syntax_analizator/syntax_error/SyntaxError.h
        semantic_analizator/SemanticAnalizator.h
        semantic_analizator/SemanticAnalizator.cpp
        semantic_analizator/TID/variables_TID.cpp
        semantic_analizator/TID/variables_TID.h
        semantic_analizator/TID/Tree_variables_TID.cpp
        semantic_analizator/TID/Tree_variables_TID.h
        semantic_analizator/TID/Function_TID.cpp
        semantic_analizator/TID/Function_TID.h
        semantic_analizator/SemanticError/SemanticError.cpp
        semantic_analizator/SemanticError/SemanticError.h
        Generation/Operator/PolizOperator.h
        Generation/Operand/PolizOperand.h
        Generation/Operand/PolizOperand.cpp
        Generation/Operator/PolizOperator.cpp
        Generation/StackElement/StackElement.cpp
)

add_compile_definitions("")
add_compile_definitions("DEBUG")


