#include "globalVariables.h"
#include "starter.h"
#include "lexer/lexer.h"
#include "iostream"
//
//std::string enum_string(LexemeType t) {
//  if (t == LexemeType::Close_brace) return "Close_brace";
//  if (t == NULLLEXEME) return "NULLLEXEME";
//  if (t == Identificator) return "Identificator";
//  if (t == Service_word) return "Service_word";
//  if (t == Expression_Type) return "Expression_Type";
//  if (t == Literal) return "Literal";
//  if (t == PolizOperator) return "PolizOperator";
//  if (t == Comma) return "Comma";
//  if (t == Semicolon) return "Semicolon";
//  if (t == Open_brace) return "Open_brace";
//  if (t == Open_curly_brace) return "Open_curly_brace";
//  if (t == Close_curly_brace) return "Close_curly_brace";
//  if (t == Other) return "Other";
//  if (t == String_Literal) return "String_Literal";
//}
#include "./syntax_analizator/SyntaxAnalizator.h"
#include "./syntax_analizator/syntax_error/SyntaxError.h"
#include "./semantic_analizator/SemanticError/SemanticError.h"
#include "Generation/Operator/PolizOperator.h"
#include "Generation/Operand/PolizOperand.h"
#include "run/run.h"

int main() {
#ifdef _GLIBCXX_DEBUG
  std::cerr << "_GLIBCXX_DEBUG" << std::endl;
#endif
  try {
    starter();
    program_();
//    int j = 0;
//    for(auto i : global::poliz_stack){
//        if (i->is_operator()) {
//            auto p = dynamic_cast<PolizOperator*>(i);
//            if (!p->function.name.empty()) {
//                std::cout << j << ") " << p->function.name << '\n';
//                ++j;
//                continue;
//            }
//        }
//      std::cout << j << ") " << *i << '\n';
//      ++j;
//    }
  }
  catch (SyntaxError &e) {
    std::cout << e.what() << '\n';
  } catch (SemanticError &e) {
    std::cout << e.what() << '\n';
  }
  std::map<std::pair<K_Variable_Type, std::vector<void *> *>, bool> init;
  for (auto &[i, j] : global::tree_of_variables.cur->tid.tid) {
    init[j] = true;
  }
  run(global::start_pos_on_poliz, init);
  for (auto &[i, j] : init) {
    if (i.first == K_Variable_Type_Int) {
      delete (int *) (i.second->back());
    } else if (i.first == K_Variable_Type_Bool) {
      delete (bool *) (i.second->back());
    } else if (i.first == K_Variable_Type_Float) {
      delete (double *) (i.second->back());
    } else if (i.first == K_Variable_Type_Char) {
      delete (char *) (i.second->back());
    } else if (i.first == K_Variable_Type_String) {
      delete (std::string *) (i.second->back());
    } else if (i.first == K_Variable_Type_Array) {
      delete (std::vector<int> *) (i.second->back());
    }
    i.second->pop_back();
  }
  return 0;
}

