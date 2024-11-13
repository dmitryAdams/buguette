#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "map"
enum Types{int_, float_, bool_, char_, array_, string_, NULLTYPE};

struct Type_{
  Types t;
  bool is_lvalue;
  friend bool operator<(const Type_ &a, const Type_ &b){
    return a.t < b.t || (a.t == b.t && a.is_lvalue < b.is_lvalue);
  }
};