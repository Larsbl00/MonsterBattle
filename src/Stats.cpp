/**
 * @file Stats.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-11
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "Stats.h"

#define IS_NORMALIZED(F) (!(F < 0) || (F > 1))

namespace monsterbattle
{
    namespace monster
    {
        /*******************
         * 
         * Constructor
         * 
         */
        Stats::Stats(int16_t health, uint8_t defense, uint8_t attack, float precision, float avoidance, uint8_t speed):
            maxHealth(health), health(health), defense(defense), attack(attack), 
            speed(speed)
        {
            this->setAvoidance(avoidance);
            this->setPresicion(precision);
        }

        /***********************
         * 
         * Functions
         * 
         */

        float Stats::getAvoidance() const { return this->avoidance; }
        float Stats::getPrecision() const { return this->precision; }

        void Stats::setAvoidance(float avoidance) 
        {
            if (IS_NORMALIZED(avoidance)) this->avoidance = avoidance;
            else throw std::invalid_argument("Value not normalized for Stats::avoidance");
        }

        void Stats::setPresicion(float precision) 
        {
            if (IS_NORMALIZED(precision)) this->precision = precision;
            else throw std::invalid_argument("Value not normalized for Stats::avoidance");
        }


        std::ostream& operator<< (std::ostream& str, const Stats& stats)
        {
            return str 
            << "{(" 
            << (int)stats.health 
            << '/' 
            << (int)stats.maxHealth 
            << "),"
            << (int)stats.defense
            << ','
            << (int)stats.attack 
            << ','
            << stats.precision 
            << ','
            << stats.avoidance
            << ','
            << (int)stats.speed
            << '}';
        }


    }
}