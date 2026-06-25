#include "../include/DocumentLoader.h"

#include <filesystem>
#include <fstream>




std::vector<Document> // this line refers to the return type of the function below.
DocumentLoader::loadDocuments(const std::string &folderPath)
{
    std::vector<Document> documents;

    int id = 1;

    for (const auto &entry : std::filesystem::directory_iterator(folderPath))
    {
        if (entry.path().extension() == ".txt")
        {
            // Read the file
            std::ifstream file(entry.path());

            std::string line;
            std::string content;

            while (std::getline(file, line))
            {
                content += line + '\n';
            }

            std::string filename= entry.path().filename().string();
            std::string filepath= entry.path().string();

            // Document doc(id, filename, filepath, content);
            // documents.push_back(doc);
            documents.emplace_back(id, filename, filepath, content);

            id++;

        }
    }
    return documents;
}