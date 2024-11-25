//
// Created by adams on 11/12/24.
//

#ifndef BUGGUETTE_SEMANTIC_ANALIZATOR_TID_TREE_VARIABLES_TID_H_
#define BUGGUETTE_SEMANTIC_ANALIZATOR_TID_TREE_VARIABLES_TID_H_
#include "variables_TID.h"
#include "../SemanticError/SemanticError.h"
class Tree_variables_TID {
 public:
  Tree_variables_TID(){
    cur = new Node(nullptr);
  }
  ~Tree_variables_TID(){
    for(auto &i : nodes) delete i;
  }
  void create_scope(){
    cur = new Node(cur);
  }
  void exit_scope(){
    cur = cur->pred;
#ifdef DEBUG
    if (cur == nullptr){
      std::cerr << "WARNING!!!! you went out of scopes\n";
    }
#endif
  }
  void push_id(const std::string &name, const std::string &type_){
    K_Variable_Type type = K_Variable_Type::K_Variable_Type_NULLTYPE;
    if (type_ == "int"){
      type = K_Variable_Type::K_Variable_Type_Int;
    } else if (type_ == "char"){
      type = K_Variable_Type::K_Variable_Type_Char;
    } else if (type_ == "bool"){
      type = K_Variable_Type::K_Variable_Type_Bool;
    } else if (type_ == "float"){
      type = K_Variable_Type::K_Variable_Type_Float;
    } else if (type_ == "string"){
      type = K_Variable_Type::K_Variable_Type_String;
    } else if (type_ == "array"){
      type = K_Variable_Type::K_Variable_Type_Array;
    }
    if(!cur->tid.addId(name, type)){
      throw SemanticError("multiply definition of var with name: " + name);
    }
  }
  void push_id(const std::string &name, K_Variable_Type &type_){
    K_Variable_Type type = type_;
    if(!cur->tid.addId(name, type)){
      throw SemanticError("multiply definition of var with name: " + name);
    }
  }
  K_Variable_Type check_id(const std::string &name){
    auto now = cur;
    while (now != nullptr){
      auto tmp = now->tid.isInTID(name);
      if (tmp != K_Variable_Type::K_Variable_Type_NULLTYPE){
        return tmp;
      }
      now = now->pred;
    }
    return K_Variable_Type::K_Variable_Type_NULLTYPE;
  }
  void * getAdress(const std::string &name){
    auto now = cur;
    while (now != nullptr){
      auto tmp = now->tid.isInTID(name);
      if (tmp != K_Variable_Type::K_Variable_Type_NULLTYPE){
        return now->tid.getVariableAdress(name);
      }
      now = now->pred;
    }
    return nullptr;
  }
 private:
  struct Node{
    Node *pred;
    variables_TID tid;
    Node(Node *pred_) : pred(pred_), tid() {}
  };
// Node *root;
 Node *cur;
 std::vector<Node *> nodes;
};

#endif //BUGGUETTE_SEMANTIC_ANALIZATOR_TID_TREE_VARIABLES_TID_H_
