#include <objects/void_object.h>

VoidObject::VoidObject() : BaseObject(OBJECT::VOID) {}

std::map<uint64_t, ACTION::Action> VoidObject::Move(ACTION::Action act) const
{
    std::map<uint64_t, ACTION::Action> ret_act;
    ret_act.insert({(uint64_t)this, ACTION::DISAPPEAR});
    return ret_act;
}