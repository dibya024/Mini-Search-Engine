#pragma once

#include "Document.h"
#include "InvertedIndex.h"
#include "Ranker.h"

#include <vector>
#include <string>

class QueryProcessor
{
private:
    const std::vector<Document> &documents;
    const InvertedIndex &index;

    std::vector<int> intersect(const std::vector<int> &first, const std::vector<int> &second) const;
    std::vector<int> unite(const std::vector<int> &first, const std::vector<int> &second) const;
    std::vector<int> difference(const std::vector<int> &first, const std::vector<int> &second) const;
    std::vector<int> complement(const std::vector<int> &ids) const;

    enum class TokenType
    {
        TERM,
        PHRASE,
        AND,
        OR,
        NOT,
        LPAREN,
        RPAREN
    };

    struct QueryToken
    {
        TokenType type;
        std::string text;
    };
    std::vector<QueryToken> lexQuery(const std::string &query) const;

    void printDocuments(const std::vector<int> &ids) const;

    void printRankedDocuments(const std::vector<SearchResult> &results) const;

    std::vector<int> evaluateTerm(const QueryToken &token);
    std::vector<int> parseExpression();
    std::vector<int> parseOr();
    std::vector<int> parseAnd();
    std::vector<int> parseUnary();
    std::vector<int> parsePrimary();

    size_t currentToken = 0;
    std::vector<QueryToken> tokens;

    bool match(TokenType type) const;
    void consume(TokenType type);
    bool startsPrimary() const;

public:
    QueryProcessor(const std::vector<Document> &documents, const InvertedIndex &index);

    void run() const;
};