#pragma once

#include "type.hpp"

namespace light
{
    void Init(const exercice& _actualEx);
    void Update(const exercice& _actualEx, const double2& _cameraRotation, const float3& _cameraPosition);
}