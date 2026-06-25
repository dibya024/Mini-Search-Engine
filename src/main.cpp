#include "../include/DocumentLoader.h"
#include <iostream>

int main()
{

    DocumentLoader loader;
    std::vector<Document> docs= loader.loadDocuments("data");

    std::cout << "Documents Loaded : " << docs.size() << '\n';

    for(const auto& doc : docs)
    {
        std::cout << doc.getId() << " " << doc.getFilename() << '\n';
    }

    return 0;
}