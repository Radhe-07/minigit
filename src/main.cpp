#include "../include/init.h"
#include "../include/status.h"
#include "../include/add.h"
#include "../include/commit.h"
#include "../include/log.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage: minigit <command>\n";
        return 1;
    }

    std::string command = argv[1];



    if (command == "init") {
        init();
    }
     
    else if (command == "status") {
        status();
    }

    else if(command == "add")
    {
        if(argc < 3)
        {
            std::cout << "Usage: minigit add <filename>\n";
            return 1;
        }

        add(argv[2]);
        }
    
    else if(command == "commit")
        {
            if(argc < 4 || std::string(argv[2]) != "-m")
            {
                std::cout << "Usage: minigit commit -m \"message\"\n";
                return 1;
            }

            commit(argv[3]);
        }
    
    else if(command == "log")
        {
            log();
        }

    else {
        std::cout << "Unknown command\n";
    }

    return 0;
}