//
// Created by adams on 11/25/24.
//

#ifndef BUGGUETTE_GENERATION_POLIZOPERAND_H_
#define BUGGUETTE_GENERATION_POLIZOPERAND_H_
#include "../StackElement/StackElement.h"

#include "../../lib.h"

class PolizOperand : public StackElement {
 public:
  bool is_operator() override {
    return false;
  }
  PolizOperand(K_Variable_Type type, void* address) : element_type_(type), element_address_(address) {}
 private:
  K_Variable_Type element_type_;
  void *element_address_;
};

#endif //BUGGUETTE_GENERATION_POLIZOPERAND_H_
