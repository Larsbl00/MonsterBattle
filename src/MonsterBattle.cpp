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
#define DEFINE_TO_STRING(DEF) (_AS_STRING(DEF))

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

    MonsterBattle::MonsterBattle(IDisplay& display, const std::string& playerFile, const std::string& enemyFile, bool enemyIsBot, float updatesPerSecond):
        isRunning(true), game(MonsterBattle::AssetDir, TerminalInputReader::getInstance(), this->player, this->enemy, enemyIsBot),
        display(display), millisSecondsPerUpdate(static_cast<uint64_t>((1/updatesPerSecond) * 1000)), previousUpdateTime(0),
        enemy(enemyIsBot ? MonsterBattle::CpuDefaultName : MonsterBattle::EnemyDefaultName), enemyFile(enemyFile), 
        player(MonsterBattle::PlayerDefaultName), playerFile(playerFile)
    {
        displayManager().setDisplay(&this->display);
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
        std::cout << "| MonsterBattle | Build: " << DEFINE_TO_STRING(BUILD_TYPE) << " | Version: v" << DEFINE_TO_STRING(VERSION) << " |" << std::endl;

        //Load trainers
        if (!loadTrainer(this->player, this->playerFile))
        {
            fprintf(stderr, "Error loading player '%s' from file: '%s'\n", this->player.getName().c_str(), this->playerFile.c_str());
            this->isRunning = false;
            return;
        }

        if (!loadTrainer(this->enemy, this->enemyFile))
        {
            fprintf(stderr, "Error loading enemy '%s' from file: '%s'\n", this->enemy.getName().c_str(), this->enemyFile.c_str());
            this->isRunning = false;
            return;
        }
    }

    void MonsterBattle::run()
    {
        if (!displayManager().getDisplayIsSet())
        {
            this->isRunning = false;
            return; 
        }

        auto now = clock();

        auto elapsedTime = static_cast<float>(now - this->previousUpdateTime) / 1000;

        if (elapsedTime >= this->millisSecondsPerUpdate)
        {
            this->previousUpdateTime = now;

            displayManager().render();
            displayManager().displayAllItems();
        }
    }

    bool MonsterBattle::getIsRunning() const { return this->isRunning; }

    /********************************
     * 
     * 
     * Private Functions
     * 
     */
}