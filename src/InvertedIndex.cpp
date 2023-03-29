#include "InvertedIndex.h"

#include <sstream>
#include <vector>
#include <string>

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> docs) {
	std::vector<int> threadPacks;
	int required_threads = docs.size();

	this->docs.resize(required_threads);
	int threadsMax = std::thread::hardware_concurrency();
    
	while (required_threads > 0) {
		threadPacks.push_back((required_threads / threadsMax > 0) ? threadsMax : required_threads);
		required_threads -= threadsMax;
	}

	std::mutex mutexDocs;
    std::mutex mutexFreqDictionary;

	auto updatedDocsLambda = [&](const size_t& doc_id) {
		std::stringstream textDocument(docs[doc_id]);
		std::string word, text = "";

		while (textDocument >> word) {
			{
				std::lock_guard<std::mutex> lock(mutexFreqDictionary);
				freq_dictionary[word];
			}
			text += word + " ";
		}

		std::lock_guard<std::mutex> lock(mutexDocs);               // calling lock() deprecated, lock_guard better
		this->docs[doc_id] = text;
	};

	std::vector<std::thread> threads;
	std::size_t doc_id = 0;

	for (auto& threads_pack : threadPacks) {
		while (threads_pack-- != 0) { threads.push_back(std::thread(updatedDocsLambda, doc_id++)); }
    }

	for (int i = 0; i < threads.size(); ++i) {
		threads[i].join();
    }

	Entry entry;
	for (auto key_it = begin(freq_dictionary); key_it != end(freq_dictionary); ++key_it) {
		std::string key_word = key_it->first;

		for (entry.doc_id = 0; entry.doc_id < this->docs.size(); ++entry.doc_id) {
			std::string word;
			entry.count = 0;

            std::stringstream dataContent(this->docs[entry.doc_id]);
			while (dataContent >> word) { if (word == key_word) ++entry.count; }

			if (entry.count != 0) { key_it->second.push_back(entry); }
		}
	}
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) const {
	std::vector<Entry> vec;
	auto key = freq_dictionary.find(word);

	return (key != end(freq_dictionary)) ? key->second : vec;
}