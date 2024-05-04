#pragma once
#include "3DVectorStruct.h"

enum class MaterialType {
    Default,
    Water,
    PlasticLow,
    PlasticHigh,
    GlassHigh,
    Ruby,
    Diamond,
    Iron,
    Copper,
    Gold,
    Aluminium,
    Silver
};

CoordinateStruct getMaterialProperties(MaterialType type);