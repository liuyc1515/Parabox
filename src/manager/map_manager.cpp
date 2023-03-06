#include <manager/map_manager.h>

MapManager::MapManager()
{
    current_map_ = std::make_shared<const BaseStaticMap>();
}

Coordinate MapManager::CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const
{
    return current_map_->CalcCoordByAction(coord, act);
}

OBJECT::ObjectType MapManager::GetObjectType(const Coordinate &coord) const
{
    return current_map_->GetObjectType(coord);
}

int MapManager::GetMapX() const
{
    return current_map_->GetMapX();
}

int MapManager::GetMapY() const
{
    return current_map_->GetMapY();
}
