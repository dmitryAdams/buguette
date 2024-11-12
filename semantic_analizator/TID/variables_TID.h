//
// Created by adams on 11/12/24.
//

#ifndef BUGGUETTE_SEMANTIC_ANALIZATOR_TID_VARIABLES_TID_H_
#define BUGGUETTE_SEMANTIC_ANALIZATOR_TID_VARIABLES_TID_H_

#include "../../lib.h"

class variables_TID {
 public:
  variables_TID() = default;
  enum Types{int_, float_, bool_, char_, array_, string_, NULLTYPE};
  bool addId(const std::string &name, Types type){
    if (tid.count(name)){
      return false;
    } else {
      auto &tmp = tid[name] = {type, nullptr};
      if (type == Types::int_){
        tmp.second = new int;
      } else if (type == Types::float_){
        tmp.second = new float ;
      } else if(type == Types::bool_){
        tmp.second = new bool ;
      } else if (type == Types::char_){
        tmp.second = new char;
      } else if (type == Types::array_){
        tmp.second = new std::vector<int>;
      } else if (type == Types::string_){
        tmp.second = new std::string;
      } else {
        throw std::logic_error("type with undefined behaviour");
      }
      return true;
    }
  }
//  bool addEl(const std::string &name, Types type, int x = 0){
//    if (tid.count(name)){
//      return false;
//    } else {
//      tid[name] = {type, (void *)(new int(x))};
//      return true;
//    }
//  }
  Types isInTID(const std::string &name){
    if (tid.count(name)){
      return tid.find(name)->second.first;
    } else {
      return NULLTYPE;
    }
  }
  ~variables_TID(){
    for(const auto &[i, j] : tid){
      if (j.first == Types::int_){
        delete (int*)j.second;
      } else if (j.first == Types::float_){
        delete (float*)j.second;
      } else if(j.first == Types::bool_){
        delete (bool*)j.second;
      } else if (j.first == Types::char_){
        delete (char*) j.second;
      } else if (j.first == Types::array_){
        delete (std::vector<int> *)j.second;
      } else if (j.first == Types::string_){
        delete (std::string *)j.second;
      } else {
        throw std::logic_error("type with undefined behaviour");
      }
    }
  }
 private:
  std::map<std::string, std::pair<Types, void *>> tid;
};

#endif //BUGGUETTE_SEMANTIC_ANALIZATOR_TID_VARIABLES_TID_H_
