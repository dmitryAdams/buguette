
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
//  if (t == Type_) return "Type_";
//  if (t == Literal) return "Literal";
//  if (t == Operator) return "Operator";
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

int main() {
  float a = 0;
  ++a;
//  try{
    starter();
    program_();
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

