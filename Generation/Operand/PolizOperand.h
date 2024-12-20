//
// Created by adams on 11/25/24.
//

#ifndef BUGGUETTE_GENERATION_POLIZOPERAND_H_
#define BUGGUETTE_GENERATION_POLIZOPERAND_H_
#include "../StackElement/StackElement.h"

#include "../../lib.h"
#include "cstdint"

/**
 * \brief Класс отвечающий за хранение операндов, в формате необходимом Интерпретатору
 */
class PolizOperand : public StackElement {
 public:
  bool is_operator() override {
    return false;
  }
  PolizOperand(K_Variable_Type type_, void *address) : element_type_(type_), element_address_(address) {
    switch (element_type_) {
      case K_Variable_Type_Float:
        string_representation_ = "float_" + std::to_string(intptr_t(element_address_)) + "_";
            //+ std::to_string(element_address_ ? *(double *) (element_address_) : 0);
        break;
      case K_Variable_Type_String:
        string_representation_ = "string_" + std::to_string(intptr_t(element_address_)) + "_";
            //+ (element_address_ ? *(std::string *) (element_address_) : "");
        break;
      case K_Variable_Type_Bool:
        string_representation_ = "bool_" + std::to_string(intptr_t(element_address_)) + "_";
            //+ std::to_string(element_address_ ? *(bool *) (element_address_) : false);
        break;
      case K_Variable_Type_Array:
        string_representation_ = "array_" + std::to_string(intptr_t(element_address_)) + "_"
          /*+ std::to_string(element_address_ ? *(std::vector<int> *) (element_address_) : std::vector<int>())*/;
        break;
      case K_Variable_Type_Char:string_representation_ = "char_" + std::to_string(intptr_t(element_address_))  + "_";
            //+ std::to_string(element_address_ ? *(char *) (element_address_) : '0');
        break;
      case K_Variable_Type_Int:string_representation_ = "int_" + std::to_string(intptr_t(element_address_))  + "_";
            //+ std::to_string(element_address_ ? *(int *) (element_address_) : 0);
        break;
      default:element_address_ = nullptr;
        string_representation_ = "NULLTYPE_" + std::to_string(intptr_t(element_address_));
        break;
    }
  }
  /// Обновляет информацию об объекте лежащем по element_address_, в случае изменения этого адреса
  void upd(void *new_addr) override {
    element_address_ = new_addr;
    switch (element_type_) {
      case K_Variable_Type_Float:
        string_representation_ = "float_" + std::to_string(intptr_t(element_address_)) + "_"
            + std::to_string(element_address_ ? *(float *) (element_address_) : 0);
        break;
      case K_Variable_Type_String:
        string_representation_ = "string_" + std::to_string(intptr_t(element_address_)) + "_"
            + (element_address_ ? *(std::string *) (element_address_) : "");
        break;
      case K_Variable_Type_Bool:
        string_representation_ = "bool_" + std::to_string(intptr_t(element_address_)) + "_"
            + std::to_string(element_address_ ? *(bool *) (element_address_) : false);
        break;
      case K_Variable_Type_Array:
        string_representation_ = "array_" + std::to_string(intptr_t(element_address_)) + "_"
          /*+ std::to_string(element_address_ ? *(std::vector<int> *) (element_address_) : std::vector<int>())*/;
        break;
      case K_Variable_Type_Char:string_representation_ = "char_" + std::to_string(intptr_t(element_address_))  + "_"
            + std::to_string(element_address_ ? *(char *) (element_address_) : '0');
        break;
      case K_Variable_Type_Int:string_representation_ = "int_" + std::to_string(intptr_t(element_address_))  + "_"
            + std::to_string(element_address_ ? *(int *) (element_address_) : 0);
        break;
      default:element_address_ = nullptr;
        string_representation_ = "NULLTYPE_" + std::to_string(intptr_t(element_address_));
        break;
    }
  }
// private:
  K_Variable_Type element_type_;
  void *element_address_;
};

#endif //BUGGUETTE_GENERATION_POLIZOPERAND_H_
