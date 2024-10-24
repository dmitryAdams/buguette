
#include "globalVariables.h"
#include "starter.h"
#include "lexer/lexer.h"
#include "iostream"
int main(){
    starter();
    while (getLex())
    {
        std::cout << global::lex.name << ' ' << global::lex.type << std::endl;
    }
    return 0;
}
