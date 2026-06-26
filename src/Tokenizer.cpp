#include "../include/Tokenizer.h"


#include <sstream>         //stringstream

std::vector<std::string>
Tokenizer::tokenize(const std::string& text)
{
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string word;

    while (ss >> word)
    {
        tokens.push_back(word);
    }
    return tokens;
}