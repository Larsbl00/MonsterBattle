#include <iostream>
#include <thread>
#include <cstdio>


#include "Game.h"
#include "IDisplay.h"
#include "IDisplayable.h"
#include "Vector.h"
#include "DisplayManager.h"
#include "TerminalDisplay.h"
#include "Monster.h"
#include "Model.h"
#include "MoveManager.h"
#include "MonsterManager.h"

int main(void)
{
    monsterbattle::TerminalDisplay display;

    auto& displayManager = monsterbattle::DisplayManager::getInstance();
    monsterbattle::monster::MoveManager::getInstance().load("./assets/moves.txt");

    displayManager.setDisplay(&display);
    display.setPixel(monsterbattle::Vector2i32(10,10), '#', monsterbattle::Color::Blue);
    display.setPixel(monsterbattle::Vector2i32(11,10), '!', monsterbattle::Color::White);
    display.setPixel(monsterbattle::Vector2i32(12,10), monsterbattle::Color::Cyan);


    auto& monsterManager = monsterbattle::monster::MonsterManager::getInstance();
    monsterManager.load("./assets/monsters.txt");

    auto temp = monsterManager.getMonsterCopy("BiggerBird");
    temp.getName();

    displayManager.addToRenderQueue(&temp);
    displayManager.render();
    displayManager.displayAllItems();

    return 0;
}
