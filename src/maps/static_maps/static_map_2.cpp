#include <maps/static_maps/static_map_2.h>

StaticMap2::StaticMap2() : BaseStaticMap(6, 5) {
	std::cout << "start init static map 2" << std::endl;
	SetSpecificObjects();
}

void StaticMap2::SetSpecificObjects() {
	SetObject({2, 2}, OBJECT::BLOCK);
	SetObject({3, 4}, OBJECT::VOID);
	SetObject({0, 2}, OBJECT::VOID);
	SetObject({2, 0}, OBJECT::VOID);
}
