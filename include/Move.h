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

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <vector>
#include <stdexcept>

#include "Type.h"
#include "TypeWeaknessManager.h"

namespace monsterbattle
{
    namespace monster
    {
        class Monster; //Forward Decl
        
        class Move
        {
            public:
            
            Move() = default;
            /**
             * @brief Construct a new Move object
             * 
             * @param name The name of the move
             * @param attackType Move type, determines whether an attack is super effective
             * @param damage The Default damage it will deal, without any attack or defense stats
             * @param precision A normalized value showing the probabillity of hitting the opponent 
            */
            Move(const std::string& name, Type attackType, uint8_t damage, float precision);
            Move(const Move& other);
            virtual ~Move() noexcept = default;

            /**
             * @brief Uses the move against the 'oponent'
             * 
             * @param caller The monster calling the move
             * @param opponent The monstyer that is getting attacked
             * @return true If the move hits the target
             * @return false If the move misses the target
            */
            virtual bool use(Monster& caller, Monster& opponent) const;

            /**
             * @brief Loads a Move from simple string format;
             * 
             * @param str Format is as folows:
             *  (<NAME>,<TYPE_AS_INTEGER>,<DAMAGE>,<PRECISION>)
             * 
             * @throw runtime_error Incorrect data, exact number of data fields do not match
             * @throw out_of_range Format is not in correct form
             * 
            */
            void loadFromString(const std::string& str);

            Type getType() const;

            const std::string& getName() const;

            friend std::ostream& operator<<(std::ostream& str, const Move& move);
            friend std::istream& operator>>(std::istream& str, Move& move);

            protected:
            Type attackType;
            uint8_t damage;
            float precision;

            /**
             * @brief Get the Attack Multiplier
             * 
             * @param opponent 
             * @return const float 
            */
            float getAttackMultiplier(const Monster& opponent) const;

            private:
            std::string name;
        };
    }
}

#endif
