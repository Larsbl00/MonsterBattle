#include <iostream>
#include <thread>
#include <cstdio>


#include "Game.h"
#include "IDisplay.h"
#include "IDisplayable.h"
#include "Vector.h"
#include "DisplayManager.h"
#include "TerminalDisplay.h"
#include "TypeWeaknessManager.h"
#include "Monster.h"
#include "Model.h"
#include "MoveManager.h"

int main(void)
{
    monsterbattle::TerminalDisplay display;

    auto& displayManager = monsterbattle::DisplayManager::getInstance();

    displayManager.setDisplay(&display);
    display.setPixel(monsterbattle::Vector2i32(10,10), '#', monsterbattle::Color::Blue);
    display.setPixel(monsterbattle::Vector2i32(11,10), '!', monsterbattle::Color::White);
    display.setPixel(monsterbattle::Vector2i32(12,10), monsterbattle::Color::Cyan);

    //monsterbattle::Game game;

    monsterbattle::Model spr("./assets/test.txt", monsterbattle::Color::Yellow);
    spr.load();
    monsterbattle::Sprite copy(monsterbattle::Vector2i32(0,5), spr.getBuffer(), monsterbattle::Color::Red);
    copy.flipVertical();

    displayManager.addToRenderQueue(&spr);
    displayManager.addToRenderQueue(&copy);
    displayManager.render();
    displayManager.displayAllItems();


    monsterbattle::monster::Monster test("Charmander", monsterbattle::monster::Stats(255, 100, 100, 0.5, 0.5, 112), monsterbattle::Type::ICE);

    auto move = monsterbattle::monster::MoveManager::getInstance().getMove("TEST");

    if (move == nullptr) std::cerr << "Could not find move" << std::endl;
    else move->use(test, test);
    std::cout << *move << std::endl;

    monsterbattle::monster::Move mo;

    monsterbattle::RaiiFileHandle f("./assets/moves.txt");
    f.stream >> mo;
    f.stream >> mo;

    std::cout << mo << std::endl;

    return 0;
}
