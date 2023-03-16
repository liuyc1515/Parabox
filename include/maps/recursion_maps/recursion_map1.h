#pragma once

#include <maps/recursion_maps/base_recursion_map.h>

class RecursionMap1 : public BaseRecursionMap
{
private:
    virtual void SetSpecificObjects();
public:
    RecursionMap1();
};