#include "../include/QueryProcessor.h"
#include "../include/Tokenizer.h"
#include "../include/Ranker.h"

#include <iostream>
#include <unordered_set>





QueryProcessor::QueryProcessor(const std::vector<Document> &docs, const InvertedIndex &idx) : documents(docs), index(idx) {}




void QueryProcessor::run() const
{
    std::cout << "=========================\n";
    std::cout << "    Mini Search Engine\n";
    std::cout << "=========================\n";

    std::string query;

    while (true)
    {
        std::cout << "\nEnter search word ( or 'exit') : ";
        std::getline(std::cin >> std::ws, query);

        if (query == "exit")
        {
            break;
        }

        Tokenizer tknzr;
        std::vector<std::string> words = tknzr.tokenize(query);

        if (words.empty())
        {
            continue;
        }

        std::vector<int> res = index.search(words[0]);

        for (size_t i = 1; i < words.size(); i++)
        {
            res = intersect(res, index.search(words[i]));
        }

        Ranker ranker;

        auto rankedResults =
            ranker.rank(words, res, index, documents.size());

        printRankedDocuments(rankedResults);
    }

    std::cout << "\nBye!\nSee you again!\n";
}




std::vector<int> QueryProcessor::intersect(const std::vector<int> &first, const std::vector<int> &second) const
{
    std::unordered_set<int> lookup(first.begin(), first.end());
    std::vector<int> res;

    for (int id : second)
    {
        if (lookup.count(id))
        {
            res.push_back(id);
        }
    }
    return res;
}




void QueryProcessor::printDocuments(const std::vector<int> &ids) const
{
    if (ids.empty())
    {
        std::cout << "No documents found!\n";
        return;
    }

    std::cout << "Found in : \n";
    for (int id : ids)
    {
        for (const auto &doc : documents)
        {
            if (doc.getId() == id)
            {
                std::cout << doc.getFilename() << '\n';
                break;
            }
        }
    }
}




void QueryProcessor::printRankedDocuments(
    const std::vector<SearchResult> &results) const
{
    if (results.empty())
    {
        std::cout << "No documents found!\n";
        return;
    }

    std::cout << "\nSearch Results\n";
    std::cout << "--------------\n";

    int rank = 1;

    for (const auto &result : results)
    {
        for (const auto &doc : documents)
        {
            if (doc.getId() == result.docId)
            {
                std::cout << rank++ << ". " << doc.getFilename() << "   Score: " << result.score << '\n';
                break;
            }
        }
    }
}