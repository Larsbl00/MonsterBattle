/**
 * @file Monster.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-24
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "Monster.h"

namespace monsterbattle
{
    namespace monster
    {
        Monster::Monster(const std::string& name, const Stats& stats, Type primaryType):
            name(name), nickName(name), stats(stats), types{primaryType, Type::NONE}
        {
        }

        Monster::Monster(const std::string& name, const Stats& stats, Type primaryType, Type secondaryType):
            name(name), nickName(name), stats(stats), types{primaryType, secondaryType}
        {    
        }

        bool Monster::attack(Monster& other)
        {
            other.getName();
            throw std::runtime_error("Attack not yet implemented");
            return true;
        }

        const std::string& Monster::getName() const { return this->name; }
        const std::string& Monster::getNickName() const { return this->nickName; }
        const Stats& Monster::getStats() const { return this->stats; }
        const std::array<Type, Monster::TypeCount>& Monster::getTypes() const { return this->types; }

        void Monster::setNickName(const std::string& nickName) { this->nickName = nickName; }
    }
}