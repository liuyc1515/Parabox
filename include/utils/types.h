#pragma once

#include <map>

typedef std::pair<int, int> Coordinate;

namespace ACTION
{
    enum Action
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        DISAPPEAR,
        ESC,
        NOP
    };
}

namespace OBJECT
{
    enum ObjectType
    {
        VOID = 0,
        WALL,
        PLAYER,
        BLOCK,

        OBJ_COUNT
    };
}

struct ObjectInfo
{
    Coordinate coordinate_;
    OBJECT::ObjectType type_;
};
