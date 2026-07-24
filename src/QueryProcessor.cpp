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

        bool isPhraseQry = query.size() >= 2 && query.front() == '"' && query.back() == '"';

        if (isPhraseQry)
        {
            query= query.substr(1, query.size() - 2);
        }

        Tokenizer tknzr;
        std::vector<std::string> words = tknzr.tokenize(query);
        std::vector<std::string> queryTerms;

        for (const std::string& word : words)
        {
            if (word != "or")
            {
                queryTerms.push_back(word);
            }
        }

        if (words.empty())
        {
            continue;
        }

        if (isPhraseQry)
        {
            std::vector<int> res= index.phraseSearch(words);
            printDocuments(res);
            continue;
        }

        std::vector<int> res = index.search(words[0]);

        for (size_t i = 1; i < words.size(); i++)
        {
            if (words[i] == "or")
            {
                if (i + 1 < words.size())
                {
                    std::vector<int> ids = index.search(words[i + 1]);
                    res= unite(res, ids);
                    i++;
                }
            }
            else
            {
                std::vector<int> ids= index.search(words[i]);
                res= intersect(res, ids);
            }
        }

        Ranker ranker;

        auto rankedResults =
            ranker.rank(queryTerms, res, index, documents.size());

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

std::vector<int> QueryProcessor::unite(const std::vector<int> &first, const std::vector<int> &second) const
{
    std::unordered_set<int> uniqueIds;

    for (int id : first)
    {
        uniqueIds.insert(id);
    }

    for (int id : second)
    {
        uniqueIds.insert(id);
    }
    return std::vector<int> (uniqueIds.begin(), uniqueIds.end());
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