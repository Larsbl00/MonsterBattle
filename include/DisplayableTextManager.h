/**
 * @file DisplayableTextManager.h
 * @author Lars Bloemers 
 * @brief 
 * @version 0.1
 * @date 2019-11-09
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef DISPLAYABLE_TEXT_MANAGER_H
#define DISPLAYABLE_TEXT_MANAGER_H

#include <array>
#include <cstdint>
#include <map>

#include "Color.h"
#include "DisplayManager.h"
#include "DisplayableText.h"
#include "DisplayableTextManager.h"
#include "Monster.h"
#include "MonsterBattle.h"
#include "Game.h"
#include "Singleton.h"
#include "Vector.h"
#include "Trainer.h"
#include "TypeColorManager.h"


namespace monsterbattle
{
    class DisplayableTextManager:
        public Singleton<DisplayableTextManager>
    {
        friend Singleton;

        public:

        const static inline Vector2i32 DefaultTextLocation = Vector2i32(0, 0);
        const static inline Color HighlightColor = Color(0, 155, 185);
        const static inline Color DefaultColor = Color(255, 255, 255);
        const static inline Vector2f RelativeStartPositionBattleMonsterOption = Vector2f(0.05, 0.85);
        const static inline Vector2f RelativeStartPositionBattleMoveOption = Vector2f(0.35, 0.85);
        const static inline Vector2f RelativeStartPositionMoveSelect = Vector2f(0.35, 0.3);
        const static inline Vector2f RelativeStartPositionMonsterSelect = Vector2f(0.05, 0.3);
        const static inline Vector2f RelativeStartPositionSubtitle = Vector2f(0.05, 0.95);
        const static inline Vector2f RealtiveSpacingMonsters = Vector2f(0, 0.1);
        const static inline Vector2f RealtiveSpacingMoves = Vector2f(0, 0.1);

        ~DisplayableTextManager() noexcept;

        std::array<DisplayableText, Game::BattleOptions>& getBattleOptionText();
        std::array<DisplayableText, monster::Monster::MoveCount>& getMoveText();
        DisplayableText& getSubtitleText();
        std::array<DisplayableText, Trainer::PartyCount>& getTrainerPartyText();

        /**
         * @brief Sets the index of the battle options active
         * 
         * @param index 
        */
        void selectBattleOption(uint8_t index);

        /**
         * @brief Highlights the currently selected member
         * 
         * @param index 
        */
        void selectPartyMember(uint8_t index);

        /**
         * @brief 
         * 
         * @param index Highlights the selected move
         * @param moves The list of moves present in the monster, used for getting the color of the move
        */
        void selectMove(uint8_t index, const std::array<const monster::Move*, monster::Monster::MoveCount>& moves);

        /**
         * @brief Sets the battle options
         * 
         * @param battleOps 
        */
        void setBattleOptions(const std::array<std::string, Game::BattleOptions>& battleOps);

        /**
         * @brief Sets the text for the parties, based on the given party
         * 
         * @param party 
        */
        void setPartyText(const std::array<std::unique_ptr<monster::Monster>, Trainer::PartyCount>& party);
        
        /**
         * @brief Set the text for the moves, based on the given moves
         * 
         * @param moves 
        */
        void setMoveText(const std::array<const monster::Move*, monster::Monster::MoveCount>& moves);

        /**
         * @brief Sets the subtitle of the screen
         * 
         * @param str 
        */
        void setSubtitle(const std::string& str);

        /**
         * @brief Sets all text fields to the correct position
         * 
         * @throw runtime_error Display not yet set, the display of the displaymanager is not yet set 
         * 
        */
        void setup();

        private:

        std::array<DisplayableText, Game::BattleOptions> battleOptionText;
        std::array<DisplayableText, monster::Monster::MoveCount> moveText;
        DisplayableText subtitleText;
        std::array<DisplayableText, Trainer::PartyCount> trainerPartyText;
        Vector2i32 displaySize;


        DisplayableTextManager();

    };
};

#endif