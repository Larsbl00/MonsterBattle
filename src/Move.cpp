/**
 * @file Move.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-07-11
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "Move.h"

namespace monsterbattle
{
    namespace monster
    {
        static auto& manager = monsterbattle::TypeWeaknessManager::getInstance();

        /***************************
         * 
         * Constructors
         * 
         */
        Move::Move(const std::string& name, Type attackType, uint8_t damage, float precision):
            attackType(attackType), damage(damage), precision(precision), name(name)
        {}

        /****************************
         * 
         * Functions
         * 
         */
        bool Move::use(Monster& caller, Monster& opponent) const
        {
            auto attackMultiplier = this->getAttackMultiplier(opponent);

            float randomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

            auto& cStats = caller.getStats();   //Caller stats
            auto& oStats = opponent.getStats(); //Opponnent stats

            if ((cStats.getPrecision() / (1 - oStats.getAvoidance()) * this->precision) > randomValue)
            {
                //Calculate initial damage
                auto damage = this->damage * static_cast<float>(cStats.attack / static_cast<float>(oStats.defense));
                damage *= attackMultiplier;
                oStats.health -= damage;

                if (oStats.health <= 0) oStats.health = 0;
                return true;
            }
            else 
            {
                return false;
            }
        }

        const std::string& Move::getName() const { return this->name; }

        /*******************************
         * 
         * Private functions
         * 
         */

        float Move::getAttackMultiplier(const Monster& opponent) const
        {
            float attackMultiplier = 1.0;

            //For each type
            for (auto& monsterType : opponent.getTypes())
            {
                //Get each weakness
                for (auto& weakness : manager.getWeaknesses(monsterType))
                {   
                    //And check the effectiveness
                    if (this->attackType == weakness)
                    {
                        attackMultiplier *= manager.WeaknessMultiplier;
                    }
                }
            }

            return attackMultiplier;
        }
    }
}