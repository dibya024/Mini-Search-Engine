#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

#include "Document.h"


struct Posting
{
    int docId;
    int freq;
};


class InvertedIndex
{
    private:
        std::unordered_map<std::string, std::vector<Posting>> index;

    public:
        void build(const std::vector<Document>& documents);
        std::vector<int> search(const std::string& word) const;
        void print() const;

        std::vector<Posting> searchPostings(const std::string& word) const;

};