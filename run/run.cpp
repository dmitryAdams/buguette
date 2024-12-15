//
// Created by adams on 12/15/24.
//

#include "run.h"
#include "../Generation/Operand/PolizOperand.h"
#include "../Generation/Operator/PolizOperator.h"


//std::map<std::pair<K_Variable_Type, std::vector<void *> *>, bool> init;

void run(int poliz_ind, const std::map<std::pair<K_Variable_Type, std::vector<void *> *>, bool> &init) {
  auto used = init;
  while (poliz_ind < global::poliz_stack.size()) {
    if (global::poliz_stack[poliz_ind]->is_operator()) {
      auto cur_operator = dynamic_cast<PolizOperator *>(global::poliz_stack[poliz_ind]);
      if (cur_operator->self_ == KOperator::KO_Bin_Plus) {

      } else if (cur_operator->self_ == KOperator::KO_Bin_Minus) {

      } else if (cur_operator->self_ == KOperator::KO_Unary_Plus) {

      } else if (cur_operator->self_ == KOperator::KO_Unary_Minus) {

      } else if (cur_operator->self_ == KOperator::KO_Mul) {

      } else if (cur_operator->self_ == KOperator::KO_Div) {

      } else if (cur_operator->self_ == KOperator::KO_Mod) {

      } else if (cur_operator->self_ == KOperator::KO_Less) {

      } else if (cur_operator->self_ == KOperator::KO_Greater) {

      } else if (cur_operator->self_ == KOperator::KO_Equal) {

      } else if (cur_operator->self_ == KOperator::KO_Greater_Equal) {

      } else if (cur_operator->self_ == KOperator::KO_Less_Equal) {

      } else if (cur_operator->self_ == KOperator::KO_Not_Equal) {

      } else if (cur_operator->self_ == KOperator::KO_Comma) {

      } else if (cur_operator->self_ == KOperator::KO_Assigment) {

      } else if (cur_operator->self_ == KOperator::KO_Or) {

      } else if (cur_operator->self_ == KOperator::KO_Xor) {

      } else if (cur_operator->self_ == KOperator::KO_And) {

      } else if (cur_operator->self_ == KOperator::KO_Not) {

      } else if (cur_operator->self_ == KOperator::KO_Plus_Increment) {

      } else if (cur_operator->self_ == KOperator::KO_Minus_Increment) {

      } else if (cur_operator->self_ == KOperator::KO_Open_Square_Brace) {

      } else if (cur_operator->self_ == KOperator::KO_Semicolon) {

      } else if (cur_operator->self_ == KOperator::KO_Function_Call) {

      } else if (cur_operator->self_ == KOperator::KO_Go_False) {

      } else if (cur_operator->self_ == KOperator::KO_Go) {

      } else if (cur_operator->self_ == KOperator::KO_PRN) {

      } else if (cur_operator->self_ == KOperator::KO_SCN) {

      } else if (cur_operator->self_ == KOperator::KO_RET) {

      }
      //operator
    } else {
      auto cur_operand = dynamic_cast<PolizOperand *>(global::poliz_stack[poliz_ind]);
      if (!used.count({cur_operand->element_type_, (std::vector<void *> *) cur_operand->element_address_})) {
        auto cur_el = ((std::vector<void *> *) (cur_operand->element_address_))->back();
        if (cur_operand->element_type_ == K_Variable_Type::K_Variable_Type_Int) {
          ((std::vector<void *> *) (cur_operand->element_address_))->push_back(new int(*((int *) (cur_el))));
        } else if (cur_operand->element_type_ == K_Variable_Type::K_Variable_Type_Bool) {
          ((std::vector<void *> *) (cur_operand->element_address_))->push_back(new bool(*((bool *) (cur_el))));
        } else if (cur_operand->element_type_ == K_Variable_Type::K_Variable_Type_Float) {
          ((std::vector<void *> *) (cur_operand->element_address_))->push_back(new double(*((double *) (cur_el))));
        } else if (cur_operand->element_type_ == K_Variable_Type::K_Variable_Type_Char) {
          ((std::vector<void *> *) (cur_operand->element_address_))->push_back(new char(*((char *) (cur_el))));
        } else if (cur_operand->element_type_ == K_Variable_Type::K_Variable_Type_String) {
          ((std::vector<void *> *) (cur_operand->element_address_))->push_back(new std::string(*((std::string *) (cur_el))));
        } else if (cur_operand->element_type_ == K_Variable_Type::K_Variable_Type_Array) {
          ((std::vector<void *> *) (cur_operand->element_address_))->push_back(new std::vector<int>(*((std::vector<int> *) (cur_el))));
        }
        used[{cur_operand->element_type_, (std::vector<void *> *) cur_operand->element_address_}] = true;
      }
      global::stack_of_calculations.emplace_back(cur_operand->element_type_,
                                                 ((std::vector<void *> *) (cur_operand->element_address_))->back());
      //operand
    }
    ++poliz_ind;
  }
  for (auto &[i, j] : used) {
    if (!init.count(i)) {
      //TODO Пофиксить утечку памяти
      i.second->pop_back();
    }
  }
}
