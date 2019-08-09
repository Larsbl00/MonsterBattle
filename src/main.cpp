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
