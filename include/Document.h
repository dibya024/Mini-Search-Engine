#pragma once

#include <string>

class Document{
    private:
        int id;
        std::string filename;
        std::string filepath;
        std::string content;
        int wordCount;

    public:
        //Constructors
        Document();
        Document(int id, const std::string& filename, const std::string& filepath, const std::string& content);

        //Getters
        int getId() const;
        std::string getFilename() const;
        std::string getFilepath() const;
        std::string getContent() const;
        int getWordCount() const;

};