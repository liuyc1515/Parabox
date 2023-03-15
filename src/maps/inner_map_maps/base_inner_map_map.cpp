#include <maps/inner_map_maps/base_inner_map_map.h>

BaseInnerMapMap::BaseInnerMapMap(int x, int y) : BaseMap()
{
    x_ = x;
    y_ = y;

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
}

BaseInnerMapMap::~BaseInnerMapMap()
{
    
}

void BaseInnerMapMap::SetObject(const Coordinate &coord, OBJECT::ObjectType obj)
{
    if (BaseMap::IsOutOfBorder(coord))
    {
        return;
    }
    
    map_.at(coord) = obj;
}

Coordinate BaseInnerMapMap::CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const
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
        std::cout << "out of border" << std::endl;
    }
    return new_coord;
}

Coordinate BaseInnerMapMap::GetVoidBorder(DIRECTION::Direction dir) const
{
    Coordinate coord(-1, -1);

    std::function<Coordinate(int, int, int)> GetVoidFromLine = [this] (int axis, int value, int boundary)
    {
        Coordinate coord(-1, -1);
        int min_distance_to_mid = boundary;

        assert(axis == 0 || axis == 1);

        for (int i = 0; i < boundary; ++i)
        {
            if (GetObjectInitType({value * (1 - axis) + i * axis, value * axis + i * (1 - axis)}) == OBJECT::VOID)
            {
                if (std::abs(i - boundary / 2) < min_distance_to_mid)
                {
                    coord.first = value * (1 - axis) + i * axis;
                    coord.second = value * axis + i * (1 - axis);
                }
            }
        }

        return coord;
    };

    switch (dir)
    {
    case DIRECTION::UP:
        coord = GetVoidFromLine(0, 0, GetMapY());
        break;
    case DIRECTION::DOWN:
        coord = GetVoidFromLine(0, GetMapX() - 1, GetMapY());
        break;
    case DIRECTION::LEFT:
        coord = GetVoidFromLine(1, 0, GetMapX());
        break;
    case DIRECTION::RIGHT:
        coord = GetVoidFromLine(1, GetMapY() - 1, GetMapX());
        break;
    default:
        break;
    }
    
    return coord;
}
