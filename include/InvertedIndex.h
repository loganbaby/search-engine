#pragma once

#include <mutex>
#include <thread>
#include <vector>
#include <set>
#include <string>
#include <map>

static std::mutex searchThreadLock;
static std::set<std::string> wordsBase;

struct Entry {
    int doc_id;
    int count;

    bool operator==(const Entry &other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};

class InvertedIndex {

public:
    InvertedIndex() = default;

    /* write new changed with erasing in the base of documents */
    void UpdateDocumentBase(std::vector<std::string> docs);

    /* get the count entries of the word into the base of documents */
    std::vector<Entry> GetWordCount(const std::string &word) const;

    /* @getter */
    inline const std::map<std::string, std::vector<Entry>> &getDictionary() const { return this->freq_dictionary; };

    /* @getter */
    inline std::vector<std::string> getDocs() const { return this->docs; };

  private:
    std::map<std::string, std::vector<Entry>> freq_dictionary;
    std::vector<std::string> docs;
};