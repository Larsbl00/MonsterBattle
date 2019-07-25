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

namespace monsterbattle
{

    class Game: public InputDelegate
    {
        friend inline void updateGameInput(Game& game) noexcept;

        public:

        const static constexpr auto MonsterFileName = "monsters.txt";
        const static constexpr auto MoveFileName = "moves.txt";

        Game(const std::string& assetDir, InputReader& inputReader);
        Game(const Game& other) = delete;
        ~Game() noexcept;

        void operator=(const Game& other) = delete;

        private:

        std::string assetDirectory;
        bool isUpdatingReader;
        InputReader& inputReader;
        std::thread inputThread;


        void loadAssets();
        void onKeyPress(char pressedKey);

    };
}

#endif