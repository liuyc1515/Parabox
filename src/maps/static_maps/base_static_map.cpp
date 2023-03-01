#include <static_maps/base_static_map.h>

BaseStaticMap::BaseStaticMap(int x, int y, const coordinate &operator_coord) : BaseMap(x, y)
{
    operator_ = new PlayerObject();

    for (int i = 0; i < x_; ++i)
    {
        for (int j = 0; j < y_; ++j)
        {
            if (!IsBorder({i, j}))
            {
                if (i == operator_coord.first && j == operator_coord.second)
                {
                    map_.insert({{i, j}, operator_});
                }
                else
                {
                    map_.insert({{i, j}, new VoidObject()});
                }
            }
        }
    }
    SetObject({2, 2}, new BlockObject());
    SetObject({3, 2}, new BlockObject());
    SetObject({3, 3}, new BlockObject());

    UpdateObject();
}

BaseStaticMap::~BaseStaticMap()
{
    for (int i = 0; i < x_; ++i)
    {
        for (int j = 0; j < y_; ++j)
        {
            if (!IsBorder({i, j}) && map_.find({i, j}) != map_.end())
            {
                delete map_.at({i, j});
                map_.at({i, j}) = NULL;
            }
        }
    }
}

void BaseStaticMap::SetObject(const coordinate &coord, BaseObject *obj)
{
    if (BaseMap::IsOutOfBorder(coord))
    {
        return;
    }
    
    delete map_.at(coord);
    map_.at(coord) = obj;

    UpdateObject();
}

void BaseStaticMap::UpdateMap(const std::map<uint64_t, ACTION::Action> &changes)
{
    std::map<coordinate, BaseObject *> swap_map;
    for (auto obj : map_)
    {
        if (changes.find((uint64_t)obj.second) != changes.end())
        {
            if (obj.second->GetType() != OBJECT::VOID)
            {
                swap_map.insert({CalcCoordByAction(obj.first, changes.at((uint64_t)obj.second)), obj.second});
            }
        }
        else
        {
            if (obj.second->GetType() != OBJECT::VOID)
            {
                swap_map.insert({obj.first, obj.second});
            }
        }
    }
    CopyMap(swap_map, map_);
    UpdateObject();
}

void BaseStaticMap::UpdateObject()
{
    BaseObject *tmp_obj = NULL;
    for (int i = 0; i < x_; ++i)
    {
        for (int j = 0; j < y_; ++j)
        {
            if (map_.find({i, j}) == map_.end())
            {
                std::cerr << "Failed to update object : Incomplete Map" << std::endl;
            }
            tmp_obj = map_.at({i, j});
            tmp_obj->SetAround(DIRECTION::UP, GetObject({i, j - 1}));
            tmp_obj->SetAround(DIRECTION::DOWN, GetObject({i, j + 1}));
            tmp_obj->SetAround(DIRECTION::LEFT, GetObject({i - 1, j}));
            tmp_obj->SetAround(DIRECTION::RIGHT, GetObject({i + 1, j}));
        }
    }
}

coordinate BaseStaticMap::CalcCoordByAction(const coordinate &coord, ACTION::Action act) const
{
    coordinate new_coord;

    switch (act)
    {
    case ACTION::UP:
        new_coord.first = coord.first;
        new_coord.second = coord.second - 1;
        break;
    case ACTION::DOWN:
        new_coord.first = coord.first;
        new_coord.second = coord.second + 1;
        break;
    case ACTION::LEFT:
        new_coord.first = coord.first - 1;
        new_coord.second = coord.second;
        break;
    case ACTION::RIGHT:
        new_coord.first = coord.first + 1;
        new_coord.second = coord.second;
        break;
    case ACTION::NOP:
        new_coord.first = coord.first;
        new_coord.second = coord.second;
        break;
    default:
        break;
    }
    if (new_coord.first < 0 || new_coord.first > x_ - 1 || new_coord.second < 0 || new_coord.second > y_ - 1)
    {
        new_coord.first = coord.first;
        new_coord.second = coord.second;
    }
    return new_coord;
}

void BaseStaticMap::CopyMap(const std::map<coordinate, BaseObject *> &from, std::map<coordinate, BaseObject *> &to)
{
    for (int i = 0; i < x_; ++i)
    {
        for (int j = 0; j < y_; ++j)
        {
            if (to.at({i, j})->GetType() == OBJECT::VOID)
            {
                delete to.at({i, j});
                to.at({i, j}) = NULL;
            }
            if (from.find({i, j}) != from.end())
            {
                to.at({i, j}) = from.at({i, j});
            }
            else
            {
                to.at({i, j}) = new VoidObject();
            }
        }
    }
}

void BaseStaticMap::Operate(ACTION::Action act)
{
    std::map<uint64_t, ACTION::Action> changes;
    changes = operator_->Move(act);
    UpdateMap(changes);
}