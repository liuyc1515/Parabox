#pragma once

#include <vector>
#include <map>

#include <canvas/canvas.h>
#include <objects/base_object.h>
#include <objects/block_object.h>
#include <objects/player_object.h>
#include <objects/wall_object.h>
#include <objects/void_object.h>
#include <objects/map_object.h>
#include <objects/recursion_object.h>
#include <manager/object_manager.h>
#include <manager/map_manager.h>
#include <utils/types.h>

class BaseAgent
{
private:

protected:
    std::shared_ptr<std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects_;
    std::shared_ptr<const BaseObject> operator_;
    std::shared_ptr<ObjectManager> object_manager_;
    std::shared_ptr<MapManager> map_manager_;
    virtual void UpdateObjects(const std::map<uint64_t, ACTION::Action> &changes);
    virtual std::shared_ptr<BaseObject> NewObjectByType(OBJECT::ObjectType type) const;
public:
    BaseAgent();
    virtual ~BaseAgent();
    std::shared_ptr<const ObjectManager> GetObjectManager() const;
    std::shared_ptr<const MapManager> GetMapManager() const;
    int GetMapX(uint64_t map_id) const;
    int GetMapY(uint64_t map_id) const;
    int GetCurrentMapX() const;
    int GetCurrentMapY() const;
    virtual void OperatorMove(ACTION::Action act);
};
