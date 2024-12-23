//
// Created by adams on 11/12/24.
//

#ifndef BUGGUETTE_SEMANTIC_ANALIZATOR_TID_VARIABLES_TID_H_
#define BUGGUETTE_SEMANTIC_ANALIZATOR_TID_VARIABLES_TID_H_

#include "../../lib.h"
/// \brief Хранит переменные текущего scope
class variables_TID {
 public:
  variables_TID() = default;
  /// \brief Добавить переменную в текущий scope
  bool addId(const std::string &name, K_Variable_Type type) {
    if (tid.count(name)) {
      return false;
    } else {
      auto &tmp = tid[name] = {type, nullptr};
      if (type == K_Variable_Type::K_Variable_Type_Int) {
        tmp.second = new std::vector<void *>(1, new int);
      } else if (type == K_Variable_Type::K_Variable_Type_Float) {
        tmp.second = new std::vector<void *>(1, new double );
      } else if (type == K_Variable_Type::K_Variable_Type_Bool) {
        tmp.second = new std::vector<void *>(1, new bool);
      } else if (type == K_Variable_Type::K_Variable_Type_Char) {
        tmp.second = new std::vector<void *>(1, new char);
      } else if (type == K_Variable_Type::K_Variable_Type_Array) {
        tmp.second = new std::vector<void *>(1, new std::vector<int>);
      } else if (type == K_Variable_Type::K_Variable_Type_String) {
        tmp.second = new std::vector<void *>(1, new std::string);
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
/// \brief Проверить есть ли переменная в текущем scope, если да - вернуть тип, иначе - вернуть K_Variable_Type_NULLTYPE
  K_Variable_Type isInTID(const std::string &name) {
    if (tid.count(name)) {
      return tid.find(name)->second.first;
    } else {
      return K_Variable_Type_NULLTYPE;
    }
  }
  /// \brief Адрес вектора копий вызовов переменной
  std::vector<void *> *getVariableAdress(const std::string &name) {
    if (tid.count(name)) {
      return tid.find(name)->second.second;
    } else {
      return nullptr;
    }
  }
  ~variables_TID() {
    for (const auto &[i, k] : tid) {
      for (auto &j : *k.second) {
        if (k.first == K_Variable_Type::K_Variable_Type_Int) {
          delete (int *) j;
        } else if (k.first == K_Variable_Type::K_Variable_Type_Float) {
          delete (double *) j;
        } else if (k.first == K_Variable_Type::K_Variable_Type_Bool) {
          delete (bool *) j;
        } else if (k.first == K_Variable_Type::K_Variable_Type_Char) {
          delete (char *) j;
        } else if (k.first == K_Variable_Type::K_Variable_Type_Array) {
          delete (std::vector<int> *) j;
        } else if (k.first == K_Variable_Type::K_Variable_Type_String) {
          delete (std::string *) j;
        } else {
          throw std::logic_error("type with undefined behaviour");
        }
      }
    }
  }
// private:
  std::map<std::string, std::pair<K_Variable_Type, std::vector<void *> *>> tid;
};

#endif //BUGGUETTE_SEMANTIC_ANALIZATOR_TID_VARIABLES_TID_H_
