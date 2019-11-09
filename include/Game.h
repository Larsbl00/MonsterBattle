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

#include "GameStates.h"
#include "InputReader.h"
#include "InputDelegate.h"
#include "MonsterManager.h"
#include "MoveManager.h"
#include "Trainer.h"

namespace monsterbattle
{   
    class Game: 
        public InputDelegate
    {
        friend inline void updateGameInput(Game& game) noexcept;

        public:

        static constexpr auto BattleOptions = 2;
        static constexpr auto MonsterFileName = "monsters.txt";
        static constexpr auto MoveFileName = "moves.txt";

        static constexpr char SelectKey = '\n';
        static constexpr char BackKey = 127;
        static constexpr char UpKey = 'A';      //Lazy way to detect an arrow up press
        static constexpr char DownKey = 'B';    //Lazy way to detect an arrow down press
        static constexpr char RightKey = 'C';   //Lazy way to detect an arrow right press
        static constexpr char LeftKey = 'D';    //Lazy way to detect an arrow left press

        Game(const std::string& assetDir, InputReader& inputReader, Trainer& trainer, Trainer& enemy, bool enemyIsBot);
        Game(const Game& other) = delete;
        ~Game() noexcept;

        void stop();
        bool getIsRunning() const;

        void operator=(const Game& other) = delete;

        private:
        std::string assetDirectory;
        bool enemyIsBot;
        GameState gameState;
        GameState selectedState = GameState::GAME_STATE_SELECTING_MOVE;
        bool isUpdatingReader;
        InputReader& inputReader;
        std::thread inputThread;
        Trainer& player;
        Trainer& opponent;
        uint8_t moveIndex = 0;
        uint8_t monsterIndex = 0;



        /**
         * @brief Loads the assets present in the asset directory
         * 
        */
        void loadAssets();
        void onKeyPress(char pressedKey);

        void stateEnd();
        void stateInBattle(char pressedChar);
        void stateSelectingMonster(char pressedChar);
        void stateSelectingMove(char pressedChar);
    };
}

#endif