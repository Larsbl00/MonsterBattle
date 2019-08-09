/**
 * @file MonsterManager.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-23
 * 
 * @copyright Copyright (c) 2019
 * 
*/
#ifndef MONSTER_MANAGER_H
#define MONSTER_MANAGER_H

#include "unordered_map"

#include "Monster.h"
#include "Singleton.h"
#include "RaiiFileHandle.h"

namespace monsterbattle 
{
    namespace monster
    {
        class MonsterManager:
            public Singleton<MonsterManager>
        {
            //Make the singleton a friend, so it can access the private constructor
            friend Singleton;

            public:

            static constexpr auto LineCommentChar = Monster::LineCommentChar;

            MonsterManager(const MonsterManager& other) = delete;
            ~MonsterManager() noexcept = default;

            /**
             * @brief Get the Monster object
             * 
             * @param name Name of the monster you want to get
             * @return const Monster* Returns a pointer to the monster, returns nullptr when the monster is not found 
            */
            const Monster* getMonster(const std::string& name) const;

            /**
             * @brief Get the Monster Copy object
             * 
             * @param name 
             * @return Monster Returns a copy of the requested monster
             * 
             * @throw runtime_error No monster with the requested alias was found
            */
            Monster getMonsterCopy(const std::string& name) const;

            /**
             * @brief Loads all monsterMap from a given file
             * 
             * @param fileName 
             * 
             * @throw runtime_error Data file is corrupted, more args found thgan present
             * @throw out_of_range The input format is incorrect
            */
            void load(const std::string& fileName);

            /**
             * @brief Unloads all stored data
             * 
            */
            void unload();

            private:
            std::unordered_map<std::string, Monster> monsterMap;

            MonsterManager() = default;

            void addMonster(Monster&& monster);
            void removeMonster(const std::string& name);
        };
    }
}

#endif