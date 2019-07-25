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
#include <istream>
#include <string>
#include <stdexcept>
#include <ostream>
#include <vector>

#include "IDisplayable.h"
#include "IMoveable.h"
#include "RaiiFileHandle.h"
#include "MoveManager.h"
#include "Model.h"
#include "Stats.h"
#include "Type.h"
#include "TypeColorManager.h"

#define MONSTER_TYPE_COUNT (2)
#define MONSTER_MOVE_COUNT (4)
#define MONSTER_LINE_COMMENT_CHAR ('#')
#define MONSTER_ATTRIBUTE_SPLIT_CHAR (';')

namespace monsterbattle
{
    namespace monster
    {
        class Monster: 
            public IDisplayable, 
            public IMoveable
        {
            public:

            const static constexpr char AttributeSplitChar = MONSTER_ATTRIBUTE_SPLIT_CHAR;
            const static constexpr char LineCommentChar = MONSTER_LINE_COMMENT_CHAR;
            const static constexpr uint8_t MoveCount = MONSTER_MOVE_COUNT;
            const static constexpr uint8_t TypeCount = MONSTER_TYPE_COUNT;

            Monster();
            Monster(const std::string& name, const Stats& stats, const std::string& modelFile, const Color& color, Type primaryType);
            Monster(const std::string& name, const Stats& stats, const std::string& modelFile, const Color& color, Type primaryType, Type secondaryType);

            Monster(const Monster& other) = default;

            virtual ~Monster() noexcept = default;

            bool attack(Monster& other);
            void addMove(const std::string& name);
            void addMoves(const std::vector<std::string>& names);

            void display(IDisplay& display) override;

            const std::array<const Move*, Monster::MoveCount>& getMoves() const;
            const std::string& getName() const;
            const std::string& getNickName() const; 
            const Stats& getStats() const;
            Stats& getStats();
            const std::array<Type, Monster::TypeCount>& getTypes() const;

            /**
             * @brief Loads a monster from a single formatted string
             * 
             * 
             * @param str String must be formatted as the follows: 
             *  (<NICK_NAME>; <NAME>; <TYPES>; <STATS>; <MOVES>; <MODEL_FILE>;)
            */
            void loadFromString(const std::string& str);

            void move(const Vector2i32& direction) override;

            void setNickName(const std::string& nickName);
        

            friend std::ostream& operator<<(std::ostream& str, const Monster& mon);
            friend std::istream& operator>>(std::istream& str, Monster& mon);

            private:

            Model model;
            std::array<const Move*, Monster::MoveCount> moves;
            std::string name;
            std::string nickName;
            Stats stats;
            std::array<Type, Monster::TypeCount> types;

            void clearMoves();

            /**
             * @brief Sets the types when given a string formatted as such: {1,0}
             * 
             * @param str 
            */
            void loadTypeFromSubString(const std::string& str);

            /**
             * @brief Loads moves when given a formatted string
             * 
             * @param str Formated string must look like this: {MV1,MV2,MV3,MV4}
             *  *MVx: The name of a move
            */
            void loadMovesFromSubString(const std::string& str);
        };
    }
}

#endif