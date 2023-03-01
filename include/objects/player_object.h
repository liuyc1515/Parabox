#pragma once

#include <objects/base_object.h>

class PlayerObject : public BaseObject
{
public:
    PlayerObject();
    std::map<uint64_t, ACTION::Action> Move(ACTION::Action act) const;
};