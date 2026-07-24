#include "../include/InvertedIndex.h"
#include "../include/Tokenizer.h"

#include <algorithm>
#include <unordered_set>
#include <iostream>




void InvertedIndex::build(const std::vector<Document> &documents)
{
    Tokenizer tknzr;

    for (const auto &doc : documents)
    {
        std::vector<std::string> words = tknzr.tokenize(doc.getContent());

        std::unordered_map<std::string, std::vector<int>> wordPositions;

        for (size_t i= 0; i < words.size(); i++)
        {
            wordPositions[words[i]].push_back(static_cast<int>(i));
        }

        for (const auto& entry : wordPositions)
        {
            Posting post;

            post.docId= doc.getId();
            post.freq= entry.second.size();
            post.positions= entry.second;

            index[entry.first].push_back(post);
        }

    }
}



std::vector<int> InvertedIndex::search(const std::string &word) const
{
    auto it = index.find(word);
    if (it == index.end())
    {
        return {};
    }

    std::vector<int> ids;
    for (const Posting& post : it->second)
    {
        ids.push_back(post.docId);
    }

    return ids;
}



void InvertedIndex::print() const
{
    for (const auto &entry : index)
    {
        std::cout << entry.first << " : ";

        for (const Posting& post : entry.second)
        {
            std::cout << "(" << post.docId << ", " << post.freq << ") ";
        }
        std::cout << '\n';
    }
}



std::vector<Posting> InvertedIndex::searchPostings(const std::string& word) const
{
    auto it= index.find(word);

    if (it == index.end())
    {
        return {};
    }

    return it->second;

}



std::vector<int> InvertedIndex::phraseSearch(const std::vector<std::string>& words) const
{
    std::vector<int> res;
    if (words.empty())
    {
        return res;
    }
    std::vector<Posting> firstPosting= searchPostings(words[0]);

    if (firstPosting.empty())
    {
        return res;
    }

    for (const Posting& firstPost : firstPosting)
    {
        int docId = firstPost.docId;

        for (int startPos : firstPost.positions){
            bool phraseFound= true;

            for (size_t i= 1; i < words.size(); i++)
            {
                int expPos= startPos + static_cast<int>(i);

                std::vector<Posting> postings = searchPostings(words[i]);
                bool posFound= false;

                for (const Posting& post : postings)
                {
                    if (post.docId == docId)
                    {
                        for (int pos : post.positions)
                        {
                            if (pos == expPos)
                            {
                                posFound= true;
                                break;
                            }
                        }
                        break;
                    }
                }
                if (!posFound)
                {
                    phraseFound= false;
                    break;
                }
            }
            if (phraseFound)
            {
                res.push_back(docId);
                break;
            }

        }
    }

    return res;

}