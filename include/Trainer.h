/**
 * @file Trainer.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-25
 * 
 * @copyright Copyright (c) 2019
 * 
*/
#ifndef TRAINER_H
#define TRAINER_H

#include <array>
#include <cstdint>
#include <memory>
#include <type_traits>

#include "Move.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "MoveManager.h"
#include "RaiiFileHandle.h"

namespace monsterbattle
{
    class Trainer
    {
        public:

        static constexpr auto CommentChar = '#';
        static constexpr auto DefaultName = "NAME_NOT_SPECIFIED";
        static constexpr uint8_t PartyCount = 6;

        Trainer();
        Trainer(const std::string& name);
        Trainer(const Trainer& other) = delete;
        ~Trainer() noexcept = default;

        /**
         * @brief Uses the currently selected move to attack the opponent
         * 
         * @param opponent Mopnstger to attack
         * @return true When attack hits
         * @return false When attack misses
        */
        bool attack(monster::Monster& opponent);

        monster::Monster& getCurrentMonster();
        const std::array<std::unique_ptr<monster::Monster>, Trainer::PartyCount>& getMonsters() const;
        const std::string& getName() const;
        
        /**
         * @brief Loads a trainer from a file
         * 
         * @param filename 
        */
        void loadFromFile(const std::string& filename);

        /**
         * @brief Loads a singular member to add to the party
         * 
         * @param str Monster should be formatted like this: {MONSTER_NAME, NICK_NAME}
         * @return true When a monster can be added
         * @return false When a monster can not be added
        */
        bool loadMemberFromString(const std::string& str);

        void selectMove(uint8_t moveIndex);
        void selectMove(const std::string& name);
        void selectMonster(uint8_t monsterIndex);

        private:

        const std::string name;
        std::array<std::unique_ptr<monster::Monster>, Trainer::PartyCount> party;
        uint8_t selectedMonsterIndex;

        bool addToParty(const std::string& name, const std::string& nickname);

    };
}

#endif