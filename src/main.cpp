#include <iostream>
#include <thread>


#include "Game.h"
#include "IDisplay.h"
#include "IDisplayable.h"
#include "Vector.h"
#include "DisplayManager.h"
#include "TerminalDisplay.h"

//Small function to change the stack, to see if the display manager still works properly
void test()
{
    int x=1,y=2,z=3;

    std::cout << x << y << z << std::endl;
}

struct TestItem: public monsterbattle::IDisplayable
{
    void display(monsterbattle::IDisplay& display)
    {   
        std::cout << display.getSize() << std::endl;
    }
};

int main(void)
{
    auto& displayManager = monsterbattle::DisplayManager::getInstance();
    displayManager.setDisplay(std::shared_ptr<monsterbattle::IDisplay>(new monsterbattle::TerminalDisplay));

    displayManager.addToRenderQueue(std::shared_ptr<monsterbattle::IDisplayable>(new TestItem));

    displayManager.displayAllItems();

    monsterbattle::Game game;


    test();

    displayManager.displayAllItems();

    return 0;
}
