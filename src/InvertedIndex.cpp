#include "InvertedIndex.h"

int InvertedIndex::countWordsInStr(const std::string &word, const std::string &str) const {
    if ((str.find(word) != std::string::npos && (str.find(word) == 0))
    || str[(str.find(word) - 1)] == ' ' 
    || str[(str.find(word) - 1)] == '\n')
        return 1 + countWordsInStr(word, str.substr(str.find(word) + word.length(), str.length()));

    return 0;
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) const {
    std::vector<Entry> result;
    for (int i = 0; i < this->docs.size(); ++i) {
      Entry entry = {i, this->countWordsInStr(word, this->docs[i])};
      
      if (entry.count > 0) result.push_back(entry);
    }

    return result;
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> docs) {
    this->docs = std::move(docs);
    this->freq_dictionary.clear();

    for (auto const& word : this->getWordsBaseFromDoc(this->docs)) {
        auto entryVectors = GetWordCount(word);
        auto freq_pair = std::make_pair(word, entryVectors);
        freq_dictionary.insert(freq_pair);
    }
}