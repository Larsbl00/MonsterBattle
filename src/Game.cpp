/**
 * @file Game.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Game.h"

namespace monsterbattle 
{
    void updateGameInput(Game* game, bool& isUpdating)
    {
        while (isUpdating)
        {
            game->inputReader.update();
        }
        
    }

    Game::Game():
        isUpdatingReader(true), inputReader(*this), inputThread(updateGameInput, this, std::ref(this->isUpdatingReader))
    {
    }

    Game::~Game()
    {
        //Stop updating the reader
        this->isUpdatingReader = false;

        //Wait for it to join
        if (this->inputThread.joinable()) this->inputThread.join();
    }

    /**************************************************
     * 
     * Private functions
     * 
     */

    void Game::onKeyPress(char pressedChar)
    {
        std::cout << "Pressed: " << pressedChar << std::endl;
    }
}