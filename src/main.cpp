#include <iostream>
#include <thread>
#include <cstdio>
#include <unistd.h>
#include <getopt.h>

#include "Game.h"
#include "Vector.h"
#include "DisplayManager.h"
#include "TerminalDisplay.h"
#include "TerminalInputReader.h"
#include "Monster.h"
#include "Model.h"
#include "Trainer.h"

int main(int argc, char* argv[])
{
    std::string trainerFile;
    std::string cpuTrainerFile;
    std::string opponentTrainerFile;

    //Get input flags
    const static struct option longOptions[] = {
        {"trainer", required_argument, nullptr, 't'},
        {"opponent", required_argument, nullptr, 'o'},
        {"cpu-trainer", required_argument, nullptr, 'c'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, no_argument, nullptr, 0}
    };

    int optLong;
    int longIndex = 0;
    while ((optLong = getopt_long(argc, argv, "t:o:c:h", longOptions, &longIndex)) != -1)
    {
        switch (optLong)
        {
            case 't':
                trainerFile = optarg;
                break;
            
            case 'o':
                opponentTrainerFile = optarg;
                break;

            case 'c':
                cpuTrainerFile = optarg;
                break;

            case 'h':
                std::cout << "Trainer options:" << '\n' 
                <<"--trianer / -t: Selects a file for the 1st user" << '\n'
                <<"--opponent / -o: Selects a trainerfile for a seconds person, use it when you want to fight eachother" << '\n'
                <<"--cpu-trainer / -c: Selects the trainerfile for an automated opponent" << std::endl;
                break;
        
            default:
                std::cerr << "Unknown flag " << optLong << ", use -h or --help" << std::endl;
                break;
        }
    }
    

    monsterbattle::TerminalDisplay display;

    auto& displayManager = monsterbattle::DisplayManager::getInstance();
    
    monsterbattle::Game game("./assets", monsterbattle::TerminalInputReader::getInstance());

    displayManager.setDisplay(&display);

    monsterbattle::Trainer test("John");
    test.loadFromFile(trainerFile);
    
    for (auto& i : test.getMonsters())
    {
        if (i != nullptr)
            std::cout << "MON: " << *i << std::endl;
    }

    test.selectMonster(2);
    test.selectMove(1);

    std::cout << test.attack(test.getCurrentMonster()) << std::endl;
    std::cout << test.attack(test.getCurrentMonster()) << std::endl;

    std::cout << "Selected MON: " << test.getCurrentMonster() << std::endl;

    displayManager.render();
    displayManager.removeFromRenderQueue(nullptr);
    displayManager.displayAllItems();

    return 0;
}
