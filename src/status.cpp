#include "../include/status.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>

namespace fs = std::filesystem;

void status(){

    if(!fs::exists(".minigit"))
    {
        std::cout << "minigit repo does not exist" << std::endl;
        return;
    }


    //checking index for staged files

    std::unordered_set<std::string> tracked;

    std::vector<std::string> trackedFiles;
    std::vector<std::string> untrackedFiles;

    if(fs::exists(".minigit/index"))
    {    
        std::ifstream index(".minigit/index");
        std::string line;
        
        while(std::getline(index, line))
        {
        tracked.insert(line);
        }
    }

    for(const auto& entry : fs::directory_iterator("."))
    {
        std::string name = entry.path().filename().string();

        if(name == ".minigit")
            continue;

        else if(tracked.count(name))
            trackedFiles.push_back(name);
        
        else
            untrackedFiles.push_back(name);

        }

        std::cout << "On branch main\n\n";

            std::cout << "Tracked files:\n";

            if(trackedFiles.empty())
            {
                std::cout << "  (none)\n";
            }
            else
            {
                for(const auto& file : trackedFiles)
                {
                    std::cout << "  - " << file << '\n';
                }
            }

            std::cout << "\nUntracked files:\n";

            if(untrackedFiles.empty())
            {
                std::cout << "  (none)\n";
            }
            else
            {
                for(const auto& file : untrackedFiles)
                {
                    std::cout << "  - " << file << '\n';
                }
            }


}