#include "globalVariables.h"

namespace global
{
    Trie service_words_trie, types_trie;
    lexeme lex;
    int ind = 0;
    std::string text;
    int string_number = 0;
    bool eof = false;
    Tree_variables_TID tree_of_variables = Tree_variables_TID();
    Function_TID function_table = Function_TID();
    std::vector<Expression_Type> stack_of_call = std::vector<Expression_Type>();
    std::vector<StackElement*> poliz_stack = std::vector<StackElement*>();
    std::vector<std::vector<int>> break_stack, continue_stack;
    std::vector<std::pair<K_Variable_Type, void *>> stack_of_calculations;
    int start_pos_on_poliz = 0;
};
