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
                {Type::FIRE,        {Type::GROUND}},
                {Type::WATER,       {Type::GRASS, Type::ELECTRIC}},
                {Type::GRASS,       {Type::FIRE, Type::ICE}},
                {Type::GROUND,      {Type::GRASS, Type::WATER, Type::ICE}},
                {Type::FLYING,      {Type::ELECTRIC, Type::ICE}},
                {Type::ICE,         {Type::FIRE}},
                {Type::ELECTRIC,    {Type::GROUND}}
            }
        )
    {}

    TypeWeaknessManager::~TypeWeaknessManager() noexcept
    {

    }

    TypeWeaknessManager& TypeWeaknessManager::getInstance()
    {
        static TypeWeaknessManager manager;
        return manager;
    }

    std::vector<Type>& TypeWeaknessManager::getWeaknesses(Type type)
    {
        return this->weaknessMap[type];
    }

}