/**
 * @file Monster.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-24
 * 
 * @copyright Copyright (c) 2019
 * 
*/
 
#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <cstdint>
#include <stdexcept>
#include <array>

#include "Stats.h"
#include "Type.h"

#define MONSTER_TYPE_COUNT (2)

namespace monsterbattle
{
    namespace monster
    {

        class Monster
        {
            public:
            const static constexpr uint8_t TypeCount = MONSTER_TYPE_COUNT;

            /**
             * @brief Construct a new Monster object with one type
             * 
             * @param name 
             * @param stats 
             * @param primaryType 
            */
            Monster(const std::string& name, const Stats& stats, Type primaryType);

            /**
             * @brief Construct a new Monster object with two types
             * 
             * @param name 
             * @param stats 
             * @param primaryType 
             * @param secondaryType 
            */
            Monster(const std::string& name, const Stats& stats, Type primaryType, Type secondaryType);

            Monster(const Monster& other) = default;

            virtual ~Monster() noexcept = default;

            bool attack(Monster& other);

            const std::string& getName() const;
            const std::string& getNickName() const; 
            const Stats& getStats() const;
            Stats& getStats();
            const std::array<Type, Monster::TypeCount>& getTypes() const;

            void setNickName(const std::string& nickName);
        

            private:
            std::string name;
            std::string nickName;
            Stats stats;
            std::array<Type, Monster::TypeCount> types;
        };
    }
}

#endif