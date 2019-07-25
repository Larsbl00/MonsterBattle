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

namespace monsterbattle
{

    class Game: public InputDelegate
    {
        public:

        Game(InputReader& inputReader);
        Game(const Game& other) = delete;
        ~Game() noexcept;

        friend inline void updateGameInput(Game* game, bool& isUpdating);

        void operator=(const Game& other) = delete;

        private:
        bool isUpdatingReader;
        InputReader& inputReader;
        std::thread inputThread;


        void onKeyPress(char pressedKey);

    };
}

#endif