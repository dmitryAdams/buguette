//
// Created by adams on 11/11/24.
//

#ifndef BUGGUETTE_SYNTAX_ANALIZATOR_SYNTAXANALIZATOR_H_
#define BUGGUETTE_SYNTAX_ANALIZATOR_SYNTAXANALIZATOR_H_
#include "../globalVariables.h"
#include "../lexer/lexer.h"
void program_();
void main_();
void function_();
void type_();
void identificator_();
void operator_();
Type_ return_();
void block_();
void if_();
void for_();
void while_();
void switch_();
void variables_declaration_();
//is lvalue
Type_ expression_();
Type_ expression10_();
Type_ expression9_();
Type_ expression8_();
Type_ expression7_();
Type_ expression6_();
Type_ expression5_();
Type_ expression4_();
Type_ expression3_();
Type_ expression2_();
Type_ expression1_();
Type_ expression0_();
Type_ expression_cool_();
std::vector<Type_>  function_call_();
void break_();
void continue_();
void pass_();
void print_();
void scan_();
void literal_();
void string_literal_();
#endif //BUGGUETTE_SYNTAX_ANALIZATOR_SYNTAXANALIZATOR_H_
