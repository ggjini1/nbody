#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>
#include <cmath>
#include <stdexcept>

#include <system.h>
#include <vec3.h>
#include <plot.h>
#include <initialConditions.h>

int main(int argc, char *argv[])
{
    InitialConditionResult result = getInitialConditions("solar_system");
    plotInitialConditions(result.system, result.colors, result.labels, result.legend, "initial_conditions.png");
    return 0;
}