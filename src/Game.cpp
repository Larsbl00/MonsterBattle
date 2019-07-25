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
#include "Trainer.h"

#include "DisplayManager.h"

namespace monsterbattle 
{
     static auto& monstermanager = monster::MonsterManager::getInstance();
     static auto& moveManager = monster::MoveManager::getInstance();


    inline void updateGameInput(Game& game) noexcept
    {
        while (game.isUpdatingReader)
        {
            game.inputReader.update();
        }
        
    }

    /**************************
     * 
     * Constructor
     * 
     */
    Game::Game(const std::string& assetDir, InputReader& inputReader):
        assetDirectory(assetDir), isUpdatingReader(true), inputReader(inputReader), 
        inputThread(updateGameInput, std::ref(*this))
    {

        //Load assets
        this->loadAssets();

        //Set delegate
        this->inputReader.setDelegate(this);

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
        //Load Moves
        //moveManager.unload();
        monster::MoveManager::getInstance().load(this->assetDirectory + '/' + Game::MoveFileName);

        
        //Load Monsters
        //monstermanager.unload();
        monster::MonsterManager::getInstance().load(this->assetDirectory + '/' + Game::MonsterFileName);
    }

    void Game::onKeyPress(char pressedChar)
    {
        std::cout << "Pressed: " << pressedChar << std::endl;
    }
}