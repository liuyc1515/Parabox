#pragma once

#include <vector>
#include <stack>
#include <memory>

#include <maps/static_maps/all_static_maps.h>
#include <maps/inner_map_maps/all_inner_map_maps.h>

class MapManager
{
private:
    MAP::MapID current_map_id_;
    std::stack<MAP::MapID> maps_stack_;
public:
    static std::shared_ptr<const BaseMap> MAPS[MAP::MAP_COUNT];
    static void InitMaps();

    MapManager();
    Coordinate CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const;
    Coordinate GetVoidBorder(DIRECTION::Direction dir, MAP::MapID map_id) const;
    OBJECT::ObjectType GetObjectInitType(MAP::MapID map_id, const Coordinate &coord) const;
    MAP::MapID GetCurrentMapID() const;
    int GetMapX(MAP::MapID map_id) const;
    int GetMapY(MAP::MapID map_id) const;
    bool IsBorder(MAP::MapID map_id, const Coordinate &coord) const;
    bool IsOutOfBorder(MAP::MapID map_id, const Coordinate &coord) const;

    void SetCurrentMapID(MAP::MapID map_id);
};
