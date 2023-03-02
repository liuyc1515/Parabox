#pragma once

#include <keyboard/keyboard_control.h>

namespace DIRECTION
{
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        HERE
    };
}

inline ACTION::Action DirectionToAction(DIRECTION::Direction dir)
{
    ACTION::Action ret_act;

    switch (dir)
    {
    case DIRECTION::UP:
        ret_act = ACTION::UP;
        break;
    case DIRECTION::DOWN:
        ret_act = ACTION::DOWN;
        break;
    case DIRECTION::LEFT:
        ret_act = ACTION::LEFT;
        break;
    case DIRECTION::RIGHT:
        ret_act = ACTION::RIGHT;
        break;
    default:
        ret_act = ACTION::NOP;
        break;
    }

    return ret_act;
}

inline DIRECTION::Direction ActionToDirection(ACTION::Action act)
{
    DIRECTION::Direction ret_dir;

    switch (act)
    {
    case ACTION::UP:
        ret_dir = DIRECTION::UP;
        break;
    case ACTION::DOWN:
        ret_dir = DIRECTION::DOWN;
        break;
    case ACTION::LEFT:
        ret_dir = DIRECTION::LEFT;
        break;
    case ACTION::RIGHT:
        ret_dir = DIRECTION::RIGHT;
        break;
    default:
        ret_dir = DIRECTION::HERE;
        break;
    }

    return ret_dir;
}
