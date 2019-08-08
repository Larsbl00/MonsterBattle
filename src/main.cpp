#include <iostream>
#include <thread>
#include <cstdio>


#include "Game.h"
#include "Vector.h"
#include "DisplayManager.h"
#include "TerminalDisplay.h"
#include "TerminalInputReader.h"
#include "Monster.h"
#include "Model.h"
#include "Trainer.h"

int main(void)
{
    monsterbattle::TerminalDisplay display;

    auto& displayManager = monsterbattle::DisplayManager::getInstance();
    
    monsterbattle::Game game("./assets", monsterbattle::TerminalInputReader::getInstance());

    displayManager.setDisplay(&display);

    monsterbattle::Trainer test("John");
    test.loadFromFile("./assets/Trainer0.txt");
    
    for (auto& i : test.getMonsters())
    {
        std::cout << "MON: " << *i << std::endl;
    }

    displayManager.render();
    displayManager.displayAllItems();

    return 0;
}
