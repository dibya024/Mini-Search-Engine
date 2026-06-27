#pragma once

#include "Document.h"
#include "InvertedIndex.h"
#include "Ranker.h"

#include <vector>
#include <string>



class QueryProcessor
{
private:
    const std::vector<Document> &documents;
    const InvertedIndex &index;

    std::vector<int> intersect(const std::vector<int>& first, const std::vector<int>& second) const;

    void printDocuments(const std::vector<int>& ids) const;

    void printRankedDocuments(const std::vector<SearchResult>& results) const;

public:
    QueryProcessor(const std::vector<Document> &documents, const InvertedIndex &index);

    void run() const;
};