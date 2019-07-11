/**
 * @file MoveManager.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-11
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef MOVE_MANAGER_H
#define MOVE_MANAGER_H

#include <unordered_map>

#include "Type.h"
#include "Move.h"

namespace monsterbattle
{
    namespace monster
    {
        class MoveManager
        {
            public:
            ~MoveManager() noexcept = default;

            static MoveManager& getInstance();

            /**
             * @brief Gets move on based ona given name
             * 
             * @param name 
             * @return const Move* A pointer to the move, return nullptr if it is not found
            */
            const Move* getMove(const std::string& name) const;

            private:
            MoveManager();

            std::unordered_map<std::string, Move> moveMap;

            void addMove(Move&& move);
        };
    }
}

#endif