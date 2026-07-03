#include "../include/repository.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage: minigit <command>\n";
        return 1;
    }

    std::string command = argv[1];

    Repository repo;

    if (command == "init") {
        repo.init();
    }
    else {
        std::cout << "Unknown command\n";
    }

    return 0;
}