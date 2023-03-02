#pragma once

#include <objects/base_object.h>

class VoidObject : public BaseObject
{
public:
    VoidObject();
    std::map<uint64_t, ACTION::Action> Move(ACTION::Action act) const;
};