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

        MoveManager::MoveManager():
            moveMap({
                {"TEST", Move("TEST", Type::FIRE, 10, 0.9)}
            })
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