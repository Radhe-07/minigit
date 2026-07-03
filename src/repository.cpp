#include "../include/repository.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

void Repository::init() {

    if (fs::exists(".mygit")) {
        std::cout << "Repository already initialized\n";
        return;
    }

    fs::create_directory(".mygit");
    fs::create_directory(".mygit/objects");
    fs::create_directory(".mygit/refs");

    std::ofstream head(".mygit/HEAD");
    head << "refs/main";
    head.close();

    std::cout << "Initialized empty MiniGit repository\n";
}