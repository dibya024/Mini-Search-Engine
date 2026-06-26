#include "../include/DocumentLoader.h"
#include "../include/Tokenizer.h"
#include "../include/InvertedIndex.h"

#include <iostream>

int main()
{

    DocumentLoader loader;
    Tokenizer tknzr;
    InvertedIndex index;

    std::vector<Document> docs= loader.loadDocuments("data");

    std::cout << "Documents Loaded : " << docs.size() << '\n';

    for(const auto& doc : docs)
    {
        std::cout << doc.getId() << " " << doc.getFilename() << '\n';

        std::vector<std::string> words = tknzr.tokenize(doc.getContent());

        for (const auto& word : words)
        {
            std::cout<<word<<'\n';
        }
        std::cout << "---------------------\n";
    }    

    index.build(docs);

    index.print();

    return 0;
}