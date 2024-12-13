#version 430

// Input data
layout(location = 0) in vec3 iPosition;  // 3D position
layout(location = 1) in vec3 iColor;     // Color

uniform mat4 uProjCameraWorld;           // Projection-View-Model matrix

out vec3 v2fColor; // v2f = vertex to fragment

void main()
{
    v2fColor = iColor;
    gl_Position = uProjCameraWorld * vec4(iPosition, 1.0); // Apply transformation
}
