#pragma once

#include <objects/base_object.h>
#include <utils/types.h>
#include <utils/direction.h>

class BlockObject : public BaseObject
{
public:
    BlockObject(std::shared_ptr<const ObjectManager> object_manager, std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects);
    std::map<uint64_t, ACTION::Action> Move(ACTION::Action act) const;
};