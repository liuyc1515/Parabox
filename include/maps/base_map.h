#pragma once

#include <iostream>

#include <utils/types.h>
#include <utils/direction.h>

class BaseMap
{
protected:
    std::map<Coordinate, OBJECT::ObjectType> map_;
    int x_;
    int y_;
    BaseMap();
    virtual void SetObject(const Coordinate &coord, OBJECT::ObjectType obj) = 0;
public:
    virtual ~BaseMap();
    virtual OBJECT::ObjectType GetObjectInitType(const Coordinate &coord) const;
    virtual Coordinate GetVoidBorder(DIRECTION::Direction dir) const = 0;
    virtual Coordinate CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const = 0;
    bool IsBorder(const Coordinate &coord) const;
    bool IsOutOfBorder(const Coordinate &coord) const;
    int GetMapX() const;
    int GetMapY() const;
};