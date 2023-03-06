#include <objects/wall_object.h>

WallObject::WallObject(std::shared_ptr<const ObjectManager> object_manager, 
std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects) : BaseObject(OBJECT::WALL, object_manager, objects) 
{

}

std::map<uint64_t, ACTION::Action> WallObject::Move(ACTION::Action act) const
{
    std::map<uint64_t, ACTION::Action> ret_act;
    ret_act.insert({(uint64_t)this, ACTION::NOP});
    return ret_act;
}