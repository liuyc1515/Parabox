#include <objects/player_object.h>

PlayerObject::PlayerObject(
	std::shared_ptr<const ObjectManager> object_manager, std::shared_ptr<MapManager> map_manager,
	std::shared_ptr<const std::map<uint64_t, std::shared_ptr<const BaseObject>>> objects
)
	: BaseObject(OBJECT::PLAYER, object_manager, map_manager, objects) {
}

std::map<uint64_t, ACTION::Action> PlayerObject::Move(ACTION::Action act, uint64_t map_id) const {
	std::shared_ptr<const BaseObject> around;
	std::map<uint64_t, ACTION::Action> ret_act;
	std::map<uint64_t, ACTION::Action> recursive_act;
	around = GetAround(act, map_id);
	act = DirectionToAction(ActionToDirection(act));
	if (around == NULL) {
		recursive_act = Move((ACTION::Action)(act + (ACTION::UP_OUT - ACTION::UP)), 0);
		ret_act.insert(recursive_act.begin(), recursive_act.end());
		if (ret_act.at(GetID()) == act) {
			ret_act.at(GetID()) = (ACTION::Action)(act + (ACTION::UP_OUT - ACTION::UP));
		} else {
			std::cerr << "Failed to move player : Incomplete map" << std::endl;
			ret_act.at(GetID()) = ACTION::NOP;
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
		} else {
			ret_act.insert({GetID(), ACTION::NOP});
		}
	}
	return ret_act;
}

std::map<uint64_t, ACTION::Action> PlayerObject::Move(ACTION::Action act) const {
	return Move(act, GetObjectMapID());
}
