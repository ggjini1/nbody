#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <system.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <matplotlib-cpp/matplotlibcpp.h>
#pragma GCC diagnostic pop

namespace plt = matplotlibcpp;

void plotInitialConditions(
    const System& system, 
    const std::vector<std::string>& colors, 
    std::vector<std::string>& labels,
    bool legend = true,
    const std::string& filename = "") {
    // Set axis labels with LaTeX-style formatting
    plt::xlabel("$x$ (AU)");
    plt::ylabel("$y$ (AU)");

    for (size_t i = 0; i < system.m_numParticles; ++i) {
        std::vector<double> x = {static_cast<double>(system.m_x[i].x)};
        std::vector<double> y = {static_cast<double>(system.m_x[i].y)};
        plt::scatter(x, y, 10.0, { {"color", colors[i]}, {"label", labels[i]} });
    }
    if (legend) {
        plt::legend();
    }
    if (!filename.empty()) {
        plt::save(filename);  
    }
}
