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
            name(name), nickName(name), stats(stats), types({primaryType, Type::NONE})
        {
        }

        Monster::Monster(const std::string& name, const Stats& stats, Type primaryType, Type secondaryType):
            name(name), nickName(name), stats(stats), types({primaryType, secondaryType})
        {
            
        }
    }
}