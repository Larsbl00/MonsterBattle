/**
 * @file Move.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-11
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef MOVE_H
#define MOVE_H

#include "Monster.h"
#include "Type.h"

namespace monsterbattle
{
    namespace monster
    {
        class Move
        {
            public:
            /**
             * @brief Construct a new Move object
             * 
             * @param name The name of the move
             * @param attackType Move type, determines whether an attack is super effective
             * @param damage The Default damage it will deal, without any attack or defense stats
             * @param precision A normalized value showing the probabillity of hitting the opponent 
            */
            Move(const std::string& name, Type attackType, uint8_t damage, float precision);
            Move(const Move& other) = default;
            virtual ~Move() noexcept = default;

            /**
             * @brief Uses the move against the 'oponent'
             * 
             * @param caller The monster calling the move
             * @param opponent The monstyer that is getting attacked
            */
            void use(Monster& caller, Monster& opponent);

            const std::string& getName() const;

            private:
            std::string name;
            Type attackType;
            uint8_t damage;
            float precision;
        };
    }
}

#endif