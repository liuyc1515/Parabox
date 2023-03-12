#include <objects/map_object.h>

MapObject::MapObject(std::shared_ptr<const ObjectManager> object_manager, 
                std::shared_ptr<const MapManager> map_manager, 
                std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects) : BaseObject(OBJECT::MAP, object_manager, map_manager, objects)
{
    inner_map_id_ = MAP::STATIC_2;
}

std::map<uint64_t, ACTION::Action> MapObject::Move(ACTION::Action act, MAP::MapID map_id) const
{
    std::shared_ptr<const BaseObject> around;
    std::map<uint64_t, ACTION::Action> ret_act;
    std::map<uint64_t, ACTION::Action> recursive_act;
    around = GetAround(ActionToDirection(act), map_id);
    if (around == NULL)
    {
        std::cerr << "Failed to move map : Incomplete map" << std::endl;
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
            if (HasVoidBorder(ActionToDirection(act), GetInnerMapID()) && IsEatableType(around->GetType()))
            {
                recursive_act = around->Move(DirectionToAction(OppositeDirection(ActionToDirection(act))), GetInnerMapID());
                ret_act.insert(recursive_act.begin(), recursive_act.end());
                ret_act.at(around->GetID()) = (ACTION::Action)(recursive_act.at(around->GetID()) + ACTION::LEFT_INTO - ACTION::LEFT);
                ret_act.insert({GetID(), act});
            }
            else if (HasVoidBorder(OppositeDirection((ActionToDirection(act))), GetInnerMapID()))
            {
                ret_act.insert({GetID(), ACTION::INTO_ALLOWED});
            }
            else
            {
                ret_act.insert({GetID(), ACTION::NOP});
            }
        }
    }
    return ret_act;
}

bool MapObject::IsEatableType(OBJECT::ObjectType obj_type) const
{
    return obj_type != OBJECT::VOID && obj_type != OBJECT::WALL;
}

std::map<uint64_t, ACTION::Action> MapObject::Move(ACTION::Action act) const
{
    return Move(act, GetObjectMapID());
}

MAP::MapID MapObject::GetInnerMapID() const
{
    return inner_map_id_;
}
