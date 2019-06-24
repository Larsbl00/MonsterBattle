#include <iostream>
#include <thread>


#include "Game.h"
#include "IDisplay.h"
#include "IDisplayable.h"
#include "Vector.h"
#include "DisplayManager.h"
#include "TerminalDisplay.h"
#include "TypeWeaknessManager.h"
#include "Monster.h"

int main(void)
{
    auto& displayManager = monsterbattle::DisplayManager::getInstance();

    displayManager.setDisplay(std::shared_ptr<monsterbattle::IDisplay>(new monsterbattle::TerminalDisplay));

    monsterbattle::Game game;

    monsterbattle::monster::Monster test("Charmander", {255, 12, 12, 0.9, 0.1, 123}, monsterbattle::Type::FIRE);

    return 0;
}
