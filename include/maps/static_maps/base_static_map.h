#pragma once

#include <maps/base_map.h>

class BaseStaticMap : public BaseMap
{
protected:
    std::shared_ptr<BaseObject> operator_;
    virtual void SetObject(const coordinate &coord, std::shared_ptr<BaseObject> obj);
    virtual void UpdateMap(const std::map<uint64_t, ACTION::Action> &changes);
    virtual void UpdateObject();
    void CopyMap(const std::map<coordinate, std::shared_ptr<BaseObject>> &from, std::map<coordinate, std::shared_ptr<BaseObject>> &to);
    coordinate CalcCoordByAction(const coordinate &coord, ACTION::Action act) const;
public:
    virtual ~BaseStaticMap();
    BaseStaticMap(int x, int y, const coordinate &operator_coord);
    virtual void Operate(ACTION::Action act);
};