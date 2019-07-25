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
    /******************
     * 
     * Constructors
     * 
     */

    Trainer::Trainer():
        name(Trainer::DefaultName), selectedMonster(0)
    {
        for(auto& i : this->party)
        {
            i = nullptr;
        }
    }

    Trainer::Trainer(const std::string& name):
        name(name), selectedMonster(0)
    {
        for(auto& i : this->party)
        {
            i = nullptr;
        }

        auto k = monster::MonsterManager::getInstance().getMonster("Kyle");

        this->party[0].reset(new monster::Monster(*k));
    }


    /********************
     * 
     * Public functions
     * 
     */

    bool Trainer::attack(monster::Monster& opponent)
    {
        opponent.getName();
        return false;
    }

    monster::Monster& Trainer::getCurrentMonster() 
    {
        if (this->party[this->selectedMonster] == nullptr) throw std::runtime_error("No monster selected");
    
        for (const auto& i : (*this->party[this->selectedMonster]).getMoves())
        {
            std::cout << i << std::endl;
        }

        return *this->party[this->selectedMonster];
    }

    const std::array<std::unique_ptr<monster::Monster>, Trainer::PartyCount>& Trainer::getMonsters() const { return this->party; }

    const std::string& Trainer::getName() const { return this->name; }

    void Trainer::loadFromString(const std::string& str)
    {
        str.c_str();
    }



    /*********************
     * 
     * Private Functions
     * 
     */
}