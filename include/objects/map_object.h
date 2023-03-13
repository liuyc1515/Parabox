#pragma once

#include <objects/base_object.h>
#include <maps/static_maps/all_static_maps.h>

class MapObject : public BaseObject
{
private:
    uint64_t inner_map_id_;
    bool IsEatableType(OBJECT::ObjectType obj_type) const;
public:
    MapObject(std::shared_ptr<const ObjectManager> object_manager, 
                std::shared_ptr<MapManager> map_manager, 
                std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects);
    virtual std::map<uint64_t, ACTION::Action> Move(ACTION::Action act) const;
    virtual std::map<uint64_t, ACTION::Action> Move(ACTION::Action act, uint64_t map_id) const;
    virtual uint64_t GetInnerMapID() const;
};
