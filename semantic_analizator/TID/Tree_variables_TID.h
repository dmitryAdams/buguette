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
    Types type = Types::NULLTYPE;
    if (type_ == "int"){
      type = Types::int_;
    } else if (type_ == "char"){
      type = Types::char_;
    } else if (type_ == "bool"){
      type = Types::bool_;
    } else if (type_ == "float"){
      type = Types::float_;
    } else if (type_ == "string"){
      type = Types::string_;
    } else if (type_ == "array"){
      type = Types::array_;
    }
    if(!cur->tid.addId(name, type)){
      throw SemanticError("multiply definition of var with name: " + name);
    }
  }
  void push_id(const std::string &name, Types &type_){
    Types type = type_;
    if(!cur->tid.addId(name, type)){
      throw SemanticError("multiply definition of var with name: " + name);
    }
  }
  Types check_id(const std::string &name){
    auto now = cur;
    while (now != nullptr){
      auto tmp = now->tid.isInTID(name);
      if (tmp != Types::NULLTYPE){
        return tmp;
      }
      now = now->pred;
    }
    return Types::NULLTYPE;
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
