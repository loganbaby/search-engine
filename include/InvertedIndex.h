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

    /* earsing duplicates and commit splitted words to base of documents */
    inline static void getWordsFromFile(const std::string &str) {
        std::string word;
        for (auto &c: str) {
            if (c == ' ' || c == '\n') {
                searchThreadLock.lock();
                wordsBase.insert(word);
                searchThreadLock.unlock();
                word.clear();
                continue;
            }
            if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '-' || c == '+')
                word += (char) tolower(c);
        }
        if (word.length() != 0) {
            searchThreadLock.lock();
            wordsBase.insert(word);
            searchThreadLock.unlock();
        }
    }

    /* method for each document in threads [mutex using] */
    /* better use lock_guard -> deprecating warning */
    inline static std::set<std::string> getWordsBaseFromDoc(const std::vector<std::string> &data) {
        std::vector<std::thread> threads;
        for (auto &str: data) {
            threads.push_back(std::thread(getWordsFromFile, std::ref(str)));
        }
        for (auto &thr: threads) {
            thr.join();
        }
        return wordsBase;
    }

  protected:
    int countWordsInStr(const std::string &word, const std::string &str) const;

  private:
    std::map<std::string, std::vector<Entry>> freq_dictionary;
    std::vector<std::string> docs;
};