#pragma once

#include <map>
#include <utils/map_id.h>

typedef std::pair<int, int> Coordinate;

// All of the direction related enum must be in the order of (UP DOWN LEFT RIGHT)
namespace ACTION
{
    enum Action
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        DISAPPEAR,
        INTO_ALLOWED,
        INTO_ALLOWED_OPPOSITE,
        UP_INTO,
        DOWN_INTO,
        LEFT_INTO,
        RIGHT_INTO,
        NOP
    };
}

namespace KEYBOARD
{
    enum Action
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
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
        MAP,

        OBJ_COUNT
    };
}

namespace AGENT
{
    enum AgentType
    {
        BASE = 0,
        INNER,

        AGENT_COUNT
    };
}

struct ObjectInfo
{
    Coordinate coordinate_;
    OBJECT::ObjectType type_;
    MAP::MapID map_id_;
};
