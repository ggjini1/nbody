#pragma once

#include <vector>

struct vec3
{
    double x;
    double y;
    double z;
    vec3(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}
    vec3(const vec3& other) : x(other.x), y(other.y), z(other.z) {}
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

inline double norm(const vec3& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}