#pragma once

#include <map>

#include <utils/types.h>
#include <utils/direction.h>
#include <utils/map_id.h>
#include <manager/object_manager.h>
#include <manager/map_manager.h>

class BaseObject
{
private:
    const OBJECT::ObjectType type_;
    std::shared_ptr<const ObjectManager> object_manager_;
    std::shared_ptr<const MapManager> map_manager_;
    std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects_;
protected:
    BaseObject(OBJECT::ObjectType type, 
                std::shared_ptr<const ObjectManager> object_manager, 
                std::shared_ptr<const MapManager> map_manager, 
                std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects);
    Coordinate CalcCoordByDirection(const Coordinate &coord, DIRECTION::Direction dir) const;
    virtual std::shared_ptr<const BaseObject> GetAround(DIRECTION::Direction dir, MAP::MapID map_id) const;
    std::shared_ptr<const BaseObject> GetObjectByID(uint64_t object_id) const;
    MAP::MapID GetObjectMapID() const;
    bool HasVoidBorder(DIRECTION::Direction dir, MAP::MapID map_id) const;
    Coordinate CalcCoordInMap(const Coordinate &coord, MAP::MapID from_map_id, MAP::MapID to_map_id, DIRECTION::Direction dir) const;
public:
    virtual ~BaseObject();
    virtual std::map<uint64_t, ACTION::Action> Move(ACTION::Action act) const = 0;
    virtual uint64_t GetID() const;
    virtual MAP::MapID GetInnerMapID() const;
    OBJECT::ObjectType GetType() const;
};