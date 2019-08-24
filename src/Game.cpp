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
    constexpr auto monsterManager = &monster::MonsterManager::getInstance;
    constexpr auto moveManager = &monster::MoveManager::getInstance;


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
    Game::Game(const std::string& assetDir, InputReader& inputReader, Trainer& trainer, Trainer& enemy, bool enemyIsBot):
        assetDirectory(assetDir), enemyIsBot(enemyIsBot), isUpdatingReader(true), inputReader(inputReader),
        inputThread(updateGameInput, std::ref(*this)), player(trainer), opponent(enemy)
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
        moveManager().unload();
        moveManager().load(this->assetDirectory + '/' + Game::MoveFileName);

        
        //Load Monsters
        monsterManager().unload();
        monsterManager().load(this->assetDirectory + '/' + Game::MonsterFileName);
    }

    void Game::onKeyPress(char pressedChar)
    {
        std::cout << "Pressed: " << pressedChar << std::endl;
    }
}