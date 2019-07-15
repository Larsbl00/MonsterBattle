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

#include <array>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <vector>

#include "IDisplayable.h"
#include "MoveManager.h"
#include "Model.h"
#include "Stats.h"
#include "Type.h"

#define MONSTER_TYPE_COUNT (2)
#define MONSTER_MOVE_COUNT (4)

namespace monsterbattle
{
    namespace monster
    {
        class Monster: public IDisplayable
        {
            public:
            const static constexpr uint8_t TypeCount = MONSTER_TYPE_COUNT;
            const static constexpr uint8_t MoveCount = MONSTER_MOVE_COUNT;

            Monster();
            Monster(const std::string& name, const Stats& stats, const std::string& modelFile, const Color& color, Type primaryType);
            Monster(const std::string& name, const Stats& stats, const std::string& modelFile, const Color& color, Type primaryType, Type secondaryType);

            Monster(const Monster& other) = default;

            virtual ~Monster() noexcept = default;

            bool attack(Monster& other);
            void addMove(const std::string& name);
            void addMoves(const std::vector<std::string>& names);
            void display(IDisplay& display);

            const std::array<const Move*, Monster::MoveCount>& getMoves() const;
            const std::string& getName() const;
            const std::string& getNickName() const; 
            const Stats& getStats() const;
            Stats& getStats();
            const std::array<Type, Monster::TypeCount>& getTypes() const;

            void move(const Vector2i32& direction);

            void setNickName(const std::string& nickName);
        

            private:
            Model model;
            std::array<const Move*, Monster::MoveCount> moves;
            std::string name;
            std::string nickName;
            Stats stats;
            std::array<Type, Monster::TypeCount> types;
        };
    }
}

#endif