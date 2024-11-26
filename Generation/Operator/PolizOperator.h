//
// Created by adams on 11/25/24.
//

#ifndef BUGGUETTE_GENERATION_POLIZOPERATOR_H_
#define BUGGUETTE_GENERATION_POLIZOPERATOR_H_
#include "../StackElement/StackElement.h"
#include "../../semantic_analizator/TID/Function_TID.h"
enum KOperator {
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
  KO_Function_Call,
  KO_Go_False,
  KO_Go,
};

#include "../../lib.h"

class PolizOperator : public StackElement {
 public:
  PolizOperator(const std::string &operator_name, bool is_unary = false) {
    string_representation_ = operator_name;
    if (!is_unary) {
      if (operator_name == "+") {
        self_ = KO_Bin_Plus;
      } else if (operator_name == "-") {
        self_ = KO_Bin_Minus;
      } else if (operator_name == "*") {
        self_ = KO_Mul;
      } else if (operator_name == "/") {
        self_ = KO_Div;
      } else if (operator_name == "%") {
        self_ = KO_Mod;
      } else if (operator_name == "=") {
        self_ = KO_Assigment;
      } else if (operator_name == "==") {
        self_ = KO_Equal;
      } else if (operator_name == "<") {
        self_ = KO_Less;
      } else if (operator_name == ">") {
        self_ = KO_Greater;
      } else if (operator_name == "<=") {
        self_ = KO_Less_Equal;
      } else if (operator_name == ">=") {
        self_ = KO_Greater_Equal;
      } else if (operator_name == "!=") {
        self_ = KO_Not_Equal;
      } else if (operator_name == ",") {
        self_ = KO_Comma;
      } else if (operator_name == "|") {
        self_ = KO_Or;
      } else if (operator_name == "^") {
        self_ = KO_Xor;
      } else if (operator_name == "&") {
        self_ = KO_And;
      } else if (operator_name == "[") {
        self_ = KO_Open_Square_Brace;
      } else if (operator_name == "func") {
        self_ = KO_Function_Call;
      } else if (operator_name == "F") {
        self_ = KO_Go_False;
      } else {
#ifdef DEBUG
        //TODO
        throw std::logic_error("INVALID OPERATOR");
#endif
      }
    } else {
      if (operator_name == "+") {
        self_ = KO_Unary_Plus;
      } else if (operator_name == "-") {
        self_ = KO_Unary_Minus;
      } else if (operator_name == "++") {
        self_ = KO_Plus_Increment;
      } else if (operator_name == "--") {
        self_ = KO_Minus_Increment;
      } else if (operator_name == "!") {
        self_ = KO_Not;
      } else if (operator_name == ";") {
        self_ = KO_Semicolon;
      } else if (operator_name == "Go") {
        self_ = KO_Go;
      } else {
#ifdef DEBUG
        //TODO
        throw std::logic_error("INVALID OPERATOR");
#endif
      }
    }
  }
  void upd(void *) override {
    return;
  }
  bool is_operator() override {
    return true;
  }
  FunctionKey function;
 private:
  KOperator self_;
//  std::string string_representation_;
};

#endif //BUGGUETTE_GENERATION_POLIZOPERATOR_H_
