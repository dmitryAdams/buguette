#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

// #include "lib.h"

#include "./structures/trie/Trie.h"
#include "lexer/lexer.h"
#include "semantic_analizator/TID/Tree_variables_TID.h"
#include "semantic_analizator/TID/Function_TID.h"

namespace global
{
    extern Trie service_words_trie, types_trie;
    extern lexeme lex;
    extern int ind;
    extern std::string text;
    extern int string_number;
    extern bool eof;
    extern Tree_variables_TID tree_of_variables;
    extern Function_TID function_table;
};



#endif