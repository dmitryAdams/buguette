#include "lexer.h"
#include "../globalVariables.h"

bool getLex()
{
    if (global::ind >= global::text.size())
    {
        return false;
    }
    std::string cur_lex;
    while (global::ind < global::text.size() && global::text[global::ind] == ' ' || global::text[global::ind] == '\n')
    {
        ++global::ind;
    }
    if (std::isalpha(global::text[global::ind]) || global::text[global::ind] == '_')
    {
        while (global::ind < global::text.size() && (std::isalpha(global::text[global::ind]) || std::isdigit(global::text[global::ind])) || global::text[global::ind] == '_')
        {
            cur_lex.push_back(global::text[global::ind]);
            ++global::ind;
        }
        if (global::service_words_trie.checkString(cur_lex))
        {
            global::lex.type = Service_word;
            global::lex.name = cur_lex;
            global::lex.num = -1;
            return true;
        }
        if (global::types_trie.checkString(cur_lex))
        {
            global::lex.type = Type;
            global::lex.name = cur_lex;
            global::lex.num = -1;
            return true;
        }
        global::lex.type = Identificator;
        global::lex.name = cur_lex;
        global::lex.num = -1;
        return true;
    }
    if (std::isdigit(global::text[global::ind]))
    {
        while (global::ind < global::text.size() && (std::isdigit(global::text[global::ind]) || global::text[
            global::ind] == '.'))
        {
            cur_lex.push_back(global::text[global::ind]);
            ++global::ind;
        }
        global::lex.type = Literal;
        global::lex.name = cur_lex;
        global::lex.num = -1;
        return true;
    }
    if (global::text[global::ind] == ';')
    {
        global::lex.type = Semicolon;
        global::lex.name = ";";
        global::lex.num = -1;
        ++global::ind;
        return true;
    }
    if (global::text[global::ind] == ',')
    {
        global::lex.type = Comma;
        global::lex.name = ",";
        global::lex.num = -1;
        ++global::ind;
        return true;
    }
    if (global::text[global::ind] == '(')
    {
        global::lex.type = Open_brace;
        global::lex.name = "(";
        global::lex.num = -1;
        ++global::ind;
        return true;
    }
    if (global::text[global::ind] == ')')
    {
        global::lex.type = Close_brace;
        global::lex.name = ")";
        global::lex.num = -1;
        ++global::ind;
        return true;
    }
    if (global::text[global::ind] == '{')
    {
        global::lex.type = Open_curly_brace;
        global::lex.name = "{";
        global::lex.num = -1;
        ++global::ind;
        return true;
    }
    if (global::text[global::ind] == '}')
    {
        global::lex.type = Close_curly_brace;
        global::lex.name = "}";
        global::lex.num = -1;
        ++global::ind;
        return true;
    }
    if (global::text[global::ind] == '+' || global::text[global::ind] == '-')
    {
        cur_lex.push_back(global::text[global::ind]);
        ++global::ind;
        if (global::ind < global::text.size() && global::text[global::ind] == global::text[global::ind - 1])
        {
            cur_lex.push_back(global::text[global::ind]);
            ++global::ind;
        }
        global::lex.type = Operator;
        global::lex.name = cur_lex;
        global::lex.num = -1;
        return true;
    }
    if (global::text[global::ind] == '*' || global::text[global::ind] == '/' || global::text[global::ind] == '%' ||
        global::text[global::ind] == '|' || global::text[global::ind] == '&' || global::text[global::ind] == '^')
    {
        cur_lex.push_back(global::text[global::ind]);
        global::lex.type = Operator;
        global::lex.name = cur_lex;
        global::lex.num = -1;
        ++global::ind;
        return true;
    }
    if(global::text[global::ind] == '<' || global::text[global::ind] == '>' || global::text[global::ind] == '=')
    {
        cur_lex.push_back(global::text[global::ind]);
        ++global::ind;
        if (global::ind < global::text.size() && global::text[global::ind] == '=')
        {
            cur_lex.push_back(global::text[global::ind]);
            ++global::ind;
        }
        global::lex.type = Operator;
        global::lex.name = cur_lex;
        global::lex.num = -1;
        return true;
    }
    global::lex.type = Other;
    cur_lex.push_back(global::text[global::ind]);
    global::lex.name = cur_lex;
    global::lex.num = -1;
    ++global::ind;
    return true;
}
