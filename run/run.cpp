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
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (lhs.first == K_Variable_Type_String || rhs.first == K_Variable_Type_String) {
          auto l = *(std::string *) (lhs.second);
          auto r = *(std::string *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_String, new std::string(l + r));
        } else {
          if (lhs.first == K_Variable_Type_Float && rhs.first == K_Variable_Type_Float) {
            double l = *(double *) (lhs.second);
            double r = *(double *) (rhs.second);
            global::stack_of_calculations.emplace_back(K_Variable_Type_Float, new double(r + l));
          } else if (lhs.first == K_Variable_Type_Float && rhs.first == K_Variable_Type_Int) {
            double l = *(double *) (lhs.second);
            int r = *(int *) (rhs.second);
            global::stack_of_calculations.emplace_back(K_Variable_Type_Float, new double(r + l));
          } else if (lhs.first == K_Variable_Type_Int && rhs.first == K_Variable_Type_Float) {
            int l = *(int *) (lhs.second);
            double r = *(double *) (rhs.second);
            global::stack_of_calculations.emplace_back(K_Variable_Type_Float, new double(r + l));
          } else if (lhs.first == K_Variable_Type_Int && rhs.first == K_Variable_Type_Int) {
            int l = *(int *) (lhs.second);
            int r = *(int *) (rhs.second);
            global::stack_of_calculations.emplace_back(K_Variable_Type_Int, new int(r + l));
          }
        }
      } else if (cur_operator->self_ == KOperator::KO_Bin_Minus) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (lhs.first == K_Variable_Type_Float && rhs.first == K_Variable_Type_Float) {
          double l = *(double *) (lhs.second);
          double r = *(double *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Float, new double(l - r));
        } else if (lhs.first == K_Variable_Type_Float && rhs.first == K_Variable_Type_Int) {
          double l = *(double *) (lhs.second);
          int r = *(int *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Float, new double(l - r));
        } else if (lhs.first == K_Variable_Type_Int && rhs.first == K_Variable_Type_Float) {
          int l = *(int *) (lhs.second);
          double r = *(double *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Float, new double(l - r));
        } else if (lhs.first == K_Variable_Type_Int && rhs.first == K_Variable_Type_Int) {
          int l = *(int *) (lhs.second);
          int r = *(int *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Int, new int(l - r));
        }
      } else if (cur_operator->self_ == KOperator::KO_Unary_Plus) {

      } else if (cur_operator->self_ == KOperator::KO_Unary_Minus) {
        auto hs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (hs.first == K_Variable_Type_Float) {
          double l = *(double *) (hs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Float, new double(-l));
        } else if (hs.first == K_Variable_Type_Int) {
          int l = *(int *) (hs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Int, new int(-l));
        }
      } else if (cur_operator->self_ == KOperator::KO_Mul) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (lhs.first == K_Variable_Type_Float && rhs.first == K_Variable_Type_Float) {
          double l = *(double *) (lhs.second);
          double r = *(double *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Float, new double(l * r));
        } else if (lhs.first == K_Variable_Type_Float && rhs.first == K_Variable_Type_Int) {
          double l = *(double *) (lhs.second);
          int r = *(int *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Float, new double(l * r));
        } else if (lhs.first == K_Variable_Type_Int && rhs.first == K_Variable_Type_Float) {
          int l = *(int *) (lhs.second);
          double r = *(double *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Float, new double(l * r));
        } else if (lhs.first == K_Variable_Type_Int && rhs.first == K_Variable_Type_Int) {
          int l = *(int *) (lhs.second);
          int r = *(int *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Int, new int(l * r));
        }
      } else if (cur_operator->self_ == KOperator::KO_Div) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (lhs.first == K_Variable_Type_Float && rhs.first == K_Variable_Type_Float) {
          double l = *(double *) (lhs.second);
          double r = *(double *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Float, new double(l / r));
        } else if (lhs.first == K_Variable_Type_Float && rhs.first == K_Variable_Type_Int) {
          double l = *(double *) (lhs.second);
          int r = *(int *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Float, new double(l / r));
        } else if (lhs.first == K_Variable_Type_Int && rhs.first == K_Variable_Type_Float) {
          int l = *(int *) (lhs.second);
          double r = *(double *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Float, new double(l / r));
        } else if (lhs.first == K_Variable_Type_Int && rhs.first == K_Variable_Type_Int) {
          int l = *(int *) (lhs.second);
          int r = *(int *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Int, new int(l / r));
        }
      } else if (cur_operator->self_ == KOperator::KO_Mod) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        int l = *(int *) (lhs.second);
        int r = *(int *) (rhs.second);
        global::stack_of_calculations.emplace_back(K_Variable_Type_Int, new int(l % r));
      } else if (cur_operator->self_ == KOperator::KO_Less) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (lhs.first == K_Variable_Type_Int) {
          auto l = *(int *) (lhs.second);
          auto r = *(int *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l < r));
        } else if (lhs.first == K_Variable_Type_Float) {
          auto l = *(double *) (lhs.second);
          auto r = *(double *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l < r));
        } else if (lhs.first == K_Variable_Type_String) {
          auto l = *(std::string *) (lhs.second);
          auto r = *(std::string *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l < r));
        } else if (lhs.first == K_Variable_Type_Array) {
          auto l = *(std::vector<int> *) (lhs.second);
          auto r = *(std::vector<int> *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l < r));
        } else if (lhs.first == K_Variable_Type_Bool) {
          auto l = *(bool *) (lhs.second);
          auto r = *(bool *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l < r));
        } else if (lhs.first == K_Variable_Type_Char) {
          auto l = *(char *) (lhs.second);
          auto r = *(char *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l < r));
        }
      } else if (cur_operator->self_ == KOperator::KO_Greater) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (lhs.first == K_Variable_Type_Int) {
          auto l = *(int *) (lhs.second);
          auto r = *(int *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l > r));
        } else if (lhs.first == K_Variable_Type_Float) {
          auto l = *(double *) (lhs.second);
          auto r = *(double *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l > r));
        } else if (lhs.first == K_Variable_Type_String) {
          auto l = *(std::string *) (lhs.second);
          auto r = *(std::string *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l > r));
        } else if (lhs.first == K_Variable_Type_Array) {
          auto l = *(std::vector<int> *) (lhs.second);
          auto r = *(std::vector<int> *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l > r));
        } else if (lhs.first == K_Variable_Type_Bool) {
          auto l = *(bool *) (lhs.second);
          auto r = *(bool *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l > r));
        } else if (lhs.first == K_Variable_Type_Char) {
          auto l = *(char *) (lhs.second);
          auto r = *(char *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l > r));
        }
      } else if (cur_operator->self_ == KOperator::KO_Equal) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (lhs.first == K_Variable_Type_Int) {
          auto l = *(int *) (lhs.second);
          auto r = *(int *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l == r));
        } else if (lhs.first == K_Variable_Type_Float) {
          auto l = *(double *) (lhs.second);
          auto r = *(double *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l == r));
        } else if (lhs.first == K_Variable_Type_String) {
          auto l = *(std::string *) (lhs.second);
          auto r = *(std::string *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l == r));
        } else if (lhs.first == K_Variable_Type_Array) {
          auto l = *(std::vector<int> *) (lhs.second);
          auto r = *(std::vector<int> *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l == r));
        } else if (lhs.first == K_Variable_Type_Bool) {
          auto l = *(bool *) (lhs.second);
          auto r = *(bool *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l == r));
        } else if (lhs.first == K_Variable_Type_Char) {
          auto l = *(char *) (lhs.second);
          auto r = *(char *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l == r));
        }
      } else if (cur_operator->self_ == KOperator::KO_Greater_Equal) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (lhs.first == K_Variable_Type_Int) {
          auto l = *(int *) (lhs.second);
          auto r = *(int *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l >= r));
        } else if (lhs.first == K_Variable_Type_Float) {
          auto l = *(double *) (lhs.second);
          auto r = *(double *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l >= r));
        } else if (lhs.first == K_Variable_Type_String) {
          auto l = *(std::string *) (lhs.second);
          auto r = *(std::string *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l >= r));
        } else if (lhs.first == K_Variable_Type_Array) {
          auto l = *(std::vector<int> *) (lhs.second);
          auto r = *(std::vector<int> *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l >= r));
        } else if (lhs.first == K_Variable_Type_Bool) {
          auto l = *(bool *) (lhs.second);
          auto r = *(bool *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l >= r));
        } else if (lhs.first == K_Variable_Type_Char) {
          auto l = *(char *) (lhs.second);
          auto r = *(char *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l >= r));
        }
      } else if (cur_operator->self_ == KOperator::KO_Less_Equal) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (lhs.first == K_Variable_Type_Int) {
          auto l = *(int *) (lhs.second);
          auto r = *(int *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l <= r));
        } else if (lhs.first == K_Variable_Type_Float) {
          auto l = *(double *) (lhs.second);
          auto r = *(double *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l <= r));
        } else if (lhs.first == K_Variable_Type_String) {
          auto l = *(std::string *) (lhs.second);
          auto r = *(std::string *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l <= r));
        } else if (lhs.first == K_Variable_Type_Array) {
          auto l = *(std::vector<int> *) (lhs.second);
          auto r = *(std::vector<int> *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l <= r));
        } else if (lhs.first == K_Variable_Type_Bool) {
          auto l = *(bool *) (lhs.second);
          auto r = *(bool *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l <= r));
        } else if (lhs.first == K_Variable_Type_Char) {
          auto l = *(char *) (lhs.second);
          auto r = *(char *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l <= r));
        }
      } else if (cur_operator->self_ == KOperator::KO_Not_Equal) {

        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (lhs.first == K_Variable_Type_Int) {
          auto l = *(int *) (lhs.second);
          auto r = *(int *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l != r));
        } else if (lhs.first == K_Variable_Type_Float) {
          auto l = *(double *) (lhs.second);
          auto r = *(double *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l != r));
        } else if (lhs.first == K_Variable_Type_String) {
          auto l = *(std::string *) (lhs.second);
          auto r = *(std::string *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l != r));
        } else if (lhs.first == K_Variable_Type_Array) {
          auto l = *(std::vector<int> *) (lhs.second);
          auto r = *(std::vector<int> *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l != r));
        } else if (lhs.first == K_Variable_Type_Bool) {
          auto l = *(bool *) (lhs.second);
          auto r = *(bool *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l != r));
        } else if (lhs.first == K_Variable_Type_Char) {
          auto l = *(char *) (lhs.second);
          auto r = *(char *) (rhs.second);
          global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l != r));
        }
      } else if (cur_operator->self_ == KOperator::KO_Comma) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        global::stack_of_calculations.push_back(rhs);
      } else if (cur_operator->self_ == KOperator::KO_Assigment) {

        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (lhs.first == K_Variable_Type_Int) {
          *(int *) (lhs.second) = *(int *) (rhs.second);
        } else if (lhs.first == K_Variable_Type_Float) {
          *(double *) (lhs.second) = *(double *) (rhs.second);
        } else if (lhs.first == K_Variable_Type_String) {
          *(std::string *) (lhs.second) = *(std::string *) (rhs.second);
        } else if (lhs.first == K_Variable_Type_Array) {
          *(std::vector<int> *) (lhs.second) = *(std::vector<int> *) (rhs.second);
        } else if (lhs.first == K_Variable_Type_Bool) {
          *(bool *) (lhs.second) = *(bool *) (rhs.second);
        } else if (lhs.first == K_Variable_Type_Char) {
          *(char *) (lhs.second) = *(char *) (rhs.second);
        }
        global::stack_of_calculations.push_back(lhs);
      } else if (cur_operator->self_ == KOperator::KO_Or) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto l = *(bool *) (lhs.second);
        auto r = *(bool *) (rhs.second);
        global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l || r));
      } else if (cur_operator->self_ == KOperator::KO_Xor) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto l = *(bool *) (lhs.second);
        auto r = *(bool *) (rhs.second);
        global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l ^ r));
      } else if (cur_operator->self_ == KOperator::KO_And) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto l = *(bool *) (lhs.second);
        auto r = *(bool *) (rhs.second);
        global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(l && r));
      } else if (cur_operator->self_ == KOperator::KO_Not) {
        auto hs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto l = *(bool *) (hs.second);
        global::stack_of_calculations.emplace_back(K_Variable_Type_Bool, new bool(!l));
      } else if (cur_operator->self_ == KOperator::KO_Plus_Increment) {
        auto hs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (hs.first == K_Variable_Type_Int) {
          ++(*(int *) (hs.second));
        } else {
          ++(*(double *) (hs.second));
        }
        global::stack_of_calculations.push_back(hs);
      } else if (cur_operator->self_ == KOperator::KO_Minus_Increment) {
        auto hs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (hs.first == K_Variable_Type_Int) {
          --(*(int *) (hs.second));
        } else {
          --(*(double *) (hs.second));
        }
        global::stack_of_calculations.push_back(hs);
      } else if (cur_operator->self_ == KOperator::KO_Open_Square_Brace) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
//        auto l = *(std::vector<int> *) (lhs.second);
//        auto r = *(int *) rhs.second;
        global::stack_of_calculations.emplace_back(K_Variable_Type_Int,
                                                   &((*(std::vector<int> *) (lhs.second))[*(int *) (rhs.second)]));
      } else if (cur_operator->self_ == KOperator::KO_Semicolon) {
        global::stack_of_calculations.pop_back();
      } else if (cur_operator->self_ == KOperator::KO_Function_Call) {
        auto res = global::function_table.check_id(cur_operator->function);
        auto next_init = init;
        for (int i = (int) cur_operator->function.types_of_args.size() - 1; i >= 0; --i) {
          auto cur_operand = dynamic_cast<PolizOperand *>(global::poliz_stack[res.poliz_addr + i * 2]);
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
            ((std::vector<void *> *) (cur_operand->element_address_))->push_back(new std::vector<int>(*((std::vector<
                int> *) (cur_el))));
          }
          next_init[{cur_operand->element_type_, (std::vector<void *> *) cur_operand->element_address_}] = true;

          auto lhs = std::make_pair(cur_operand->element_type_,
                                    ((std::vector<void *> *) (cur_operand->element_address_))->back());
          auto rhs = global::stack_of_calculations.back();
          global::stack_of_calculations.pop_back();
          if (lhs.first == K_Variable_Type_Int) {
            *(int *) (lhs.second) = *(int *) (rhs.second);
          } else if (lhs.first == K_Variable_Type_Float) {
            *(double *) (lhs.second) = *(double *) (rhs.second);
          } else if (lhs.first == K_Variable_Type_String) {
            *(std::string *) (lhs.second) = *(std::string *) (rhs.second);
          } else if (lhs.first == K_Variable_Type_Array) {
            *(std::vector<int> *) (lhs.second) = *(std::vector<int> *) (rhs.second);
          } else if (lhs.first == K_Variable_Type_Bool) {
            *(bool *) (lhs.second) = *(bool *) (rhs.second);
          } else if (lhs.first == K_Variable_Type_Char) {
            *(char *) (lhs.second) = *(char *) (rhs.second);
          }
        }
        run(res.poliz_addr + cur_operator->function.types_of_args.size() * 2, next_init);
        for (int i = (int) cur_operator->function.types_of_args.size() - 1; i >= 0; --i) {
          auto cur_operand = dynamic_cast<PolizOperand *>(global::poliz_stack[res.poliz_addr + i * 2]);
          ((std::vector<void *> *) cur_operand->element_address_)->pop_back();
        }
      } else if (cur_operator->self_ == KOperator::KO_Go_False) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        bool l = *(bool *) (lhs.second);
        int r = *(int *) (rhs.second);
        if (!l) {
          poliz_ind = r;
          continue;
        }
      } else if (cur_operator->self_ == KOperator::KO_Go) {
        auto rhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        int r = *(int *) (rhs.second);
        poliz_ind = r;
        continue;
      } else if (cur_operator->self_ == KOperator::KO_PRN) {
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (lhs.first == K_Variable_Type_Int) {
          std::cout << *(int *) (lhs.second);
        } else if (lhs.first == K_Variable_Type_Float) {
          std::cout << *(double *) (lhs.second);
        } else if (lhs.first == K_Variable_Type_String) {
          std::cout << *(std::string *) (lhs.second);
        } else if (lhs.first == K_Variable_Type_Bool) {
          std::cout << *(bool *) (lhs.second);
        } else if (lhs.first == K_Variable_Type_Char) {
          std::cout << *(char *) (lhs.second);
        }
        std::cout.flush();
      } else if (cur_operator->self_ == KOperator::KO_SCN) {
        auto lhs = global::stack_of_calculations.back();
        global::stack_of_calculations.pop_back();
        if (lhs.first == K_Variable_Type_Int) {
          std::cin >> *(int *) (lhs.second);
        } else if (lhs.first == K_Variable_Type_Float) {
          std::cin >> *(double *) (lhs.second);
        } else if (lhs.first == K_Variable_Type_String) {
          std::cin >> *(std::string *) (lhs.second);
        } else if (lhs.first == K_Variable_Type_Bool) {
          std::cin >> *(bool *) (lhs.second);
        } else if (lhs.first == K_Variable_Type_Char) {
          std::cin >> *(char *) (lhs.second);
        }
      } else if (cur_operator->self_ == KOperator::KO_RET) {
        break;
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
      if (i.first == K_Variable_Type_Int) {
        delete (int *) (i.second->back());
      } else if (i.first == K_Variable_Type_Bool) {
        delete (bool *) (i.second->back());
      } else if (i.first == K_Variable_Type_Float) {
        delete (double *) (i.second->back());
      } else if (i.first == K_Variable_Type_Char) {
        delete (char *) (i.second->back());
      } else if (i.first == K_Variable_Type_String) {
        delete (std::string *) (i.second->back());
      } else if (i.first == K_Variable_Type_Array) {
        delete (std::vector<int> *) (i.second->back());
      }
      i.second->pop_back();
    }
  }
}
