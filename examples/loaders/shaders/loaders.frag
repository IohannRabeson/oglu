#version 330 core

in vec3 vertexPositionWorld;
in vec3 vertexNormalWorld;

out vec3 color;

uniform mat4 Matrix_MV;
uniform vec3 LightPosition;
uniform vec3 LightAmbientColor = vec3(1.0, 0.0, 0.0);
uniform vec3 LightDiffuseColor = vec3(1.0);

void main()
{
    vec3 ray = LightPosition - vertexPositionWorld;
    float angle = dot(vertexNormalWorld, ray);

//    vec3 n = normalize(vertexNormalCamera);
//    vec3 l = normalize(lightDirectionCamera);
//    float angle = dot(n, l);
//    float d = length(LightPosition);
//    float diffuseFactor = angle * (d * d);

//    vec3 lightColor = 1000.0 * LightAmbientColor * LightDiffuseColor * diffuseFactor;

    color = vec3(1.0) * angle;
}
