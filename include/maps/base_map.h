#pragma once

#include <objects/player_object.h>
#include <objects/void_object.h>
#include <objects/wall_object.h>
#include <objects/block_object.h>
#include <canvas/canvas.h>

typedef std::pair<int, int> coordinate;

class BaseMap
{
protected:
    std::map<coordinate, std::shared_ptr<BaseObject>> map_;
    int x_;
    int y_;
    BaseMap(int x, int y);
    bool IsBorder(const coordinate &coord) const;
    bool IsOutOfBorder(const coordinate &coord) const;
    virtual void UpdateMap(const std::map<uint64_t, ACTION::Action> &changes) = 0;
    virtual void SetObject(const coordinate &coord, std::shared_ptr<BaseObject> obj) = 0;
    
public:
    virtual ~BaseMap();
    virtual std::shared_ptr<const BaseObject> GetObject(const coordinate &coord) const;
    virtual void Operate(ACTION::Action act) = 0;
};