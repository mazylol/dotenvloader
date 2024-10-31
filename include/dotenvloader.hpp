#ifndef DOTENVLOADER_DOTENVLOADER_HPP
#define DOTENVLOADER_DOTENVLOADER_HPP

#include <vector>
#include <string>

class dotenvloader {
private:
    static std::vector<std::string> loadFile(const char *path = ".env");
    static void parseLine(const std::string &line);

public:
    [[maybe_unused]]
    static void load(const char *path);
    [[maybe_unused]]
    static void load();
};

#endif //DOTENVLOADER_DOTENVLOADER_HPP
