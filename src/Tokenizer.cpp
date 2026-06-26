#include "../include/Tokenizer.h"

#include <sstream> //stringstream
#include <cctype>



std::vector<std::string>
Tokenizer::tokenize(const std::string &text) const
{
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string word;

    while (ss >> word)
    {
        word = normalizeWord(word);
        if (!word.empty())
        {
            tokens.push_back(word);
        }
    }
    return tokens;
}



std::string Tokenizer::normalizeWord(const std::string &word) const
{
    std::string res;

    for (char ch : word)
    {
        if (std::isalnum(static_cast<unsigned char>(ch)))
        {
            res += std::tolower(static_cast<unsigned char>(ch));
        }
    }

    return res;
}