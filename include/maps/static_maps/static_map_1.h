#pragma once

#include <maps/static_maps/base_static_map.h>
#include <utils/map_types.h>

class StaticMap1 : public BaseStaticMap {
	private:
		virtual void SetSpecificObjects();

	public:
		StaticMap1();
};