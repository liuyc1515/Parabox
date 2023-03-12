#include <objects/block_object.h>

BlockObject::BlockObject(std::shared_ptr<const ObjectManager> object_manager, 
                std::shared_ptr<const MapManager> map_manager, 
                std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects) : BaseObject(OBJECT::BLOCK, object_manager, map_manager, objects) 
{

}

std::map<uint64_t, ACTION::Action> BlockObject::Move(ACTION::Action act, MAP::MapID map_id) const
{
    std::shared_ptr<const BaseObject> around;
    std::map<uint64_t, ACTION::Action> ret_act;
    std::map<uint64_t, ACTION::Action> recursive_act;
    around = GetAround(ActionToDirection(act), map_id);
    if (around == NULL)
    {
        std::cerr << "Failed to move block : Incomplete map" << std::endl;
        ret_act.insert({GetID(), ACTION::NOP});
    }
    else
    {
        ret_act = around->Move(act);
        if (ret_act.at(around->GetID()) == act || ret_act.at(around->GetID()) == act + (ACTION::LEFT_INTO - ACTION::LEFT) || ret_act.at(around->GetID()) == ACTION::DISAPPEAR)
        {
            ret_act.insert({GetID(), act});
        }
        else if (ret_act.at(around->GetID()) == ACTION::INTO_ALLOWED)
        {
            if (around->GetType() == OBJECT::MAP)
            {
                recursive_act = Move(act, around->GetInnerMapID());
                ret_act.insert(recursive_act.begin(), recursive_act.end());
                if (ret_act.at(GetID()) == act)
                {
                    ret_act.at(GetID()) = (ACTION::Action)(act + (ACTION::UP_INTO - ACTION::UP));
                }
            }
        }
        else if (ret_act.at(around->GetID()) == ACTION::INTO_ALLOWED_OPPOSITE)
        {
            
        }
        else
        {
            ret_act.insert({GetID(), ACTION::NOP});
        }
    }
    return ret_act;
}

std::map<uint64_t, ACTION::Action> BlockObject::Move(ACTION::Action act) const
{
    return Move(act, GetObjectMapID());
}