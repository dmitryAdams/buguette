//
// Created by adams on 11/13/24.
//

#ifndef BUGGUETTE_SEMANTIC_ANALIZATOR_TID_FUNCTION_TID_H_
#define BUGGUETTE_SEMANTIC_ANALIZATOR_TID_FUNCTION_TID_H_
#include "../../lib.h"
#include "../SemanticError/SemanticError.h"
struct key {
  std::string name;
  std::vector<Expression_Type> types_of_args;
  friend bool operator<(const key &a, const key &b) {
    if (a.name == b.name) {
      return a.types_of_args < b.types_of_args;
    }
    return a.name < b.name;
  }
};
struct value {
  K_Variable_Type type_of_return;
  std::vector<std::string> names_of_args;
};
class Function_TID {
 public:
  Function_TID() = default;
  void push_id(K_Variable_Type type,
               const std::string &name,
               const std::vector<Expression_Type> &args_types,
               const std::vector<std::string> &args_names) {
    if (tid.count({name, args_types})) {
      //TODO
      throw SemanticError("multiply definition of function " + name);
    }
    tid[{name, args_types}] = {type, args_names};
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
  std::map<key, value> tid;
};

#endif //BUGGUETTE_SEMANTIC_ANALIZATOR_TID_FUNCTION_TID_H_
