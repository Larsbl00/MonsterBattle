/**
 * @file Type.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-11
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "Type.h"

namespace monsterbattle
{
    std::ostream& operator<<(std::ostream& str, Type type)
    {
        return str << static_cast<int>(type);
    }
    std::istream& operator>>(std::istream& str, Type& type)
    {
        int temp = 0;
        
        str >> temp;
        type = static_cast<Type>(temp);

        return str;
    }
}