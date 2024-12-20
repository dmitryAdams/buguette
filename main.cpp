#include "globalVariables.h"
#include "starter.h"
#include "lexer/lexer.h"
#include "iostream"
#include "./syntax_analizator/SyntaxAnalizator.h"
#include "./syntax_analizator/syntax_error/SyntaxError.h"
#include "run/run.h"

int main() {
  try {
    starter();///< Запускает стартер
    program_(); ///< Запускает семантический и синтаксический анализатор

  }
  /// \details Ловля семантических и синтаксических ошибок
  catch (SyntaxError &e) {
    std::cout << e.what() << '\n';
  } catch (SemanticError &e) {
    std::cout << e.what() << '\n';
  }
  /**
   * \details init - говорит о том, что необходимая копии переменной уже создана кем-то до,
   * поэтому копировать ее еще раз или удалять текущему вызову функции не надо, очевидно
   * что при начальном запуске любой функции не надо удалять только глобальные переменные,
   * поэтому init по умолчанию заполнен ими
  */std::map<std::pair<K_Variable_Type, std::vector<void *> *>, bool> init;
  for (auto &[i, j] : global::tree_of_variables.cur->tid.tid) {
    init[j] = true;
  }
  run(global::start_pos_on_poliz, init); ///< \details вызов основной функции интерпретации
  /// \details Очищение памяти после окончания исполнения интерпретации в соответствии с типом удаляемого значения
  for (auto &[i, j] : init) {
    if (i.first == K_Variable_Type_Int) {
      delete (int *) (i.second->back());
    } else if (i.first == K_Variable_Type_Bool) {
      delete (bool *) (i.second->back());
    } else if (i.first == K_Variable_Type_Float) {
      delete (double *) (i.second->back());
    } else if (i.first == K_Variable_Type_Char) {
      delete (char *) (i.second->back());
    } else if (i.first == K_Variable_Type_String) {
      delete (std::string *) (i.second->back());
    } else if (i.first == K_Variable_Type_Array) {
      delete (std::vector<int> *) (i.second->back());
    }
    i.second->pop_back();
  }
  return 0;
}

