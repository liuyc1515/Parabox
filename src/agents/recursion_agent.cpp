#include <agents/recursion_agent.h>

RecursionAgent::RecursionAgent() {
	std::cout << "start init recursion agent" << std::endl;
	std::shared_ptr<BaseObject> tmp_object;
	for (auto obj : *objects_) {
		if (obj.second->GetType() == OBJECT::RECURSION) {
			tmp_object = std::const_pointer_cast<BaseObject>(obj.second);
			tmp_object->SetInnerMapID(map_manager_->GetCurrentMapID());
		}
	}
}

RecursionAgent::~RecursionAgent() {
}
