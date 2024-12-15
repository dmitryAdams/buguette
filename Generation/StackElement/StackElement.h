//
// Created by adams on 11/25/24.
//

#ifndef BUGGUETTE_GENERATION_STACKELEMENT_H_
#define BUGGUETTE_GENERATION_STACKELEMENT_H_
#include "iostream"

class StackElement {
 public:
  virtual bool is_operator() = 0;
  friend std::ostream &operator<<(std::ostream &out, const StackElement &po){
    out << po.string_representation_;
    return out;
  }
  virtual void upd(void *) = 0;
  virtual ~StackElement() = default;
 protected:
  std::string string_representation_;
};

#endif //BUGGUETTE_GENERATION_STACKELEMENT_H_
