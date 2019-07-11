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
            Stats(uint8_t health, uint8_t defense, uint8_t attack, float precision, float avoidance, uint8_t speed):
                maxHealth(health), health(health), defense(defense), attack(attack), 
                precision(precision), avoidance(avoidance), speed(speed)
            {}

            Stats(const Stats& other) = default;
            ~Stats() noexcept = default;

            const uint8_t maxHealth;    //Maximum health stat
            uint8_t health;             //Health stat
            uint8_t defense;            //Defense stat
            uint8_t attack;             //Attack stat
            float precision;            //Precision, a normalized value showing the accuracy
            float avoidance;            //Avoidance, a normalized value displaying the probability of avoiding an attack
            uint8_t speed;              //Speed stat
        };
    }  
}

#endif

