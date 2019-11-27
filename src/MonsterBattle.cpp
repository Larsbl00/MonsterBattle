/**
 * @file MonsterBattle.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-08-24
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "MonsterBattle.h"

#define _AS_STRING(DEF) (#DEF)
#define TO_STRING(DEF) (_AS_STRING(DEF))
#define SMART_PTR_TO_C_PTR(SMART_PTR) (SMART_PTR == nullptr ? assert(SMART_PTR != nullptr) : &(*(SMART_PTR)))

namespace monsterbattle
{
    static constexpr auto displayManager = &monsterbattle::DisplayManager::getInstance;


    inline bool loadTrainer(monsterbattle::Trainer& trainer, const std::string& fileName)
    {
        try
        {
            trainer.loadFromFile(fileName);
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
            return false;
        }
        catch(const std::out_of_range& e)
        {
            std::cerr << e.what() << std::endl;
            return false;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Unexpected exception: " << e.what() << std::endl;
            return false;
        }

        return true;
    }


    /*****************************
     * 
     * Constructors
     * 
     */

    MonsterBattle::MonsterBattle(IDisplay& display, const std::string& playerFile, const std::string& enemyFile, float updatesPerSecond):
        isRunning(true), game(MonsterBattle::AssetDir, TerminalInputReader::getInstance(), this->player, this->enemy),
        display(display), millisSecondsPerUpdate(static_cast<uint64_t>((1/updatesPerSecond) * 1000)), previousUpdateTime(0),
        enemy(MonsterBattle::CpuDefaultName), enemyFile(enemyFile), 
        player(MonsterBattle::PlayerDefaultName), playerFile(playerFile)
    {  
        displayManager().setDisplay(&this->display);
        DisplayableTextManager::getInstance().setup(); 

        
        srand(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
    }

    MonsterBattle::~MonsterBattle() noexcept
    {
        this->game.stop();
        displayManager().setDisplay(nullptr);
    }

    /******************************
     * 
     * 
     * Public functions
     * 
     */
    void MonsterBattle::setup()
    {
        std::cout << "| MonsterBattle | Build: " << TO_STRING(BUILD_TYPE) << " | Version: v" << TO_STRING(VERSION) << " |" << std::endl;

        //Load trainers
        if (!loadTrainer(this->player, this->playerFile))
        {
            fprintf(stderr, "Error loading player '%s' from file: '%s'\n", this->player.getName().c_str(), this->playerFile.c_str());
            this->isRunning = false;
            throw std::runtime_error("Error loading given file for player");
        }

        if (!loadTrainer(this->enemy, this->enemyFile))
        {
            fprintf(stderr, "Error loading enemy '%s' from file: '%s'\n", this->enemy.getName().c_str(), this->enemyFile.c_str());
            this->isRunning = false;
            throw std::runtime_error("Error loading given file for enemy");
        }

        if (!displayManager().getDisplayIsSet()) 
        {
            std::cerr << "Cannot set visuals, display not yet set" << std::endl;
            this->isRunning = false;
            throw std::runtime_error("Display not yet set, cannot setup visuals");
        };

        //Check if the window is big enough to play
        if (this->display.getSize().x < this->MinimumSize.x || this->display.getSize().y < this->MinimumSize.y)
        {   
            std::cerr << "Window is too small, must be atleast " << this->MinimumSize << " was " << this->display.getSize() << std::endl;
            this->isRunning= false;
            throw std::runtime_error("Window is too small, use Check Monsterbattle::MinimumSize for more info");
        }

        Vector<int32_t> winSize =  displayManager().getDisplay()->getSize();

        //Set monsters for both trainers
        this->player.selectMonster(0);
        this->player.getCurrentMonster().moveTo(winSize * Game::RelativeMonsterLocationTrainer);


        this->enemy.selectMonster(0);
        this->enemy.getCurrentMonster().moveTo(winSize * Game::RelativeMonsterLocationOpponent);

        DisplayableTextManager::getInstance().setPartyText(this->player.getMonsters());
        DisplayableTextManager::getInstance().setMoveText(this->player.getCurrentMonster().getMoves());
        DisplayableTextManager::getInstance().selectMove(0, this->player.getCurrentMonster().getMoves());
    }

    void MonsterBattle::run()
    {
        this->isRunning = this->game.getIsRunning();

        if (!displayManager().getDisplayIsSet())
        {
            this->isRunning = false;
            return; 
        }

        auto now = clock();

        auto elapsedTime = static_cast<float>(now - this->previousUpdateTime) / 1000;

        if (elapsedTime >= this->millisSecondsPerUpdate)
        {
            displayManager().render();
            displayManager().displayAllItems();
            this->previousUpdateTime = now;
        }
    }

    const IDisplay& MonsterBattle::getDisplay() const { return this->display; }

    bool MonsterBattle::getIsRunning() const { return this->isRunning && this->game.getIsRunning(); }

    /********************************
     * 
     * 
     * Private Functions
     * 
     */
}