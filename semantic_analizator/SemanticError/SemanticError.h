//
// Created by adams on 11/13/24.
//

#ifndef BUGGUETTE_SEMANTIC_ANALIZATOR_SEMANTICERROR_SEMANTICERROR_H_
#define BUGGUETTE_SEMANTIC_ANALIZATOR_SEMANTICERROR_SEMANTICERROR_H_
#include <utility>

#include "../../lib.h"
///\brief Ошибки, бросаемые блоками семантического анализатора
class SemanticError: public std::exception{
 public:
  explicit SemanticError(std::string  _str) : str(std::move(_str)) {}
  [[nodiscard]] const char* what() const noexcept override{
    return str.c_str();
  }
 private:
  std::string str;

};

#endif //BUGGUETTE_SEMANTIC_ANALIZATOR_SEMANTICERROR_SEMANTICERROR_H_
