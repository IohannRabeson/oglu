#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3	vertexPosition;
layout(location = 1) in vec3	vertexColor;

uniform mat4    camera;
out vec3        fragmentColor;

void main()
{
    gl_Position = camera * vec4(vertexPosition, 1.0);
    fragmentColor = vertexColor;
}

