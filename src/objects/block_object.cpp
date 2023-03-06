#include <objects/block_object.h>

BlockObject::BlockObject(std::shared_ptr<const ObjectManager> object_manager,
std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects) : BaseObject(OBJECT::BLOCK, object_manager, objects) 
{

}

std::map<uint64_t, ACTION::Action> BlockObject::Move(ACTION::Action act) const
{
    std::shared_ptr<const BaseObject> around;
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
        if (ret_act.at(around->GetID()) == act || ret_act.at(around->GetID()) == ACTION::DISAPPEAR)
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