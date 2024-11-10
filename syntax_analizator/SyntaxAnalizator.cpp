#include "SyntaxAnalizator.h"
#include "./syntax_error/SyntaxError.h"

void program_() {
  getLex();
  while (true) {
    if (global::lex.name == "def") {
      function_();
    } else if (global::lex.type == LexemeType::Type) {
      variables_declaration_();
      if (global::lex.type == LexemeType::Semicolon) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num)).c_str());
      }
    } else {
      break;
    }
  }
  if (global::lex.name == "main") {
    main_();
  } else {
    throw SyntaxError("No main in programm");
  }
  while (!global::eof) {
    if (global::lex.name == "def") {
      function_();
    } else if (global::lex.type == LexemeType::Type) {
      variables_declaration_();
      if (global::lex.type == LexemeType::Semicolon) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num)).c_str());
      }
    } else {
      auto tmp = (std::string("Expected function or variable definition") + std::to_string(global::lex.num)).c_str();
      throw SyntaxError(tmp);
    }
  }
}

void main_() {
  if (global::lex.name == "main") {
    getLex();
    if (global::lex.name == "(") {
      getLex();
      if (global::lex.name == ")") {
        getLex();
        if (global::lex.name == "{") {
          getLex();
          block_();
          if (global::lex.name == "}") {
            getLex();
          } else {
            throw SyntaxError((std::string("Expected '}' ") + std::to_string(global::lex.num)).c_str());
          }
        } else {
          throw SyntaxError((std::string("Expected '{' ") + std::to_string(global::lex.num)).c_str());
        }
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num)).c_str());
      }
    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num)).c_str());
    }
  }
}
void function_() {
  if (global::lex.name == "def") {
    getLex();
    type_();
    identificator_();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      while (global::lex.type != LexemeType::Close_brace) {
        type_();
        identificator_();
        if (global::lex.type == LexemeType::Comma) {
          getLex();
        }
      }
      if (global::lex.name == ")") {
        getLex();
        if (global::lex.name == "{") {
          getLex();
          block_();
          if (global::lex.name == "}") {
            getLex();
          } else {
            throw SyntaxError((std::string("Expected '}' ") + std::to_string(global::lex.num)).c_str());
          }
        } else {
          throw SyntaxError((std::string("Expected '{' ") + std::to_string(global::lex.num)).c_str());
        }
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num)).c_str());
      }
    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num)).c_str());
    }

  } else {
    throw SyntaxError((std::string("Expected 'def' ") + std::to_string(global::lex.num)).c_str());
  }
}

void type_() {
  if (global::lex.type == LexemeType::Type) {
    getLex();
  } else {
    throw SyntaxError((std::string("Expected 'type' ") + std::to_string(global::lex.num)).c_str());
  }
}

void identificator_() {
  if (global::lex.type == LexemeType::Identificator) {
    getLex();
  } else {
    throw SyntaxError((std::string("Expected 'Identificator' ") + std::to_string(global::lex.num)).c_str());
  }
}

void operator_() {
  switch (global::lex.type) {
    case LexemeType::Open_curly_brace:getLex();
      block_();
      getLex();
      break;
    case LexemeType::Service_word:
      if (global::lex.name == "for") {
        for_();
      } else if (global::lex.name == "while") {
        while_();
      } else if (global::lex.name == "break") {
        break_();
      } else if (global::lex.name == "continue") {
        continue_();
      } else if (global::lex.name == "if") {
        if_();
      } else if (global::lex.name == "switch") {
        switch_();
      } else if (global::lex.name == "pass") {
        pass_();
      } else if (global::lex.name == "return") {
        return_();
      } else if (global::lex.name == "print") {
        print_();
      }
      break;
    case LexemeType::Type:variables_declaration_();
      if (global::lex.type == LexemeType::Semicolon) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num)).c_str());
      }
      break;
    default:expression_();
  }
}
void return_() {
  if (global::lex.name == "return") {
    getLex();
    expression_();
    if (global::lex.type == LexemeType::Semicolon) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num)).c_str());
    }
  } else {
    throw SyntaxError((std::string("Expected 'return' ") + std::to_string(global::lex.num)).c_str());
  }
}
void block_() {
  while (global::lex.type != LexemeType::Close_curly_brace) {
    operator_();
  }
}
void if_() {
  if (global::lex.name == "if") {
    getLex();
    if (global::lex.type == LexemeType::Open_brace) {
      expression_();
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
        operator_();
        if (global::lex.name == "else") {
          getLex();
          operator_();
        }
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num)).c_str());
      }
    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num)).c_str());
    }
  } else {
    throw SyntaxError((std::string("Expected 'if' ") + std::to_string(global::lex.num)).c_str());
  }
}
void for_() {
  if (global::lex.name == "for") {
    getLex();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      variables_declaration_();
      if (global::lex.type == LexemeType::Semicolon) {
        getLex();
        expression_();
        if (global::lex.type == LexemeType::Semicolon) {
          getLex();
          expression_();
          if (global::lex.type == LexemeType::Close_brace) {
            operator_();
          } else {
            throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num)).c_str());
          }
        } else {
          throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num)).c_str());
        }
      } else {
        throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num)).c_str());
      }
    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num)).c_str());
    }
  } else {
    throw SyntaxError((std::string("Expected 'for' ") + std::to_string(global::lex.num)).c_str());
  }
}
void while_() {
  if (global::lex.name == "while") {
    getLex();
    if (global::lex.type == LexemeType::Open_brace) {
      expression_();
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
        operator_();
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num)).c_str());
      }
    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num)).c_str());
    }
  }
}
void switch_() {
  if (global::lex.name == "switch") {
    getLex();
    if (global::lex.type == LexemeType::Open_brace) {
      expression_();
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
        operator_();
        if (global::lex.type == LexemeType::Open_curly_brace) {
          getLex();
          int cnt = 0;
          while (global::lex.name == "case") {
            getLex();
            if (global::lex.type == LexemeType::Open_brace) {
              if (global::lex.type == LexemeType::Literal || global::lex.type == LexemeType::String_Literal) {
                getLex();
                if (global::lex.type == LexemeType::Close_brace) {
                  getLex();
                  operator_();
                } else {
                  throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num)).c_str());
                }
              } else {
                throw SyntaxError((std::string("Expected 'literal' or 'string literal' ")
                    + std::to_string(global::lex.num)).c_str());
              }
            } else {
              throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num)).c_str());
            }
            ++cnt;
          }
          if (cnt == 0) {
            throw SyntaxError((std::string("Expected at least one case ") + std::to_string(global::lex.num)).c_str());
          }
          //TODO Добавить else в switch
        } else {
          throw SyntaxError((std::string("Expected '{' ") + std::to_string(global::lex.num)).c_str());
        }
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num)).c_str());
      }
    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num)).c_str());
    }
  } else {
    throw SyntaxError((std::string("Expected 'switch' ") + std::to_string(global::lex.num)).c_str());
  }
}
void variables_declaration_() {
  if (global::lex.type == LexemeType::Type) {
    getLex();
    while (global::lex.type != LexemeType::Semicolon) {
      if (global::lex.type == LexemeType::Identificator) {
        getLex();
        if (global::lex.type == LexemeType::Comma) {
          getLex();
        } else if (global::lex.name == "=") {
          getLex();
          expression_();
        } else if (global::lex.type != LexemeType::Semicolon) {
          throw SyntaxError((std::string("Expected '=' or ',' ") + std::to_string(global::lex.num)).c_str());
        }
      } else {
        throw SyntaxError((std::string("Expected 'identificator' ") + std::to_string(global::lex.num)).c_str());
      }
    }
  } else {
    throw SyntaxError((std::string("Expected 'type' ") + std::to_string(global::lex.num)).c_str());
  }
}
void expression_() {
  expression10_();
}
void expression10_() {
  expression9_();
  while (global::lex.name == ",") {
    getLex();
    expression9_();
  }
}
void expression9_() {
  expression8_();
  while (global::lex.name == "=") {
    getLex();
    expression8_();
  }
}
void expression8_() {
  expression7_();
  while (global::lex.name == "|") {
    getLex();
    expression7_();
  }
}
void expression7_() {
  expression6_();
  while (global::lex.name == "^") {
    getLex();
    expression6_();
  }
}
void expression6_() {
  expression5_();
  while (global::lex.name == "&") {
    getLex();
    expression5_();
  }
}
void expression5_() {
  expression4_();
  while (global::lex.name == "==" || global::lex.name == "!=") {
    getLex();
    expression4_();
  }
}
void expression4_() {
  expression3_();
  while (global::lex.name == "<" || global::lex.name == ">" || global::lex.name == ">=" || global::lex.name == "<=") {
    getLex();
    expression3_();
  }
}
void expression3_() {
  expression2_();
  while (global::lex.name == "+" || global::lex.name == "-") {
    getLex();
    expression2_();
  }
}
void expression2_() {
  expression1_();
  while (global::lex.name == "*" || global::lex.name == "/" || global::lex.name == "%") {
    getLex();
    expression1_();
  }
}
void expression1_() {
  if (global::lex.name == "+" || global::lex.name == "-" || global::lex.name == "++" || global::lex.name == "--"
      || global::lex.name == "!") {
    getLex();
  }
  expression_cool_();
}
void expression_cool_() {
  if (global::lex.type == LexemeType::String_Literal) {
    getLex();
  } else if (global::lex.type == LexemeType::Literal) {
    getLex();
  } else if (global::lex.type == LexemeType::Identificator) {
    getLex();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      function_call_();
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num)).c_str());
      }
    }
  } else if (global::lex.type == LexemeType::Open_brace) {
    getLex();
    expression_();
    if (global::lex.type == LexemeType::Close_curly_brace) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num)).c_str());
    }
  } else if (global::lex.type == LexemeType::Open_square_brace) {
    getLex();
    expression_();
    if (global::lex.type == LexemeType::Close_square_brace) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ']' ") + std::to_string(global::lex.num)).c_str());
    }
  } else {
    throw SyntaxError((std::string("Expected 'expression' ") + std::to_string(global::lex.num)).c_str());
  }
  while (global::lex.type == LexemeType::Literal ||
      global::lex.type == LexemeType::Identificator ||
      global::lex.type == LexemeType::Open_brace ||
      global::lex.type == LexemeType::Open_square_brace) {
    if (global::lex.type == LexemeType::Literal) {
      getLex();
    } else if (global::lex.type == LexemeType::Identificator) {
      getLex();
    } else if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      expression_();
      if (global::lex.type == LexemeType::Close_curly_brace) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num)).c_str());
      }
    } else if (global::lex.type == LexemeType::Open_square_brace) {
      getLex();
      expression_();
      if (global::lex.type == LexemeType::Close_square_brace) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected ']' ") + std::to_string(global::lex.num)).c_str());
      }
    } else {
      throw SyntaxError((std::string("Expected 'expression' ") + std::to_string(global::lex.num)).c_str());
    }
  }
}
void function_call_() {
  while (global::lex.type != LexemeType::Close_brace) {
    expression_();
    if (global::lex.type == LexemeType::Comma) {
      getLex();
    } else if (global::lex.type != LexemeType::Close_brace) {
      throw SyntaxError((std::string("Expected ',' or ')' ") + std::to_string(global::lex.num)).c_str());
    }
  }
}

void break_() {
  if (global::lex.name == "break") {
    getLex();
    if (global::lex.type == LexemeType::Semicolon) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num)).c_str());
    }
  } else {
    throw SyntaxError((std::string("Expected 'break' ") + std::to_string(global::lex.num)).c_str());
  }
}
void continue_() {
  if (global::lex.name == "continue") {
    getLex();
    if (global::lex.type == LexemeType::Semicolon) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num)).c_str());
    }
  } else {
    throw SyntaxError((std::string("Expected 'continue' ") + std::to_string(global::lex.num)).c_str());
  }
}
void pass_() {
  if (global::lex.name == "pass") {
    getLex();
    if (global::lex.type == LexemeType::Semicolon) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num)).c_str());
    }
  } else {
    throw SyntaxError((std::string("Expected 'pass' ") + std::to_string(global::lex.num)).c_str());
  }
}
void print_() {
  return;
}
void literal_() {
  if (global::lex.type == LexemeType::Literal) {
    getLex();
  } else {
    throw SyntaxError((std::string("Expected 'literal' ") + std::to_string(global::lex.num)).c_str());
  }
}
void string_literal_() {
  if (global::lex.type == LexemeType::String_Literal) {
    getLex();
  } else {
    throw SyntaxError((std::string("Expected 'string literal' ") + std::to_string(global::lex.num)).c_str());
  }
}