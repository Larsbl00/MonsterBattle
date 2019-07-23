/**
 * @file MonsterManager.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-23
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "MonsterManager.h"

namespace monsterbattle
{
    namespace monster
    {
        /********************
         * 
         * Public Functions
         * 
         */

        const Monster* MonsterManager::getMonster(const std::string& name) const
        {
            auto monster = this->monsterMap.find(name);

            //Check if monster is found or not
            if (monster == this->monsterMap.end()) return nullptr;
            else return &monster->second;
        }

        Monster&& MonsterManager::getMonsterCopy(const std::string& name) const
        {
            auto monster = this->getMonster(name);

            if (monster == nullptr) 
            {
                throw std::runtime_error("No monster named '" + name + "' is present");
                return std::move(Monster());
            }
            else 
            {
                return std::move(Monster(*monster));
            }
        }

        void MonsterManager::load(const std::string& fileName)
        {
            RaiiFileHandle file(fileName);

            for (std::string line; getline(file, line); )
            {
                //Check if it's a comment; if not, read the data
                auto index = line.find_first_not_of(' ') == SIZE_MAX ? 0 : line.find_first_not_of(' ');
                if(line[index] != MonsterManager::LineCommentChar)
                {
                    Monster temp;
                    temp.loadFromString(line);
                    this->addMonster(std::move(temp));
                }
            }
        }

        void MonsterManager::unload()
        {
            this->monsterMap.erase(this->monsterMap.begin(), this->monsterMap.end());
        }

        /********************
         * 
         * Private Functions
         * 
         */
        
        void MonsterManager::addMonster(Monster&& monster)
        {
            this->monsterMap.insert({monster.getName(), monster});
        }

        void MonsterManager::removeMonster(const std::string& name)
        {
            this->monsterMap.erase(name);
        }
    }
}
