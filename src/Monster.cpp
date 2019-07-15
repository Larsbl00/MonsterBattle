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
#include "Move.h"

namespace monsterbattle
{
    namespace monster
    {
        static auto& moveManager = MoveManager::getInstance();

        Monster::Monster():
            stats(0, 0, 0, 0, 0, 0)
        {
            this->clearMoves();
        }

        Monster::Monster(const std::string& name, const Stats& stats, const std::string& modelFile, const Color& color, Type primaryType):
            model(modelFile, color), name(name), nickName(name), stats(stats), types{primaryType, Type::NONE}
        {
            this->model.load();
            this->clearMoves();
        }

        Monster::Monster(const std::string& name, const Stats& stats, const std::string& modelFile, const Color& color, Type primaryType, Type secondaryType):
            model(modelFile, color), name(name), nickName(name), stats(stats), types{primaryType, secondaryType}
        {    
            this->model.load();
            this->clearMoves();
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

        void Monster::display(IDisplay& display)
        {
            this->model.display(display);
        }

        const std::array<const Move*, Monster::MoveCount>& Monster::getMoves() const { return this->moves; }
        const std::string& Monster::getName() const { return this->name; }
        const std::string& Monster::getNickName() const { return this->nickName; }
        const Stats& Monster::getStats() const { return this->stats; }
        Stats& Monster::getStats() { return this->stats; }
        const std::array<Type, Monster::TypeCount>& Monster::getTypes() const { return this->types; }

        void Monster::loadFromFile(const std::string& fileName)
        {
            auto i = fileName; {i.c_str();}
        }

        void Monster::move(const Vector2i32& direction)
        {
            this->model.move(direction);
        }

        void Monster::setNickName(const std::string& nickName) { this->nickName = nickName; }


        /*****************
         * 
         * Friends
         * 
         */
        std::ostream& operator<<(std::ostream& str, const Monster& mon)
        {
            return str 
            << '('
            << mon.getNickName()
            << ','
            << mon.getName()
            << ",{"
            << mon.getTypes()[0]
            << ','
            << mon.getTypes()[1]
            << "},"
            << mon.getStats()
            << ",{"
            << mon.getMoves()[0]->getName()
            << ','
            << mon.getMoves()[1]->getName()
            << ','
            << mon.getMoves()[2]->getName()
            << ','
            << mon.getMoves()[3]->getName()
            << ")}";
        }

        /******************
         * 
         * Private funstions 
         * 
         */
        
        void Monster::clearMoves()
        {
            for (auto& i : this->moves)
            { 
                i = nullptr; 
            }
        }
    }
}