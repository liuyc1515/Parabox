#pragma once

#include <maps/static_maps/base_static_map.h>
#include <utils/map_id.h>

class StaticMap2 : public BaseStaticMap
{
private:
    virtual void SetSpecificObjects();
public:
    StaticMap2();
};