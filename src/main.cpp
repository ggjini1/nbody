#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>
#include <cmath>
#include <stdexcept>

#include <system.h>
#include <vec3.h>
#include <initialConditions.h>
#include <computeAccelerations.h>
#include <plot.h>


int main(int argc, char *argv[])
{
    InitialConditionResult result = getInitialConditions("solar_system");
    //plotInitialConditions(result.system, result.colors, result.labels, result.legend, "initial_conditions.png");
    std::vector<vec3> accelerations(result.system.m_numParticles);
    computeAccelerations(result.system, accelerations);
    std::cout << "Accelerations computed for " << result.system.m_numParticles << " particles." << std::endl;
    for (int i = 0; i < result.system.m_numParticles; ++i) {
        std::cout << "Particle " << i << ": "
                  << "Position: (" << result.system.m_x[i].x << ", "
                  << result.system.m_x[i].y << ", "
                  << result.system.m_x[i].z << "), "
                  << "Acceleration: (" << accelerations[i].x << ", "
                  << accelerations[i].y << ", "
                  << accelerations[i].z << ")" << std::endl;
    }
    return 0;
}