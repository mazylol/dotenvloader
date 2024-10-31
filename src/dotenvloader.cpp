#include "dotenvloader.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>

void dotenvloader::load(const char *path) {
    auto lines = loadFile(path);

    for (const auto &line: lines) {
        parseLine(line);
    }
}

void dotenvloader::load() {
    auto lines = loadFile();

    for (const auto &line: lines) {
        parseLine(line);
    }
}

std::vector<std::string> dotenvloader::loadFile(const char *path) {
    std::ifstream file(path);

    std::vector<std::string> lines;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Trim preceding and trailing whitespaces
            line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
            line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(), line.end());

            // Skip empty lines and comments
            if (line.empty() || line[0] == '#') {
                continue;
            }

            lines.push_back(line);
        }
        file.close();
        return lines;
    } else {
        std::cerr << "Unable to open file!" << std::endl;
        return {};
    }
}

void dotenvloader::parseLine(const std::string &line) {
    std::string key;
    std::string value;

    auto keyEnd = line.find('=');

    if (keyEnd != std::string::npos) {
        key = line.substr(0, keyEnd);
        value = line.substr(keyEnd + 1, line.size() - keyEnd);
    } else {
        key = line;
        value = "";
    }

    setenv(key.c_str(), value.c_str(), 1);
}
