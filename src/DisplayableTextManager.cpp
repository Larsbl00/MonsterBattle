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

#define DEFAULT_TEXT (DisplayableText("<temp>", DisplayableTextManager::DefaultTextLocation, DisplayableTextManager::DefaultColor))

namespace monsterbattle
{
    constexpr auto displayManager = &DisplayManager::getInstance;

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

    void DisplayableTextManager::setPartyText(const std::array<std::unique_ptr<monster::Monster>, Trainer::PartyCount>& party)
    {
        for (uint8_t index = 0; index < Trainer::PartyCount; index++)
        {
            if (party[index] != nullptr)
            {
                this->trainerPartyText[index].setText(party[index]->getName());
            }
        }
    }
};
