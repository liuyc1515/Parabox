#pragma once

#include <vector>
#include <stack>
#include <memory>

#include <maps/static_maps/all_static_maps.h>
#include <maps/inner_map_maps/all_inner_map_maps.h>

class MapManager
{
private:
    uint64_t current_map_id_;
    std::stack<uint64_t> maps_stack_;
public:
    std::map<uint64_t, std::shared_ptr<const BaseMap>> maps_;

    MapManager();
    Coordinate CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const;
    Coordinate GetVoidBorder(DIRECTION::Direction dir, uint64_t map_id) const;
    OBJECT::ObjectType GetObjectInitType(uint64_t map_id, const Coordinate &coord) const;
    uint64_t GetCurrentMapID() const;
    int GetMapX(uint64_t map_id) const;
    int GetMapY(uint64_t map_id) const;
    bool IsBorder(uint64_t map_id, const Coordinate &coord) const;
    bool IsOutOfBorder(uint64_t map_id, const Coordinate &coord) const;

    uint64_t NewMap(MAP::MapType map_type);
    void SetCurrentMapID(uint64_t map_id);
};
