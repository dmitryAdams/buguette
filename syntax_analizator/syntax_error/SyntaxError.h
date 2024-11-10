//
// Created by adams on 11/11/24.
//

#ifndef BUGGUETTE_SYNTAX_ANALIZATOR_SYNTAX_ERROR_SYNTAXERROR_H_
#define BUGGUETTE_SYNTAX_ANALIZATOR_SYNTAX_ERROR_SYNTAXERROR_H_

#include "exception"

class SyntaxError : public std::exception{
 public:
  SyntaxError(const char *_str) : str(_str) {}
  const char* what() const noexcept override{
    return str;
  }
 private:
  const char *str;
};

#endif //BUGGUETTE_SYNTAX_ANALIZATOR_SYNTAX_ERROR_SYNTAXERROR_H_
