#include "ConverterJSON.h"
#include "exceptions.h"

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

ConverterJSON::ConverterJSON(const std::string configPath, const std::string requestsPath) {
    this->setConfigData(configPath);

    std::ifstream inRequests(requestsPath, std::ios::in);
    nlohmann::json jsonReader;
    inRequests >> jsonReader;
    inRequests.close();

    for (auto const& request : jsonReader["requests"]) {
        config.requests.push_back(request);
    }
}

void ConverterJSON::setConfigData(const std::string& path) {
    std::ifstream configIn(path, std::ios::in);
    if (configIn.is_open()) {
        nlohmann::json jsonReader;
        configIn >> jsonReader;
        configIn.close();

        if (!jsonReader.contains("config")) throw ConfigFieldMissing();

        if (!jsonReader["config"].contains("name") || !jsonReader["config"].contains("max_responses") || !jsonReader["config"].contains("version")) throw AnyFieldMissing();
        config.name = jsonReader["config"]["name"];
        config.max_responses = jsonReader["config"]["max_responses"];
        config.version = jsonReader["config"]["version"];

        if (jsonReader.find("files") != jsonReader.end()) {
            for (auto const &file : jsonReader["files"]) {
                config.files.push_back(file);
            }
        }

        for (auto& file : config.files) {
            std::ifstream fileIn(file);

            try {
              if (!fileIn.is_open()) throw FileNotExists();
            } catch(FileNotExists x) {
                std::cerr << "file in res/: " << x.what() << std::endl;
            }
        }
    } else {
        throw ConfigMissing();
    }
}

std::string ConverterJSON::GetDocumentContent(const std::string &path) const {
    std::ifstream file(path, std::ios::in);
    std::string answer, buff;

    if (!file.is_open()) throw FileNotExists();
    while (file) {
        std::getline(file, buff);
        answer.append(buff);
        if (!file.eof()) answer.append("\n");
        buff.clear();
    }
    if (answer.length() <= 1) throw FileIsEmpty();
    for (auto &c: answer) c = (char) tolower(c);

    return answer;
}

std::vector<std::string> ConverterJSON::GetTextDocuments() const {
    std::vector<std::string> result;
    for (const auto &file: config.files) {
        try {
            result.push_back(this->GetDocumentContent((std::string) file));
        } catch (FileNotExists &x) {
            std::cout << "file in res/: " << x.what() << std::endl;
        } catch (FileIsEmpty &x) {
            std::cout << "file in res/: " << x.what() << std::endl;
        }
    }

    return result;
}

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> &answers, const std::string& answersPath) const {
    std::ofstream file(answersPath, std::ios::out | std::ios::trunc);
    nlohmann::json doc;

    doc["answers"];
    for (int i = 0; i < answers.size(); i++) {
        std::string request = "request" + std::to_string(i);
        auto relevanceVector = answers[i];
        doc.find("answers").value()[request];

        if (relevanceVector.size() > 1) {
            int limit = 0;
            doc.find("answers").value().find(request).value()["relevance"];
            for (auto data: relevanceVector) {
                limit++;
                doc.find("answers").value().find(request).value().find("relevance").value()["docid: " + std::to_string(data.doc_id)] = "rank: " + std::to_string(data.rank);
            }
            doc.find("answers").value().find(request).value()["result"] = "true";
        } else if (relevanceVector.size() == 1) {
            doc.find("answers").value().find(request).value()["docid: " + std::to_string(relevanceVector.back().doc_id)] = "rank: " + std::to_string(relevanceVector.back().rank);
            doc.find("answers").value().find(request).value()["result"] = "true";
        } else {
            doc.find("answers").value().find(request).value()["result"] = "false";
        }
    }
    file << doc;
    file.close();
}