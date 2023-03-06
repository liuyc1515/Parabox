#pragma once

#include <map>

#include <utils/types.h>
#include <utils/direction.h>
#include <manager/object_manager.h>


class BaseObject
{
private:
    const OBJECT::ObjectType type_;
    std::shared_ptr<const ObjectManager> object_manager_;
    std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects_;
protected:
    BaseObject(OBJECT::ObjectType type, std::shared_ptr<const ObjectManager> object_manager, std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects);
    Coordinate CalcCoordByDirection(const Coordinate &coord, DIRECTION::Direction dir) const;
    std::shared_ptr<const BaseObject> GetObjectByID(uint64_t object_id) const;
public:
    virtual ~BaseObject();
    virtual std::map<uint64_t, ACTION::Action> Move(ACTION::Action act) const = 0;
    virtual std::shared_ptr<const BaseObject> GetAround(DIRECTION::Direction dir) const;
    virtual uint64_t GetID() const;
    OBJECT::ObjectType GetType() const;
};