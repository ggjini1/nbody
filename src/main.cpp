#include <iostream>
#include "common.h"

int main(int argc, char *argv[])
{
    plotInitialConditions(
        System(3, { {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {-1.0f, -1.0f, 0.0f} },
               { {0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {1.5f, -1.5f, 0.0f} },
               {1.0f, 2.0f, 3.0f}, 6.67430e-11),
        {"red", "green", "blue"},
        true,
        "initial_conditions.png"
    );
    std::cout << "Plot saved to initial_conditions.png" << std::endl;
    return 0;
}