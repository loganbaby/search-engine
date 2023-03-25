#include "ConverterJSON.h"
#include "exceptions.h"

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

ConverterJSON::ConverterJSON(const std::string configPath, const std::string requestsPath) {
    this->config = std::make_unique<ConfigData>();
    this->setConfigData(configPath);

    std::ifstream inRequests(requestsPath);
    nlohmann::json jsonReader;
    inRequests >> jsonReader;
    inRequests.close();

    for (auto const& request : jsonReader["requests"]) {
        this->config->requests.push_back(request);
    }
}

void ConverterJSON::setConfigData(const std::string path) {
    std::ifstream configIn(path);
    if (configIn.is_open()) {
        nlohmann::json jsonReader;
        configIn >> jsonReader;
        configIn.close();

        if (!jsonReader.contains("config")) throw ConfigFieldMissing();

        if (!jsonReader["config"].contains("name") || !jsonReader["config"].contains("max_responses") || !jsonReader["config"].contains("version")) throw AnyFieldMissing();
        this->config->name = jsonReader["config"]["name"];
        this->config->max_responses = jsonReader["config"]["max_responses"];
        this->config->version = jsonReader["config"]["version"];

        if (jsonReader.find("files") != jsonReader.end()) {
            for (auto const &file : jsonReader["files"]) {
                this->config->files.push_back(file);
            }
        }

        for (auto& file : this->config->files) {
            std::ifstream fileIn(file);

            try {
              if (!fileIn.is_open()) throw FileNotExists();
            } catch(FileNotExists x) {
                std::cerr << x.what() << std::endl;
            }
        }
    } else {
        throw ConfigMissing();
    }
}