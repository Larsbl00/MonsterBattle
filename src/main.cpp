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

    test.addMoves({"Tackle", "", "Freeze", "Chill"});


    monsterbattle::monster::Monster test2;
    test2.loadFromFile("./assets/monsters/test.txt");
    //std::cout << test2 << std::endl;
     

    displayManager.addToRenderQueue(&test);
    displayManager.render();
    displayManager.displayAllItems();

    std::cout << test << std::endl;

    return 0;
}
