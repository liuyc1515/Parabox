#include <maps/base_map.h>

BaseMap::BaseMap(int x, int y) : x_(x), y_(y)
{
    BaseObject *tmp_obj = NULL;
    for (int i = 0; i < x_; ++i)
    {
        for (int j = 0; j < y_; ++j)
        {
            if (IsBorder({i, j}))
            {
                tmp_obj = new WallObject();
                map_.insert({{i, j}, tmp_obj});
            }
        }
    }
}

BaseMap::~BaseMap()
{
    for (int i = 0; i < x_; ++i)
    {
        for (int j = 0; j < y_; ++j)
        {
            if (IsBorder({i, j}) && map_.find({i, j}) != map_.end())
            {
                delete map_.at({i, j});
                map_.at({i, j}) = NULL;
            }
        }
    }
}

const BaseObject *BaseMap::GetObject(const coordinate &coord) const
{
    if (map_.find(coord) == map_.end())
    {
        return NULL;
    }
    return map_.at(coord);
}

bool BaseMap::IsBorder(const coordinate &coord) const
{
    return coord.first == 0 || coord.second == 0 || coord.first == x_ - 1 || coord.second == y_ - 1;
}

bool BaseMap::IsOutOfBorder(const coordinate &coord) const
{
    return coord.first < 0 || coord.second < 0 || coord.first > x_ - 1 || coord.second > y_ - 1;
}