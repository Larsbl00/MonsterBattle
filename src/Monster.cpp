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

        /******************************
         * 
         * Constructors
         * 
         */

        Monster::Monster():
            model(), stats(0, 0, 0, 0, 0, 0)
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

        Monster::Monster(const Monster& other):
            model(other.model), moves(other.moves), name(other.name), nickName(other.nickName), stats(other.stats), types(other.types)
        {}


        /****************************
         * 
         * Public functions
         * 
         */
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

        void Monster::loadFromString(const std::string& str)
        {
            if (str.empty()) return;

            this->clearMoves();

            //Remove start and end brackets
            std::istringstream stream(str.substr(1, str.length() - 2));
            std::vector<std::string> data;

            for (std::string val; getline(stream, val, Monster::AttributeSplitChar); )
            {
                if (!val.empty() && val[0] != Monster::LineCommentChar)
                {
                    data.push_back(val.substr(val.find_first_not_of(' '), val.find_last_not_of(' ') + 1));
                }
            }
    
            //Check if it has split the input into different pieces, if it is not the case, leave the function
            if (data.size() <= 1) return;

            //Check to see if the amount of received data is correct
            if (data.size() != 6) throw std::runtime_error("Deserialization error; Monster is corrupted");

            this->name = data[0];
            this->setNickName(data[1]);
            this->loadTypeFromSubString(data[2]);
            this->stats.loadFromString(data[3]);
            this->loadMovesFromSubString(data[4]);
            this->model.load(data[5]);

            //Set the color of the sprite
            this->model.setColor(TypeColorManager::getInstance().getColorFromType(this->types[0]));
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
            str 
            << '('
            << mon.getNickName()
            << ','
            << mon.getName()
            << ",["
            << mon.getTypes()[0]
            << ','
            << mon.getTypes()[1]
            << "],"
            << mon.getStats()
            << ",[";

            for (auto pMove = mon.getMoves().begin(); pMove != mon.getMoves().end(); pMove++)
            {
                if (*pMove != nullptr)
                {
                    str << (*pMove)->getName();
                    if (pMove != mon.getMoves().end()-1){ str << ','; }
                }
            }

            str << "])";


            return str;
        }

        /******************
         * 
         * Private functions 
         * 
         */
        
        void Monster::clearMoves()
        {
            for (auto& i : this->moves)
            { 
                i = nullptr; 
            }
        }

        void Monster::loadTypeFromSubString(const std::string& str)
        {
            auto splitIndex = str.find(',');
            if (splitIndex == std::string::npos) throw std::runtime_error("Deserialization error; Types are corrupted");

            this->types = {
                static_cast<Type>(stoi(str.substr(1, str.length() - splitIndex))),
                static_cast<Type>(stoi(str.substr(str.length() - splitIndex, str.length() - 1)))
            };
        }

        void Monster::loadMovesFromSubString(const std::string& str)
        {
            if (str.empty()) throw std::runtime_error("Deserialization error; Moves are corrupted");

            std::istringstream stream(str.substr(str.find_first_not_of('[') , str.find_last_not_of(']') + 1 - str.find_first_not_of('['))); 
            std::vector<std::string> data;
            uint8_t it = 0;

            for (std::string val; getline(stream, val, ','); )
            {
                if (!val.empty())
                {
                    this->moves[it++] = moveManager.getMove(val.substr(val.find_first_not_of(' '), val.find_last_not_of(' ') + 1 -val.find_first_not_of(' ')));
                }
            }
        }
    }
}