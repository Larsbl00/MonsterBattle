/**
 * @file MonsterBattle.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-08-24
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef MONSTER_BATTLE_H
#define MONSTER_BATTLE_H

#include <ctime>
#include <cassert>

#include "IDisplay.h"
#include "DisplayManager.h"
#include "DisplayableTextManager.h"
#include "Singleton.h"
#include "TerminalDisplay.h"
#include "TerminalInputReader.h"
#include "Game.h"
#include "Vector.h"

namespace monsterbattle
{
    class MonsterBattle
    {
        public:

        static constexpr auto AssetDir = "./assets";
        static constexpr auto PlayerDefaultName = "PLAYER 1";
        static constexpr auto CpuDefaultName = "CPU";
        static constexpr auto EnemyDefaultName = "PLAYER 2";
        const static inline auto MinimumSize = Vector2i32(0, 16);

        MonsterBattle(IDisplay& display, const std::string& playerFile, const std::string& enemyFile, bool enemyIsBot, float updatesPerSecond);
        ~MonsterBattle() noexcept;

        /**
         * @brief Loads the data from the trainer files, and starts the visuals
         * 
         * @throw runtime_error Cannot load player file, file is corrupt
         * @throw runtime_error Cannot load enemy file, file is corrupt
         * @throw runtime_error Cannot load visuals, display not yet set when calling setup
         * @throw runtime_error Window too small, window does not meet the size requirements
         * 
        */
        void setup();
        void run();

        const IDisplay& getDisplay() const;
        bool getIsRunning() const;

        private:

        bool isRunning;
        Game game;
        IDisplay& display;
        int64_t millisSecondsPerUpdate;
        std::clock_t previousUpdateTime; 
        Trainer enemy;
        std::string enemyFile;
        Trainer player;
        std::string playerFile;

        MonsterBattle();

    };
}

#endif