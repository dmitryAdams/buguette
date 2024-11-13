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
          expression9_();
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
std::pair<variables_TID::Types, bool> expression_() {
  return expression10_();
}
std::pair<variables_TID::Types, bool> expression10_() {
  expression9_();
  while (global::lex.name == ",") {
    getLex();
    expression9_();
  }
}
std::pair<variables_TID::Types, bool> expression9_() {
  auto lhs = expression8_();
  while (global::lex.name == "=") {
    getLex();
    auto rhs = expression8_();
    if(!lhs.second){
      //TODO
      throw std::logic_error("not lvalue int lhs operator =");
    } else if(lhs.first != rhs.first){
      //TODO
      throw std::logic_error("different types in operator =");
    }
    lhs = rhs;
  }
  return lhs;
}
std::pair<variables_TID::Types, bool> expression8_() {
  auto lhs = expression7_();
  while (global::lex.name == "|") {
    getLex();
    auto rhs = expression7_();
    if(lhs.first != variables_TID::Types::bool_){
      //TODO
      throw std::logic_error("left operand not bool");
    } else if(rhs.first != variables_TID::Types::bool_){
      //TODO
      throw std::logic_error("right operand not bool");
    }
    lhs = rhs;
    lhs.second = false;
  }
  return lhs;
}
std::pair<variables_TID::Types, bool> expression7_() {
  auto lhs = expression6_();
  while (global::lex.name == "^") {
    getLex();
    auto rhs = expression6_();
    if(lhs.first != variables_TID::Types::bool_){
      //TODO
      throw std::logic_error("left operand not bool");
    } else if(rhs.first != variables_TID::Types::bool_){
      //TODO
      throw std::logic_error("right operand not bool");
    }
    lhs = rhs;
    lhs.second = false;
  }
  return lhs;
}
std::pair<variables_TID::Types, bool> expression6_() {
  auto lhs = expression5_();
  while (global::lex.name == "&") {
    getLex();
    auto rhs = expression5_();
    if(lhs.first != variables_TID::Types::bool_){
      //TODO
      throw std::logic_error("left operand not bool");
    } else if(rhs.first != variables_TID::Types::bool_){
      //TODO
      throw std::logic_error("right operand not bool");
    }
    lhs = rhs;
    lhs.second = false;
  }
  return lhs;
}
std::pair<variables_TID::Types, bool> expression5_() {
  auto lhs = expression4_();
  while (global::lex.name == "==" || global::lex.name == "!=") {
    getLex();
    auto rhs = expression4_();
    if(lhs.first != rhs.second){
      //TODO
      throw std::logic_error("different types in ==");
    }
    lhs.first = variables_TID::Types::bool_;
    lhs.second = false;
  }
  return lhs;
}
std::pair<variables_TID::Types, bool> expression4_() {
  auto lhs = expression3_();
  while (global::lex.name == "<" || global::lex.name == ">" || global::lex.name == ">=" || global::lex.name == "<=") {
    getLex();
    auto rhs = expression3_();
    if(lhs.first != rhs.second){
      //TODO
      throw std::logic_error("different types in <");
    }
    lhs = {variables_TID::Types::bool_, false};
  }
  return lhs;
}
std::pair<variables_TID::Types, bool> expression3_() {
  auto lhs = expression2_();
  while (global::lex.name == "+" || global::lex.name == "-") {
    getLex();
    auto rhs = expression2_();
    if(lhs.first != rhs.first){
      //TODO
      throw std::logic_error("different types in +");
    }
    if (lhs.first != variables_TID::Types::int_ && lhs.first != variables_TID::Types::float_){
      //TODO
      throw std::logic_error("+ -overloaded only for int and float");
    }
    lhs = rhs;
    lhs.second = false;
  }
  return lhs;
}
std::pair<variables_TID::Types, bool> expression2_() {
  auto lhs = expression1_();
  while (global::lex.name == "*" || global::lex.name == "/" || global::lex.name == "%") {
    getLex();
    auto rhs = expression1_();
    if(lhs.first != rhs.first){
      //TODO
      throw std::logic_error("different types in +");
    }
    if (lhs.first != variables_TID::Types::int_ && lhs.first != variables_TID::Types::float_){
      //TODO
      throw std::logic_error("* / % overloaded only for int and float");
    }
    lhs = rhs;
    lhs.second = false;
  }
  return lhs;
}
std::pair<variables_TID::Types, bool> expression1_() {
  auto operat = global::lex;
  if (global::lex.name == "+" || global::lex.name == "-" || global::lex.name == "++" || global::lex.name == "--"
      || global::lex.name == "!") {
    getLex();
  }
  auto lhs = expression_cool_();
  if (operat.name == "+" || operat.name == "-") {
    if(lhs.first != variables_TID::Types::int_ && lhs.first != variables_TID::Types::float_){
      //TODO
      throw std::logic_error("unary + - overloaded only for int and float");
    }
    lhs.second = false;
    return lhs;
  } else if(operat.name == "++" || operat.name == "--"){
    if(lhs.first != variables_TID::Types::int_){
      //TODO
      throw std::logic_error("++ -- overloaded only for int");
    }
    if (!lhs.second){
      //TODO
      throw std::logic_error("++ -- overloaded only for lvalue int");
    }
    return lhs;
  } else if(operat.name == "!"){
    if(lhs.first != variables_TID::Types::bool_){
      //TODO
      throw std::logic_error("! overloaded only for bool");
    }
    lhs.second = false;
    return lhs;
  } else {
    return lhs;
  }
}
variables_TID::Types type_by_name(const std::string &type_name){
  if (type_name == "int"){
    return variables_TID::int_;
  } else if (type_name == "float"){
    return variables_TID::float_;
  } else if (type_name == "string"){
    return variables_TID::string_;
  } else if (type_name == "array"){
    return variables_TID::array_;
  } else if (type_name == "char"){
    return variables_TID::char_;
  } else if (type_name == "bool"){
    return variables_TID::bool_;
  } else {
    throw std::logic_error("unexpected type in type_by_name()");
  }
}
std::pair<variables_TID::Types, bool> expression_cool_() {
  if (global::lex.name == "true") {
    getLex();
    return {variables_TID::Types::bool_, false};
  } else if (global::lex.name == "false") {
    getLex();
    return {variables_TID::Types::bool_, false};
  } else if (global::lex.type == LexemeType::String_Literal) {
    getLex();
    return {variables_TID::Types::string_, false};
  } else if (global::lex.type == LexemeType::Literal) {
    getLex();
    return {variables_TID::Types::int_, false};
  } else if (global::lex.type == LexemeType::Identificator) {
    auto cur_lex = global::lex;
    identificator_();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      std::vector<std::string> args_types;
      //TODO написать, чтобы функция возвращала считанные аргументы
      function_call_();
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
      }
      return {type_by_name(global::function_table.check_id(cur_lex.name, args_types).type_of_return), false};
    } else {
      if (global::tree_of_variables.check_id(cur_lex.name) == variables_TID::Types::NULLTYPE){
        //TODO
        throw std::logic_error("No var in this scope");
      }
      return {global::tree_of_variables.check_id(cur_lex.name), true};
    }
  } else if (global::lex.type == LexemeType::Open_brace) {
    getLex();
    auto lhs = expression_();
    if (global::lex.type == LexemeType::Close_brace) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
    }
    return lhs;

  } else if (global::lex.type == LexemeType::Open_square_brace) {
    getLex();
    auto lhs = expression_();
    if (global::lex.type == LexemeType::Close_square_brace) {
      getLex();
    } else {
      throw SyntaxError((std::string("Expected ']' ") + std::to_string(global::lex.num + 1)));
    }
    return lhs;
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