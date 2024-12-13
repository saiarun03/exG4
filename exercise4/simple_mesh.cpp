#include "simple_mesh.hpp"

// Concatenate two SimpleMeshData objects
SimpleMeshData concatenate(SimpleMeshData aM, SimpleMeshData const& aN)
{
    aM.positions.insert(aM.positions.end(), aN.positions.begin(), aN.positions.end());
    aM.colors.insert(aM.colors.end(), aN.colors.begin(), aN.colors.end());
    return aM;
}

// Create a VAO from SimpleMeshData
GLuint create_vao(SimpleMeshData const& aMeshData)
{
    GLuint vao = 0;
    GLuint positionVBO = 0;
    GLuint colorVBO = 0;

    // Generate and bind the VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Generate and fill position VBO
    glGenBuffers(1, &positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        aMeshData.positions.size() * sizeof(Vec3f), // Size of position data
        aMeshData.positions.data(),                // Pointer to position data
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Attribute location 0
    glEnableVertexAttribArray(0);

    // Generate and fill color VBO
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        aMeshData.colors.size() * sizeof(Vec3f), // Size of color data
        aMeshData.colors.data(),                // Pointer to color data
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Attribute location 1
    glEnableVertexAttribArray(1);

    // Unbind VAO and VBO to prevent accidental modifications
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vao;
}
