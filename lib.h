#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "map"
enum Types{int_, float_, bool_, char_, array_, string_, NULLTYPE};

struct Type{
  Types t;
  bool is_lvalue;
};