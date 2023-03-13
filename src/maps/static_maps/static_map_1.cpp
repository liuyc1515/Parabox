#include <maps/static_maps/static_map_1.h>

StaticMap1::StaticMap1() : BaseStaticMap(8, 8)
{
    std::cout << "start init static map 1" << std::endl;
    SetSpecificObjects();
}

void StaticMap1::SetSpecificObjects()
{
    Coordinate operator_coord(1, 1);

    SetObject(operator_coord, OBJECT::PLAYER);
    SetObject({2, 2}, OBJECT::BLOCK);
    SetObject({3, 2}, OBJECT::BLOCK);
    SetObject({3, 3}, OBJECT::BLOCK);
}
