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
#include "Move.h"

int main(void)
{
    monsterbattle::TerminalDisplay display;

    auto& displayManager = monsterbattle::DisplayManager::getInstance();

    displayManager.setDisplay(&display);
    display.setPixel(monsterbattle::Vector2i32(10,10), '#', monsterbattle::Color::Blue);
    display.setPixel(monsterbattle::Vector2i32(11,10), '!', monsterbattle::Color::White);
    display.setPixel(monsterbattle::Vector2i32(12,10), monsterbattle::Color::Cyan);

    monsterbattle::Game game;

    monsterbattle::Model spr("./assets/test.txt", monsterbattle::Color::Yellow);
    spr.load();
    monsterbattle::Sprite copy(monsterbattle::Vector2i32(0,5), spr.getBuffer(), monsterbattle::Color::Red);
    copy.flipVertical();

    displayManager.addToRenderQueue(&spr);
    displayManager.addToRenderQueue(&copy);
    displayManager.render();
    displayManager.displayAllItems();


    monsterbattle::monster::Monster test("Charmander", monsterbattle::monster::Stats(255, 100, 100, 0.5, 0.5, 112), monsterbattle::Type::ICE);

    monsterbattle::monster::Move yeet("Yeet", monsterbattle::Type::GROUND, 240, 0.9);
    std::cout << "Pre: " << test.getStats() << ", Hit: " << yeet.use(test, test) << ", Post: " << test.getStats() << std::endl;
    std::cout << "Pre: " << test.getStats() << ", Hit: " << yeet.use(test, test) << ", Post: " << test.getStats() << std::endl;
    std::cout << "Pre: " << test.getStats() << ", Hit: " << yeet.use(test, test) << ", Post: " << test.getStats() << std::endl;
    std::cout << "Pre: " << test.getStats() << ", Hit: " << yeet.use(test, test) << ", Post: " << test.getStats() << std::endl;
    std::cout << "Pre: " << test.getStats() << ", Hit: " << yeet.use(test, test) << ", Post: " << test.getStats() << std::endl; 

    return 0;
}
