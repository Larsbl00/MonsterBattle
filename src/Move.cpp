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
#include "Monster.h" //Retreive functionality from the forward decleration

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

        void Move::loadFromString(const std::string& str)
        {
            if (str.empty()) return;

            //Remove start and end brackets
            std::istringstream stream(str.substr(1, str.length() - 2));
            std::vector<std::string> data;

            for (std::string val; getline(stream, val, ','); )
            {
                data.push_back(std::move(val));
            }

            if (data.size() != 4) throw std::runtime_error("Deserialization error; Move is corrupted");

            this->name = data[0];
            this->attackType = static_cast<Type>(atoi(data[1].c_str())); 
            this->damage = atoi(data[2].c_str());
            this->precision = atof(data[3].c_str());
        }

        const std::string& Move::getName() const { return this->name; }

        std::ostream& operator<<(std::ostream& str, const Move& move)
        {
            return str 
            << '(' 
            << move.getName()
            << ','
            << move.attackType
            << ','
            << static_cast<int>(move.damage)
            << ','
            << move.precision
            << ')';
        }

        std::istream& operator>>(std::istream& str, Move& move)
        {
            std::string readLine;
            str >> readLine;
            move.loadFromString(readLine);
            return str;
        }

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