#include "lexer.h"
#include "../globalVariables.h"

bool getLex() {
  std::string cur_lex;
  //TODO Напистаь комментарии
//   if(global::text[global::ind] == '#')
//   {
//       while (global::ind < global::text.size() && global::text[global::ind] != '\n')
//       {
//           ++global::ind;
//       }
//   }
  while (global::ind < global::text.size() && global::text[global::ind] == ' ' || global::text[global::ind] == '\n') {
    global::string_number += global::text[global::ind] == '\n';
    ++global::ind;
  }
  if (global::ind >= global::text.size()) {
    global::eof = true;
    global::lex.type = NULLLEXEME;
    global::lex.name = "main";
    return false;
  }
  if (std::isalpha(global::text[global::ind]) || global::text[global::ind] == '_') {
    while (global::ind < global::text.size() && (std::isalpha(global::text[global::ind]) ||
        std::isdigit(global::text[global::ind])) || global::text[global::ind] == '_') {
      cur_lex.push_back(global::text[global::ind]);
      ++global::ind;
    }
    if (global::service_words_trie.checkString(cur_lex)) {
      if (cur_lex == "main") {
        global::lex.type = Main;
        global::lex.name = cur_lex;
        global::lex.num = global::string_number;
        return true;
      } else {
        global::lex.type = Service_word;
        global::lex.name = cur_lex;
        global::lex.num = global::string_number;
        return true;
      }
    }
    if (global::types_trie.checkString(cur_lex)) {
      global::lex.type = Type;
      global::lex.name = cur_lex;
      global::lex.num = global::string_number;
      return true;
    }
    global::lex.type = Identificator;
    global::lex.name = cur_lex;
    global::lex.num = global::string_number;
    return true;
  }
  if (std::isdigit(global::text[global::ind])) {
    while (global::ind < global::text.size() && (std::isdigit(global::text[global::ind]))) {
      cur_lex.push_back(global::text[global::ind]);
      ++global::ind;
    }
    if (global::ind < global::text.size() && global::text[global::ind] == '.') {
      cur_lex.push_back(global::text[global::ind]);
      ++global::ind;
    }
    while (global::ind < global::text.size() && (std::isdigit(global::text[global::ind]))) {
      cur_lex.push_back(global::text[global::ind]);
      ++global::ind;
    }
    global::lex.type = Literal;
    global::lex.name = cur_lex;
    global::lex.num = global::string_number;
    return true;
  }
  if (global::text[global::ind] == ';') {
    global::lex.type = Semicolon;
    global::lex.name = ";";
    global::lex.num = global::string_number;
    ++global::ind;
    return true;
  }
  if (global::text[global::ind] == ',') {
    global::lex.type = Comma;
    global::lex.name = ",";
    global::lex.num = global::string_number;
    ++global::ind;
    return true;
  }
  if (global::text[global::ind] == '(') {
    global::lex.type = Open_brace;
    global::lex.name = "(";
    global::lex.num = global::string_number;
    ++global::ind;
    return true;
  }
  if (global::text[global::ind] == '[') {
    global::lex.type = Open_square_brace;
    global::lex.name = "[";
    global::lex.num = global::string_number;
    ++global::ind;
    return true;
  }
  if (global::text[global::ind] == ')') {
    global::lex.type = Close_brace;
    global::lex.name = ")";
    global::lex.num = global::string_number;
    ++global::ind;
    return true;
  }
  if (global::text[global::ind] == ']') {
    global::lex.type = Close_square_brace;
    global::lex.name = "]";
    global::lex.num = global::string_number;
    ++global::ind;
    return true;
  }
  if (global::text[global::ind] == '{') {
    global::lex.type = Open_curly_brace;
    global::lex.name = "{";
    global::lex.num = global::string_number;
    ++global::ind;
    return true;
  }
  if (global::text[global::ind] == '}') {
    global::lex.type = Close_curly_brace;
    global::lex.name = "}";
    global::lex.num = global::string_number;
    ++global::ind;
    return true;
  }
  if (global::text[global::ind] == '+' || global::text[global::ind] == '-') {
    cur_lex.push_back(global::text[global::ind]);
    ++global::ind;
    if (global::ind < global::text.size() && global::text[global::ind] == global::text[global::ind - 1]) {
      cur_lex.push_back(global::text[global::ind]);
      ++global::ind;
    }
    global::lex.type = Operator;
    global::lex.name = cur_lex;
    global::lex.num = global::string_number;
    return true;
  }
  if (global::text[global::ind] == '|' || global::text[global::ind] == '&') {
    cur_lex.push_back(global::text[global::ind]);
    ++global::ind;
    if (global::ind < global::text.size() && global::text[global::ind] == global::text[global::ind - 1]) {
      cur_lex.push_back(global::text[global::ind]);
      ++global::ind;
    }
    global::lex.type = Operator;
    global::lex.name = cur_lex;
    global::lex.num = global::string_number;
    return true;
  }
  if (global::text[global::ind] == '!' || global::text[global::ind] == '~') {
    cur_lex.push_back(global::text[global::ind]);
    ++global::ind;
    if (global::text[global::ind] == '=') {
        cur_lex.push_back(global::text[global::ind]);
        ++global::ind;
    }
    global::lex.type = Operator;
    global::lex.name = cur_lex;
    global::lex.num = global::string_number;
    return true;
  }
  if (global::text[global::ind] == '*' || global::text[global::ind] == '/' || global::text[global::ind] == '%' ||
      global::text[global::ind] == '^') {
    cur_lex.push_back(global::text[global::ind]);
    global::lex.type = Operator;
    global::lex.name = cur_lex;
    global::lex.num = global::string_number;
    ++global::ind;
    return true;
  }
  if (global::text[global::ind] == '<' || global::text[global::ind] == '>' || global::text[global::ind] == '=') {
    cur_lex.push_back(global::text[global::ind]);
    ++global::ind;
    if (global::ind < global::text.size() && global::text[global::ind] == '=') {
      cur_lex.push_back(global::text[global::ind]);
      ++global::ind;
    }
    global::lex.type = Operator;
    global::lex.name = cur_lex;
    global::lex.num = global::string_number;
    return true;
  }
  if (global::text[global::ind] == '"') {
    ++global::ind;
    while (global::ind < global::text.size() && global::text[global::ind] != '"') {
      cur_lex.push_back(global::text[global::ind]);
      ++global::ind;
    }
    ++global::ind;
    global::lex.type = String_Literal;
    global::lex.name = cur_lex;
    global::lex.num = global::string_number;
    return true;
  }
  global::lex.type = Other;
  cur_lex.push_back(global::text[global::ind]);
  global::lex.name = cur_lex;
  global::lex.num = global::string_number;
  ++global::ind;
  return true;
}
