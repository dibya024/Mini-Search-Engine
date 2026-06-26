#include "../include/InvertedIndex.h"
#include "../include/Tokenizer.h"

// #include <algorithm>
#include <unordered_set>
#include <iostream>




void InvertedIndex::build(const std::vector<Document> &documents)
{
    Tokenizer tknzr;

    for (const auto &doc : documents)
    {
        std::vector<std::string> words = tknzr.tokenize(doc.getContent());

        std::unordered_set<std::string> uniqueWords(words.begin(), words.end());

        for (const auto &word : words)
        {
            index[word].push_back(doc.getId());
        }
    }
}

std::vector<int> InvertedIndex::search(const std::string &word) const
{
    auto it = index.find(word);
    if (it != index.end())
    {
        return it->second;
    }

    return {};
}

void InvertedIndex::print() const
{
    for (const auto &entry : index)
    {
        std::cout << entry.first << ":";

        for (int id : entry.second)
        {
            std::cout << id << " ";
        }
        std::cout << '\n';
    }
}