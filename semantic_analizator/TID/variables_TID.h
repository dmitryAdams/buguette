//
// Created by adams on 11/12/24.
//

#ifndef BUGGUETTE_SEMANTIC_ANALIZATOR_TID_VARIABLES_TID_H_
#define BUGGUETTE_SEMANTIC_ANALIZATOR_TID_VARIABLES_TID_H_

#include "../../lib.h"

class variables_TID {
 public:
  variables_TID() = default;

  bool addId(const std::string &name, K_Variable_Type type){
    if (tid.count(name)){
      return false;
    } else {
      auto &tmp = tid[name] = {type, nullptr};
      if (type == K_Variable_Type::K_Variable_Type_Int){
        tmp.second = new int;
      } else if (type == K_Variable_Type::K_Variable_Type_Float){
        tmp.second = new float ;
      } else if(type == K_Variable_Type::K_Variable_Type_Bool){
        tmp.second = new bool ;
      } else if (type == K_Variable_Type::K_Variable_Type_Char){
        tmp.second = new char;
      } else if (type == K_Variable_Type::K_Variable_Type_Array){
        tmp.second = new std::vector<int>;
      } else if (type == K_Variable_Type::K_Variable_Type_String){
        tmp.second = new std::string;
      } else {
        throw std::logic_error("type with undefined behaviour");
      }
      return true;
    }
  }
//  bool addEl(const std::string &name, K_Variable_Type type, int x = 0){
//    if (tid.count(name)){
//      return false;
//    } else {
//      tid[name] = {type, (void *)(new int(x))};
//      return true;
//    }
//  }
  K_Variable_Type isInTID(const std::string &name){
    if (tid.count(name)){
      return tid.find(name)->second.first;
    } else {
      return K_Variable_Type_NULLTYPE;
    }
  }
  void *getVariableAdress(const std::string &name){
    if (tid.count(name)){
      return tid.find(name)->second.second;
    } else {
      return nullptr;
    }
  }
  ~variables_TID(){
    for(const auto &[i, j] : tid){
      if (j.first == K_Variable_Type::K_Variable_Type_Int){
        delete (int*)j.second;
      } else if (j.first == K_Variable_Type::K_Variable_Type_Float){
        delete (double*)j.second;
      } else if(j.first == K_Variable_Type::K_Variable_Type_Bool){
        delete (bool*)j.second;
      } else if (j.first == K_Variable_Type::K_Variable_Type_Char){
        delete (char*) j.second;
      } else if (j.first == K_Variable_Type::K_Variable_Type_Array){
        delete (std::vector<int> *)j.second;
      } else if (j.first == K_Variable_Type::K_Variable_Type_String){
        delete (std::string *)j.second;
      } else {
        throw std::logic_error("type with undefined behaviour");
      }
    }
  }
 private:
  std::map<std::string, std::pair<K_Variable_Type, void *>> tid;
};

#endif //BUGGUETTE_SEMANTIC_ANALIZATOR_TID_VARIABLES_TID_H_
