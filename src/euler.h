#pragma once

#include <vector>
#include <system.h>
#include <vec3.h>
#include <computeAccelerations.h>

void eulerStep(System& system, std::vector<vec3>& accelerations, double dt)
{
    computeAccelerations(system, accelerations);
    for (int i = 0; i < system.m_numParticles; ++i) {
        system.m_x[i] += system.m_v[i] * dt;
        system.m_v[i] += accelerations[i] * dt;
    }
}
