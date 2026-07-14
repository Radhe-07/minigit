#include "../include/init.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>

namespace fs = std::filesystem;

void init() {

    if (fs::exists(".minigit")) {
        std::cout << "Repository already initialized\n";
        return;
    }

    fs::create_directory(".minigit");
    fs::create_directory(".minigit/objects");
    fs::create_directory(".minigit/commits");
    fs::create_directory(".minigit/refs");

    std::ofstream head(".minigit/HEAD");
    head << "refs/main";
    head.close();


    std::ofstream index(".minigit/index");
    index.close();

    std::ofstream mainRef(".minigit/refs/main");
    mainRef.close();

    std::ofstream nextObject(".minigit/next_object");
    nextObject << 1;
    nextObject.close();

    std::ofstream nextCommit(".minigit/next_commit");
    nextCommit << 1;
    nextCommit.close();

    std::cout << "Initialized empty MiniGit repository\n";
}