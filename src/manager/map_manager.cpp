#include <manager/map_manager.h>

std::shared_ptr<const BaseMap> MapManager::MAPS[MAP::MAP_COUNT];

void MapManager::InitMaps()
{
    MAPS[MAP::STATIC_1] = std::make_shared<const StaticMap1>();
    MAPS[MAP::STATIC_2] = std::make_shared<const StaticMap2>();
    MAPS[MAP::INNER_1] = std::make_shared<const InnerMapMap1>();

    std::cout << "finish init maps" << std::endl;
}

MapManager::MapManager()
{
    current_map_id_ = MAP::INNER_1;
}

Coordinate MapManager::CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const
{
    return MAPS[current_map_id_]->CalcCoordByAction(coord, act);
}

Coordinate MapManager::GetVoidBorder(DIRECTION::Direction dir, MAP::MapID map_id) const
{
    return MAPS[map_id]->GetVoidBorder(dir);
}

OBJECT::ObjectType MapManager::GetObjectInitType(MAP::MapID map_id, const Coordinate &coord) const
{
    return MAPS[map_id]->GetObjectInitType(coord);
}

MAP::MapID MapManager::GetCurrentMapID() const
{
    return current_map_id_;
}

void MapManager::SetCurrentMapID(MAP::MapID map_id)
{
    current_map_id_ = map_id;
}

int MapManager::GetMapX(MAP::MapID map_id) const
{
    return MAPS[map_id]->GetMapX();
}

int MapManager::GetMapY(MAP::MapID map_id) const
{
    return MAPS[map_id]->GetMapY();
}

bool MapManager::IsBorder(MAP::MapID map_id, const Coordinate &coord) const
{
    return MAPS[map_id]->IsBorder(coord);
}

bool MapManager::IsOutOfBorder(MAP::MapID map_id, const Coordinate &coord) const
{
    return MAPS[map_id]->IsOutOfBorder(coord);
}
