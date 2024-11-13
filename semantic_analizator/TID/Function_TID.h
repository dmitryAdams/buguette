//
// Created by adams on 11/13/24.
//

#ifndef BUGGUETTE_SEMANTIC_ANALIZATOR_TID_FUNCTION_TID_H_
#define BUGGUETTE_SEMANTIC_ANALIZATOR_TID_FUNCTION_TID_H_
#include "../../lib.h"
#include "../SemanticError/SemanticError.h"
struct key {
  std::string name;
  std::vector<Type_> types_of_args;
  friend bool operator<(const key &a, const key &b) {
    if (a.name == b.name) {
      return a.types_of_args < b.types_of_args;
    }
    return a.name < b.name;
  }
};
struct value {
  Types type_of_return;
  std::vector<std::string> names_of_args;
};
class Function_TID {
 public:
  Function_TID() = default;
  void push_id(Types type,
               const std::string &name,
               const std::vector<Type_> &args_types,
               const std::vector<std::string> &args_names) {
    if (tid.count({name, args_types})) {
      //TODO
      throw SemanticError("multiply definition of function " + name);
    }
    tid[{name, args_types}] = {type, args_names};
  }
  value check_id(const std::string &name,
                 const std::vector<Type_> &args_types) {
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
  std::string string_by_type(Type_ t){
    if(t.t == int_){
      return "int";
    } else if (t.t == float_){
      return "float";
    } else if (t.t == bool_){
      return "bool";
    } else if (t.t == char_){
      return "char";
    } else if (t.t == array_){
      return "array";
    } else if (t.t == string_){
      return "string";
    } else {
      throw std::logic_error("working error unexpected type");
    }
  }
  std::map<key, value> tid;
};

#endif //BUGGUETTE_SEMANTIC_ANALIZATOR_TID_FUNCTION_TID_H_
