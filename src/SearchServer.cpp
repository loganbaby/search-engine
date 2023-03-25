#include "SearchServer.h"
#include <algorithm>

int SearchServer::countWordsInDocument(const std::string &word, int &doc_id) const {
    int count = 0;

    for (const auto &pair: this->invertedIndex.getDictionary()) {
        if (pair.first == word) {
            for (auto const& data: pair.second) {
                if (data.doc_id == doc_id) count = data.count;
            }
        }
    }

    return count;
}

std::vector<std::string> SearchServer::getWordsFromDocument(const std::string &str) const {
    std::vector<std::string> result;
    std::string eachWord;

    for (auto const &c: str) {
        if ((c == ' ' || c == '\n') && eachWord.length() != 0) {
            result.push_back(eachWord);
            eachWord.clear();
            continue;
        }
        eachWord += (char) tolower(c);
    }
    if (eachWord.length() != 0) result.push_back(eachWord);
    return result;
}

std::vector<RelativeIndex> SearchServer::getRelativeVector(const std::string &query) const {
    std::vector<RelativeIndex> indexes;

    int absoluteRelevance[this->invertedIndex.getDocs().size()];
    float relevance[this->invertedIndex.getDocs().size()];

    for (int i = 0; i < this->invertedIndex.getDocs().size(); i++) {
        absoluteRelevance[i] = 0;
        relevance[i] = 0;
    }

    for (int i = 0; i < this->invertedIndex.getDocs().size(); i++) {
        for (const auto &word: this->getWordsFromDocument(query)) {
            absoluteRelevance[i] += this->countWordsInDocument(word, i);
        }
    }

    int maxRelevance = absoluteRelevance[0];

    for (const auto &i: absoluteRelevance) if (i >= maxRelevance) maxRelevance = i;
    if (maxRelevance == 0) return indexes;

    for (int i = 0; i < this->invertedIndex.getDocs().size(); i++) {
        relevance[i] = (float) absoluteRelevance[i] / (float) maxRelevance;
        if (relevance[i] > 0) indexes.push_back(RelativeIndex{i, relevance[i]});
    }

    return indexes;
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) const {
    std::vector<std::vector<RelativeIndex>> result;

    result.reserve(queries_input.size());
    for (auto &query: queries_input) result.push_back(this->getRelativeVector(query));

    for (auto &relativeVectors: result) {
        std::sort(relativeVectors.begin(), relativeVectors.end(), [](RelativeIndex index_1, RelativeIndex index_2) {
            if (index_1.rank > index_2.rank) return true;
            if (index_1.rank < index_2.rank) return false;
            if (index_1.doc_id < index_2.doc_id) return true;

            return false;
        });

        while (relativeVectors.size() > this->maxResponses) relativeVectors.pop_back();
    }

    return result;
}