#include "../include/Ranker.h"

#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>





std::vector<SearchResult> Ranker::rank(
    const std::vector<std::string> &queryWords,
    const std::vector<int> &candidateDocs,
    const InvertedIndex &index,
    int totalDocs) const
{
    std::unordered_set<int> candidates(
        candidateDocs.begin(),
        candidateDocs.end());

    std::unordered_map<int, double> scores;

    for (const std::string &word : queryWords)
    {
        std::vector<Posting> postings = index.searchPostings(word);

        if (postings.empty())
        {
            continue;
        }

        int documentFrequency = postings.size();

        double idf = std::log(
            1.0 + static_cast<double>(totalDocs) /
                      documentFrequency);

        for (const Posting &post : postings)
        {
            if (candidates.count(post.docId))
            {
                scores[post.docId] += post.freq * idf;
            }
        }
    }

    std::vector<SearchResult> results;

    for (const auto &entry : scores)
    {
        SearchResult result;

        result.docId = entry.first;
        result.score = entry.second;

        results.push_back(result);
    }

    std::sort(results.begin(), results.end(),
              [](const SearchResult &a,
                 const SearchResult &b)
              {
                  return a.score > b.score;
              });

    return results;
}