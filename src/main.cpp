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


    auto& monsterManager = monsterbattle::monster::MonsterManager::getInstance();

    auto temp = monsterManager.getMonsterCopy("Thor");

    monsterbattle::Trainer test("John");

    for (auto& i : test.getCurrentMonster().getMoves())
    {
        if (i != nullptr) std::cout << i->getName() << std::endl;
    }

    displayManager.addToRenderQueue(&temp);
    displayManager.render();
    displayManager.displayAllItems();

    return 0;
}
