/**
 * @file TypeWeaknessManager.cpp
 * @author Lars Bloemers (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-06-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "TypeWeaknessManager.h"

namespace monsterbattle 
{
    /*********************
     * 
     * Constructors
     * 
     */
    TypeWeaknessManager::TypeWeaknessManager():
        weaknessMap(
            {
                {Type::FIRE,        {Type::WATER, Type::GROUND}},
                {Type::WATER,       {Type::GRASS, Type::ELECTRIC}},
                {Type::GRASS,       {Type::FIRE, Type::ICE}},
                {Type::GROUND,      {Type::GRASS, Type::WATER}},
                {Type::FLYING,      {Type::ELECTRIC, Type::ICE}},
                {Type::ICE,         {Type::FIRE, Type::GROUND}},
                {Type::ELECTRIC,    {Type::GROUND}}
            }
        )
    {}

    /*********************
     * 
     * Public Functions
     * 
     */
    const std::vector<Type>& TypeWeaknessManager::getWeaknesses(Type type) const
    {
        auto weaknesses = this->weaknessMap.find(type);

        if (weaknesses == this->weaknessMap.end())
        {
            throw std::invalid_argument("No weaknesses present for Type = " + static_cast<int>(type));
        }

        return weaknesses->second;
    }

}