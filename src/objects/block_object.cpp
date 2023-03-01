#include <objects/block_object.h>

BlockObject::BlockObject() : BaseObject(OBJECT::BLOCK) {}

std::map<uint64_t, ACTION::Action> BlockObject::Move(ACTION::Action act) const
{
    const BaseObject * around;
    std::map<uint64_t, ACTION::Action> ret_act;
    around = GetAround(ActionToDirection(act));
    if (around == NULL)
    {
        std::cerr << "Failed to move block : Incomplete map" << std::endl;
        ret_act.insert({(uint64_t)this, ACTION::NOP});
    }
    else
    {
        ret_act = around->Move(act);
        if (ret_act.at((uint64_t)around) == act || ret_act.at((uint64_t)around) == ACTION::DISAPPEAR)
        {
            ret_act.insert({(uint64_t)this, act});
        }
        else
        {
            ret_act.insert({(uint64_t)this, ACTION::NOP});
        }
    }
    return ret_act;
}