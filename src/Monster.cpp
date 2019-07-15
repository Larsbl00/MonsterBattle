/**
 * @file Monster.cpp
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-06-24
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "Monster.h"

namespace monsterbattle
{
    namespace monster
    {
        static auto& moveManager = MoveManager::getInstance();

        Monster::Monster():
            stats(0, 0, 0, 0, 0, 0)
        {
            for (auto& i : this->moves)
            { 
                i = nullptr; 
            }
        }

        Monster::Monster(const std::string& name, const Stats& stats, const std::string& modelFile, const Color& color, Type primaryType):
            model(modelFile, color), name(name), nickName(name), stats(stats), types{primaryType, Type::NONE}
        {
            this->model.load();
            for (auto& i : this->moves)
            { 
                i = nullptr; 
            }
        }

        Monster::Monster(const std::string& name, const Stats& stats, const std::string& modelFile, const Color& color, Type primaryType, Type secondaryType):
            model(modelFile, color), name(name), nickName(name), stats(stats), types{primaryType, secondaryType}
        {    
            this->model.load();
            for (auto& i : this->moves)
            { 
                i = nullptr; 
            }
        }


        bool Monster::attack(Monster& other)
        {
            other.getName();
            throw std::runtime_error("Attack not yet implemented");
            return true;
        }

        void Monster::addMove(const std::string& name)
        {
            //Check for free space
            for (auto& move : this->moves)
            {
                if (move == nullptr)
                {
                    move = moveManager.getMove(name);
                    return;
                }
            }

            //No free space found
            throw std::runtime_error("Cannot add move to Monster");
        }

        void Monster::addMoves(const std::vector<std::string>& names)
        {
            for (auto& name : names)
            {
                this->addMove(name);
            }
        }



        Model& Monster::getModel() { return this->model; }
        const std::array<const Move*, Monster::MoveCount>& Monster::getMoves() const { return this->moves; }
        const std::string& Monster::getName() const { return this->name; }
        const std::string& Monster::getNickName() const { return this->nickName; }
        const Stats& Monster::getStats() const { return this->stats; }
        Stats& Monster::getStats() { return this->stats; }
        const std::array<Type, Monster::TypeCount>& Monster::getTypes() const { return this->types; }

        void Monster::setNickName(const std::string& nickName) { this->nickName = nickName; }
    }
}