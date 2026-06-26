#pragma once

#include "Document.h"
#include "InvertedIndex.h"

#include <vector>
#include <string>



class QueryProcessor
{
private:
    const std::vector<Document> &documents;
    const InvertedIndex &index;

public:
    QueryProcessor(const std::vector<Document> &documents, const InvertedIndex &index);

    void search(const std::string &word) const;
    void run() const;
};