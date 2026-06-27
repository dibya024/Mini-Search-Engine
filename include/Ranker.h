#pragma once

#include <vector>
#include <string>

#include "InvertedIndex.h"

struct SearchResult
{
    int docId;
    double score;
};

class Ranker
{
public:
    std::vector<SearchResult> rank(
        const std::vector<std::string> &queryWords,
        const std::vector<int> &candidateDocs,
        const InvertedIndex &index,
        int totalDocs) const;
};