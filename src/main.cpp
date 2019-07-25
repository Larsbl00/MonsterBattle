#include <iostream>
#include <thread>
#include <cstdio>


#include "Game.h"
#include "IDisplay.h"
#include "IDisplayable.h"
#include "Vector.h"
#include "DisplayManager.h"
#include "TerminalDisplay.h"
#include "TerminalInputReader.h"
#include "Monster.h"
#include "Model.h"
#include "MoveManager.h"
#include "MonsterManager.h"

int main(void)
{
    monsterbattle::TerminalDisplay display;

    auto& displayManager = monsterbattle::DisplayManager::getInstance();
    
    monsterbattle::Game game("./assets", monsterbattle::TerminalInputReader::getInstance());

    displayManager.setDisplay(&display);


    auto& monsterManager = monsterbattle::monster::MonsterManager::getInstance();

    auto temp = monsterManager.getMonsterCopy("BiggerBird");
    temp.getName();

    displayManager.addToRenderQueue(&temp);
    displayManager.render();
    displayManager.displayAllItems();

    return 0;
}
