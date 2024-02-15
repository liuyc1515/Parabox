#include <maps/recursion_maps/recursion_map1.h>

RecursionMap1::RecursionMap1() : BaseRecursionMap(10, 8) {
	std::cout << "start init inner map map 1" << std::endl;
	SetSpecificObjects();
}

void RecursionMap1::SetSpecificObjects() {
	Coordinate operator_coord(1, 1);

	SetObject(operator_coord, OBJECT::PLAYER);
	SetObject({2, 2}, OBJECT::BLOCK);
	SetObject({3, 2}, OBJECT::BLOCK);
	SetObject({3, 3}, OBJECT::RECURSION);
	SetObject({3, 4}, OBJECT::MAP);
	SetObject({0, 5}, OBJECT::VOID);
}
