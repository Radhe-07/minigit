#include "../include/log.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void log()
{
    if (!fs::exists(".minigit"))
    {
        std::cout << "Not a MiniGit repository\n";
        return;
    }

    std::ifstream refFile(".minigit/refs/main");

    std::string currentCommit;
    std::getline(refFile, currentCommit);

    refFile.close();

    if (currentCommit.empty())
    {
        std::cout << "No commits found\n";
        return;
    }

    while (currentCommit != "none")
    {
        std::ifstream commitFile(
            ".minigit/commits/" + currentCommit
        );

        std::string commitLine;
        std::string messageLine;
        std::string parentLine;

        std::getline(commitFile, commitLine);
        std::getline(commitFile, messageLine);
        std::getline(commitFile, parentLine);

        std::cout << commitLine << '\n';
        std::cout << messageLine << '\n';
        std::cout << '\n';

        currentCommit = parentLine.substr(8);

        commitFile.close();
    }
}