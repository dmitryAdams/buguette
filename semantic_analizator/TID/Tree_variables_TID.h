//
// Created by adams on 11/12/24.
//

#ifndef BUGGUETTE_SEMANTIC_ANALIZATOR_TID_TREE_VARIABLES_TID_H_
#define BUGGUETTE_SEMANTIC_ANALIZATOR_TID_TREE_VARIABLES_TID_H_
#include "variables_TID.h"
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
    variables_TID::Types type = variables_TID::NULLTYPE;
    if (type_ == "int"){
      type = variables_TID::int_;
    } else if (type_ == "char"){
      type = variables_TID::char_;
    } else if (type_ == "bool"){
      type = variables_TID::bool_;
    } else if (type_ == "float"){
      type = variables_TID::float_;
    } else if (type_ == "string"){
      type = variables_TID::string_;
    } else if (type_ == "array"){
      type = variables_TID::array_;
    }
    if(!cur->tid.addId(name, type)){
      //TODO свои ошибки
      throw std::logic_error("multiply definition");
    }
  }
  variables_TID::Types check_id(const std::string &name){
    auto now = cur;
    while (now != nullptr){
      auto tmp = now->tid.isInTID(name);
      if (tmp != variables_TID::NULLTYPE){
        return tmp;
      }
      now = now->pred;
    }
    return variables_TID::NULLTYPE;
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
