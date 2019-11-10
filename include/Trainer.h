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

#include "DisplayManager.h"
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
         * @param opponent Monster to attack
         * @return true When attack hits
         * @return false When attack misses
         * 
         * @throw runtime_error No monster is currently selected
         * 
        */
        bool attack(monster::Monster& opponent);

        /**
         * @brief Get the Current Monster object
         * 
         * @return monster::Monster&
         * 
         * @throw runtime_error No monster is currently selected
        */
        monster::Monster& getCurrentMonster();
        /**
         * @brief Checks if a monster has been selected
         * 
         * @return true 
         * @return false
        */
        bool selectedMonster() const;
        const std::array<std::unique_ptr<monster::Monster>, Trainer::PartyCount>& getMonsters() const;
        const std::string& getName() const;
        uint8_t getPartySize() const;
        /**
         * @brief Returns the index of a randomly selected move that is not NULL
         * 
         * @return uint8_t 
         * 
         * @throw out_of_range No moves present in monster's move set
        */
        uint8_t getRandomMove() const;

        /**
         * @brief Returns the index of a randomly selected monster that is not NULL
         * 
         * @return uint8_t 
         * 
         * @throw out_of_range No monsters present in the party
        */
        uint8_t getRandomMonster() const;
        
        /**
         * @brief Loads a trainer from a file
         * 
         * @param filename 
         * 
         * @throw runtime_error Cannot open file
         * @throw out_of_range File content is not correct
        */
        void loadFromFile(const std::string& filename);

        /**
         * @brief Loads a singular member to add to the party
         * 
         * @param str Monster should be formatted like this: {MONSTER_NAME, NICK_NAME}
         * @return true When a monster can be added
         * @return false When a monster can not be added
         * 
         * @throw runtime_error More arguments were found when deserializing than needed
         * @throw out_of_range Str does not have the correct data format
        */
        bool loadMemberFromString(const std::string& str);

        /**
         * @brief Changes the current monster to the monster in the new index
         * 
         * @param monsterIndex 
         * 
         * @throw out_of_range Index > Trainer::Partycount
         * @throw out_of_range No monster is present at newIndex
         * @throw out_of_range The index given is greater than the maximum of moves present in a monster
         * @throw logic_error The monster you're trying to select has no hp
        */
        void selectMonster(uint8_t monsterIndex);   

        /**
         * @brief Selects the move used during Trainer::attack()
         * 
         * @param moveIndex Move index to use
         * 
         * @throw out_of_range The index given is greater than the maximum of moves present in  a monster
         * @throw out_of_range The index given is a nullptr in the monster's move set
        */
        void selectMove(uint8_t moveIndex);

        private:

        const std::string name;
        std::array<std::unique_ptr<monster::Monster>, Trainer::PartyCount> party;
        uint8_t partyIterator;          //Used to iterate through the party, not usefull for accessing the monster you want
        uint8_t selectedMonsterIndex;   //Used to access the currently selected monster by the trainer
        uint8_t selectedMoveIndex;      //Used to access which move should be used to attack

        /**
         * @brief Adds a monster to the party
         * 
         * @param name 
         * @param nickname 
         * @return true When another monster can be added
         * @return false When the party if full
         * 
         * @throw runtime_error Could not find monster
        */
        bool addToParty(const std::string& name, const std::string& nickname);

    };
}

#endif