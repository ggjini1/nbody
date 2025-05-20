#pragma once

#include <vector>

struct vec3
{
    float x;
    float y;
    float z;
    vec3 operator+(const vec3& other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }
    vec3 operator-(const vec3& other) const
    {
        return {x - other.x, y - other.y, z - other.z};
    }
    vec3 operator*(float scalar) const
    {
        return {x * scalar, y * scalar, z * scalar};
    }
    vec3 operator/(float scalar) const
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
    vec3& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    vec3& operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }
};

// Allow scalar * vec3 multiplication
inline vec3 operator*(float scalar, const vec3& v)
{
    return {v.x * scalar, v.y * scalar, v.z * scalar};
}

class System
{
    System(int numParticles, std::vector<vec3>& x, std::vector<vec3>& v,  std::vector<vec3>& m, float G) 
        : m_numParticles(numParticles), m_x(x), m_v(v), m_m(m), m_G(G) {}

    void correctCenterOfMass(void)
    {
        vec3 xcm;
        vec3 vcm;
        float M = 0;
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
private:
    int m_numParticles;
    std::vector<vec3> m_x;
    std::vector<vec3> m_v;
    std::vector<float> m_m;
    float m_G;
};
