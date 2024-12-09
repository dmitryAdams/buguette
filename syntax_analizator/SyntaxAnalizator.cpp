#include <algorithm>
#include "SyntaxAnalizator.h"
#include "./syntax_error/SyntaxError.h"
#include "../lib.h"
#include "../Generation/Operator/PolizOperator.h"
#include "../Generation/Operand/PolizOperand.h"
K_Variable_Type type_by_name(const std::string &type_name) {
  if (type_name == "int") {
    return K_Variable_Type::K_Variable_Type_Int;
  } else if (type_name == "float") {
    return K_Variable_Type::K_Variable_Type_Float;
  } else if (type_name == "string") {
    return K_Variable_Type::K_Variable_Type_String;
  } else if (type_name == "array") {
    return K_Variable_Type::K_Variable_Type_Array;
  } else if (type_name == "char") {
    return K_Variable_Type::K_Variable_Type_Char;
  } else if (type_name == "bool") {
    return K_Variable_Type::K_Variable_Type_Bool;
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
      std::vector<Expression_Type> args_types;
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
//        global::opened_operators.insert("cycle");
        global::tree_of_variables.create_scope();
        for_();
        global::tree_of_variables.exit_scope();
//        global::opened_operators.extract("cycle");
      } else if (global::lex.name == "while") {
//        global::opened_operators.insert("cycle");
        global::tree_of_variables.create_scope();
        while_();
        global::tree_of_variables.exit_scope();
//        global::opened_operators.extract("cycle");
      } else if (global::lex.name == "break") {
//        if (global::opened_operators.find("cycle") == global::opened_operators.end()) {
//          throw SyntaxError("'break' is not in cycle in line:" + std::to_string(global::lex.num + 1));
//        }
        break_();
      } else if (global::lex.name == "continue") {
//        if (global::opened_operators.find("cycle") == global::opened_operators.end()) {
//          throw SyntaxError("'continue' is not in cycle in line:" + std::to_string(global::lex.num + 1));
//        }
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
Expression_Type return_() {
  if (global::lex.name == "return") {
    getLex();
    auto ans = expression_();
    global::poliz_stack.pop_back();
    global::poliz_stack.push_back(new PolizOperator("ret", true));
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
      global::poliz_stack.pop_back();
      int addr1 = global::poliz_stack.size();
      global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Int, nullptr));
      global::poliz_stack.push_back(new PolizOperator("F"));
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
        operator_();
        int addr2 = global::poliz_stack.size();
        global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Int, nullptr));
        global::poliz_stack.push_back(new PolizOperator("Go", true));
        global::poliz_stack[addr1]->upd(new int (global::poliz_stack.size()));
        if (global::lex.name == "else") {
          getLex();
          operator_();
        }
        global::poliz_stack[addr2]->upd(new int(global::poliz_stack.size()));
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
    global::break_stack.emplace_back();
    global::continue_stack.emplace_back();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      variables_declaration_();
      if (global::lex.type == LexemeType::Semicolon) {
        getLex();
        int expression_addr = global::poliz_stack.size();
        expression_();
        global::poliz_stack.pop_back();
        //Сюда положим конец for'a
        int addr1 = global::poliz_stack.size();
        global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Int, nullptr));
        global::poliz_stack.push_back(new PolizOperator("F"));
        //Сюда положим начало тела цикла
        int addr2 = global::poliz_stack.size();
        global::poliz_stack.push_back( new PolizOperand(K_Variable_Type_Int, nullptr));
        global::poliz_stack.push_back(new PolizOperator("Go", true));
        if (global::lex.type == LexemeType::Semicolon) {
          int step_expr_addr = global::poliz_stack.size();
          getLex();
          expression_();
          global::poliz_stack.pop_back();
          global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Int, new int(expression_addr)));
          global::poliz_stack.push_back((new PolizOperator("Go", true)));
          //ПЕРЕХОД В ТЕЛО
          global::poliz_stack[addr2]->upd(new int(global::poliz_stack.size()));
          if (global::lex.type == LexemeType::Close_brace) {
            getLex();
            operator_();
            global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Int, new int(step_expr_addr)));
            global::poliz_stack.push_back(new PolizOperator("Go", true));
            global::poliz_stack[addr1]->upd(new int(global::poliz_stack.size()));
            for(auto i : global::break_stack.back()){
              global::poliz_stack[i]->upd(new int(global::poliz_stack.size()));
            }
            global::break_stack.pop_back();
            for(auto i : global::continue_stack.back()){
              global::poliz_stack[i]->upd(new int(step_expr_addr));
            }
            global::continue_stack.pop_back();
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
    global::break_stack.emplace_back();
    global::continue_stack.emplace_back();
    if (global::lex.type == LexemeType::Open_brace) {
      int expr_address = global::poliz_stack.size();
      getLex();
      expression_();
      global::poliz_stack.pop_back();
      int addr1 = global::poliz_stack.size();
      global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Int, nullptr));
      global::poliz_stack.push_back(new PolizOperator("F"));
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
        operator_();
        global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Int, new int(expr_address)));
        global::poliz_stack.push_back(new PolizOperator("Go", true));
        global::poliz_stack[addr1]->upd(new int(global::poliz_stack.size()));
        for(auto i : global::break_stack.back()){
          global::poliz_stack[i]->upd(new int(global::poliz_stack.size()));
        }
        global::break_stack.pop_back();
        for(auto i : global::continue_stack.back()){
          global::poliz_stack[i]->upd(new int(expr_address));
        }
        global::continue_stack.pop_back();
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
    global::break_stack.emplace_back();
    getLex();
    if (global::lex.type == LexemeType::Open_brace) {
      getLex();
      auto lhs = global::poliz_stack.size();
      auto tp = expression_();
      std::vector<StackElement*> expr;

      while(global::poliz_stack.size() > lhs) {
          expr.push_back(global::poliz_stack.back());
          global::poliz_stack.pop_back();
      }
      std::reverse(expr.begin(), expr.end());
      expr.pop_back();

      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
        if (global::lex.type == LexemeType::Open_curly_brace) {
          getLex();
          int cnt = 0;
          std::vector<std::pair<PolizOperand*, int>> cases;
          while (global::lex.name == "case") {
            getLex();
            if (global::lex.type == LexemeType::Open_brace) {
              getLex();
              if (global::lex.type == LexemeType::Literal || global::lex.type == LexemeType::String_Literal) {
                if (global::lex.type == LexemeType::Literal &&
                  (tp.t == K_Variable_Type_Int || tp.t == K_Variable_Type_Float)
                  || global::lex.type == LexemeType::String_Literal &&
                  (tp.t == K_Variable_Type_String)) {
                    if (tp.t == K_Variable_Type_Float) {
                        cases.emplace_back(
                                new PolizOperand(K_Variable_Type_Float,
                                new double(std::stod(global::lex.name))),
                                global::poliz_stack.size());
                    } else {
                        cases.emplace_back(
                                new PolizOperand(K_Variable_Type_Int,
                                new int(std::stoi(global::lex.name))),
                                global::poliz_stack.size());
                    }

                    getLex();
                    if (global::lex.type == LexemeType::Close_brace) {
                      getLex();
                      operator_();
                    } else {
                        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
                    }
                  } else {
                      throw SemanticError(std::string("Type expression must be type of case in line: "
                      + std::to_string(global::lex.num + 1)));
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
            int adrEnd = global::poliz_stack.size();
            global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Int, nullptr));
            global::poliz_stack.push_back(new PolizOperator("Go", true));
            for (auto& [op, adr] : cases) {
                for (auto& to : expr) {
                    global::poliz_stack.push_back(to);
                }
                global::poliz_stack.push_back(op);
                global::poliz_stack.push_back(new PolizOperator("!="));
                global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Int, new int(adr)));
                global::poliz_stack.push_back(new PolizOperator("F"));
            }
            dynamic_cast<PolizOperand*>(global::poliz_stack[adrEnd])->upd(new int(global::poliz_stack.size()));
            for (auto& to : global::break_stack.back()) {
                dynamic_cast<PolizOperand*>(global::poliz_stack[to])->upd(new int(global::poliz_stack.size()));
            }
            global::break_stack.pop_back();
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
      //TODO написать хуйню для массивов
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
        cur_lex = global::lex;
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
      }
    } else {
      auto cur_type = global::lex;
      getLex();
      auto cur_id = global::lex;
      identificator_();
      global::tree_of_variables.push_id(cur_id.name, cur_type.name);
      global::poliz_stack.push_back(new PolizOperand(global::tree_of_variables.check_id(cur_id.name),
                                                     global::tree_of_variables.getAdress(cur_id.name)));
      if (global::lex.name == "=") {
        getLex();
        auto rhs = expression9_();
        global::poliz_stack.push_back(new PolizOperator("="));
        if (type_by_name(cur_type.name) != rhs.t) {
          throw SyntaxError("Incorrect type in variable declaration in line: " + std::to_string(cur_id.num + 1));
        }
      }
      global::poliz_stack.push_back(new PolizOperator(";", true));
      while (global::lex.type == LexemeType::Comma) {
        getLex();
        cur_id = global::lex;
        identificator_();
        global::tree_of_variables.push_id(cur_id.name, cur_type.name);
        global::poliz_stack.push_back(new PolizOperand(global::tree_of_variables.check_id(cur_id.name),
                                                       global::tree_of_variables.getAdress(cur_id.name)));
        if (global::lex.name == "=") {
          getLex();
          auto rhs = expression9_();
          global::poliz_stack.push_back(new PolizOperator("="));
          if (type_by_name(cur_type.name) != rhs.t) {
            throw SyntaxError("Incorrect type in variable declaration in line: " + std::to_string(cur_id.num + 1));
          }
        }
        global::poliz_stack.push_back(new PolizOperator(";", true));
      }
    }
  } else {
    throw SyntaxError((std::string("Expected 'type' ") + std::to_string(global::lex.num + 1)));
  }
}
Expression_Type expression_() {
  auto ans =  expression10_();
  global::poliz_stack.push_back(new PolizOperator(";", true));
  return ans;
}
Expression_Type expression10_() {
  auto lhs = expression9_();
  while (global::lex.name == ",") {
    auto cur_id = global::lex.name;
    getLex();
    lhs = expression9_();
    global::poliz_stack.push_back(new PolizOperator(cur_id));

  }
  return lhs;
}
Expression_Type expression9_() {
  auto lhs = expression8_();
  while (global::lex.name == "=") {
    auto cur_id = global::lex.name;
    getLex();
    auto rhs = expression8_();
    if (!lhs.is_lvalue) {
      throw SyntaxError("not lvalue int lhs operator =  in line: " + std::to_string(global::lex.num + 1));
    } else if (lhs.t != rhs.t) {
      throw SyntaxError("different types in operator =  in line: " + std::to_string(global::lex.num + 1));
    }
    lhs = rhs;
    global::poliz_stack.push_back(new PolizOperator(cur_id));

  }
  return lhs;
}
Expression_Type expression8_() {
  auto lhs = expression7_();
  while (global::lex.name == "|") {
    auto cur_id = global::lex.name;
    getLex();
    auto rhs = expression7_();
    if (lhs.t != K_Variable_Type::K_Variable_Type_Bool) {

      throw SyntaxError("left operand not bool  in line: " + std::to_string(global::lex.num + 1));
    } else if (rhs.t != K_Variable_Type::K_Variable_Type_Bool) {

      throw SyntaxError("right operand not bool  in line: " + std::to_string(global::lex.num + 1));
    }
    lhs = rhs;
    lhs.is_lvalue = false;
    global::poliz_stack.push_back(new PolizOperator(cur_id));

  }
  return lhs;
}
Expression_Type expression7_() {
  auto lhs = expression6_();
  while (global::lex.name == "^") {
    auto cur_id = global::lex.name;
    getLex();
    auto rhs = expression6_();
    if (lhs.t != K_Variable_Type::K_Variable_Type_Bool) {

      throw SyntaxError("left operand not bool  in line: " + std::to_string(global::lex.num + 1));
    } else if (rhs.t != K_Variable_Type::K_Variable_Type_Bool) {

      throw SyntaxError("right operand not bool  in line: " + std::to_string(global::lex.num + 1));
    }
    lhs = rhs;
    lhs.is_lvalue = false;
    global::poliz_stack.push_back(new PolizOperator(cur_id));

  }
  return lhs;
}
Expression_Type expression6_() {
  auto lhs = expression5_();
  while (global::lex.name == "&") {
    auto cur_id = global::lex.name;
    getLex();
    auto rhs = expression5_();
    if (lhs.t != K_Variable_Type::K_Variable_Type_Bool) {

      throw SyntaxError("left operand not bool  in line: " + std::to_string(global::lex.num + 1));
    } else if (rhs.t != K_Variable_Type::K_Variable_Type_Bool) {

      throw SyntaxError("right operand not bool  in line: " + std::to_string(global::lex.num + 1));
    }
    lhs = rhs;
    lhs.is_lvalue = false;
    global::poliz_stack.push_back(new PolizOperator(cur_id));

  }
  return lhs;
}
Expression_Type expression5_() {
  auto lhs = expression4_();
  while (global::lex.name == "==" || global::lex.name == "!=") {
    auto cur_id = global::lex.name;
    getLex();
    auto rhs = expression4_();
    if (lhs.t != rhs.t) {

      throw SyntaxError("different types in ==  in line: " + std::to_string(global::lex.num + 1));
    }
    lhs.t = K_Variable_Type::K_Variable_Type_Bool;
    lhs.is_lvalue = false;
    global::poliz_stack.push_back(new PolizOperator(cur_id));

  }
  return lhs;
}
Expression_Type expression4_() {
  auto lhs = expression3_();
  while (global::lex.name == "<" || global::lex.name == ">" || global::lex.name == ">=" || global::lex.name == "<=") {
    auto cur_id = global::lex.name;
    getLex();
    auto rhs = expression3_();
    if (lhs.t != rhs.t) {

      throw SyntaxError("different types in <  in line: " + std::to_string(global::lex.num + 1));
    }
    lhs = {K_Variable_Type::K_Variable_Type_Bool, false};
    global::poliz_stack.push_back(new PolizOperator(cur_id));

  }
  return lhs;
}
Expression_Type expression3_() {
  auto lhs = expression2_();
  while (global::lex.name == "+" || global::lex.name == "-") {
    bool is_plus = global::lex.name == "+";
    auto cur_id = global::lex.name;
    getLex();
    auto rhs = expression2_();
    if (is_plus && lhs.t == K_Variable_Type::K_Variable_Type_String
        && rhs.t == K_Variable_Type::K_Variable_Type_String) {
      lhs.is_lvalue = false;
    } else if ((lhs.t != K_Variable_Type::K_Variable_Type_Int && lhs.t != K_Variable_Type::K_Variable_Type_Float)
        || (rhs.t != K_Variable_Type::K_Variable_Type_Int && rhs.t != K_Variable_Type::K_Variable_Type_Float)) {
      throw SyntaxError("'-' overloaded only for int and float  in line: " + std::to_string(global::lex.num + 1));
    }
    global::poliz_stack.push_back(new PolizOperator(cur_id));
    if (lhs.t != K_Variable_Type::K_Variable_Type_Float)lhs = rhs;
    lhs.is_lvalue = false;
  }
  return lhs;
}
Expression_Type expression2_() {
  auto lhs = expression1_();
  while (global::lex.name == "*" || global::lex.name == "/" || global::lex.name == "%") {
    auto cur_id = global::lex.name;
    getLex();
    auto rhs = expression1_();
    if ((lhs.t != K_Variable_Type::K_Variable_Type_Int && lhs.t != K_Variable_Type::K_Variable_Type_Float)
        || (rhs.t != K_Variable_Type::K_Variable_Type_Int && rhs.t != K_Variable_Type::K_Variable_Type_Float)) {
      throw SyntaxError("* / % overloaded only for int and float  in line: " + std::to_string(global::lex.num + 1));
    }
    global::poliz_stack.push_back(new PolizOperator(cur_id));
    if (lhs.t != K_Variable_Type::K_Variable_Type_Float)lhs = rhs;
    lhs.is_lvalue = false;
  }
  return lhs;
}
Expression_Type expression1_() {
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
      if (lhs.t != K_Variable_Type::K_Variable_Type_Int && lhs.t != K_Variable_Type::K_Variable_Type_Float) {

        throw SyntaxError(
            "unary + - overloaded only for int and float  in line: " + std::to_string(global::lex.num + 1));
      }
      lhs.is_lvalue = false;
    } else if (operat.name == "++" || operat.name == "--") {
      if (lhs.t != K_Variable_Type::K_Variable_Type_Int && lhs.t != K_Variable_Type::K_Variable_Type_Float) {

        throw SyntaxError("++ -- overloaded only for int  in line: " + std::to_string(global::lex.num + 1));
      }
      if (!lhs.is_lvalue) {
        throw SyntaxError(
            "++ -- overloaded only for lvalue int or float in line: " + std::to_string(global::lex.num + 1));
      }
    } else if (operat.name == "!") {
      if (lhs.t != K_Variable_Type::K_Variable_Type_Bool) {
        throw SyntaxError(
            "! overloaded only for bool" + std::string(" in line: ") + std::to_string(global::lex.num + 1));
      }
      lhs.is_lvalue = false;
    }
    global::poliz_stack.push_back(new PolizOperator(unary_operators.back().name, true));
    unary_operators.pop_back();
  }
  return lhs;
}

Expression_Type expression0_() {
  auto lhs = expression_cool_();
  if (global::lex.type == LexemeType::Open_square_brace) {
    if (lhs.t != K_Variable_Type::K_Variable_Type_Array) {
      throw SyntaxError("Indexation is only for arrays in line: " + std::to_string(global::lex.num + 1));
    }
    getLex();
    auto ind = expression_();
    if (ind.t != K_Variable_Type::K_Variable_Type_Int) {
      throw SyntaxError("Index is only int, in line: " + std::to_string(global::lex.num + 1));
    }
    if (global::lex.type != LexemeType::Close_square_brace) {
      throw SyntaxError("Expected ']' in line: " + std::to_string(global::lex.num + 1));
    }
    getLex();
    Expression_Type return_type = {K_Variable_Type::K_Variable_Type_Int, false};
    return_type.is_lvalue = lhs.is_lvalue;
    global::poliz_stack.push_back(new PolizOperator("["));
    return return_type;
  }
  return lhs;
}

Expression_Type expression_cool_() {
  if (global::lex.name == "true") {
    getLex();
    global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Bool, (void *) (new bool(true))));
    return {K_Variable_Type::K_Variable_Type_Bool, false};
  } else if (global::lex.name == "false") {
    getLex();
    global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Bool, (void *) (new bool(false))));
    return {K_Variable_Type::K_Variable_Type_Bool, false};
  } else if (global::lex.type == LexemeType::String_Literal) {
    global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_String,
                                                   (void *) (new std::string(global::lex.name))));
    getLex();
    return {K_Variable_Type::K_Variable_Type_String, false};
  } else if (global::lex.type == LexemeType::Literal) {
    auto tp = K_Variable_Type::K_Variable_Type_Int;
    if (std::count(global::lex.name.begin(), global::lex.name.end(), '.')) {
      tp = K_Variable_Type::K_Variable_Type_Float;
      global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Float,
                                                     (void *) (new double(std::stod(global::lex.name)))));
    } else {
      global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Int,
                                                     (void *) (new int(std::stoi(global::lex.name)))));
    }
    getLex();
    return {tp, false};
  } else if (global::lex.type == LexemeType::Identificator) {
    auto cur_id = global::lex;
    identificator_();
    if (global::lex.type == LexemeType::Open_brace) {
      //TODO НАПИСАТЬ ОПЕРАТОР ФУНКЦИИ И ДОБАВЛЯТЬ ЕЕ В ПОЛИЗ
      getLex();
      std::vector<Expression_Type> args_types = function_call_();
      if (global::lex.type == LexemeType::Close_brace) {
        getLex();
      } else {
        throw SyntaxError((std::string("Expected ')' ") + std::to_string(global::lex.num + 1)));
      }
      auto cur_func = global::function_table.check_id(cur_id.name, args_types);
      global::poliz_stack.push_back(new PolizOperator("func"));
      dynamic_cast<PolizOperator*>(global::poliz_stack.back())->function = {cur_id.name, args_types};
      return {cur_func.type_of_return, false};
    } else {
      if (global::tree_of_variables.check_id(cur_id.name) == K_Variable_Type::K_Variable_Type_NULLTYPE) {
        throw SyntaxError("No var " + cur_id.name + " in this scope" + std::string(" in line: ")
                              + std::to_string(global::lex.num + 1));
      }
      global::poliz_stack.push_back(new PolizOperand(global::tree_of_variables.check_id(cur_id.name),
                                                     global::tree_of_variables.getAdress(cur_id.name)));
      return {global::tree_of_variables.check_id(cur_id.name), true};
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

  } else {
    //TODO возможно экспрешены не ловят ошибки
    throw SyntaxError((std::string("Expected identificator, literal, braces or function call or some another primitive ")
        + std::to_string(global::lex.num + 1)));
//    return expression_();
//    throw SyntaxError((std::string("Expected 'expression' ") + std::to_string(global::lex.num + 1)));
  }
}
std::vector<Expression_Type> function_call_() {
  std::vector<Expression_Type> args_types;
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
    if (global::break_stack.empty()){
      throw SyntaxError("Break is not in cycle or switch in line: " + std::to_string(global::lex.num + 1));
    }
    getLex();
    if (global::lex.type == LexemeType::Semicolon) {
      getLex();
      global::break_stack.back().push_back(global::poliz_stack.size());
      global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Int, nullptr));
      global::poliz_stack.push_back(new PolizOperator("Go", true));
    } else {
      throw SyntaxError((std::string("Expected ';' ") + std::to_string(global::lex.num + 1)));
    }
  } else {
    throw SyntaxError((std::string("Expected 'break' ") + std::to_string(global::lex.num + 1)));
  }
}
void continue_() {
  if (global::lex.name == "continue") {
    if (global::continue_stack.empty()){
      throw SyntaxError("Continue is not in cycle or switch in line: " + std::to_string(global::lex.num + 1));
    }
    getLex();
    if (global::lex.type == LexemeType::Semicolon) {
      getLex();
      global::continue_stack.back().push_back(global::poliz_stack.size());
      global::poliz_stack.push_back(new PolizOperand(K_Variable_Type_Int, nullptr));
      global::poliz_stack.push_back(new PolizOperator("Go", true));
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
      global::poliz_stack.pop_back();
      global::poliz_stack.push_back(new PolizOperator("Prn", true));
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
      auto arg = expression_();
      if (!arg.is_lvalue) {
          throw SemanticError((std::string("operator scan is only for l_value") + std::to_string(global::lex.num + 1)));
      }
      global::poliz_stack.pop_back();
      global::poliz_stack.push_back(new PolizOperator("Scn", true));
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