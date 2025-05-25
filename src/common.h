#pragma once

#include <vector>
#include <string>
#include "matplotlib-cpp/matplotlibcpp.h"

struct vec3
{
    double x;
    double y;
    double z;
    vec3 operator+(const vec3& other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }
    vec3 operator-(const vec3& other) const
    {
        return {x - other.x, y - other.y, z - other.z};
    }
    vec3 operator*(double scalar) const
    {
        return {x * scalar, y * scalar, z * scalar};
    }
    vec3 operator/(double scalar) const
    {
        return {x / scalar, y / scalar, z / scalar};
    }
    vec3 operator-() const
    {
        return {-x, -y, -z};
    }
    vec3& operator+=(const vec3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    vec3& operator-=(const vec3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    vec3& operator*=(double scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    vec3& operator/=(double scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }
};

// Allow scalar * vec3 multiplication
inline vec3 operator*(double scalar, const vec3& v)
{
    return {v.x * scalar, v.y * scalar, v.z * scalar};
}

class System
{
public:
    System(int numParticles, const std::vector<vec3>& x, const std::vector<vec3>& v, const std::vector<double>& m, double G) 
        : m_numParticles(numParticles), m_x(x), m_v(v), m_m(m), m_G(G) {}

    void correctCenterOfMass(void)
    {
        vec3 xcm;
        vec3 vcm;
        double M = 0;
        for (int i = 0; i < m_numParticles; ++i)
        {
            xcm += m_m[i]*m_x[i];
            vcm += m_m[i]*m_v[i];
            M += m_m[i];
        }
        xcm /= M;
        vcm /= M;
        for (int i = 0; i < m_numParticles; ++i)
        {
            m_x[i] -= xcm;
            m_v[i] -= vcm;
        }
    }

    int m_numParticles;
    std::vector<vec3> m_x;
    std::vector<vec3> m_v;
    std::vector<double> m_m;
    double m_G;
};

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
