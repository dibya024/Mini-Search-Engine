#include "../include/QueryProcessor.h"
#include "../include/Tokenizer.h"
#include "../include/Ranker.h"

#include <iostream>
#include <unordered_set>
#include <cctype>
#include <stdexcept>

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
            query = query.substr(1, query.size() - 2);
        }

        Tokenizer tknzr;
        std::vector<std::string> words = tknzr.tokenize(query);
        std::vector<std::string> queryTerms;

        for (const std::string &word : words)
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
            std::vector<int> res = index.phraseSearch(words);
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
                    res = unite(res, ids);
                    i++;
                }
            }
            else
            {
                std::vector<int> ids = index.search(words[i]);
                res = intersect(res, ids);
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

std::vector<QueryProcessor::QueryToken> QueryProcessor::lexQuery(const std::string &query) const
{
    std::vector<QueryToken> result;

    Tokenizer tknzr;
    size_t i = 0;

    while (i < query.size())
    {
        if (std::isspace(static_cast<unsigned char>(query[i])))
        {
            ++i;
            continue;
        }
        if (query[i] == '(')
        {
            result.push_back({TokenType::LPAREN, "("});
            ++i;
            continue;
        }
        if (query[i] == ')')
        {
            result.push_back({TokenType::RPAREN, ")"});
            ++i;
            continue;
        }
        if (query[i] == '"')
        {
            ++i;
            std::string phrase;
            while (i < query.size() && query[i] != '"')
            {
                phrase += query[i];
                ++i;
            }
            if (i < query.size() && query[i] == '"')
            {
                ++i;
            }
            std::vector<std::string> words = tknzr.tokenize(phrase);
            if (!words.empty())
            {
                std::string normalizedPhrase = words[0];
                for (size_t j = 1; j < words.size(); ++j)
                {
                    normalizedPhrase += " ";
                    normalizedPhrase += words[j];
                }
                result.push_back({TokenType::PHRASE, normalizedPhrase});
            }
            continue;
        }
        size_t start = i;
        while (i < query.size() && !std::isspace(static_cast<unsigned char>(query[i])) && query[i] != '(' && query[i] != ')')
        {
            ++i;
        }
        std::string rawWord = query.substr(start, i - start);
        std::vector<std::string> normalized = tknzr.tokenize(rawWord);

        if (normalized.empty())
            continue;
        std::string word = normalized[0];

        if (word == "and")
        {
            result.push_back({TokenType::AND, word});
        }
        else if (word == "or")
        {
            result.push_back({TokenType::OR, word});
        }
        else if (word == "not")
        {
            result.push_back({TokenType::NOT, word});
        }
        else
        {
            result.push_back({TokenType::TERM, word});
        }
    }
    return result;
}

std::vector<int> QueryProcessor::difference(const std::vector<int> &first, const std::vector<int> &second) const
{
    std::unordered_set<int> lookup(second.begin(), second.end());

    std::vector<int> res;

    for (int id : first)
    {
        if (!lookup.count(id))
            res.push_back(id);
    }
    return res;
}

std::vector<int> QueryProcessor::complement(
    const std::vector<int> &ids) const
{
    std::vector<int> allDocuments;

    for (int i = 0; i < static_cast<int>(documents.size()); ++i)
    {
        allDocuments.push_back(i);
    }

    return difference(allDocuments, ids);
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
    return std::vector<int>(uniqueIds.begin(), uniqueIds.end());
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

bool QueryProcessor::match(TokenType type) const
{
    return currentToken < tokens.size() && tokens[currentToken].type == type;
}

void QueryProcessor::consume(TokenType type)
{
    if (!match(type))
    {
        throw std::runtime_error("Unexpected token in query!");
    }
    ++currentToken;
}

bool QueryProcessor::startsPrimary() const
{
    return match(TokenType::TERM) || match(TokenType::PHRASE) || match(TokenType::LPAREN) || match(TokenType::NOT);
}

std::vector<int> QueryProcessor::parseUnary()
{
    if (match(TokenType::NOT))
    {
        consume(TokenType::NOT);

        std::vector<int> result = parseUnary();

        return complement(result);
    }

    return parsePrimary();
}

std::vector<int> QueryProcessor::parsePrimary()
{

    if (match(TokenType::TERM) || match(TokenType::PHRASE))
    {
        QueryToken token = tokens[currentToken];
        ++currentToken;

        return evaluateTerm(token);
    }
    if (match(TokenType::LPAREN))
    {
        consume(TokenType::LPAREN);
        std::vector<int> result = parseExpression();
        if (!match(TokenType::RPAREN))
        {
            throw std::runtime_error("Missing ')' in query!");
        }
        consume(TokenType::RPAREN);
        return result;
    }
    throw std::runtime_error("Search term Expected!");
}

std::vector<int> QueryProcessor::evaluateTerm(const QueryToken &token)
{
    Tokenizer tknzr;
    if (token.type == TokenType::TERM)
    {
        return index.search(token.text);
    }
    if (token.type == TokenType::PHRASE)
    {
        std::vector<std::string> words = tknzr.tokenize(token.text);
        return index.phraseSearch(words);
    }
    return {};
}

std::vector<int> QueryProcessor::parseExpression()
{
    return parseOr();
}

std::vector<int> QueryProcessor::parseOr()
{
    std::vector<int> result = parseAnd();

    while (match(TokenType::OR))
    {
        consume(TokenType::OR);

        std::vector<int> right = parseAnd();
        result = unite(result, right);
    }

    return result;
}

std::vector<int> QueryProcessor::parseAnd()
{
    std::vector<int> result = parseUnary();

    while (match(TokenType::AND) || startsPrimary())
    {
        if (match(TokenType::AND))
        {
            consume(TokenType::AND);
        }

        std::vector<int> right = parseUnary();

        result = intersect(result, right);
    }

    return result;
}