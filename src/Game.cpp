/**
 * @file Game.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Game.h"

#include "DisplayManager.h"

namespace monsterbattle 
{
    static auto& monstermanager = monster::MonsterManager::getInstance();
    static auto& moveManager = monster::MoveManager::getInstance();


    inline void updateGameInput(Game* game, bool& isUpdating)
    {
        while (isUpdating)
        {
            game->inputReader.update();
        }
        
    }

    /**************************
     * 
     * Constructor
     * 
     */
    Game::Game(const std::string& assetDir, InputReader& inputReader):
        assetDirectory(assetDir), isUpdatingReader(true), inputReader(inputReader), 
        inputThread(updateGameInput, this, std::ref(this->isUpdatingReader))
    {
        //Set delegate
        this->inputReader.setDelegate(this);

        //Load assets
        this->loadAssets();
    }

    Game::~Game() noexcept
    {
        //Stop updating the reader
        this->isUpdatingReader = false;

        //Wait for it to join
        if (this->inputThread.joinable()) this->inputThread.join();
    }

    /************************
     * 
     * Public Functions
     * 
     */


    /**************************************************
     * 
     * Private functions
     * 
     */

    void Game::loadAssets()
    {
        //Load Monsters
        monstermanager.load(this->assetDirectory + '/' + Game::MonsterFileName);

        //Load Moves
        moveManager.load(this->assetDirectory + '/' + Game::MoveFileName);
    }

    void Game::onKeyPress(char pressedChar)
    {
        std::cout << "Pressed: " << pressedChar << std::endl;
    }
}