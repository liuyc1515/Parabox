#pragma once

#include <objects/base_object.h>
#include <utils/types.h>
#include <utils/direction.h>

class WallObject : public BaseObject
{
public:
    WallObject(std::shared_ptr<const ObjectManager> object_manager, 
                std::shared_ptr<MapManager> map_manager, 
                std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects);
    virtual std::map<uint64_t, ACTION::Action> Move(ACTION::Action act) const;
    virtual std::map<uint64_t, ACTION::Action> Move(ACTION::Action act, uint64_t map_id) const;
};