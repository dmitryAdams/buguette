#pragma once
#include "../lib.h"
/// \brief Типы лексем
enum LexemeType
{
    NULLLEXEME, Identificator, Service_word, Type, Literal, Operator, Comma, Semicolon, Open_brace,
    Close_brace, Open_curly_brace, Close_curly_brace, Other, String_Literal, Open_square_brace, Close_square_brace, Main
};

/// \brief Структура хранящая всю информацию о лексемах языка buggette
struct lexeme
{
    LexemeType type = NULLLEXEME;
    int num = 0;
    std::string name;
};

bool getLex();
