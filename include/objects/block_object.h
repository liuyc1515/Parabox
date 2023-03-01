#pragma once

#include <objects/base_object.h>

class BlockObject : public BaseObject
{
public:
    BlockObject();
    std::map<uint64_t, ACTION::Action> Move(ACTION::Action act) const;
};