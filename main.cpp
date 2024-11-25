
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
int main() {
//  try{
    starter();
    program_();
    for(auto i : global::poliz_stack){
      if (i->is_operator()){
        auto p = dynamic_cast<PolizOperator*>(i);
        std::cerr << "aboba";
      } else {
        auto p = dynamic_cast<PolizOperand*>(i);
        std::cerr << "aboba";
      }
    }
//  }
//  catch (SyntaxError &e){
//    std::cout << e.what() << '\n';
//  }catch (SemanticError &e){
//    std::cout << e.what() << '\n';
//  }
//  auto c = 'ok';
//  std::cout << typeid(c).name() << ' ' << c <<  ' ' << (int)'o';
  return 0;
}

