#include "../include/InvertedIndex.h"
#include "../include/Tokenizer.h"

#include <algorithm>
#include <unordered_set>
#include <iostream>




void InvertedIndex::build(const std::vector<Document> &documents)
{
    Tokenizer tknzr;

    for (const auto &doc : documents)
    {
        std::vector<std::string> words = tknzr.tokenize(doc.getContent());

        std::unordered_map<std::string, int> freq;
        for (const auto& word : words)
        {
            freq[word]++;
        }

        for (const auto& entry : freq)
        {
            Posting post;

            post.docId= doc.getId();
            post.freq= entry.second;

            index[entry.first].push_back(post);
        }

    }
}



std::vector<int> InvertedIndex::search(const std::string &word) const
{
    auto it = index.find(word);
    if (it == index.end())
    {
        return {};
    }

    std::vector<int> ids;
    for (const Posting& post : it->second)
    {
        ids.push_back(post.docId);
    }

    return ids;
}



void InvertedIndex::print() const
{
    for (const auto &entry : index)
    {
        std::cout << entry.first << " : ";

        for (const Posting& post : entry.second)
        {
            std::cout << "(" << post.docId << ", " << post.freq << ") ";
        }
        std::cout << '\n';
    }
}



std::vector<Posting> InvertedIndex::searchPostings(const std::string& word) const
{
    auto it= index.find(word);

    if (it == index.end())
    {
        return {};
    }

    return it->second;

}