/**
 * @file Game.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef GAME_H
#define GAME_H

#include <thread>

#include "InputReader.h"
#include "InputDelegate.h"
#include "MonsterManager.h"
#include "MoveManager.h"
#include "Trainer.h"

namespace monsterbattle
{

    class Game: public InputDelegate
    {
        friend inline void updateGameInput(Game& game) noexcept;

        public:

        static constexpr auto MonsterFileName = "monsters.txt";
        static constexpr auto MoveFileName = "moves.txt";

        Game(const std::string& assetDir, InputReader& inputReader,  Trainer& trainer, Trainer& enemy, bool enemyIsBot);
        Game(const Game& other) = delete;
        ~Game() noexcept;

        void stop();

        void operator=(const Game& other) = delete;

        private:
        std::string assetDirectory;
        bool enemyIsBot;
        bool isUpdatingReader;
        InputReader& inputReader;
        std::thread inputThread;
        Trainer& player;
        Trainer& opponent;


        /**
         * @brief Loads the assets present in the asset directory
         * 
        */
        void loadAssets();
        void onKeyPress(char pressedKey);

    };
}

#endif