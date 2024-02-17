#pragma once

#include <utils/map_types.h>

#include <cstdint>
#include <map>

typedef std::pair<int, int> Coordinate;

// All of the direction related enum must be in the order of (UP DOWN LEFT
// RIGHT)
namespace ACTION {
enum Action {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DISAPPEAR,
	INTO_ALLOWED,
	INTO_ALLOWED_OPPOSITE,
	UP_INTO,
	DOWN_INTO,
	LEFT_INTO,
	RIGHT_INTO,
	UP_OUT,
	DOWN_OUT,
	LEFT_OUT,
	RIGHT_OUT,
	NOP
};
}  // namespace ACTION

namespace KEYBOARD {
enum Action {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ESC,
	NOP
};
}  // namespace KEYBOARD

namespace OBJECT {
enum ObjectType {
	VOID = 0,
	WALL,
	PLAYER,
	BLOCK,
	MAP,
	RECURSION,

	OBJ_COUNT
};

enum ObjectStatus {
	NORMAL = 0,
	TARGET,

	STATUS_COUNT
}
}  // namespace OBJECT

namespace AGENT {
enum AgentType {
	BASE = 0,
	INNER,
	RECURSION,

	AGENT_COUNT
};
}  // namespace AGENT

struct ObjectInfo {
		Coordinate coordinate_;
		OBJECT::ObjectType type_;
		uint64_t map_id_;
};
