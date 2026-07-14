#include "../include/add.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

std::string getNextObjectId(){
      std::ifstream input(".minigit/next_object");

    int id;
    input >> id;
    input.close();

    std::ofstream output(".minigit/next_object");
    output << (id + 1);
    output.close();

    return "object" + std::to_string(id);
};

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

    // Read file content
    std::ifstream input(filename);

    std::string content(
        (std::istreambuf_iterator<char>(input)),
        std::istreambuf_iterator<char>()
    );

    // get object id
    std::string objectId = getNextObjectId();

    //create obj file
    std::ofstream objectFile(
    ".minigit/objects/" + objectId
    );

    objectFile << content;
    objectFile.close();



    std::unordered_map<std::string, std::string> tracked;

    if(fs::exists(".minigit/index"))
        {
        std::ifstream indexFile(".minigit/index");

        std::string trackedFile;
        std::string trackedObject;

        while(indexFile >> trackedFile >> trackedObject)
        {
            tracked[trackedFile] = trackedObject;
        }

        }

        tracked[filename] = objectId;
    
        
        std::ofstream index(".minigit/index");    
        for(const auto& entry : tracked)
        {
            index << entry.first
                << " "
                << entry.second
                << '\n';
        }
        index.close();
  
    std::cout << "Added " << filename << '\n';



}