#include <manager/object_manager.h>

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
    
}

Coordinate ObjectManager::GetObjectCoord(uint64_t object_id) const
{
    // std::cout << "object manager get object " << object_id << std::endl;
    if (object_coord_map_.find(object_id) == object_coord_map_.end())
    {
        return Coordinate(-1, -1);
    }
    return object_coord_map_.at(object_id).coordinate_;
}

uint64_t ObjectManager::GetObjectMap(uint64_t object_id) const
{
    if (object_coord_map_.find(object_id) == object_coord_map_.end())
    {
        return 0;
    }
    return object_coord_map_.at(object_id).map_id_;
}

std::vector<uint64_t> ObjectManager::GetObjectInMap(uint64_t map_id) const
{
    std::vector<uint64_t> objects;
    for (auto obj : object_coord_map_)
    {
        if (obj.second.map_id_ == map_id)
        {
            objects.push_back(obj.first);
        }
    }
    return std::move(objects);
}

uint64_t ObjectManager::GetObjectInMapAtCoord(uint64_t map_id, const Coordinate &coord) const
{
    for (auto obj : object_coord_map_)
    {
        if (coord.first == obj.second.coordinate_.first && 
            coord.second == obj.second.coordinate_.second &&
            map_id == obj.second.map_id_)
        {
            return obj.first;
        }
    }
    return 0;
}

void ObjectManager::SetWholeMap(std::map<uint64_t, ObjectInfo> &new_map)
{
    object_coord_map_ = std::move(new_map);
}

OBJECT::ObjectType ObjectManager::GetObjectType(uint64_t object_id) const
{
    if (object_coord_map_.find(object_id) == object_coord_map_.end())
    {
        std::cerr << "Cannot get object type : Invalid object id" << std::endl;
        return OBJECT::OBJ_COUNT;
    }
    return object_coord_map_.at(object_id).type_;
}

void ObjectManager::SetObjectInfo(uint64_t object_id, const ObjectInfo &info)
{
    if (object_coord_map_.find(object_id) == object_coord_map_.end())
    {
        object_coord_map_.insert({object_id, info});
    }
    object_coord_map_.at(object_id) = info;
}
