#pragma once

#include <cmath>
#include <functional>
#include <assert.h>

#include <maps/base_map.h>
#include <utils/types.h>
#include <utils/direction.h>

class BaseStaticMap : public BaseMap
{
protected:
    virtual void SetObject(const Coordinate &coord, OBJECT::ObjectType obj);
    virtual void SetSpecificObjects() = 0;
public:
    virtual ~BaseStaticMap();
    BaseStaticMap(int x, int y);
    virtual Coordinate CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const;
    virtual Coordinate GetVoidBorder(DIRECTION::Direction dir) const;
};