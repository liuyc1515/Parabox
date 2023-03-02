#pragma once

#include <objects/base_object.h>

class WallObject : public BaseObject
{
public:
    WallObject();
    std::map<uint64_t, ACTION::Action> Move(ACTION::Action act) const;
};