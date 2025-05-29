#pragma once

#include <vector>
#include <algorithm>
#include <vec3.h>
#include "system.h"

// Function to compute gravitational accelerations for a system of particles
// Assumes that the accelerations are stored in the vector 'a'.
void computeAccelerations(
    const System& system,
    std::vector<vec3>& accelerations)
{
    std::fill(accelerations.begin(), accelerations.end(), vec3());
    for (int i = 0; i < system.m_numParticles; ++i) {
        for (int j = i+1; j < system.m_numParticles; ++j) {
            vec3 R = system.m_x[j] - system.m_x[i];
            double norm_R = norm(R);
            if (norm_R > 0.0) {
                auto temp_value = system.m_G * R / (norm_R * norm_R * norm_R);
                accelerations[i] += temp_value * system.m_m[j];
                accelerations[j] -= temp_value * system.m_m[i];
            }
        }
    }
}