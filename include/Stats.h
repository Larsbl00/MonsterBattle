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

#include <ostream>
#include <cstdint>

namespace monsterbattle
{
    namespace monster
    {
        struct Stats
        {
            /**
             * @brief Construct a new Stats object
             * 
             * @param health 
             * @param defense 
             * @param attack 
             * @param precision A normalized value displaying the probability of hitting an attack (value is based on 0.5)
             * @param avoidance A normalized value displaying the probability of avoiding an attack (value is based on 0.5)
             * @param speed 
            */
            Stats(int16_t health, uint8_t defense, uint8_t attack, float precision, float avoidance, uint8_t speed);

            Stats(const Stats& other) = default;
            ~Stats() noexcept = default;

            const int16_t maxHealth;    //Maximum health stat
            int16_t health;             //Health stat
            uint8_t defense;            //Defense stat
            uint8_t attack;             //Attack stat
            uint8_t speed;              //Speed stat

            float getAvoidance() const;
            float getPrecision() const;
            void setAvoidance(float avoidance);
            void setPresicion(float precision);

            friend std::ostream& operator<<(std::ostream& str, const Stats& stats);

            private:
            float precision;            //Precision, a normalized value showing the accuracy
            float avoidance;            //Avoidance, a normalized value displaying the probability of avoiding an attack
        };
    }  
}

#endif

