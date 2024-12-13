#include "cylinder.hpp"
#include <numbers>

SimpleMeshData make_cylinder(bool aCapped, std::size_t aSubdivs, Vec3f aColor, Mat44f aPreTransform)
{
    std::vector<Vec3f> pos;

    // Generate side faces
    float prevY = std::cos(0.f);
    float prevZ = std::sin(0.f);

    for (std::size_t i = 0; i < aSubdivs; ++i)
    {
        float const angle = (i + 1) / float(aSubdivs) * 2.f * std::numbers::pi_v<float>;
        float y = std::cos(angle);
        float z = std::sin(angle);

        // Create two triangles for the current segment
        pos.emplace_back(Vec3f{0.f, prevY, prevZ});
        pos.emplace_back(Vec3f{0.f, y, z});
        pos.emplace_back(Vec3f{1.f, prevY, prevZ});

        pos.emplace_back(Vec3f{0.f, y, z});
        pos.emplace_back(Vec3f{1.f, y, z});
        pos.emplace_back(Vec3f{1.f, prevY, prevZ});

        prevY = y;
        prevZ = z;
    }

    // Generate caps if required
    if (aCapped)
    {
        Vec3f bottomCenter = {0.f, 0.f, 0.f};
        Vec3f topCenter = {1.f, 0.f, 0.f};

        // Bottom cap
        for (std::size_t i = 0; i < aSubdivs; ++i)
        {
            float angle1 = i / float(aSubdivs) * 2.f * std::numbers::pi_v<float>;
            float angle2 = (i + 1) / float(aSubdivs) * 2.f * std::numbers::pi_v<float>;

            Vec3f p1 = {0.f, std::cos(angle1), std::sin(angle1)};
            Vec3f p2 = {0.f, std::cos(angle2), std::sin(angle2)};

            pos.emplace_back(bottomCenter);
            pos.emplace_back(p1);
            pos.emplace_back(p2);
        }

        // Top cap
        for (std::size_t i = 0; i < aSubdivs; ++i)
        {
            float angle1 = i / float(aSubdivs) * 2.f * std::numbers::pi_v<float>;
            float angle2 = (i + 1) / float(aSubdivs) * 2.f * std::numbers::pi_v<float>;

            Vec3f p1 = {1.f, std::cos(angle1), std::sin(angle1)};
            Vec3f p2 = {1.f, std::cos(angle2), std::sin(angle2)};

            pos.emplace_back(topCenter);
            pos.emplace_back(p2);
            pos.emplace_back(p1);
        }
    }

    // Apply the pre-transform matrix
    for (auto& p : pos)
    {
        Vec4f p4{p.x, p.y, p.z, 1.f};
        Vec4f transformed = aPreTransform * p4;
        transformed /= transformed.w; // Homogeneous normalization
        p = {transformed.x, transformed.y, transformed.z};
    }

    // Generate color data for all vertices
    std::vector col(pos.size(), aColor);

    return SimpleMeshData(std::move(pos), std::move(col));
}
