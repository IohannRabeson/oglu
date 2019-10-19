#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

uniform mat4 Matrix_MVP;
uniform mat4 Matrix_M;
uniform vec3 LightPosition;

out vec3 vertexPositionWorld;
out vec3 vertexNormalWorld;

vec3 multiply(mat4 matrix, vec3 vector)
{
    return (matrix * vec4(vector, 1.0)).xyz;
}

void main()
{
    gl_Position = Matrix_MVP * vec4(vertexPosition, 1.0);
    vertexPositionWorld = multiply(Matrix_M, vertexPosition);
    vertexNormalWorld = vertexNormal;
}

