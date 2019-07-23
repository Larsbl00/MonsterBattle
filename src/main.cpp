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

    //monsterbattle::Game game;

    monsterbattle::Model spr("./assets/models/test.txt", monsterbattle::Color::Yellow);
    spr.load();
    monsterbattle::Sprite copy(monsterbattle::Vector2i32(0,5), spr.getBuffer(), monsterbattle::Color::Red);
    copy.flipVertical();

    displayManager.addToRenderQueue(&spr);
    displayManager.addToRenderQueue(&copy);

    monsterbattle::monster::Monster test(
        "Charmander", 
        monsterbattle::monster::Stats(255, 100, 100, 0.5, 0.5, 112), 
        "./assets/models/test.txt",
        monsterbattle::Color::Blue, 
        monsterbattle::Type::ICE
    );


    auto& monsterManager = monsterbattle::monster::MonsterManager::getInstance();
    monsterManager.load("./assets/monsters.txt");

    auto temp = monsterManager.getMonsterCopy("SmallBird");
    temp.getName();

    //std::cout << temp << std::endl;
     

    displayManager.addToRenderQueue(&test);
    displayManager.addToRenderQueue(&temp);
    displayManager.render();
    displayManager.displayAllItems();

    return 0;
}
