#pragma once

#include <map>

#include <objects/object_types.h>
#include <keyboard/keyboard_control.h>
#include <maps/direction.h>


class BaseObject
{
private:
    const OBJECT::ObjectType type_;
    std::map<DIRECTION::Direction, const BaseObject *> arounds_;
protected:
    BaseObject(OBJECT::ObjectType type);
public:
    virtual ~BaseObject();
    virtual std::map<uint64_t, ACTION::Action> Move(ACTION::Action act) const = 0;
    virtual const BaseObject *GetAround(DIRECTION::Direction dir) const;
    virtual bool SetAround(DIRECTION::Direction dir, const BaseObject *obj);

    OBJECT::ObjectType GetType() const;
};