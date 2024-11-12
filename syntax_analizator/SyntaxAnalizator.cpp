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
        throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num + 1)));
      }
    } else {
      break;
    }
  }
  if (global::lex.type == LexemeType::Main) {
    main_();
  } else {
    throw SyntaxError("No main in program");
  }
  while (!global::eof) {
    if (global::lex.name == "def") {
      function_();
    } else if (global::lex.type == LexemeType::Type) {
      variables_declaration_();
      if (global::lex.type == LexemeType::Semicolon) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num + 1)));
      }
    } else {
      auto tmp = (std::string("Expected function or variable definition") + std::to_string(global::lex.num + 1));
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
          global::tree_of_variables.create_scope();
          block_();
          global::tree_of_variables.exit_scope();
          if (global::lex.name == "}") {
            getLex();
          } else {
            throw SyntaxError((std::string("Expected '}' ") + std::to_string(global::lex.num + 1)));
          }
        } else {
          throw SyntaxError((std::string("Expected '{' ") + std::to_string(global::lex.num + 1)));
        }
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
      }
    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num + 1)));
    }
  }
}
void function_() {
  if (global::lex.name == "def") {
    getLex();
    auto ret_type = global::lex;
    type_();
    auto name = global::lex;
    identificator_();
    global::tree_of_variables.create_scope();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      std::vector<std::string> args_types, args_names;
      while (global::lex.type != LexemeType::Close_brace) {
        auto cur_type = global::lex;
        args_types.push_back(cur_type.name);
        type_();
        auto cur_lex = global::lex;
        args_names.push_back(cur_lex.name);
        identificator_();
        global::tree_of_variables.push_id(cur_lex.name, cur_type.name);
        if (global::lex.type == LexemeType::Comma) {
          getLex();
        }
      }
      if (global::lex.name == ")") {
        getLex();
        global::function_table.push_id(ret_type.name, name.name, args_types, args_names);
        if (global::lex.name == "{") {
          getLex();
          block_();
          global::tree_of_variables.exit_scope();
          if (global::lex.name == "}") {
            getLex();
          } else {
            throw SyntaxError((std::string("Expected '}' ") + std::to_string(global::lex.num + 1)));
          }
        } else {
          throw SyntaxError((std::string("Expected '{' ") + std::to_string(global::lex.num + 1)));
        }
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
      }
    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num + 1)));
    }

  } else {
    throw SyntaxError((std::string("Expected 'def' ") + std::to_string(global::lex.num + 1)));
  }
}

void type_() {
  if (global::lex.type == LexemeType::Type) {
    getLex();
  } else {
    throw SyntaxError((std::string("Expected 'type' ") + std::to_string(global::lex.num + 1)));
  }
}

void identificator_() {
  if (global::lex.type == LexemeType::Identificator) {
    getLex();
  } else {
    throw SyntaxError((std::string("Expected 'Identificator' ") + std::to_string(global::lex.num + 1)));
  }
}

void operator_() {
  switch (global::lex.type) {
    case LexemeType::Open_curly_brace:
      getLex();
      global::tree_of_variables.create_scope();
      block_();
      global::tree_of_variables.exit_scope();
      if (global::lex.type == LexemeType::Close_curly_brace){
        getLex();
      } else {
        throw SyntaxError((std::string("Expected '}' ") + std::to_string(global::lex.num + 1)));
      }
      break;
    case LexemeType::Service_word:
      if (global::lex.name == "for") {
        global::tree_of_variables.create_scope();
        for_();
        global::tree_of_variables.exit_scope();
      } else if (global::lex.name == "while") {
        global::tree_of_variables.create_scope();
        while_();
        global::tree_of_variables.exit_scope();
      } else if (global::lex.name == "break") {
        break_();
      } else if (global::lex.name == "continue") {
        continue_();
      } else if (global::lex.name == "if") {
        global::tree_of_variables.create_scope();
        if_();
        global::tree_of_variables.exit_scope();
      } else if (global::lex.name == "switch") {
        global::tree_of_variables.create_scope();
        switch_();
        global::tree_of_variables.exit_scope();
      } else if (global::lex.name == "pass") {
        pass_();
      } else if (global::lex.name == "return") {
        return_();
      } else if (global::lex.name == "print") {
        print_();
      } else if (global::lex.name == "scan") {
        scan_();
      } else {
        throw SyntaxError(std::string("Expected operator ") + std::to_string(global::lex.num + 1));
      }
      break;
    case LexemeType::Type:variables_declaration_();
      if (global::lex.type == LexemeType::Semicolon) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num + 1)));
      }
      break;
    default:expression_();
      if (global::lex.type == LexemeType::Semicolon) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num + 1)));
      }
  }
}
void return_() {
  if (global::lex.name == "return") {
    getLex();
    expression_();
    if (global::lex.type == LexemeType::Semicolon) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num + 1)));
    }
  } else {
    throw SyntaxError((std::string("Expected 'return' ") + std::to_string(global::lex.num + 1)));
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
      getLex();
      expression_();
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
        operator_();
        if (global::lex.name == "else") {
          getLex();
          operator_();
        }
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
      }
    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num + 1)));
    }
  } else {
    throw SyntaxError((std::string("Expected 'if' ") + std::to_string(global::lex.num + 1)));
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
            getLex();
            operator_();
          } else {
            throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
          }
        } else {
          throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num + 1)));
        }
      } else {
        throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num + 1)));
      }
    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num + 1)));
    }
  } else {
    throw SyntaxError((std::string("Expected 'for' ") + std::to_string(global::lex.num + 1)));
  }
}
void while_() {
  if (global::lex.name == "while") {
    getLex();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      expression_();
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
        operator_();
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
      }
    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num + 1)));
    }
  }
}
void switch_() {
  if (global::lex.name == "switch") {
    getLex();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      expression_();
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
        if (global::lex.type == LexemeType::Open_curly_brace) {
          getLex();
          int cnt = 0;
          while (global::lex.name == "case") {
            getLex();
            if (global::lex.type == LexemeType::Open_brace) {
              getLex();
              if (global::lex.type == LexemeType::Literal || global::lex.type == LexemeType::String_Literal) {
                getLex();
                if (global::lex.type == LexemeType::Close_brace) {
                  getLex();
                  operator_();
                } else {
                  throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
                }
              } else {
                throw SyntaxError((std::string("Expected 'literal' or 'string literal' ")
                    + std::to_string(global::lex.num + 1)));
              }
            } else {
              throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num + 1)));
            }
            ++cnt;
          }
          if (global::lex.name == "else") {
            getLex();
            operator_();
          } else if (cnt == 0) {
            throw SyntaxError((std::string("Expected at least one case ") + std::to_string(global::lex.num + 1)));
          }
          if (global::lex.type == LexemeType::Close_curly_brace) {
            getLex();
          } else {
            throw SyntaxError((std::string("Expected '}' ") + std::to_string(global::lex.num + 1)));
          }
        } else {
          throw SyntaxError((std::string("Expected '{' ") + std::to_string(global::lex.num + 1)));
        }
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
      }
    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num + 1)));
    }
  } else {
    throw SyntaxError((std::string("Expected 'switch' ") + std::to_string(global::lex.num + 1)));
  }
}
void variables_declaration_() {
  if (global::lex.type == LexemeType::Type) {
    if (global::lex.name == "array") {
      getLex();
      auto cur_lex = global::lex;
      identificator_();
      global::tree_of_variables.push_id(cur_lex.name, "array");
      if (global::lex.type == LexemeType::Open_square_brace) {
        getLex();
        expression_();
        if (global::lex.type == LexemeType::Close_square_brace) {
          getLex();
        } else {
          throw SyntaxError((std::string("Expected ']' ") + std::to_string(global::lex.num + 1)));
        }
      } else {
        throw SyntaxError((std::string("Expected '[' ") + std::to_string(global::lex.num + 1)));
      }
      while (global::lex.type == LexemeType::Comma) {
        getLex();
        identificator_();
        if (global::lex.type == LexemeType::Open_square_brace) {
          getLex();
          expression_();
          if (global::lex.type == LexemeType::Close_square_brace) {
            getLex();
          } else {
            throw SyntaxError((std::string("Expected ']' ") + std::to_string(global::lex.num + 1)));
          }
        } else {
          throw SyntaxError((std::string("Expected '[' ") + std::to_string(global::lex.num + 1)));
        }
      }
    } else {
      auto cur_type = global::lex;
      getLex();
      while (global::lex.type != LexemeType::Semicolon) {
        auto cur_lex = global::lex;
        identificator_();
        global::tree_of_variables.push_id(cur_lex.name, cur_type.name);
        if (global::lex.type == LexemeType::Comma) {
          getLex();
          continue;
        } else if (global::lex.name == "=") {
          getLex();
          expression_();
          if (global::lex.type == LexemeType::Semicolon || global::lex.type == LexemeType::Comma) {
            continue;
          } else {
            throw SyntaxError((std::string("Expected ';' ',' ") + std::to_string(global::lex.num + 1)));
          }
        } else if (global::lex.type != LexemeType::Semicolon) {
          throw SyntaxError((std::string("Expected '=' or ',' ") + std::to_string(global::lex.num + 1)));
        }
      }
    }
  } else {
    throw SyntaxError((std::string("Expected 'type' ") + std::to_string(global::lex.num + 1)));
  }
}
void expression_() {
  expression10_();
}
void expression10_() {
  expression9_();
//  while (global::lex.name == ",") {
//    getLex();
//    expression9_();
//  }
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
  if (global::lex.name == "true") {
    getLex();
  } else if (global::lex.name == "false") {
    getLex();
  } else if (global::lex.type == LexemeType::String_Literal) {
    getLex();
  } else if (global::lex.type == LexemeType::Literal) {
    getLex();
  } else if (global::lex.type == LexemeType::Identificator) {
    auto cur_lex = global::lex;
    identificator_();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      function_call_();
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
      }
    } else {
      if (global::tree_of_variables.check_id(cur_lex.name) == variables_TID::Types::NULLTYPE){
        //TODO
        throw std::logic_error("No var in this scope");
      }
    }
  } else if (global::lex.type == LexemeType::Open_brace) {
    getLex();
    expression_();
    if (global::lex.type == LexemeType::Close_brace) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
    }
  } else if (global::lex.type == LexemeType::Open_square_brace) {
    getLex();
    expression_();
    if (global::lex.type == LexemeType::Close_square_brace) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ']' ") + std::to_string(global::lex.num + 1)));
    }
  } else {
    throw SyntaxError((std::string("Expected 'expression' ") + std::to_string(global::lex.num + 1)));
  }
}
void function_call_() {
  while (global::lex.type != LexemeType::Close_brace) {
    expression_();
    if (global::lex.type == LexemeType::Comma) {
      getLex();
    } else if (global::lex.type != LexemeType::Close_brace) {
      throw SyntaxError((std::string("Expected ',' or ')' ") + std::to_string(global::lex.num + 1)));
    }
  }
}

void break_() {
  if (global::lex.name == "break") {
    getLex();
    if (global::lex.type == LexemeType::Semicolon) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num + 1)));
    }
  } else {
    throw SyntaxError((std::string("Expected 'break' ") + std::to_string(global::lex.num + 1)));
  }
}
void continue_() {
  if (global::lex.name == "continue") {
    getLex();
    if (global::lex.type == LexemeType::Semicolon) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num + 1)));
    }
  } else {
    throw SyntaxError((std::string("Expected 'continue' ") + std::to_string(global::lex.num + 1)));
  }
}
void pass_() {
  if (global::lex.name == "pass") {
    getLex();
    if (global::lex.type == LexemeType::Semicolon) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num + 1)));
    }
  } else {
    throw SyntaxError((std::string("Expected 'pass' ") + std::to_string(global::lex.num + 1)));
  }
}
void print_() {
  if (global::lex.name == "print") {
    getLex();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      expression_();
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
        if (global::lex.type == LexemeType::Semicolon) {
          getLex();
        } else {
          throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num + 1)));
        }
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
      }
    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num + 1)));
    }
  } else {
    throw SyntaxError((std::string("Expected 'print' ") + std::to_string(global::lex.num + 1)));
  }
}
void scan_() {
  if (global::lex.name == "scan") {
    getLex();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      identificator_();
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
        if (global::lex.type == LexemeType::Semicolon) {
          getLex();
        } else {
          throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num + 1)));
        }
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
      }

    } else {
      throw SyntaxError((std::string("Expected '(' ") + std::to_string(global::lex.num + 1)));
    }
  } else {
    throw SyntaxError((std::string("Expected 'scan' ") + std::to_string(global::lex.num + 1)));
  }
}
void literal_() {
  if (global::lex.type == LexemeType::Literal) {
    getLex();
  } else {
    throw SyntaxError((std::string("Expected 'literal' ") + std::to_string(global::lex.num + 1)));
  }
}
void string_literal_() {
  if (global::lex.type == LexemeType::String_Literal) {
    getLex();
  } else {
    throw SyntaxError((std::string("Expected 'string literal' ") + std::to_string(global::lex.num + 1)));
  }
}