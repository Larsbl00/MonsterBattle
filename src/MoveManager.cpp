/**
 * @file MoveManager.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-11
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "MoveManager.h"

namespace monsterbattle
{
    namespace monster
    {
        /*************************
         * 
         * Constructor
         * 
         */

        MoveManager::MoveManager()
        {}

        /**************************
         * 
         * Public Functions
         * 
         */

        MoveManager& MoveManager::getInstance()
        {
            static MoveManager manager;
            return manager;
        }

        const Move* MoveManager::getMove(const std::string& name) const 
        {
            auto move = this->moveMap.find(name);

            if (move == this->moveMap.end()) return nullptr;
            else return &move->second;
        }

        void MoveManager::load(const std::string& file)
        {
            RaiiFileHandle handler(file);

            for (std::string move; getline(handler.stream, move, '\n'); )
            {
                Move attackMove;
                attackMove.loadFromString(move);
                this->addMove(std::move(attackMove));
            }
        }

        void MoveManager::unload()
        {
            this->moveMap.erase(this->moveMap.begin(), this->moveMap.end());
        }

        /**************************
         * 
         * Private Functions
         * 
         */
        void MoveManager::addMove(Move&& move)
        {
            this->moveMap.insert({move.getName(), move});
        }
    }
}