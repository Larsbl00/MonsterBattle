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

int main(void)
{
    monsterbattle::TerminalDisplay display;

    auto& displayManager = monsterbattle::DisplayManager::getInstance();

    displayManager.setDisplay(&display);
    display.setPixel(monsterbattle::Vector2i32(10,10), '#', monsterbattle::Color::Blue);
    display.setPixel(monsterbattle::Vector2i32(11,10), '!', monsterbattle::Color::White);
    display.setPixel(monsterbattle::Vector2i32(12,10), monsterbattle::Color::Cyan);

    monsterbattle::Game game;

    monsterbattle::Model spr("./assets/test.txt");
    spr.setColor(monsterbattle::Color::Red);
    spr.load();
    monsterbattle::Sprite copy(spr.getBuffer());
    copy.setColor(monsterbattle::Color::Cyan);
    copy.flipVertical();
    copy.move(std::move(monsterbattle::Vector2i32(0, 5)));

    displayManager.addToRenderQueue(&spr);
    displayManager.addToRenderQueue(&copy);
    displayManager.render();
    displayManager.displayAllItems();


    monsterbattle::monster::Monster test("Charmander", {255, 255, 12, 12, 0.9, 0.1, 123}, monsterbattle::Type::FIRE);

    return 0;
}
