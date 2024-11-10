//
// Created by adams on 10/24/24.
//

#include "Trie.h"

Trie::Trie(const std::vector<std::string>& strs)
{
    for (const auto& s : strs)
    {
        addString(s);
    }
}

void Trie::addString(const std::string& s)
{
    auto v = root_;
    for (auto c : s)
    {
        if (!v->children_.count(c))
        {
            v->children_[c] = new TrieNode;
        }
        v = v->children_[c];
    }
    v->is_terminate_ = true;
}

bool Trie::checkString(const std::string& s)
{
    auto v = root_;
    for (auto c : s)
    {
        if (!v->children_.count(c))
        {
            return false;
        }
        v = v->children_[c];
    }
    return v->is_terminate_;
}

Trie::~Trie()
{
    TrieNode::deleteSubtree(root_);
}

void Trie::TrieNode::deleteSubtree(TrieNode* v)
{
    if (v)
    {
        for (auto [c, i] : v->children_)
        {
            deleteSubtree(i);
        }
    }
    delete v;
}
