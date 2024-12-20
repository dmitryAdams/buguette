//
// Created by adams on 10/24/24.
//

#ifndef TRIE_H
#define TRIE_H

#include <signal.h>

#include "map"
#include "vector"
#include "string"
/// \brief БОР для проверки на зарезервированные слова языка
class Trie
{
public:
    Trie() : root_(new TrieNode()) {}

    Trie(const std::vector<std::string>& strs);
/// \brief добавить слово в БОР
    void addString(const std::string& s);
/// \brief Проверить есть ли слово в боре
    bool checkString(const std::string& s);
    ~Trie();

private:
    struct TrieNode
    {
        std::map<char, TrieNode*> children_;
        bool is_terminate_;

        TrieNode() : is_terminate_(false) {}
        static void deleteSubtree(TrieNode* v);
    };

    TrieNode* root_;
};


#endif //TRIE_H
