#pragma once
#include "lib.h"

struct lexeme {
    int type = 0;
    int num = 0;
    std::string name;
};

void get_lex();
