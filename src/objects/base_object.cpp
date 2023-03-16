#include <objects/base_object.h>

BaseObject::BaseObject(OBJECT::ObjectType type, 
std::shared_ptr<const ObjectManager> object_manager, 
std::shared_ptr<MapManager> map_manager,
std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects) : type_(type) 
{
    object_manager_ = std::move(object_manager);
    map_manager_ = std::move(map_manager);
    objects_ = std::move(objects);
    std::cout << "init object " << type << std::endl;
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

uint64_t BaseObject::GetObjectMapID() const
{
    return object_manager_->GetObjectMap(GetID());
}

bool BaseObject::HasVoidBorder(DIRECTION::Direction dir, uint64_t map_id) const
{
    Coordinate coord = map_manager_->GetVoidBorder(dir, map_id);
    return !(coord.first == -1 && coord.second == -1);
}

bool BaseObject::CompareReturnAndExpectedAct(ACTION::Action ret_act, ACTION::Action exp_act) const
{
    return ret_act == exp_act
    || ret_act == exp_act + (ACTION::LEFT_OUT - ACTION::LEFT)
    || ret_act == exp_act + (ACTION::LEFT_INTO - ACTION::LEFT) 
    || ret_act == ACTION::DISAPPEAR;
}

uint64_t BaseObject::GetObjectByInnerMapID(uint64_t inner_map_id) const
{
    uint64_t object_id = 0;
    for (auto obj : *objects_)
    {
        if (obj.second->GetInnerMapID() == inner_map_id)
        {
            object_id = obj.first;
        }
    }
    return object_id;
}

Coordinate BaseObject::CalcCoordInAnotherMap(const Coordinate &coord, uint64_t from_map_id, uint64_t &to_map_id, ACTION::Action act) const
{
    Coordinate new_coord(-1, -1);
    uint64_t inner_map_object_id;
    DIRECTION::Direction dir = ActionToDirection(act);

    if (act >= ACTION::UP_INTO && act <= ACTION::RIGHT_INTO)
    {
        std::cout << "getting coord in inner map" << std::endl;
        new_coord = CalcCoordByDirection(map_manager_->GetVoidBorder(OppositeDirection(dir), to_map_id), OppositeDirection(dir));
    }
    else if (act >= ACTION::UP_OUT && act <= ACTION::RIGHT_OUT)
    {
        std::cout << "getting coord in outer map" << std::endl;
        inner_map_object_id = GetObjectByInnerMapID(from_map_id);
        if (inner_map_object_id == 0)
        {
            std::cerr << "Error map id" << std::endl;
        }
        else
        {
            new_coord = object_manager_->GetObjectCoord(inner_map_object_id);
            to_map_id = object_manager_->GetObjectMap(inner_map_object_id);
        }
    }
    else
    {
        std::cerr << "Error action in calc coord in another map" << std::endl;
    }

    return new_coord;
}

uint64_t BaseObject::NewMap(MAP::MapType map_type)
{
    return map_manager_->NewMap(map_type);
}

std::shared_ptr<const BaseObject> BaseObject::GetAround(ACTION::Action act, uint64_t map_id) const
{
    
    Coordinate self_coord(-1, -1);
    std::cout << "getting around with act " << act << std::endl;
    if (act >= ACTION::UP && act <= ACTION::RIGHT)
    {
        self_coord = object_manager_->GetObjectCoord(GetID());
    }
    else
    {
        self_coord = CalcCoordInAnotherMap(object_manager_->GetObjectCoord(GetID()), object_manager_->GetObjectMap(GetID()), map_id, act);
    }
    DIRECTION::Direction dir = ActionToDirection(act);
    uint64_t around_object_id = object_manager_->GetObjectInMapAtCoord(map_id, CalcCoordByDirection(self_coord, dir));
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

uint64_t BaseObject::GetInnerMapID() const
{
    return 0;
}

void BaseObject::SetInnerMapID(uint64_t map_id)
{
    return;
}
