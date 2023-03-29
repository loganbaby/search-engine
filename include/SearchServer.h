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

  public:
    explicit inline SearchServer(const InvertedIndex &idx) : invertedIndex(idx) {};

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string> &queries_input, int responseLimit) const;

    /* setter */
    inline void setResponseLimit(const int maxResponses) { this->maxResponses = maxResponses; }
};