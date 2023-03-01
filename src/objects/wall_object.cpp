#include <objects/wall_object.h>

WallObject::WallObject() : BaseObject(OBJECT::WALL) {}

std::map<uint64_t, ACTION::Action> WallObject::Move(ACTION::Action act) const
{
    std::map<uint64_t, ACTION::Action> ret_act;
    ret_act.insert({(uint64_t)this, ACTION::NOP});
    return ret_act;
}