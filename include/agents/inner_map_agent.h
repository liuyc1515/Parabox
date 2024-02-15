#pragma once

#include <agents/base_agent.h>
#include <utils/direction.h>

class InnerMapAgent : public BaseAgent {
	private:
		virtual void UpdateObjects(const std::map<uint64_t, ACTION::Action> &changes);
		void InitObjectsInMap(uint64_t map_id);
		uint64_t GetObjectByInnerMapID(uint64_t inner_map_id) const;

	public:
		InnerMapAgent();
		virtual ~InnerMapAgent();
};
