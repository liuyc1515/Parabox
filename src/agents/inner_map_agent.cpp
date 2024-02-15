#include <agents/inner_map_agent.h>

InnerMapAgent::InnerMapAgent() : BaseAgent() {
	std::cout << "start init inner map agent" << std::endl;
	for (auto obj : *objects_) {
		if (obj.second->GetType() == OBJECT::MAP) {
			InitObjectsInMap(obj.second->GetInnerMapID());
		}
	}
}

InnerMapAgent::~InnerMapAgent() {
}

void InnerMapAgent::UpdateObjects(const std::map<uint64_t, ACTION::Action> &changes) {
	std::map<uint64_t, ObjectInfo> new_map;
	Coordinate tmp_coord;
	OBJECT::ObjectType tmp_type;
	uint64_t tmp_map_id;
	int stuck;

	for (auto c : changes) {
		std::cout << "object " << objects_->at(c.first)->GetType() << " action " << c.second << std::endl;
	}

	for (auto obj : *objects_) {
		if (obj.second.get() != NULL) {
			if (changes.find(obj.second->GetID()) != changes.end()) {
				if (obj.second->GetType() != OBJECT::VOID) {
					if (changes.at(obj.second->GetID()) <= ACTION::RIGHT_INTO &&
						changes.at(obj.second->GetID()) >= ACTION::UP_INTO) {
						// calc the coord of the map object this object will get
						// into
						tmp_coord = map_manager_->CalcCoordByAction(
							object_manager_->GetObjectCoord(obj.second->GetID()),
							(ACTION::Action)(changes.at(obj.second->GetID()) - (ACTION::UP_INTO - ACTION::UP))
						);
						tmp_map_id =
							objects_
								->at(object_manager_->GetObjectInMapAtCoord(map_manager_->GetCurrentMapID(), tmp_coord))
								->GetInnerMapID();
						tmp_type = obj.second->GetType();
						tmp_coord = map_manager_->GetVoidBorder(
							OppositeDirection(ActionToDirection((ACTION::Action
							)(changes.at(obj.second->GetID()) - (ACTION::UP_INTO - ACTION::UP)))),
							tmp_map_id
						);
						if (obj.second->GetType() == OBJECT::PLAYER) {
							map_manager_->SetCurrentMapID(tmp_map_id);
						}
					} else if (changes.at(obj.second->GetID()) <= ACTION::RIGHT_OUT && changes.at(obj.second->GetID()) >= ACTION::UP_OUT) {
						tmp_map_id = object_manager_->GetObjectMap(
							objects_->at(GetObjectByInnerMapID(object_manager_->GetObjectMap(obj.second->GetID())))
								->GetID()
						);
						tmp_coord = map_manager_->CalcCoordByAction(
							object_manager_->GetObjectCoord(
								objects_->at(GetObjectByInnerMapID(object_manager_->GetObjectMap(obj.second->GetID())))
									->GetID()
							),
							(ACTION::Action)(changes.at(obj.second->GetID()) - (ACTION::UP_OUT - ACTION::UP))
						);
						tmp_type = obj.second->GetType();
						if (obj.second->GetType() == OBJECT::PLAYER) {
							map_manager_->SetCurrentMapID(tmp_map_id);
						}
					} else {
						tmp_coord = map_manager_->CalcCoordByAction(
							object_manager_->GetObjectCoord(obj.second->GetID()), changes.at(obj.second->GetID())
						);
						tmp_type = obj.second->GetType();
						tmp_map_id = object_manager_->GetObjectMap(obj.second->GetID());
					}
				} else {
					tmp_coord = object_manager_->GetObjectCoord(operator_->GetID());
					tmp_type = obj.second->GetType();
					tmp_map_id = object_manager_->GetObjectMap(operator_->GetID());
				}
			} else {
				tmp_coord = object_manager_->GetObjectCoord(obj.second->GetID());
				tmp_type = obj.second->GetType();
				tmp_map_id = object_manager_->GetObjectMap(obj.second->GetID());
			}
			new_map.insert({obj.second->GetID(), {tmp_coord, tmp_type, tmp_map_id}});
		}
	}

	object_manager_->SetWholeMap(new_map);
	std::cout << "new player coord " << object_manager_->GetObjectCoord(operator_->GetID()).first << ", "
			  << object_manager_->GetObjectCoord(operator_->GetID()).second << std::endl;
}

void InnerMapAgent::InitObjectsInMap(uint64_t map_id) {
	std::shared_ptr<const BaseObject> tmp_object(NULL);
	for (int i = 0; i < map_manager_->GetMapX(map_id); ++i) {
		for (int j = 0; j < map_manager_->GetMapY(map_id); ++j) {
			tmp_object = NewObjectByType(map_manager_->GetObjectInitType(map_id, {i, j}));
			object_manager_->SetObjectInfo(tmp_object->GetID(), {{i, j}, tmp_object->GetType(), map_id});
			objects_->insert({tmp_object->GetID(), tmp_object});
			if (tmp_object->GetType() == OBJECT::MAP) {
				InitObjectsInMap(tmp_object->GetInnerMapID());
			}
			if (tmp_object->GetType() == OBJECT::PLAYER) {
				std::cerr << "player cannot be init in the map in object" << std::endl;
			}
		}
	}
}

uint64_t InnerMapAgent::GetObjectByInnerMapID(uint64_t inner_map_id) const {
	uint64_t object_id = 0;
	for (auto obj : *objects_) {
		if (obj.second->GetInnerMapID() == inner_map_id) {
			object_id = obj.first;
		}
	}
	return object_id;
}
