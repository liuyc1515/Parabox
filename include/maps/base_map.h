#pragma once

#include <iostream>

#include <utils/types.h>

class BaseMap
{
protected:
    std::map<Coordinate, OBJECT::ObjectType> map_;
    int x_;
    int y_;
    BaseMap();
    bool IsBorder(const Coordinate &coord) const;
    bool IsOutOfBorder(const Coordinate &coord) const;
    virtual void SetObject(const Coordinate &coord, OBJECT::ObjectType obj) = 0;
    
public:
    virtual ~BaseMap();
    virtual OBJECT::ObjectType GetObjectType(const Coordinate &coord) const;
    virtual Coordinate CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const = 0;
    int GetMapX() const;
    int GetMapY() const;
};