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

Coordinate BaseObject::CalcCoordInMap(const Coordinate &coord, uint64_t from_map_id, uint64_t to_map_id, DIRECTION::Direction dir) const
{
    Coordinate new_coord(-1, -1);

    if (from_map_id == to_map_id)
    {
        new_coord = coord;
    }
    else
    {
        if (map_manager_->IsBorder(from_map_id, coord))
        {
            
        }
        else
        {
            new_coord = CalcCoordByDirection(map_manager_->GetVoidBorder(OppositeDirection(dir), to_map_id), OppositeDirection(dir));
        }
    }

    return new_coord;
}

uint64_t BaseObject::NewMap(MAP::MapType map_type)
{
    return map_manager_->NewMap(map_type);
}

std::shared_ptr<const BaseObject> BaseObject::GetAround(DIRECTION::Direction dir, uint64_t map_id) const
{
    Coordinate self_coord = CalcCoordInMap(object_manager_->GetObjectCoord(GetID()), object_manager_->GetObjectMap(GetID()), map_id, dir);
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
