//
// Created by adams on 11/13/24.
//

#ifndef BUGGUETTE_SEMANTIC_ANALIZATOR_SEMANTICERROR_SEMANTICERROR_H_
#define BUGGUETTE_SEMANTIC_ANALIZATOR_SEMANTICERROR_SEMANTICERROR_H_
#include "../../lib.h"
class SemanticError: public std::exception{
 public:
  SemanticError(const std::string& _str) : str(_str) {}
  const char* what() const noexcept override{
    return str.c_str();
  }
 private:
  std::string str;

};

#endif //BUGGUETTE_SEMANTIC_ANALIZATOR_SEMANTICERROR_SEMANTICERROR_H_
