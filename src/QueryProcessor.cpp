#include "../include/QueryProcessor.h"

#include <iostream>

QueryProcessor::QueryProcessor(const std::vector<Document> &docs, const InvertedIndex &idx) : documents(docs), index(idx) {}




void QueryProcessor::search(const std::string &word) const
{
    std::vector<int> ids = index.search(word);

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



void QueryProcessor::run() const
{
    std::cout << "=========================\n";
    std::cout << "    Mini Search Engine\n";
    std::cout << "=========================\n";

    std::string query;

    while(true)
    {
        std::cout << "\nEnter search word ( or 'exit') : ";
        std::cin >> query;

        if (query == "exit")
        {
            break;
        }

        for (char& ch : query)
        {
            ch = std::tolower(static_cast<unsigned char>(ch));
        }
        search(query);

    }

    std::cout << "\nBye!\nSee you again!\n";

}