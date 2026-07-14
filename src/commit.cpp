#include "../include/commit.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <iterator>


std::string getNextCommitId(){

    std::ifstream input(".minigit/next_commit");
    
    int id;
    input >> id;
    input.close();

    std::ofstream output(".minigit/next_commit");
    output << (id+1);
    output.close();

    return "commit" + std::to_string(id);

}

void commit(const std::string& message)
{   
    // check if .minigit exists
    if(!std::filesystem::exists(".minigit"))
    {
        std::cout << "Not a MiniGit repository\n";
        return;
    }


    
    // Read parent from refs/main
    std::ifstream refFile(".minigit/refs/main");
    std::string parent;
    
    std::getline(refFile, parent);
    
    if(parent.empty())
    {
        parent = "none";
    }
    refFile.close();
    
    // Read index content
    std::ifstream indexFile(".minigit/index");
    
    
    std::string indexContent(
        (std::istreambuf_iterator<char>(indexFile)),
        std::istreambuf_iterator<char>()
    );
    
    //check if index is empty or is there anything to commit 
    
    if(indexContent.empty())
    {
        std::cout << "Nothing to commit\n";
        return;
    }
    
    std::string commitId = getNextCommitId(); //runs after all validations, so doent increase false counter
    
    // Create commit file
    std::ofstream commitFile(
    ".minigit/commits/" + commitId
    );

    //writing commit
    commitFile << "Commit: " << commitId << '\n';
    commitFile << "Message: " << message << '\n';
    commitFile << "Parent: " << parent << '\n';
    commitFile << '\n';
    commitFile << indexContent;
    commitFile.close();

    //updating latest commit in refs 
    std::ofstream refUpdate(".minigit/refs/main");
    refUpdate << commitId;
    refUpdate.close();

    std::cout << "Created commit " << commitId << '\n';

}