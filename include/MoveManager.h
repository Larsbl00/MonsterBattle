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
#include <cstdio>

#include "Move.h"
#include "Type.h"
#include "RaiiFileHandle.h"
#include "Singleton.h"

#define MOVE_MANAGER_LINE_COMMENT_CHAR ('#')

namespace monsterbattle
{
    namespace monster
    {   
        class MoveManager:
            public Singleton<MoveManager>
        {
            friend Singleton;
            
            public:

            static constexpr char LineCommentChar = MOVE_MANAGER_LINE_COMMENT_CHAR;

            MoveManager(const MoveManager& other) = delete;
            ~MoveManager() noexcept = default;

            /**
             * @brief Gets move on based ona given name
             * 
             * @param name 
             * @return const Move* A pointer to the move, return nullptr if it is not found
            */
            const Move* getMove(const std::string& name) const;

            /**
             * @brief Loads all moves from a given file
             * 
             * @param file 
             * 
             * @throw runtime_error Incorrect data, exact number of data fields do not match
             * @throw out_of_range Format is not in correct form
            */
            void load(const std::string& file);

            void unload();

            private:
            MoveManager();

            std::unordered_map<std::string, Move> moveMap;

            void addMove(const Move& move);
        };
    }
}

#endif