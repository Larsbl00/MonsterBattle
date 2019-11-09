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
#include "DisplayableTextManager.h"

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
        assetDirectory(assetDir), enemyIsBot(enemyIsBot), gameState(GameState::GAME_STATE_IN_BATTLE), isUpdatingReader(true), inputReader(inputReader),
        inputThread(updateGameInput, std::ref(*this)), player(trainer), opponent(enemy)
    {

        //Load assets
        this->loadAssets();

        //Set delegate
        this->inputReader.setDelegate(this);

        this->player.selectMonster(0);
        this->opponent.selectMonster(0);
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

    void Game::stop()
    {
        this->isUpdatingReader = false;
    }

    bool Game::getIsRunning() const { return this->isUpdatingReader; }

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
        switch (this->gameState)
        {
            case GameState::GAME_STATE_IN_BATTLE:
                this->stateInBattle(pressedChar);
                break;

            case GameState::GAME_STATE_SELECTING_MONSTER:
                this->stateSelectingMonster(pressedChar);
                break;

            case GameState::GAME_STATE_SELECTING_MOVE:
                this->stateSelectingMove(pressedChar);
                break;
        }
    }

    void Game::stateEnd()
    {
        this->stop();
    }

    void Game::stateInBattle(char pressedChar)
    {
        switch (pressedChar)
        {
            case Game::SelectKey:
                this->gameState = this->selectedState;
                break;
            
            case Game::BackKey:
                this->stateEnd();
                break;
        
            case Game::LeftKey:
                this->selectedState = GameState::GAME_STATE_SELECTING_MONSTER;
                std::cout << "Selected Monster" << std::endl;
                break;

            case Game::RightKey:
                this->selectedState = GameState::GAME_STATE_SELECTING_MOVE;
                std::cout << "Selected Move" << std::endl;
                break;

            default:
                break;
        }
    }

    void Game::stateSelectingMonster(char pressedChar)
    {
        switch (pressedChar)
        {
            
            case Game::BackKey:
                this->gameState = GameState::GAME_STATE_IN_BATTLE;
                break;

            case Game::SelectKey:
                try
                {
                    this->player.selectMonster(this->monsterIndex);
                    this->gameState = GameState::GAME_STATE_IN_BATTLE;
                    this->moveIndex = 0;
                }
                catch(const std::out_of_range& e)
                {
                    std::cerr << "No monster present at selected index" << std::endl;
                }
            
                break;
            
            case Game::UpKey:
                this->monsterIndex--;
                if (this->monsterIndex >= this->player.getPartySize()) this->monsterIndex = 0; //Use greater than, because of unsigned values

                break;

            case Game::DownKey:
                this->monsterIndex++;
                if (this->monsterIndex >= this->player.getPartySize()) this->monsterIndex = this->player.getPartySize() - 1;

                break;

            default:
                break;
        }

    }

    void Game::stateSelectingMove(char pressedChar)
    {
        //Leave if there is no monster to select a move from
        if (!this->player.selectedMonster()) this->gameState = GameState::GAME_STATE_IN_BATTLE;

        switch (pressedChar)
        {
            case Game::BackKey:
                this->gameState = GameState::GAME_STATE_IN_BATTLE;
                break;

            case Game::SelectKey:
                try
                {
                    this->player.selectMove(this->moveIndex);
                    this->gameState = GameState::GAME_STATE_IN_BATTLE;
                }
                catch (const std::out_of_range& e)
                {
                    std::cerr << "No move found at given index" << std::endl;
                }
                break;

            case Game::UpKey:
                this->moveIndex--;
                if (this->moveIndex >= monster::Monster::MoveCount) this->moveIndex = 0; //Check for underflow, because of unsigned value

                break;
            
            case Game::DownKey:
                this->moveIndex++;
                if (this->moveIndex >= monster::Monster::MoveCount) this->moveIndex = monster::Monster::MoveCount - 1;

                break;

            default:
                break;
        }
    }
}