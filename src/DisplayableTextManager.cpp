/**
 * @file DisplayableTextManager.cpp
 * @author Lars Bloemers 
 * @brief 
 * @version 0.1
 * @date 2019-11-09
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#include "DisplayableTextManager.h"

#define DEFAULT_TEXT (DisplayableText("<None>", DisplayableTextManager::DefaultTextLocation, DisplayableTextManager::DefaultColor))

namespace monsterbattle
{
    constexpr auto displayManager = &DisplayManager::getInstance;
    constexpr auto colorManager = &TypeColorManager::getInstance;

    /**************************
     * 
     * Constructor
     * 
     */

    DisplayableTextManager::DisplayableTextManager():
        battleOptionText{DEFAULT_TEXT, DEFAULT_TEXT},
        moveText{DEFAULT_TEXT, DEFAULT_TEXT, DEFAULT_TEXT, DEFAULT_TEXT},
        subtitleText(DEFAULT_TEXT),
        trainerPartyText{DEFAULT_TEXT, DEFAULT_TEXT, DEFAULT_TEXT, DEFAULT_TEXT, DEFAULT_TEXT, DEFAULT_TEXT}
    {
        for (auto& battleOpt : this->battleOptionText)
        {
            displayManager().addToRenderQueue(&battleOpt);
        }

        for (auto& move : this->moveText)
        {
            displayManager().addToRenderQueue(&move);
        }

        displayManager().addToRenderQueue(&this->subtitleText);

        for (auto& monster : this->trainerPartyText)
        {
            displayManager().addToRenderQueue(&monster);
        }
    }

    DisplayableTextManager::~DisplayableTextManager() noexcept
    {
        for (auto& battleOpt : this->battleOptionText)
        {
            displayManager().removeFromRenderQueue(&battleOpt);
        }

        for (auto& move : this->moveText)
        {
            displayManager().removeFromRenderQueue(&move);
        }

        displayManager().removeFromRenderQueue(&this->subtitleText);

        for (auto& monster : this->trainerPartyText)
        {
            displayManager().removeFromRenderQueue(&monster);
        }
    }

    /***************************************
     * 
     * Functions
     * 
     */
    std::array<DisplayableText, Game::BattleOptions>&  DisplayableTextManager::getBattleOptionText() { return this->battleOptionText; }
    std::array<DisplayableText, monster::Monster::MoveCount>& DisplayableTextManager::getMoveText() { return this->moveText; }
    DisplayableText& DisplayableTextManager::getSubtitleText() { return this->subtitleText; }
    std::array<DisplayableText, Trainer::PartyCount>& DisplayableTextManager::getTrainerPartyText() { return this->trainerPartyText; }

    void DisplayableTextManager::selectBattleOption(uint8_t index)
    {
        for (uint8_t i = 0; i < Game::BattleOptions; i++)
        {
            if (i == index)
            {
                this->battleOptionText[i].setColor(DisplayableTextManager::HighlightColor);
            }
            else 
            {
                this->battleOptionText[i].setColor(DisplayableTextManager::DefaultColor);
            }
        }
        
    }

    void DisplayableTextManager::selectPartyMember(uint8_t index)
    {
        for (uint8_t i = 0; i < Trainer::PartyCount; i++)
        {
            if (i == index)
            {
                this->trainerPartyText[i].setColor(DisplayableTextManager::HighlightColor);
            }
            else 
            {
                this->trainerPartyText[i].setColor(DisplayableTextManager::DefaultColor);
            }
        }
    }

    void DisplayableTextManager::selectMove(uint8_t index, const std::array<const monster::Move*, monster::Monster::MoveCount>& moves)
    {
        for (uint8_t i = 0; i < monster::Monster::MoveCount; i++)
        {
            if (i == index)
            {
                this->moveText[i].setColor(DisplayableTextManager::HighlightColor);
            }
            else 
            {
                if (moves[i] != nullptr)
                {
                    this->moveText[i].setColor(colorManager().getColorFromType(moves[i]->getType()));
                }
                else 
                {
                    this->moveText[i].setColor(DisplayableTextManager::DefaultColor);
                }
            }
        }
        
    }

    void DisplayableTextManager::setBattleOptions(const std::array<std::string, Game::BattleOptions>& battleOps)
    {
        for (uint8_t index = 0; index < Game::BattleOptions; index++)
        {
            this->battleOptionText[index].setText(battleOps[index]);
        }
    }

    void DisplayableTextManager::setPartyText(const std::array<std::unique_ptr<monster::Monster>, Trainer::PartyCount>& party)
    {
        for (uint8_t index = 0; index < Trainer::PartyCount; index++)
        {
            if (party[index] != nullptr)
            {
                this->trainerPartyText[index].setText(party[index]->getName());
            }
            else 
            {
                this->trainerPartyText[index].setText("None");
            }
        }
    }

    void DisplayableTextManager::setMoveText(const std::array<const monster::Move*, monster::Monster::MoveCount>& moves)
    {
        std::cout << "Setting text" << std::endl;
        for (uint8_t index = 0; index < monster::Monster::MoveCount; index++)
        {
            if (moves[index] != nullptr)
            {
                this->moveText[index].setText(moves[index]->getName());
                this->moveText[index].setColor(colorManager().getColorFromType(moves[index]->getType()));
            }
            else 
            {
                this->moveText[index].setText("None");
            }
        }
    }

    void DisplayableTextManager::setSubtitle(const std::string& str)
    {
        this->subtitleText.setText('"'+str+'"');
    }

    //TODO Place all items on the correct location
    void DisplayableTextManager::setup() 
    {
        //Escape if 
        if (displayManager().getDisplay() == nullptr) throw std::runtime_error("Display not yet set in displaymanager");
        Vector<int32_t> winSize = displayManager().getDisplay()->getSize();

        // Subtitle
        this->subtitleText.moveTo(winSize * DisplayableTextManager::RelativeStartPositionSubtitle);

        // Battleoptions
        this->battleOptionText[0].moveTo(winSize * DisplayableTextManager::RelativeStartPositionBattleMonsterOption);
        this->battleOptionText[1].moveTo(winSize * DisplayableTextManager::RelativeStartPositionBattleMoveOption);
        this->selectBattleOption(0);

        // Monsters
        // Copy start location
        auto monsterStartLocation = winSize * DisplayableTextManager::RelativeStartPositionMonsterSelect;
        for (auto& element : this->getTrainerPartyText())
        {
            element.moveTo(monsterStartLocation);

            // Move to next position
            monsterStartLocation += winSize * DisplayableTextManager::RealtiveSpacingMonsters;
        }
        this->selectPartyMember(0);

        auto moveStartLocation = winSize * DisplayableTextManager::RelativeStartPositionMoveSelect;
        for (auto& element : this->getMoveText())
        {
            std::cout << element.getIsHidden() << std::endl;
            std::cout << moveStartLocation << std::endl;
            element.moveTo(moveStartLocation);

            moveStartLocation += winSize * DisplayableTextManager::RealtiveSpacingMoves;
        }
        this->selectMove(0, {nullptr, nullptr, nullptr, nullptr});
    }
};
