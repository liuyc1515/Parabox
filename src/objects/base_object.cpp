#include <objects/base_object.h>

BaseObject::BaseObject(OBJECT::ObjectType type) : type_(type) 
{
    arounds_.insert({DIRECTION::UP, NULL});
    arounds_.insert({DIRECTION::DOWN, NULL});
    arounds_.insert({DIRECTION::LEFT, NULL});
    arounds_.insert({DIRECTION::RIGHT, NULL});
}

BaseObject::~BaseObject() {}

const BaseObject *BaseObject::GetAround(DIRECTION::Direction dir) const
{
    return arounds_.at(dir);
}

bool BaseObject::SetAround(DIRECTION::Direction dir, const BaseObject *obj)
{
    arounds_.at(dir) = obj;
    return true;
}

OBJECT::ObjectType BaseObject::GetType() const
{
    return type_;
}
