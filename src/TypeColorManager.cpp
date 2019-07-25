/**
 * @file TypeColorManager.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-25
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "TypeColorManager.h"

namespace monsterbattle
{
    /******************
     * 
     * Constructors
     * 
     */

    TypeColorManager::TypeColorManager():
        typeColorMap{
            {Type::NONE,        Color(255, 255, 255, 10)},
            {Type::FIRE,        Color(226, 88, 34)},
            {Type::WATER,       Color(0, 119, 190)},
            {Type::GRASS,       Color(124, 252, 0)},
            {Type::GROUND,      Color(225, 169, 95)},
            {Type::FLYING,      Color(124, 177, 205)},
            {Type::ICE,         Color(165, 242, 243)},
            {Type::ELECTRIC,    Color::Yellow}
        }
    {}

    /*******************
     * 
     * Public functions
     * 
     */

    const Color& TypeColorManager::getColorFromType(Type type)
    {
        return this->typeColorMap[type];
    }
}