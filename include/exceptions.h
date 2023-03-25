#pragma once

#include <exception>

class ConfigMissing : public std::exception {
  public:
    inline const char* what() const noexcept override { return "Exception: config file is missing"; }
};

class ConfigFieldMissing : public std::exception {
  public:
    inline const char* what() const noexcept override { return "Exception: config field in config.json is missing"; }
};

class FileNotExists : public std::exception {
  public:
    inline const char* what() const noexcept override { return "Exception: file not exists"; }
};

class FileIsEmpty : public std::exception {
  public:
    inline const char* what() const noexcept override { return "Exception: file is empty"; }
};

class AnyFieldMissing : public std::exception {
  public:
    inline const char* what() const noexcept override { return "Exception: any field in config.json [config -> field] is missing"; }
};