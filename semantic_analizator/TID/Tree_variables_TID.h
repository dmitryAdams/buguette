//
// Created by adams on 11/12/24.
//

#ifndef BUGGUETTE_SEMANTIC_ANALIZATOR_TID_TREE_VARIABLES_TID_H_
#define BUGGUETTE_SEMANTIC_ANALIZATOR_TID_TREE_VARIABLES_TID_H_
#include "variables_TID.h"
#include "../SemanticError/SemanticError.h"

/// \brief дерево TID'ов, хранит информацию о всех доступных переменных в текущем scope
class Tree_variables_TID {
 public:
  Tree_variables_TID(){
    cur = new Node(nullptr);
  }
  ~Tree_variables_TID(){
    for(auto &i : nodes) delete i;
  }
  /// \brief Создать scope (вопросы?)
  void create_scope(){
    cur = new Node(cur);
  }
  /// \brief Выйти из scope (вопросы?)
  void exit_scope(){
    cur = cur->pred;
  }
  /// \brief Добавить переменную в текущий scope
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
  /// \brief Добавить переменную в текущий scope
  void push_id(const std::string &name, K_Variable_Type &type_){
    K_Variable_Type type = type_;
    if(!cur->tid.addId(name, type)){
      throw SemanticError("multiply definition of var with name: " + name);
    }
  }
  /// \brief Доступна ли переменная с таким именем в текущем scope, да - вернуть тип, нет - кинуть исключения
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
  /// \brief Получить адрес, по которому лежит переменная
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
// private:
/// \brief структура Node хранит TID текущего scope и указатель на Node отвечающего за родительский scope
/// (scope, в который включен текущий)
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
