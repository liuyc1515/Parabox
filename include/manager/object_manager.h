#pragma once
#include <iostream>
#include <map>
#include <vector>
// #include <boost/bimap.hpp>
#include <utils/types.h>

class ObjectManager {
	private:
		std::map<uint64_t, ObjectInfo> object_coord_map_;

	public:
		ObjectManager();
		~ObjectManager();
		Coordinate GetObjectCoord(uint64_t object_id) const;
		uint64_t GetObjectMap(uint64_t object_id) const;
		std::vector<uint64_t> GetObjectInMap(uint64_t map_id) const;
		uint64_t GetObjectInMapAtCoord(uint64_t map_id, const Coordinate &coord) const;
		OBJECT::ObjectType GetObjectType(uint64_t object_id) const;

		void SetWholeMap(std::map<uint64_t, ObjectInfo> &new_map);
		void SetObjectInfo(uint64_t object_id, const ObjectInfo &info);
};