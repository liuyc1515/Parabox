#include <objects/void_object.h>

VoidObject::VoidObject(std::shared_ptr<const ObjectManager> object_manager, 
                std::shared_ptr<const MapManager> map_manager, 
                std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects) : BaseObject(OBJECT::VOID, object_manager, map_manager, objects) 
{

}

std::map<uint64_t, ACTION::Action> VoidObject::Move(ACTION::Action act) const
{
    std::map<uint64_t, ACTION::Action> ret_act;
    ret_act.insert({GetID(), ACTION::DISAPPEAR});
    return ret_act;
}

std::map<uint64_t, ACTION::Action> VoidObject::Move(ACTION::Action act, MAP::MapID map_id) const
{
    std::map<uint64_t, ACTION::Action> ret_act;
    ret_act.insert({GetID(), ACTION::DISAPPEAR});
    return ret_act;
}