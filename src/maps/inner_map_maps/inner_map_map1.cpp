#include <maps/inner_map_maps/inner_map_map1.h>

InnerMapMap1::InnerMapMap1() : BaseInnerMapMap(10, 8) {
	std::cout << "start init inner map map 1" << std::endl;
	SetSpecificObjects();
}

void InnerMapMap1::SetSpecificObjects() {
	Coordinate operator_coord(1, 1);

	SetObject(operator_coord, OBJECT::PLAYER);
	SetObject({2, 2}, OBJECT::BLOCK);
	SetObject({3, 2}, OBJECT::BLOCK);
	SetObject({3, 3}, OBJECT::MAP);
	SetObject({3, 4}, OBJECT::MAP);
}
