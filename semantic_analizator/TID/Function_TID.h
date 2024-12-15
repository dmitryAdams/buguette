//
// Created by adams on 11/13/24.
//

#ifndef BUGGUETTE_SEMANTIC_ANALIZATOR_TID_FUNCTION_TID_H_
#define BUGGUETTE_SEMANTIC_ANALIZATOR_TID_FUNCTION_TID_H_
#include "../../lib.h"
#include "../SemanticError/SemanticError.h"
struct FunctionKey {
  std::string name;
  std::vector<Expression_Type> types_of_args;
  friend bool operator<(const FunctionKey &a, const FunctionKey &b) {
    if (a.name == b.name) {
      return a.types_of_args < b.types_of_args;
    }
    return a.name < b.name;
  }
};
struct value {
  K_Variable_Type type_of_return;
  std::vector<std::string> names_of_args;
  int poliz_addr;
};
class Function_TID {
 public:
  Function_TID() = default;
  void push_id(K_Variable_Type type,
               const std::string &name,
               const std::vector<Expression_Type> &args_types,
               const std::vector<std::string> &args_names, int addr) {
    if (tid.count({name, args_types})) {
      //TODO
      throw SemanticError("multiply definition of function " + name);
    }
    tid[{name, args_types}] = {type, args_names, addr};
  }
  value check_id(const std::string &name,
                 const std::vector<Expression_Type> &args_types) {
    if (!tid.count({name, args_types})) {
      //TODO
      std::string error = "function with name: " + name + ", and args types: ";
      for(auto i : args_types){
        error += string_by_type(i);
        error += " ";
      }
      throw SemanticError(error + " doesn't exist");
    }
    return tid[{name, args_types}];
  }
  value check_id(const FunctionKey &k) {
    if (!tid.count(k)) {
      //TODO
      std::string error = "function with name: " + k.name + ", and args types: ";
      for(auto i : k.types_of_args){
        error += string_by_type(i);
        error += " ";
      }
      throw SemanticError(error + " doesn't exist");
    }
    return tid[k];
  }
 private:
  std::string string_by_type(Expression_Type t){
    if(t.t == K_Variable_Type_Int){
      return "int";
    } else if (t.t == K_Variable_Type_Float){
      return "float";
    } else if (t.t == K_Variable_Type_Bool){
      return "bool";
    } else if (t.t == K_Variable_Type_Char){
      return "char";
    } else if (t.t == K_Variable_Type_Array){
      return "array";
    } else if (t.t == K_Variable_Type_String){
      return "string";
    } else {
      throw std::logic_error("working error unexpected type");
    }
  }
  std::map<FunctionKey, value> tid;
};

#endif //BUGGUETTE_SEMANTIC_ANALIZATOR_TID_FUNCTION_TID_H_
