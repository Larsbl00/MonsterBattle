#include <iostream>
#include <thread>


#include "Game.h"
#include "IDisplay.h"
#include "IDisplayable.h"
#include "Vector.h"
#include "DisplayManager.h"
#include "TerminalDisplay.h"
#include "TypeWeaknessManager.h"

int main(void)
{
    auto& displayManager = monsterbattle::DisplayManager::getInstance();

    displayManager.setDisplay(std::shared_ptr<monsterbattle::IDisplay>(new monsterbattle::TerminalDisplay));

    monsterbattle::Game game;

    return 0;
}
