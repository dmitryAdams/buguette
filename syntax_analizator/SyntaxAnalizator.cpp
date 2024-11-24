#include <algorithm>
#include "SyntaxAnalizator.h"
#include "./syntax_error/SyntaxError.h"
#include "../lib.h"
Types type_by_name(const std::string &type_name) {
  if (type_name == "int") {
    return Types::int_;
  } else if (type_name == "float") {
    return Types::float_;
  } else if (type_name == "string") {
    return Types::string_;
  } else if (type_name == "array") {
    return Types::array_;
  } else if (type_name == "char") {
    return Types::char_;
  } else if (type_name == "bool") {
    return Types::bool_;
  } else {
    auto tmp = "unexpected type in type_by_name()" + std::to_string(global::lex.num + 1);
    throw SyntaxError(tmp);
  }
}
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
    auto return_type = type_by_name(ret_type.name);
    global::stack_of_call.push_back({return_type, false});
    auto name = global::lex;
    identificator_();
    global::tree_of_variables.create_scope();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      std::vector<Type_> args_types;
      std::vector<std::string> args_names;
      if (global::lex.type != LexemeType::Close_brace) {
        auto cur_type = global::lex;
        args_types.push_back({type_by_name(cur_type.name), false});
        type_();
        auto cur_lex = global::lex;
        args_names.push_back(cur_lex.name);
        identificator_();
        global::tree_of_variables.push_id(cur_lex.name, cur_type.name);
      }
      while (global::lex.type == LexemeType::Comma) {
        getLex();
        auto cur_type = global::lex;
        args_types.push_back({type_by_name(cur_type.name), false});
        type_();
        auto cur_lex = global::lex;
        args_names.push_back(cur_lex.name);
        identificator_();
        global::tree_of_variables.push_id(cur_lex.name, cur_type.name);
      }
      if (global::lex.name == ")") {
        getLex();
        global::function_table.push_id(return_type, name.name, args_types, args_names);
        if (global::lex.name == "{") {
          getLex();
          block_();
          global::tree_of_variables.exit_scope();
          global::stack_of_call.pop_back();
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
    case LexemeType::Open_curly_brace:getLex();
      global::tree_of_variables.create_scope();
      block_();
      global::tree_of_variables.exit_scope();
      if (global::lex.type == LexemeType::Close_curly_brace) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected '}' ") + std::to_string(global::lex.num + 1)));
      }
      break;
    case LexemeType::Service_word:
      if (global::lex.name == "for") {
        global::opened_operators.insert("cycle");
        global::tree_of_variables.create_scope();
        for_();
        global::tree_of_variables.exit_scope();
        global::opened_operators.extract("cycle");
      } else if (global::lex.name == "while") {
        global::opened_operators.insert("cycle");
        global::tree_of_variables.create_scope();
        while_();
        global::tree_of_variables.exit_scope();
        global::opened_operators.extract("cycle");
      } else if (global::lex.name == "break") {
        if (global::opened_operators.find("cycle") == global::opened_operators.end()) {
          throw SyntaxError("'break' is not in cycle in line:" + std::to_string(global::lex.num + 1));
        }
        break_();
      } else if (global::lex.name == "continue") {
        if (global::opened_operators.find("cycle") == global::opened_operators.end()) {
          throw SyntaxError("'continue' is not in cycle in line:" + std::to_string(global::lex.num + 1));
        }
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
        if (global::stack_of_call.empty()) {
          throw SyntaxError("'return' is not in function in line: " + std::to_string(global::lex.num + 1));
        }
        auto ret_type = return_();
        if (ret_type.t != global::stack_of_call.back().t) {
          throw SyntaxError("'return' has wrong type in function in line: " + std::to_string(global::lex.num + 1));
        }
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
Type_ return_() {
  if (global::lex.name == "return") {
    getLex();
    auto ans = expression_();
    if (global::lex.type == LexemeType::Semicolon) {
      getLex();
      return ans;
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
      auto cur_id = global::lex;
      identificator_();
      global::tree_of_variables.push_id(cur_id.name, cur_type.name);
      if (global::lex.name == "="){
        getLex();
        auto rhs = expression9_();
        if (type_by_name(cur_type.name) != rhs.t){
          throw SyntaxError("Incorrect type in variable declaration in line: " + std::to_string(cur_id.num + 1));
        }
      }
      while (global::lex.type == LexemeType::Comma) {
        getLex();
        auto cur_id = global::lex;
        identificator_();
        global::tree_of_variables.push_id(cur_id.name, cur_type.name);
        if (global::lex.name == "="){
          getLex();
          auto rhs = expression9_();
          if (type_by_name(cur_type.name) != rhs.t){
            throw SyntaxError("Incorrect type in variable declaration in line: " + std::to_string(cur_id.num + 1));
          }
        }
//        auto cur_id = global::lex;
//        identificator_();
//        global::tree_of_variables.push_id(cur_id.name, cur_type.name);
//        if (global::lex.type == LexemeType::Comma) {
//          getLex();
//          continue;
//        } else if (global::lex.name == "=") {
//          getLex();
//          expression9_();
//          if (global::lex.type == LexemeType::Semicolon || global::lex.type == LexemeType::Comma) {
//            continue;
//          } else {
//            throw SyntaxError((std::string("Expected ';' ',' ") + std::to_string(global::lex.num + 1)));
//          }
//        } else if (global::lex.type != LexemeType::Semicolon) {
//          throw SyntaxError((std::string("Expected '=' or ',' ") + std::to_string(global::lex.num + 1)));
//        }
      }
    }
  } else {
    throw SyntaxError((std::string("Expected 'type' ") + std::to_string(global::lex.num + 1)));
  }
}
Type_ expression_() {
  return expression10_();
}
Type_ expression10_() {
  auto lhs = expression9_();
  while (global::lex.name == ",") {
    getLex();
    lhs = expression9_();
  }
  return lhs;
}
Type_ expression9_() {
  auto lhs = expression8_();
  while (global::lex.name == "=") {
    getLex();
    auto rhs = expression8_();
    if (!lhs.is_lvalue) {
      throw SyntaxError("not lvalue int lhs operator =  in line: " + std::to_string(global::lex.num + 1));
    } else if (lhs.t != rhs.t) {
      throw SyntaxError("different types in operator =  in line: " + std::to_string(global::lex.num + 1));
    }
    lhs = rhs;
  }
  return lhs;
}
Type_ expression8_() {
  auto lhs = expression7_();
  while (global::lex.name == "|") {
    getLex();
    auto rhs = expression7_();
    if (lhs.t != Types::bool_) {

      throw SyntaxError("left operand not bool  in line: " + std::to_string(global::lex.num + 1));
    } else if (rhs.t != Types::bool_) {

      throw SyntaxError("right operand not bool  in line: " + std::to_string(global::lex.num + 1));
    }
    lhs = rhs;
    lhs.is_lvalue = false;
  }
  return lhs;
}
Type_ expression7_() {
  auto lhs = expression6_();
  while (global::lex.name == "^") {
    getLex();
    auto rhs = expression6_();
    if (lhs.t != Types::bool_) {

      throw SyntaxError("left operand not bool  in line: " + std::to_string(global::lex.num + 1));
    } else if (rhs.t != Types::bool_) {

      throw SyntaxError("right operand not bool  in line: " + std::to_string(global::lex.num + 1));
    }
    lhs = rhs;
    lhs.is_lvalue = false;
  }
  return lhs;
}
Type_ expression6_() {
  auto lhs = expression5_();
  while (global::lex.name == "&") {
    getLex();
    auto rhs = expression5_();
    if (lhs.t != Types::bool_) {

      throw SyntaxError("left operand not bool  in line: " + std::to_string(global::lex.num + 1));
    } else if (rhs.t != Types::bool_) {

      throw SyntaxError("right operand not bool  in line: " + std::to_string(global::lex.num + 1));
    }
    lhs = rhs;
    lhs.is_lvalue = false;
  }
  return lhs;
}
Type_ expression5_() {
  auto lhs = expression4_();
  while (global::lex.name == "==" || global::lex.name == "!=") {
    getLex();
    auto rhs = expression4_();
    if (lhs.t != rhs.t) {

      throw SyntaxError("different types in ==  in line: " + std::to_string(global::lex.num + 1));
    }
    lhs.t = Types::bool_;
    lhs.is_lvalue = false;
  }
  return lhs;
}
Type_ expression4_() {
  auto lhs = expression3_();
  while (global::lex.name == "<" || global::lex.name == ">" || global::lex.name == ">=" || global::lex.name == "<=") {
    getLex();
    auto rhs = expression3_();
    if (lhs.t != rhs.t) {

      throw SyntaxError("different types in <  in line: " + std::to_string(global::lex.num + 1));
    }
    lhs = {Types::bool_, false};
  }
  return lhs;
}
Type_ expression3_() {
  auto lhs = expression2_();
  while (global::lex.name == "+" || global::lex.name == "-") {
    bool is_plus = global::lex.name == "+";
    getLex();
    auto rhs = expression2_();
    if (is_plus && lhs.t == Types::string_ && rhs.t == Types::string_) {
      lhs.is_lvalue = false;
      continue;
    }
//    if (lhs.t != rhs.t) {
//
//      throw SyntaxError("different types in +  in line: " + std::to_string(global::lex.num + 1));
//    }
    if ((lhs.t != Types::int_ && lhs.t != Types::float_) || (rhs.t != Types::int_ && rhs.t != Types::float_)) {
      throw SyntaxError("'-' overloaded only for int and float  in line: " + std::to_string(global::lex.num + 1));
    }
    if (lhs.t != Types::float_)lhs = rhs;
    lhs.is_lvalue = false;
  }
  return lhs;
}
Type_ expression2_() {
  auto lhs = expression1_();
  while (global::lex.name == "*" || global::lex.name == "/" || global::lex.name == "%") {
    getLex();
    auto rhs = expression1_();
//    if (lhs.t != rhs.t) {
//
//      throw SyntaxError("different types in +  in line: " + std::to_string(global::lex.num + 1));
//    }
    if ((lhs.t != Types::int_ && lhs.t != Types::float_) || (rhs.t != Types::int_ && rhs.t != Types::float_)) {
      throw SyntaxError("* / % overloaded only for int and float  in line: " + std::to_string(global::lex.num + 1));
    }

    if (lhs.t != Types::float_)lhs = rhs;
    lhs.is_lvalue = false;
  }
  return lhs;
}
Type_ expression1_() {
//  auto operat = global::lex;
  std::vector<lexeme> unary_operators;
  while (global::lex.name == "+" || global::lex.name == "-" || global::lex.name == "++" || global::lex.name == "--"
      || global::lex.name == "!") {
    unary_operators.push_back(global::lex);
    getLex();
  }
  auto lhs = expression0_();
  while (!unary_operators.empty()) {
    auto operat = unary_operators.back();
    if (operat.name == "+" || operat.name == "-") {
      if (lhs.t != Types::int_ && lhs.t != Types::float_) {

        throw SyntaxError(
            "unary + - overloaded only for int and float  in line: " + std::to_string(global::lex.num + 1));
      }
      lhs.is_lvalue = false;
//    return lhs;
    } else if (operat.name == "++" || operat.name == "--") {
      if (lhs.t != Types::int_ && lhs.t != Types::float_) {

        throw SyntaxError("++ -- overloaded only for int  in line: " + std::to_string(global::lex.num + 1));
      }
      if (!lhs.is_lvalue) {
        throw SyntaxError(
            "++ -- overloaded only for lvalue int or float in line: " + std::to_string(global::lex.num + 1));
      }
//    return lhs;
    } else if (operat.name == "!") {
      if (lhs.t != Types::bool_) {
        throw SyntaxError(
            "! overloaded only for bool" + std::string(" in line: ") + std::to_string(global::lex.num + 1));
      }
      lhs.is_lvalue = false;
//    return lhs;
    } else {
//    return lhs;
    }
    unary_operators.pop_back();
  }
  return lhs;
//  if (operat.name == "+" || operat.name == "-") {
//    if (lhs.t != Types::int_ && lhs.t != Types::float_) {
//
//      throw SyntaxError("unary + - overloaded only for int and float  in line: " + std::to_string(global::lex.num + 1));
//    }
//    lhs.is_lvalue = false;
//    return lhs;
//  } else if (operat.name == "++" || operat.name == "--") {
//    if (lhs.t != Types::int_) {
//
//      throw SyntaxError("++ -- overloaded only for int  in line: " + std::to_string(global::lex.num + 1));
//    }
//    if (!lhs.is_lvalue) {
//      throw SyntaxError("++ -- overloaded only for lvalue int  in line: " + std::to_string(global::lex.num + 1));
//    }
//    return lhs;
//  } else if (operat.name == "!") {
//    if (lhs.t != Types::bool_) {
//
//      throw SyntaxError("! overloaded only for bool" +std::string(" in line: ") + std::to_string(global::lex.num + 1));
//    }
//    lhs.is_lvalue = false;
//    return lhs;
//  } else {
//    return lhs;
//  }
}

Type_ expression0_() {
  auto lhs = expression_cool_();
  if (global::lex.type == LexemeType::Open_square_brace){
    if (lhs.t != Types::array_){
      throw SyntaxError("Indexation is only for arrays in line: " + std::to_string(global::lex.num + 1));
    }
    getLex();
    auto ind = expression_();
    if (ind.t != Types::int_){
      throw SyntaxError("Index is only int, in line: " + std::to_string(global::lex.num + 1));
    }
    if (global::lex.type != LexemeType::Close_square_brace){
      throw SyntaxError("Expected ']' in line: " + std::to_string(global::lex.num + 1));
    }
    getLex();
    Type_ return_type = {Types::int_, false};
    return_type.is_lvalue = lhs.is_lvalue;
    return return_type;
  }
  return lhs;
}

Type_ expression_cool_() {
  if (global::lex.name == "true") {
    getLex();
    return {Types::bool_, false};
  } else if (global::lex.name == "false") {
    getLex();
    return {Types::bool_, false};
  } else if (global::lex.type == LexemeType::String_Literal) {
    getLex();
    return {Types::string_, false};
  } else if (global::lex.type == LexemeType::Literal) {
    auto tp = Types::int_;
    if (std::count(global::lex.name.begin(), global::lex.name.end(), '.')) {
      tp = Types::float_;
    }
    getLex();
    return {tp, false};
  } else if (global::lex.type == LexemeType::Identificator) {
    auto cur_lex = global::lex;
    identificator_();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      std::vector<Type_> args_types = function_call_();
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
      }
      return {global::function_table.check_id(cur_lex.name, args_types).type_of_return, false};
    }/* else if (global::lex.type == LexemeType::Open_square_brace) {
      if (global::tree_of_variables.check_id(cur_lex.name) != Types::array_) {
        throw SyntaxError(cur_lex.name + "aren't an array in line: " + std::to_string(cur_lex.num + 1));
      }
      getLex();
      auto ans = expression_();
      if (global::lex.type != LexemeType::Close_square_brace) {
        throw SyntaxError("Expected '] in line: " + std::to_string(global::lex.num + 1));
      }
      getLex();
      return {Types::int_, true};
    } */
    else {
      if (global::tree_of_variables.check_id(cur_lex.name) == Types::NULLTYPE) {
        throw SyntaxError("No var " + cur_lex.name + " in this scope" + std::string(" in line: ")
                              + std::to_string(global::lex.num + 1));
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
    //TODO возможно экспрешены не ловят ошибки
//    throw SyntaxError((std::string("Expected identificator, literal, braces or function call or some another primitive ")
//        + std::to_string(global::lex.num + 1)));
    return expression_();
//    throw SyntaxError((std::string("Expected 'expression' ") + std::to_string(global::lex.num + 1)));
  }
}
std::vector<Type_> function_call_() {
  std::vector<Type_> args_types;
  while (global::lex.type != LexemeType::Close_brace) {
    args_types.push_back(expression9_());
    if (global::lex.type == LexemeType::Comma) {
      getLex();
    } else if (global::lex.type != LexemeType::Close_brace) {
      throw SyntaxError((std::string("Expected ',' or ')' ") + std::to_string(global::lex.num + 1)));
    }
  }
  return args_types;
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