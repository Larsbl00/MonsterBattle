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
            game.onKeyPress(-1);    
        }    
    }

    /**************************
     * 
     * Constructor
     * 
     */
    Game::Game(const std::string& assetDir, InputReader& inputReader, Trainer& trainer, Trainer& enemy, bool enemyIsBot):
        assetDirectory(assetDir), enemyIsBot(enemyIsBot), gameState(GameState::GAME_STATE_IN_BATTLE),
        isUpdatingReader(true), inputReader(inputReader),
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

    void Game::attack(Trainer& attacker, Trainer& victim)
    {
        auto& attackMonster = attacker.getCurrentMonster();
        auto& opponentMonster = victim.getCurrentMonster();
        auto preHealth = opponentMonster.getStats().health;
        bool hitOpponent = attacker.attack(opponentMonster);
        auto damage = preHealth - opponentMonster.getStats().health;

        std::stringstream attackString;
        attackString << attackMonster.getName() 
        << '(' << attackMonster.getStats().health << ')'
        << (hitOpponent ? " hit " : " missed ") << opponentMonster.getName() 
        << '(' << opponentMonster.getStats().health << ')'
        << (hitOpponent ? " for " + std::to_string(damage) : "")
        << '!';
        
        textManager().setSubtitle(attackString.str());
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    void Game::handleBattleScenario()
    {
        auto& playerMonster = this->player.getCurrentMonster();
        auto& opponentMonster = this->opponent.getCurrentMonster();

        auto attackOrder = (playerMonster.getStats().speed > opponentMonster.getStats().speed) ? 
                            std::array{&playerMonster, &opponentMonster} : std::array{&opponentMonster, &playerMonster};
    
        for (auto& order : attackOrder)
        {
            // If player is faster, attack with player
            if (order == &playerMonster)
            {   
                this->attack(this->player, this->opponent);
            }
            else if (order == &opponentMonster)
            {
                this->opponent.selectMove(this->opponent.getRandomMove());
                this->attack(this->opponent, this->player);
            }

            // If a monster is down, stop battle, switch when needed
            if (playerMonster.getStats().health <= 0) 
            { 
                textManager().setSubtitle("Your monster is out of health!");
                std::this_thread::sleep_for(std::chrono::seconds(1));
                this->gameState = GameState::GAME_STATE_SELECTING_MONSTER;  
                break;
            }
            // If cpu is down, select a new random
            else if (opponentMonster.getStats().health <= 0) 
            {
                try
                {
                    textManager().setSubtitle("The opponent's monster is out of health!");
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    this->opponent.selectMonster(this->opponent.getRandomMonster());
                    Vector<int32_t> winSize =  displayManager().getDisplay()->getSize();
                    this->opponent.getCurrentMonster().moveTo(winSize * Game::RelativeMonsterLocationOpponent);
                    break;
                }   
                catch (const std::logic_error& e)
                {
                    this->stateEnd();
                }
            }
        }
    }

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

            default:
                break;
        }
    }

    void Game::stateEnd()
    {
        textManager().setSubtitle("Game Over!");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        this->stop();
    }

    void Game::stateInBattle(char pressedChar)
    {
        this->onEnterInBattle();
        switch (pressedChar)
        {
            case Game::SelectKey:
                this->gameState = this->selectedState;
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
        this->onEnterSelectingMonster();

        uint8_t availableMonsters = 0;
        for (auto& mon : this->player.getMonsters())
        {
            //If every monster is down exit the game
            if (mon != nullptr && mon->getStats().health > 0)
            {
                availableMonsters++;
            }
        }

        if (availableMonsters == 0)
        {
            this->stateEnd();
        }

        switch (pressedChar)
        {
            
            case Game::BackKey:
                if (this->player.getCurrentMonster().getStats().health <= 0)
                {
                    textManager().setSubtitle("Select a healthy monster first!");
                }
                else 
                {
                    this->gameState = GameState::GAME_STATE_IN_BATTLE;
                    this->onExitSelectingMonster();
                }
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
                }
                catch(const std::out_of_range& e)
                {
                    textManager().setSubtitle(e.what());
                }
                catch(const std::logic_error& e)
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
        this->onEnterSelectingMove();
        //Leave if there is no monster to select a move from
        if (!this->player.selectedMonster()) this->gameState = GameState::GAME_STATE_IN_BATTLE;

        switch (pressedChar)
        {
            case Game::BackKey:
                this->gameState = GameState::GAME_STATE_IN_BATTLE;
                this->onExitSelectingMove();
                break;

            case Game::SelectKey:
                try
                {
                    this->player.selectMove(this->moveIndex);
                    this->gameState = GameState::GAME_STATE_IN_BATTLE;
                    this->handleBattleScenario();
                    this->onExitSelectingMove();
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