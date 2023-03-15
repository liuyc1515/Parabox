#include <manager/map_manager.h>

MapManager::MapManager()
{
    current_map_id_ = NewMap(MAP::INNER_1);
}

Coordinate MapManager::CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const
{
    std::cout << "from " << coord.first << ", " << coord.second << " and act " << act << std::endl;
    if (maps_.find(current_map_id_) == maps_.end())
    {
        return Coordinate(-1, -1);
    }
    return maps_.at(current_map_id_)->CalcCoordByAction(coord, act);
}

Coordinate MapManager::GetVoidBorder(DIRECTION::Direction dir, uint64_t map_id) const
{
    if (maps_.find(map_id) == maps_.end())
    {
        return Coordinate(-1, -1);
    }
    return maps_.at(map_id)->GetVoidBorder(dir);
}

OBJECT::ObjectType MapManager::GetObjectInitType(uint64_t map_id, const Coordinate &coord) const
{
    if (maps_.find(map_id) == maps_.end())
    {
        return OBJECT::OBJ_COUNT;
    }
    return maps_.at(map_id)->GetObjectInitType(coord);
}

uint64_t MapManager::GetCurrentMapID() const
{
    return current_map_id_;
}

uint64_t MapManager::NewMap(MAP::MapType map_type)
{
    std::shared_ptr<const BaseMap> tmp_map(NULL);
    uint64_t tmp_map_id = 0;
    switch (map_type)
    {
    case MAP::STATIC_1:
        tmp_map = std::make_shared<const StaticMap1>();
        tmp_map_id = tmp_map->GetID();
        break;
    case MAP::STATIC_2:
        tmp_map = std::make_shared<const StaticMap2>();
        tmp_map_id = tmp_map->GetID();
        break;
    case MAP::INNER_1:
        tmp_map = std::make_shared<const InnerMapMap1>();
        tmp_map_id = tmp_map->GetID();
        break;
    default:
        break;
    }
    
    maps_.insert({tmp_map_id, std::move(tmp_map)});
    return tmp_map_id;
}

void MapManager::SetCurrentMapID(uint64_t map_id)
{
    current_map_id_ = map_id;
}

int MapManager::GetMapX(uint64_t map_id) const
{
    if (maps_.find(map_id) == maps_.end())
    {
        return -1;
    }
    return maps_.at(map_id)->GetMapX();
}

int MapManager::GetMapY(uint64_t map_id) const
{
    if (maps_.find(map_id) == maps_.end())
    {
        return -1;
    }
    return maps_.at(map_id)->GetMapY();
}

bool MapManager::IsBorder(uint64_t map_id, const Coordinate &coord) const
{
    if (maps_.find(map_id) == maps_.end())
    {
        std::cerr << "Cannot find requested map" << std::endl;
        return true;
    }
    return maps_.at(map_id)->IsBorder(coord);
}

bool MapManager::IsOutOfBorder(uint64_t map_id, const Coordinate &coord) const
{
    if (maps_.find(map_id) == maps_.end())
    {
        std::cerr << "Cannot find requested map" << std::endl;
        return true;
    }
    return maps_.at(map_id)->IsOutOfBorder(coord);
}
