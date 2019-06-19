#include <iostream>
#include <thread>


#include "Game.h"
#include "IDisplay.h"
#include "IDisplayable.h"
#include "Vector.h"
#include "DisplayManager.h"
#include "TerminalDisplay.h"

void test()
{

}

int main(void)
{
    auto& displayManager = monsterbattle::DisplayManager::getInstance();
    displayManager.setDisplay(std::shared_ptr<monsterbattle::IDisplay>(new monsterbattle::TerminalDisplay));

    displayManager.displayAllItems();
    monsterbattle::Game game;


    test();

    displayManager.displayAllItems();

    return 0;
}
