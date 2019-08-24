#include <iostream>
#include <thread>
#include <cstdio>
#include <unistd.h>
#include <getopt.h>

#include "TerminalDisplay.h"
#include "MonsterBattle.h"


#define FPS (24)

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
        
            case '?':
                std::cerr << "Unknown flag, use -h or --help" << std::endl;
                break;

            default:
                std::cerr << "Unknown flag " << optLong << ", use -h or --help" << std::endl;
                break;
        }
    }

    //Check if a trainer file is selected
    if (trainerFile.empty())
    {
        std::cerr << "No trainer selected, terminating program..." << std::endl;
        exit(EXIT_FAILURE);
    }

    //Check is an opponent is selected
    if (opponentTrainerFile.empty() && cpuTrainerFile.empty())
    {
        std::cerr << "No enemy trainer selected, terminating program..." << std::endl;
        exit(EXIT_FAILURE);
    }

    //Check if enemy is bot or not
    bool enemyIsBot = !cpuTrainerFile.empty() && opponentTrainerFile.empty();

    monsterbattle::TerminalDisplay display;
    monsterbattle::MonsterBattle battle(display, trainerFile, enemyIsBot ? cpuTrainerFile : opponentTrainerFile, enemyIsBot, FPS);
    battle.setup();

    while (battle.getIsRunning())
    {
        battle.run();
    }

    return 0;
}
