//
// Created by adams on 11/25/24.
//

#ifndef BUGGUETTE_GENERATION_POLIZOPERATOR_H_
#define BUGGUETTE_GENERATION_POLIZOPERATOR_H_
#include "../StackElement/StackElement.h"
enum KOperand {
  KO_Bin_Plus,
  KO_Bin_Minus,
  KO_Unary_Plus,
  KO_Unary_Minus,
  KO_Mul,
  KO_Div,
  KO_Mod,
  KO_Less,
  KO_Greater,
  KO_Equal,
  KO_Greater_Equal,
  KO_Less_Equal,
  KO_Not_Equal,
  KO_Comma,
  KO_Assigment,
  KO_Or,
  KO_Xor,
  KO_And,
  KO_Not,
  KO_Plus_Increment,
  KO_Minus_Increment,
  KO_Open_Brace,
  KO_CLose_Brace,
  KO_Open_Square_Brace,
  KO_Close_Square_Brace,
  KO_Semicolon,
  //TODO расписать func call
  KO_Function_Call
};

#include "../../lib.h"

class PolizOperator : public StackElement {
 public:
  PolizOperator(const std::string &operator_name, bool is_unary = false) {
    if (!is_unary) {
      if (operator_name == "+") {
        self = KO_Bin_Plus;
      } else if (operator_name == "-") {
        self = KO_Bin_Minus;
      } else if (operator_name == "*") {
        self = KO_Mul;
      } else if (operator_name == "/") {
        self = KO_Div;
      } else if (operator_name == "%") {
        self = KO_Mod;
      } else if (operator_name == "=") {
        self = KO_Assigment;
      } else if (operator_name == "==") {
        self = KO_Equal;
      } else if (operator_name == "<") {
        self = KO_Less;
      } else if (operator_name == ">") {
        self = KO_Greater;
      } else if (operator_name == "<=") {
        self = KO_Less_Equal;
      } else if (operator_name == ">=") {
        self = KO_Greater_Equal;
      } else if (operator_name == "!=") {
        self = KO_Not_Equal;
      } else if (operator_name == ",") {
        self = KO_Comma;
      } else if (operator_name == "|") {
        self = KO_Or;
      } else if (operator_name == "^") {
        self = KO_Xor;
      } else if (operator_name == "&") {
        self = KO_And;
      } else if (operator_name == "["){
        self = KO_Open_Square_Brace;
      }
    } else {
      if (operator_name == "+"){
        self = KO_Unary_Plus;
      } else if (operator_name == "-"){
        self = KO_Unary_Minus;
      } else if (operator_name == "++"){
        self = KO_Plus_Increment;
      } else if (operator_name == "--"){
        self = KO_Minus_Increment;
      } else if (operator_name == "!"){
        self = KO_Not;
      } else if (operator_name == ";"){
        self = KO_Semicolon;
      }
    }
  }
  bool is_operator() override {
    return true;
  }
 private:
  KOperand self;
};

#endif //BUGGUETTE_GENERATION_POLIZOPERATOR_H_
