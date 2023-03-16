#pragma once

#include <map>

#include <utils/types.h>
#include <utils/direction.h>
#include <utils/map_types.h>
#include <manager/object_manager.h>
#include <manager/map_manager.h>

class BaseObject
{
private:
    const OBJECT::ObjectType type_;
    std::shared_ptr<const ObjectManager> object_manager_;
    std::shared_ptr<MapManager> map_manager_;
    std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects_;
    uint64_t GetObjectByInnerMapID(uint64_t inner_map_id) const;
protected:
    BaseObject(OBJECT::ObjectType type, 
                std::shared_ptr<const ObjectManager> object_manager, 
                std::shared_ptr<MapManager> map_manager, 
                std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects);
    Coordinate CalcCoordByDirection(const Coordinate &coord, DIRECTION::Direction dir) const;
    virtual std::shared_ptr<const BaseObject> GetAround(ACTION::Action act, uint64_t map_id) const;
    std::shared_ptr<const BaseObject> GetObjectByID(uint64_t object_id) const;
    uint64_t GetObjectMapID() const;
    bool HasVoidBorder(DIRECTION::Direction dir, uint64_t map_id) const;
    bool CompareReturnAndExpectedAct(ACTION::Action ret_act, ACTION::Action exp_act) const;
    Coordinate CalcCoordInAnotherMap(const Coordinate &coord, uint64_t from_map_id, uint64_t &to_map_id, ACTION::Action act) const;
    uint64_t NewMap(MAP::MapType map_type);
public:
    virtual ~BaseObject();
    virtual std::map<uint64_t, ACTION::Action> Move(ACTION::Action act) const = 0;
    virtual std::map<uint64_t, ACTION::Action> Move(ACTION::Action act, uint64_t map_id) const = 0;
    virtual uint64_t GetID() const;
    virtual uint64_t GetInnerMapID() const;
    virtual void SetInnerMapID(uint64_t map_id);
    OBJECT::ObjectType GetType() const;
};
