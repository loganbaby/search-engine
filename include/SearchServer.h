#pragma once

#include "InvertedIndex.h"
#include <vector>
#include <string>

struct RelativeIndex {
    int doc_id;
    float rank;

    inline bool operator==(const RelativeIndex &other) const {
        return (doc_id == other.doc_id && (other.rank == rank));
    }
};

class SearchServer {
  private:
    InvertedIndex invertedIndex;
    int maxResponses;

  protected:
    /* get words strings from line document */
    std::vector<std::string> getWordsFromDocument(const std::string &str) const;

    /* get count of words in the one document */
    int countWordsInDocument(const std::string &word, int &doc_id) const;

    /* build the query with creating list of relevance */
    std::vector<RelativeIndex> getRelativeVector(const std::string &query) const;

  public:
    explicit inline SearchServer(const InvertedIndex &idx) : invertedIndex(idx) {};

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string> &queries_input) const;

    /* setter */
    inline void setResponseLimit(const int maxResponses) { this->maxResponses = maxResponses; }
};