#ifndef MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA
#define MAT44_HPP_E7187A26_469E_48AD_A3D2_63150F05A4CA

#include <cmath>
#include <cassert>
#include <cstdlib>

#include "vec3.hpp"
#include "vec4.hpp"

struct Mat44f
{
    float v[16];

    constexpr float& operator()(std::size_t aI, std::size_t aJ) noexcept
    {
        assert(aI < 4 && aJ < 4);
        return v[aI * 4 + aJ];
    }
    constexpr const float& operator()(std::size_t aI, std::size_t aJ) const noexcept
    {
        assert(aI < 4 && aJ < 4);
        return v[aI * 4 + aJ];
    }
};

// Identity matrix
constexpr Mat44f kIdentity44f = {{
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f
}};

// Matrix-matrix multiplication
constexpr Mat44f operator*(Mat44f const& aLeft, Mat44f const& aRight) noexcept
{
    Mat44f result{};
    for (std::size_t i = 0; i < 4; ++i)
    {
        for (std::size_t j = 0; j < 4; ++j)
        {
            result(i, j) = 0.f;
            for (std::size_t k = 0; k < 4; ++k)
            {
                result(i, j) += aLeft(i, k) * aRight(k, j);
            }
        }
    }
    return result;
}

// Matrix-vector multiplication
constexpr Vec4f operator*(Mat44f const& aLeft, Vec4f const& aRight) noexcept
{
    return Vec4f{
        aLeft(0, 0) * aRight.x + aLeft(0, 1) * aRight.y + aLeft(0, 2) * aRight.z + aLeft(0, 3) * aRight.w,
        aLeft(1, 0) * aRight.x + aLeft(1, 1) * aRight.y + aLeft(1, 2) * aRight.z + aLeft(1, 3) * aRight.w,
        aLeft(2, 0) * aRight.x + aLeft(2, 1) * aRight.y + aLeft(2, 2) * aRight.z + aLeft(2, 3) * aRight.w,
        aLeft(3, 0) * aRight.x + aLeft(3, 1) * aRight.y + aLeft(3, 2) * aRight.z + aLeft(3, 3) * aRight.w
    };
}

// Rotation around X-axis
inline Mat44f make_rotation_x(float aAngle) noexcept
{
    float c = std::cos(aAngle);
    float s = std::sin(aAngle);
    return {{
        1.f, 0.f, 0.f, 0.f,
        0.f, c,   -s,  0.f,
        0.f, s,    c,  0.f,
        0.f, 0.f,  0.f, 1.f
    }};
}

// Rotation around Y-axis
inline Mat44f make_rotation_y(float aAngle) noexcept
{
    float c = std::cos(aAngle);
    float s = std::sin(aAngle);
    return {{
        c,   0.f, s, 0.f,
        0.f, 1.f, 0.f, 0.f,
       -s,   0.f, c, 0.f,
        0.f, 0.f, 0.f, 1.f
    }};
}

inline Mat44f make_scaling(float scaleX, float scaleY, float scaleZ) {
    return Mat44f{{
        scaleX, 0.0f,  0.0f,  0.0f,
        0.0f,  scaleY, 0.0f,  0.0f,
        0.0f,  0.0f,  scaleZ, 0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    }};
}



// Rotation around Z-axis
inline Mat44f make_rotation_z(float aAngle) noexcept
{
    float c = std::cos(aAngle);
    float s = std::sin(aAngle);
    return {{
        c,   -s,  0.f, 0.f,
        s,    c,  0.f, 0.f,
        0.f,  0.f, 1.f, 0.f,
        0.f,  0.f, 0.f, 1.f
    }};
}

// Translation matrix
inline Mat44f make_translation(Vec3f aTranslation) noexcept
{
    return {{
        1.f, 0.f, 0.f, aTranslation.x,
        0.f, 1.f, 0.f, aTranslation.y,
        0.f, 0.f, 1.f, aTranslation.z,
        0.f, 0.f, 0.f, 1.f
    }};
}

// Perspective projection matrix
inline Mat44f make_perspective_projection(float aFovInRadians, float aAspect, float aNear, float aFar) noexcept
{
    // Convert field of view to radians if given in degrees
    float tanHalfFov = std::tan(aFovInRadians / 2.f);
    float sx = 1.f / (tanHalfFov * aAspect);
    float sy = 1.f / tanHalfFov;
    float a = -(aFar + aNear) / (aFar - aNear);
    float b = -(2.f * aFar * aNear) / (aFar - aNear);

    return {{
        sx,  0.f, 0.f, 0.f,
        0.f, sy,  0.f, 0.f,
        0.f, 0.f,  a,  b,
        0.f, 0.f, -1.f, 0.f
    }};
}

# endif