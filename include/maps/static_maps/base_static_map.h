#pragma once

#include <maps/base_map.h>
#include <utils/types.h>

class BaseStaticMap : public BaseMap
{
protected:
    virtual void SetObject(const Coordinate &coord, OBJECT::ObjectType obj);
public:
    virtual ~BaseStaticMap();
    BaseStaticMap();
    virtual Coordinate CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const;
};