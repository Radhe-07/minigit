#include "../include/add.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_set> 

namespace fs = std::filesystem;

void add(const std::string& filename)
{   
    if(!fs::exists(".minigit"))
    {
        std::cout << "Not a MiniGit repository\n";
        return;
    }
    
    if(!fs::exists(filename))
    {
        std::cout << "File does not exist\n";
        return;
    }

    std::unordered_set<std::string> tracked;
    if(fs::exists(".minigit/index"))
        {
            std::ifstream indexFile(".minigit/index");

            std::string line;

            while(std::getline(indexFile, line))
            {
                tracked.insert(line);
            }
        }
    if(tracked.count(filename))
        {
            std::cout << filename << " is already tracked\n";
            return;
        }    
    
    //Open for appending. Don't overwrite existing contents.
    std::ofstream index(".minigit/index", std::ios::app);
    index << filename << '\n';
    index.close();

    std::cout << "Added " << filename << '\n';



}