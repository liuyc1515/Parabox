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
    case ACTION::UP_INTO:
    case ACTION::UP_OUT:
        ret_dir = DIRECTION::UP;
        break;
    case ACTION::DOWN:
    case ACTION::DOWN_INTO:
    case ACTION::DOWN_OUT:
        ret_dir = DIRECTION::DOWN;
        break;
    case ACTION::LEFT:
    case ACTION::LEFT_INTO:
    case ACTION::LEFT_OUT:
        ret_dir = DIRECTION::LEFT;
        break;
    case ACTION::RIGHT:
    case ACTION::RIGHT_INTO:
    case ACTION::RIGHT_OUT:
        ret_dir = DIRECTION::RIGHT;
        break;
    default:
        ret_dir = DIRECTION::HERE;
        break;
    }

    return ret_dir;
}

inline DIRECTION::Direction OppositeDirection(DIRECTION::Direction dir)
{
    DIRECTION::Direction ret_dir;

    switch (dir)
    {
    case DIRECTION::UP:
        ret_dir = DIRECTION::DOWN;
        break;
    case DIRECTION::DOWN:
        ret_dir = DIRECTION::UP;
        break;
    case DIRECTION::LEFT:
        ret_dir = DIRECTION::RIGHT;
        break;
    case DIRECTION::RIGHT:
        ret_dir = DIRECTION::LEFT;
        break;
    default:
        ret_dir = DIRECTION::HERE;
        break;
    }

    return ret_dir;
}
