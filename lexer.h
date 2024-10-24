#pragma once
#include "lib.h"

struct lexeme {
    int type = 0;
    int num = 0;
    std::string name;
};

class Lexer {
public:

    Lexer(): current_lexeme_(0), text_() {

    }

    void getLex();


private:
    int current_lexeme_;
    std::vector<lexeme> text_;
};

void get_lex();
