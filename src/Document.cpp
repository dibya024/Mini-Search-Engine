#include "../include/Document.h"

// Document::Document()
// {
//     id = 0;
//     wordCount = 0;
// }

// Document::Document() : id(0), filename(""), filepath(""), content(""), wordCount(0) {}

Document::Document() = default;

// Document::Document( int id, const std::string& filename, const std::string& filepath, const std::string& content){
// this->id= id;
// this->filename= filename;
// this->filepath= filepath;
// this->content= content;
// wordCount= 0;
// }

Document::Document(int id, const std::string &filename, const std::string &filepath, const std::string &content) : id(id), filename(filename), filepath(filepath), content(content), wordCount(0) {}

int Document::getId() const
{
    return id;
}

std::string Document::getFilename() const
{
    return filename;
}

std::string Document::getFilepath() const
{
    return filepath;
}

std::string Document::getContent() const
{
    return content;
}

int Document::getWordCount() const
{
    return wordCount;
}
