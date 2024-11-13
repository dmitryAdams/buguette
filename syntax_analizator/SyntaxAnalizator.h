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
void return_();
void block_();
void if_();
void for_();
void while_();
void switch_();
void variables_declaration_();
//is lvalue
std::pair<variables_TID::Types, bool> expression_();
std::pair<variables_TID::Types, bool> expression10_();
std::pair<variables_TID::Types, bool> expression9_();
std::pair<variables_TID::Types, bool> expression8_();
std::pair<variables_TID::Types, bool> expression7_();
std::pair<variables_TID::Types, bool> expression6_();
std::pair<variables_TID::Types, bool> expression5_();
std::pair<variables_TID::Types, bool> expression4_();
std::pair<variables_TID::Types, bool> expression3_();
std::pair<variables_TID::Types, bool> expression2_();
std::pair<variables_TID::Types, bool> expression1_();
std::pair<variables_TID::Types, bool> expression_cool_();
void function_call_();
void break_();
void continue_();
void pass_();
void print_();
void scan_();
void literal_();
void string_literal_();
#endif //BUGGUETTE_SYNTAX_ANALIZATOR_SYNTAXANALIZATOR_H_
