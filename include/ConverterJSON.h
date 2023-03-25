#pragma once

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
    std::vector<std::string> GetTextDocuments();

    /* @return max_responses from config.json */
    int GetResponseLimit();

    /* @return list of requests included in requests.json */
    std::vector<std::string> GetRequests();

    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
  
  private:
    std::unique_ptr<ConfigData> config = nullptr;

  protected:
    void setConfigData(const std::string path);      // read config.json and requests.json into ConfigData
};