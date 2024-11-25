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
Expression_Type return_();
void block_();
void if_();
void for_();
void while_();
void switch_();
void variables_declaration_();
//is lvalue
Expression_Type expression_();
Expression_Type expression10_();
Expression_Type expression9_();
Expression_Type expression8_();
Expression_Type expression7_();
Expression_Type expression6_();
Expression_Type expression5_();
Expression_Type expression4_();
Expression_Type expression3_();
Expression_Type expression2_();
Expression_Type expression1_();
Expression_Type expression0_();
Expression_Type expression_cool_();
std::vector<Expression_Type>  function_call_();
void break_();
void continue_();
void pass_();
void print_();
void scan_();
void literal_();
void string_literal_();
#endif //BUGGUETTE_SYNTAX_ANALIZATOR_SYNTAXANALIZATOR_H_
