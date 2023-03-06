#include <static_maps/base_static_map.h>

BaseStaticMap::BaseStaticMap() : BaseMap()
{
    std::cout << "start init base static map" << std::endl;
    x_ = 8;
    y_ = 8;

    Coordinate operator_coord(1, 1);

    for (int i = 0; i < x_; ++i)
    {
        for (int j = 0; j < y_; ++j)
        {
            if (!IsBorder({i, j}))
            {
                map_.insert({{i, j}, OBJECT::VOID});
            }
            else
            {
                map_.insert({{i, j}, OBJECT::WALL});
            }
        }
    }

    SetObject(operator_coord, OBJECT::PLAYER);
    SetObject({2, 2}, OBJECT::BLOCK);
    SetObject({3, 2}, OBJECT::BLOCK);
    SetObject({3, 3}, OBJECT::BLOCK);

}

BaseStaticMap::~BaseStaticMap()
{
    
}

void BaseStaticMap::SetObject(const Coordinate &coord, OBJECT::ObjectType obj)
{
    if (BaseMap::IsOutOfBorder(coord))
    {
        return;
    }
    
    map_.at(coord) = obj;
}

Coordinate BaseStaticMap::CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const
{
    Coordinate new_coord;

    switch (act)
    {
    case ACTION::UP:
        new_coord.first = coord.first - 1;
        new_coord.second = coord.second;
        break;
    case ACTION::DOWN:
        new_coord.first = coord.first + 1;
        new_coord.second = coord.second;
        break;
    case ACTION::LEFT:
        new_coord.first = coord.first;
        new_coord.second = coord.second - 1;
        break;
    case ACTION::RIGHT:
        new_coord.first = coord.first;
        new_coord.second = coord.second + 1;
        break;
    case ACTION::NOP:
        new_coord.first = coord.first;
        new_coord.second = coord.second;
        break;
    default:
        new_coord.first = coord.first;
        new_coord.second = coord.second;
        break;
    }
    if (IsOutOfBorder(new_coord))
    {
        new_coord.first = coord.first;
        new_coord.second = coord.second;
    }
    return new_coord;
}
