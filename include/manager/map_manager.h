#pragma once

#include <vector>
#include <stack>
#include <memory>

#include <maps/static_maps/base_static_map.h>

class MapManager
{
private:
    std::shared_ptr<const BaseMap> current_map_;
    std::stack<std::shared_ptr<const BaseMap>> maps_stack_;
public:
    MapManager();
    Coordinate CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const;
    OBJECT::ObjectType GetObjectType(const Coordinate &coord) const;
    int GetMapX() const;
    int GetMapY() const;
};
