//
// Created by adams on 11/11/24.
//

#ifndef BUGGUETTE_SYNTAX_ANALIZATOR_SYNTAX_ERROR_SYNTAXERROR_H_
#define BUGGUETTE_SYNTAX_ANALIZATOR_SYNTAX_ERROR_SYNTAXERROR_H_

#include "exception"
#include "string"
/// \brief Ошибки, которые бросают блоки Синтаксического анализатора
class SyntaxError : public std::exception{
 public:
  SyntaxError(const std::string& _str) : str(_str) {}
  const char* what() const noexcept override{
    return str.c_str();
  }
 private:
  std::string str;
};

#endif //BUGGUETTE_SYNTAX_ANALIZATOR_SYNTAX_ERROR_SYNTAXERROR_H_
