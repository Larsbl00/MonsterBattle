/**
 * @file Stats.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-24
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef STATS_H
#define STATS_H

#include <cstdint>

namespace monsterbattle
{
    namespace monster
    {
        struct Stats
        {
            uint8_t health;    //Health stat
            uint8_t defense;   //Defense stat
            uint8_t attack;    //Attack stat
            float precision;    //Precision, a normalized value showing the accuracy
            float avoidance;    //Avoidancem a normalized value displaying the probability of avoiding an attack
            uint8_t speed;     //Speed stat
        };
    }  
}

#endif
