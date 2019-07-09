/**
 * @file AnsiEffects.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-09
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "AnsiEffects.h"

namespace monsterbattle
{
    namespace text
    {
        std::ostream& operator<<(std::ostream& str, const AnsiTextEffect& effect)
        {
            return str << static_cast<int>(effect);
        }
    }
}