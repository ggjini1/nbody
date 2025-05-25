#pragma once

#include <vector>
#include <string>
#include <vec3.h>

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