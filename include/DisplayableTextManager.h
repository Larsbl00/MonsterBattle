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

#ifndef DISPLAYABLE_TEXT_MANAGER
#define DISPLAYABLE_TEXT_MANAGER

#include <array>
#include <cstdint>
#include <map>

#include "Color.h"
#include "DisplayManager.h"
#include "DisplayableText.h"
#include "DisplayableTextManager.h"
#include "Monster.h"
#include "Game.h"
#include "Singleton.h"
#include "Vector.h"
#include "Trainer.h"


namespace monsterbattle
{
    class DisplayableTextManager:
        Singleton<DisplayableTextManager>
    {
        friend Singleton; 

        public:

        const static inline Vector2i32 DefaultTextLocation = Vector2i32(INT32_MAX, INT32_MAX);
        const static inline Color HighlightColor = Color(0, 23, 185);
        const static inline Color DefaultColor = Color(255, 255, 255);
        const static inline Vector2f RelativeStartPositionBattleOption = Vector2f(0.05, 0.7);
        const static inline Vector2f RelativeStartPositionMoveSelect = Vector2f(0.05, 0.7);
        const static inline Vector2f RelativeStartPositionMonsterSelect = Vector2f(0.05, 0.1);
        const static inline Vector2f RelativeStartPositionSubtitle = Vector2f(0.05, 0.7);

        ~DisplayableTextManager() noexcept;

        std::array<DisplayableText, Game::BattleOptions>& getBattleOptionText();
        std::array<DisplayableText, monster::Monster::MoveCount>& getMoveText();
        DisplayableText& getSubtitleText();
        std::array<DisplayableText, Trainer::PartyCount>& getTrainerPartyText();


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
        void setMoveText(const std::array<monster::Move, monster::Monster::MoveCount>& moves);

        /**
         * @brief Sets the subtitle of the screen
         * 
         * @param str 
        */
        void setSubtitle(const std::string& str);

        /**
         * @brief Sets the battle options
         * 
         * @param battleOps 
        */
        void setBattleOptions(const std::array<std::string, Game::BattleOptions>& battleOps);

        private:

        std::array<DisplayableText, Game::BattleOptions> battleOptionText;
        std::array<DisplayableText, monster::Monster::MoveCount> moveText;
        DisplayableText subtitleText;
        std::array<DisplayableText, Trainer::PartyCount> trainerPartyText;


        DisplayableTextManager();

    };
};

#endif