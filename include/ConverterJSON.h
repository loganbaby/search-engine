#pragma once

#include "SearchServer.h"

#include <string>
#include <vector>
#include <memory>

struct ConfigData {            // struct of config.json, requests.json   [required]
    std::string name;
    std::string version;
    int max_responses;
    std::vector<std::string> files;
    std::vector<std::string> requests;
};

class ConverterJSON {
  public:
    explicit ConverterJSON(const std::string configPath, const std::string requestsPath);

    /* @return list with content of files, included in config.json */
    std::vector<std::string> GetTextDocuments() const;

    /* @return max_responses from config.json */
    inline int GetResponseLimit() const { return this->config->max_responses; };

    /* @return list of requests included in requests.json */
    inline std::vector<std::string> GetRequests() const { return this->config->requests; };

    void putAnswers(std::vector<std::vector<RelativeIndex>> &answers, const std::string& answersPath) const;
  
  private:
    std::unique_ptr<ConfigData> config = nullptr;

  protected:
    void setConfigData(const std::string& path);      // read config.json and requests.json into ConfigData

    std::string GetDocumentContent(const std::string& path) const;
};