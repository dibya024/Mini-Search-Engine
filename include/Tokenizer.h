#pragma once

#include <vector>
#include <string>


class Tokenizer
{
    private:
        std::string normalizeWord(const std::string& word) const;

    public:
        std::vector<std::string> tokenize(const std::string& text) const;
};