#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "map"
enum K_Variable_Type {
  K_Variable_Type_Int,
  K_Variable_Type_Float,
  K_Variable_Type_Bool,
  K_Variable_Type_Char,
  K_Variable_Type_Array,
  K_Variable_Type_String,
  K_Variable_Type_NULLTYPE
};

struct Expression_Type {
  K_Variable_Type t;
  bool is_lvalue;
  friend bool operator<(const Expression_Type &a, const Expression_Type &b) {
    return a.t < b.t /*|| (a.t == b.t && a.is_lvalue < b.is_lvalue)*/;
  }
};