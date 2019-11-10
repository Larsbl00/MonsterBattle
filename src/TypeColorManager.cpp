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
            {Type::NONE,        Color(255, 255, 255, 75)},
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
        auto color = this->typeColorMap.find(type);

        if (color == this->typeColorMap.end()) 
        {
            throw std::invalid_argument("No color present for given Type");
            return monsterbattle::Color::Black;
        }
        else return color->second;
    }
}
