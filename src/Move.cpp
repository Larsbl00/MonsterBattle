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


        Move::Move(const std::string& name, Type attackType, uint8_t damage, float precision):
            name(name), attackType(attackType), damage(damage), precision(precision)
        {}

        bool Move::use(Monster& caller, Monster& opponent)
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

            std::cout << "Multiplier: " << attackMultiplier << std::endl;

            std::cout << caller.getStats() << " | " << opponent.getStats() << std::endl;
            return caller.getStats().precision > opponent.getStats().avoidance;
        }

        const std::string& Move::getName() const { return this->name; }
    }
}