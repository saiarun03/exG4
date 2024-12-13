#include "box.hpp"
#include "simple_mesh.hpp"
#include "../vmlib/vec3.hpp"
#include "../vmlib/mat44.hpp"
SimpleMeshData make_box(bool aCapped, std::size_t aSubdivs, Vec3f aColor, Mat44f aPreTransform)
{
    std::vector<Vec3f> pos;

    // Define the 8 corners of the box (cuboid) in local space
    Vec3f vertices[8] = {
        {-0.5f, -0.5f,  0.5f}, // 0 - front bottom left
        { 0.5f, -0.5f,  0.5f}, // 1 - front bottom right
        { 0.5f,  0.5f,  0.5f}, // 2 - front top right
        {-0.5f,  0.5f,  0.5f}, // 3 - front top left
        {-0.5f, -0.5f, -0.5f}, // 4 - back bottom left
        { 0.5f, -0.5f, -0.5f}, // 5 - back bottom right
        { 0.5f,  0.5f, -0.5f}, // 6 - back top right
        {-0.5f,  0.5f, -0.5f}  // 7 - back top left
    };

    // Generate the 12 triangles (2 per face) for the 6 faces of the box
    std::vector<std::size_t> indices = {
        // Front face
        0, 1, 2,  0, 2, 3,
        // Back face
        4, 5, 6,  4, 6, 7,
        // Left face
        0, 4, 7,  0, 7, 3,
        // Right face
        1, 5, 6,  1, 6, 2,
        // Top face
        3, 2, 6,  3, 6, 7,
        // Bottom face
        0, 1, 5,  0, 5, 4
    };

    // Apply the pre-transform to all vertices
    for (auto& v : vertices)
    {
        Vec4f v4{v.x, v.y, v.z, 1.f};
        Vec4f transformed = aPreTransform * v4;
        transformed /= transformed.w; // Homogeneous normalization
        v = {transformed.x, transformed.y, transformed.z};
    }

    // Add the vertices to the position list according to the indices
    for (auto idx : indices)
    {
        pos.push_back(vertices[idx]);
    }

    // Create color data for all vertices
    std::vector<Vec3f> col(pos.size(), aColor);

    // Return the SimpleMeshData with positions and colors
    return SimpleMeshData(std::move(pos), std::move(col));
}
