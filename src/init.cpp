#include "../include/repository.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

void init() {

    if (fs::exists(".mygit")) {
        std::cout << "Repository already initialized\n";
        return;
    }

    fs::create_directory(".minigit");
    fs::create_directory(".minigit/objects");
    fs::create_directory(".minigit/refs");

    std::ofstream head(".mygit/HEAD");
    head << "refs/main";
    head.close();

    std::cout << "Initialized empty MiniGit repository\n";
}