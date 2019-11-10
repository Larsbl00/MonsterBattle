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
    constexpr auto displayManager = &DisplayManager::getInstance;
    constexpr auto monsterManager = &monster::MonsterManager::getInstance;
    constexpr auto moveManager = &monster::MoveManager::getInstance;
    constexpr auto textManager = &DisplayableTextManager::getInstance;

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

        //Call entry for default state
        this->onEnterInBattle();
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

        //Set text
        textManager().setBattleOptions({"Select Monster", "Select Move"});
        textManager().setSubtitle("Select an option");
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
                switch (this->gameState)
                {
                    case GameState::GAME_STATE_SELECTING_MONSTER:
                        this->onEnterSelectingMonster();
                        break;
                    case GameState::GAME_STATE_SELECTING_MOVE:
                        this->onEnterSelectingMove();
                        break;

                    default:
                        break;
                }

                this->onExitInBattle();

                break;
            
            case Game::BackKey:
                this->stateEnd();
                this->onExitInBattle();
                break;
        
            case Game::LeftKey:
                this->selectedState = GameState::GAME_STATE_SELECTING_MONSTER;
                textManager().selectBattleOption(0);
                break;

            case Game::RightKey:
                this->selectedState = GameState::GAME_STATE_SELECTING_MOVE;
                textManager().selectBattleOption(1);
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
                this->onExitSelectingMonster();
                this->onEnterInBattle();
                break;

            case Game::SelectKey:
                try
                {
                    //Select monster
                    this->player.selectMonster(this->monsterIndex);
                    //Move to correct position
                    Vector<int32_t> winSize =  displayManager().getDisplay()->getSize();
                    this->player.getCurrentMonster().moveTo(winSize * Game::RelativeMonsterLocationTrainer);


                    textManager().setMoveText(this->player.getCurrentMonster().getMoves());
                    textManager().selectMove(this->moveIndex, this->player.getCurrentMonster().getMoves());
                    this->moveIndex = 0;
                    this->gameState = GameState::GAME_STATE_IN_BATTLE;
                    this->onExitSelectingMonster();
                    this->onEnterInBattle();
                }
                catch(const std::out_of_range& e)
                {
                    textManager().setSubtitle(e.what());
                }
            
                break;
            
            case Game::UpKey:
                this->monsterIndex--;
                if (this->monsterIndex >= this->player.getPartySize()) this->monsterIndex = 0; //Use greater than, because of unsigned values
                textManager().selectPartyMember(this->monsterIndex);

                break;

            case Game::DownKey:
                this->monsterIndex++;
                if (this->monsterIndex >= this->player.getPartySize()) this->monsterIndex = this->player.getPartySize() - 1;
                textManager().selectPartyMember(this->monsterIndex);

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
                this->onExitSelectingMove();
                this->onEnterInBattle();
                break;

            case Game::SelectKey:
                try
                {
                    this->player.selectMove(this->moveIndex);
                    this->gameState = GameState::GAME_STATE_IN_BATTLE;
                    this->onExitSelectingMove();
                    this->onEnterInBattle();
                }
                catch (const std::out_of_range& e)
                {
                    textManager().setSubtitle(e.what());
                }
                break;

            case Game::UpKey:
                this->moveIndex--;
                if (this->moveIndex >= monster::Monster::MoveCount) this->moveIndex = 0; //Check for underflow, because of unsigned value
                textManager().selectMove(this->moveIndex, this->player.getCurrentMonster().getMoves());

                break;
            
            case Game::DownKey:
                this->moveIndex++;
                if (this->moveIndex >= monster::Monster::MoveCount) this->moveIndex = monster::Monster::MoveCount - 1;
                textManager().selectMove(this->moveIndex, this->player.getCurrentMonster().getMoves());

                break;

            default:
                break;
        }
    }

    void Game::onEnterInBattle()
    {
        for (auto& battleOpt : textManager().getBattleOptionText())
        {
            battleOpt.show();
        }

        for (auto& move : textManager().getMoveText())
        {
            move.hide();
        }
        
        for (auto& partyMember : textManager().getTrainerPartyText())
        {
            partyMember.hide();
        }

    }

    void Game::onEnterSelectingMonster()
    {
        for (auto& battleOpt : textManager().getBattleOptionText())
        {
            battleOpt.hide();
        }

        for (auto& move : textManager().getMoveText())
        {
            move.hide();
        }
        
        for (auto& partyMember : textManager().getTrainerPartyText())
        {
            partyMember.show();
        }
    }

    void Game::onEnterSelectingMove()
    {
        for (auto& battleOpt : textManager().getBattleOptionText())
        {
            battleOpt.hide();
        }

        for (auto& move : textManager().getMoveText())
        {
            move.show();
        }
        
        for (auto& partyMember : textManager().getTrainerPartyText())
        {
            partyMember.hide();
        }
    }


    void Game::onExitInBattle()
    {

    }

    void Game::onExitSelectingMonster()
    {

    }

    void Game::onExitSelectingMove()
    {

    }
}