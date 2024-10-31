#include "dotenvloader.hpp"

#include <iostream>

int main() {
    dotenvloader::load();

    std::cout << std::getenv("TEST") << std::endl;
    std::cout << std::getenv("hello") << std::endl;

    return 0;
}