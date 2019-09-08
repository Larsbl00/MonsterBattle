/**
 * @file GameStates.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2019-09-08
 * 
 * @copyright Copyright (c) 2019
 * 
*/

#ifndef GAME_STATES_H
#define GAME_STATES_H

#include <cstdint>

namespace monsterbattle
{
    enum class GameState : uint8_t
    {
        GAME_STATE_IN_BATTLE,
        GAME_STATE_SELECTING_MONSTER,
        GAME_STATE_SELECTING_MOVE
    };
}

#endif