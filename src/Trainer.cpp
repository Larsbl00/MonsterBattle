/**
 * @file Trainer.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-25
 * 
 * @copyright Copyright (c) 2019
 * 
*/
#include "Trainer.h"

namespace monsterbattle
{
    constexpr auto displayManager = &DisplayManager::getInstance;

    /******************
     * 
     * Constructors
     * 
     */

    Trainer::Trainer():
        name(Trainer::DefaultName), partyIterator(0), selectedMonsterIndex(0), selectedMoveIndex(0)
    {
        for(auto& i : this->party)
        {
            i = nullptr;
        }
    }

    Trainer::Trainer(const std::string& name):
        name(name), partyIterator(0), selectedMonsterIndex(0), selectedMoveIndex(0)
    {
        for(auto& i : this->party)
        {
            i = nullptr;
        }
    }


    /********************
     * 
     * Public functions
     * 
     */

    bool Trainer::attack(monster::Monster& opponent)
    {
        auto& monster = this->getCurrentMonster();

        auto& move = monster.getMoves()[this->selectedMoveIndex];

        //No move selected, the attack will miss
        if (move == nullptr) return false;

        return move->use(monster, opponent);
    }

    monster::Monster& Trainer::getCurrentMonster() 
    {
        if (this->party[this->selectedMonsterIndex] == nullptr) throw std::runtime_error("No monster selected");

        return *this->party[this->selectedMonsterIndex];
    }

    bool Trainer::selectedMonster() const 
    {
        return this->party[this->selectedMonsterIndex] != nullptr;
    }

    const std::array<std::unique_ptr<monster::Monster>, Trainer::PartyCount>& Trainer::getMonsters() const { return this->party; }

    const std::string& Trainer::getName() const { return this->name; }

    uint8_t Trainer::getPartySize() const { return this->partyIterator; }\

    uint8_t Trainer::getRandomMove() const 
    {
        std::vector<uint8_t> availableMoveIndices;

        // Check if all moves are nullptrs
        uint8_t index = 0;
        for (const auto& move : this->getMonsters()[this->selectedMonsterIndex]->getMoves()) 
        { 
            if (move != nullptr) availableMoveIndices.push_back(index);
            index++;
        }

        if (availableMoveIndices.size() <= 0) throw std::out_of_range("Monster has no valid moves in moveset");

        return availableMoveIndices[rand() % availableMoveIndices.size()];
    }

    uint8_t Trainer::getRandomMonster() const
    {
        std::vector<uint8_t> availableMonsterIndices;

        uint8_t index = 0;
        for (const auto& monster : this->getMonsters()) 
        { 
            if (monster != nullptr && monster->getStats().health > 0) availableMonsterIndices.push_back(index);
            index++;
        }

        if (availableMonsterIndices.size() <= 0) throw std::out_of_range("Party has no valid monsters");

        return availableMonsterIndices[rand() % availableMonsterIndices.size()];
    }

    void Trainer::loadFromFile(const std::string& filename)
    {

        RaiiFileHandle trainerFile(filename);

        if (!trainerFile.is_open())
        {
            throw std::runtime_error("Could not open file: " + filename);
            return;
        }

        bool canAddMonstersToParty = true;

        //Read ech line of the file
        for (std::string line; getline(trainerFile, line, '\n') && canAddMonstersToParty; )
        {
            //Remove unwanted spaces before the line
            auto lineStartIndex = line.find_first_not_of(' ');

            if (lineStartIndex >= line.length()) lineStartIndex = 0;

            line = line.substr(lineStartIndex, line.length() - lineStartIndex);
            if (!line.empty() && line[0] != Trainer::CommentChar)
            {
                //load member if it not a comment
                canAddMonstersToParty = this->loadMemberFromString(line);
            }
        }
    }

    bool Trainer::loadMemberFromString(const std::string& str)
    {
        if (str.empty()) return false;

        std::istringstream stream(str.substr(1, str.length() - 2));
        std::vector<std::string> data;

        for (std::string val; getline(stream, val, ','); )
        {
            if (!val.empty() && val[0] != Trainer::CommentChar)
            {
                data.push_back(val.substr(val.find_first_not_of(' '), val.find_last_not_of(' ') + 1));
            }
        }

        if (data.size() != 2)
        {
            throw std::runtime_error("Deserialization error; Trainer is corrupted");
            return false;
        }

        return this->addToParty(data[0], data[1]);
    }

    void Trainer::selectMove(uint8_t index)
    {
        if (index >= monster::Monster::MoveCount) throw std::out_of_range("Move index > allowed moves");
        if (this->getCurrentMonster().getMoves()[index] == nullptr) throw std::out_of_range("Monster has no move at selected index");
        this->selectedMoveIndex = index;
    }


    void Trainer::selectMonster(uint8_t index)
    {
        
        if (index >= Trainer::PartyCount) throw std::out_of_range("Monster index greater than PartyCount of value: " + std::to_string(Trainer::PartyCount));
        else if (this->getMonsters()[index] == nullptr) throw std::out_of_range("Party has no monster at index = " + std::to_string(static_cast<int>(index)));

        if (this->getMonsters()[index]->getStats().health <= 0) throw std::logic_error("Cannot select knocked-out monster");

        //If player has selected a monster, remove it from queue
        if (this->selectedMonster()) displayManager().removeFromRenderQueue(&this->getCurrentMonster());

        //Select new monster
        this->selectedMonsterIndex = index;

        //Reset the move index, to make sure nothing weird happens
        this->selectMove(0);

        //Add new one to queue
        displayManager().addToRenderQueue(&this->getCurrentMonster());
    }

    /*********************
     * 
     * Private Functions
     * 
     */

    bool Trainer::addToParty(const std::string& name, const std::string& nickname)
    {
        if (this->partyIterator >= this->PartyCount) return false;

        //Select monster increment afterwards
        auto& pmonster = this->party[this->partyIterator++];

        auto monsterTemplate =  monster::MonsterManager::getInstance().getMonster(name);
        if (monsterTemplate == nullptr)
        {
            throw std::runtime_error("Could not find monster: " + name);
            return false;
        }

        pmonster.reset(new monster::Monster(*monsterTemplate));
        (*pmonster).setNickName(nickname);

        return true;
    }
}