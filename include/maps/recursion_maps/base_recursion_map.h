#pragma once

#include <functional>
#include <assert.h>

#include <maps/base_map.h>

class BaseRecursionMap : public BaseMap
{
protected:
    virtual void SetObject(const Coordinate &coord, OBJECT::ObjectType obj);
    virtual void SetSpecificObjects() = 0;
public:
    virtual ~BaseRecursionMap();
    BaseRecursionMap(int x, int y);
    virtual Coordinate CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const;
    virtual Coordinate GetVoidBorder(DIRECTION::Direction dir) const;
};
