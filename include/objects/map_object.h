#pragma once

#include <objects/base_object.h>
#include <maps/static_maps/all_static_maps.h>

class MapObject : public BaseObject
{
private:
    MAP::MapID inner_map_id_;
    bool IsEatableType(OBJECT::ObjectType obj_type) const;
public:
    MapObject(std::shared_ptr<const ObjectManager> object_manager, 
                std::shared_ptr<const MapManager> map_manager, 
                std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects);
    virtual std::map<uint64_t, ACTION::Action> Move(ACTION::Action act) const;
    virtual std::map<uint64_t, ACTION::Action> Move(ACTION::Action act, MAP::MapID map_id) const;
    virtual MAP::MapID GetInnerMapID() const;
};
