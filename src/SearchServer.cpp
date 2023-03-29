#include <vector>
#include <sstream>
#include <map>
#include <string>

#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input, int responses_limit) const {
    std::vector<std::vector<RelativeIndex>> result;

    result.resize(queries_input.size());
    int query_id = 0;

    for (const auto& query : queries_input) {
        std::string word;
        std::map<std::string, std::vector<Entry>> sortedWords;

        std::stringstream queryContent(query);                  // setting content of query
        while (queryContent >> word) { sortedWords[word]; }

        for (auto& [word, docs_info] : sortedWords) { docs_info = this->invertedIndex.GetWordCount(word); }

        std::map<int, int> sortedDocid;
        for (const auto& [word, docs_info] : sortedWords) {
            for (auto doc_info : docs_info) { 
                sortedDocid[doc_info.doc_id] += doc_info.count; 
            }
        }

        if (!sortedDocid.empty()) {
            std::multimap<int, int> sortedCountofWords;

            for (auto it = rbegin(sortedDocid); it != rend(sortedDocid); ++it) {
                sortedCountofWords.emplace(it->second, it->first);
            }

            int max_count = rbegin(sortedCountofWords)->first;
            RelativeIndex index;

            for (auto it = rbegin(sortedCountofWords); it != rend(sortedCountofWords); ++it) {
                index.doc_id = it->second;
                index.rank = (it->first == max_count) ? 1.f : (float)(it->first) / max_count;
                result[query_id].push_back(index);

                if (--responses_limit == 0) break;           // returned response_limit (save data)
            }
        }

        ++query_id;
    }

    return result;
}