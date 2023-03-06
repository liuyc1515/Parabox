#pragma once
#include <map>
#include <iostream>
// #include <boost/bimap.hpp>
#include <utils/types.h>

class ObjectManager
{
private:
    std::map<uint64_t, ObjectInfo> object_coord_map_;
public:
    ObjectManager();
    ~ObjectManager();
    Coordinate GetObjectCoord(uint64_t object_id) const;
    uint64_t GetObjectAtCoord(const Coordinate &coord) const;
    void SetWholeMap(std::map<uint64_t, ObjectInfo> &new_map);
    OBJECT::ObjectType GetObjectType(uint64_t object_id) const;
    void SetObjectInfo(uint64_t object_id, const ObjectInfo &info);
};