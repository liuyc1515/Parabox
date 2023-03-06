#include <objects/base_object.h>

BaseObject::BaseObject(OBJECT::ObjectType type, 
std::shared_ptr<const ObjectManager> object_manager, 
std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects) : type_(type) 
{
    object_manager_ = std::move(object_manager);
    objects_ = std::move(objects);
}

BaseObject::~BaseObject() 
{
    
}

std::shared_ptr<const BaseObject> BaseObject::GetObjectByID(uint64_t object_id) const
{
    if (objects_->find(object_id) == objects_->end())
    {
        return std::shared_ptr<const BaseObject>(NULL);
    }
    return objects_->at(object_id);
}

std::shared_ptr<const BaseObject> BaseObject::GetAround(DIRECTION::Direction dir) const
{
    Coordinate self_coord = object_manager_->GetObjectCoord((uint64_t)this);
    uint64_t around_object_id = object_manager_->GetObjectAtCoord(CalcCoordByDirection(self_coord, dir));
    if (around_object_id == 0)
    {
        return std::shared_ptr<const BaseObject>(NULL);
    }
    else
    {
        return objects_->at(around_object_id);
    }
}

OBJECT::ObjectType BaseObject::GetType() const
{
    return type_;
}

Coordinate BaseObject::CalcCoordByDirection(const Coordinate &coord, DIRECTION::Direction dir) const
{
    Coordinate new_coord;

    switch (dir)
    {
    case DIRECTION::UP:
        new_coord.first = coord.first - 1;
        new_coord.second = coord.second;
        break;
    case DIRECTION::DOWN:
        new_coord.first = coord.first + 1;
        new_coord.second = coord.second;
        break;
    case DIRECTION::LEFT:
        new_coord.first = coord.first;
        new_coord.second = coord.second - 1;
        break;
    case DIRECTION::RIGHT:
        new_coord.first = coord.first;
        new_coord.second = coord.second + 1;
        break;
    case DIRECTION::HERE:
        new_coord.first = coord.first;
        new_coord.second = coord.second;
        break;
    default:
        new_coord.first = coord.first;
        new_coord.second = coord.second;
        break;
    }

    return new_coord;
}

uint64_t BaseObject::GetID() const
{
    return (uint64_t)this;
}
