#include <maps/base_map.h>

BaseMap::BaseMap()
{
    std::cout << "start init base map" << std::endl;
}

BaseMap::~BaseMap()
{

}

OBJECT::ObjectType BaseMap::GetObjectInitType(const Coordinate &coord) const
{
    if (map_.find(coord) == map_.end())
    {
        return OBJECT::OBJ_COUNT;
    }
    return map_.at(coord);
}

bool BaseMap::IsBorder(const Coordinate &coord) const
{
    return coord.first == 0 || coord.second == 0 || coord.first == x_ - 1 || coord.second == y_ - 1;
}

bool BaseMap::IsOutOfBorder(const Coordinate &coord) const
{
    return coord.first < 0 || coord.second < 0 || coord.first > x_ - 1 || coord.second > y_ - 1;
}

uint64_t BaseMap::GetID() const
{
    return (uint64_t)this;
}

int BaseMap::GetMapX() const
{
    return x_;
}

int BaseMap::GetMapY() const
{
    return y_;
}
