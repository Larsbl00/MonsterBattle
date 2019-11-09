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
    {}

    /***************************************
     * 
     * Functions
     * 
     */
    std::array<DisplayableText, Game::BattleOptions>&  DisplayableTextManager::getBattleOptionText() { return this->battleOptionText; }
    std::array<DisplayableText, monster::Monster::MoveCount>& DisplayableTextManager::getMoveText() { return this->moveText; }
    DisplayableText& DisplayableTextManager::getSubtitleText() { return this->subtitleText; }
    std::array<DisplayableText, Trainer::PartyCount>& DisplayableTextManager::getTrainerPartyText() { return this->trainerPartyText; }

};
