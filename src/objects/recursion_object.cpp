#include <objects/recursion_object.h>

RecursionObject::RecursionObject(
	std::shared_ptr<const ObjectManager> object_manager, std::shared_ptr<MapManager> map_manager,
	std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects
)
	: BaseObject(OBJECT::RECURSION, object_manager, map_manager, objects) {
	inner_map_id_ = 0;
}

std::map<uint64_t, ACTION::Action> RecursionObject::Move(ACTION::Action act, uint64_t map_id) const {
	std::shared_ptr<const BaseObject> around;
	std::map<uint64_t, ACTION::Action> ret_act;
	std::map<uint64_t, ACTION::Action> recursive_act;
	around = GetAround(act, map_id);
	act = DirectionToAction(ActionToDirection(act));
	if (around == NULL) {
		if (GetType() == OBJECT::RECURSION) {
			ret_act.insert({GetID(), ACTION::NOP});
		} else {
			recursive_act = Move((ACTION::Action)(act + (ACTION::UP_OUT - ACTION::UP)), 0);
			ret_act.insert(recursive_act.begin(), recursive_act.end());
			if (ret_act.at(GetID()) == act) {
				ret_act.at(GetID()) = (ACTION::Action)(act + (ACTION::UP_OUT - ACTION::UP));
			} else {
				std::cerr << "Failed to move player : Incomplete map" << std::endl;
				ret_act.at(GetID()) = ACTION::NOP;
			}
		}
	} else {
		ret_act = around->Move(act);
		if (CompareReturnAndExpectedAct(ret_act.at(around->GetID()), act)) {
			ret_act.insert({GetID(), act});
		} else if (ret_act.at(around->GetID()) == ACTION::INTO_ALLOWED) {
			if (around->GetType() == OBJECT::MAP || around->GetType() == OBJECT::RECURSION) {
				recursive_act = Move((ACTION::Action)(act + (ACTION::UP_INTO - ACTION::UP)), around->GetInnerMapID());
				ret_act.insert(recursive_act.begin(), recursive_act.end());
				if (ret_act.at(GetID()) == act) {
					ret_act.at(GetID()) = (ACTION::Action)(act + (ACTION::UP_INTO - ACTION::UP));
				}
			}
		} else if (ret_act.at(around->GetID()) == ACTION::INTO_ALLOWED_OPPOSITE) {
		} else {
			if (HasVoidBorder(ActionToDirection(act), GetInnerMapID()) && IsEatableType(around->GetType())) {
				recursive_act = around->Move(
					(ACTION::Action
					)(DirectionToAction(OppositeDirection(ActionToDirection(act))) + (ACTION::UP_INTO - ACTION::UP)),
					GetInnerMapID()
				);
				ret_act.insert(recursive_act.begin(), recursive_act.end());
				ret_act.at(around->GetID()) =
					(ACTION::Action)(recursive_act.at(around->GetID()) + ACTION::LEFT_INTO - ACTION::LEFT);
				ret_act.insert({GetID(), act});
			} else if (HasVoidBorder(OppositeDirection((ActionToDirection(act))), GetInnerMapID())) {
				ret_act.insert({GetID(), ACTION::INTO_ALLOWED});
			} else {
				ret_act.insert({GetID(), ACTION::NOP});
			}
		}
	}
	return ret_act;
}

bool RecursionObject::IsEatableType(OBJECT::ObjectType obj_type) const {
	return obj_type != OBJECT::VOID && obj_type != OBJECT::WALL;
}

std::map<uint64_t, ACTION::Action> RecursionObject::Move(ACTION::Action act) const {
	return Move(act, GetObjectMapID());
}

uint64_t RecursionObject::GetInnerMapID() const {
	return inner_map_id_;
}

void RecursionObject::SetInnerMapID(uint64_t map_id) {
	inner_map_id_ = map_id;
}
