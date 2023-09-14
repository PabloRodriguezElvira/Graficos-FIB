#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float time;

const float PI = 3.141592;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    float angle = (vertex.y - 0.5) * sin(time);
    mat3 rotateMatrix;
    rotateMatrix[0] = vec3(1.0, 0.0, 0.0);
    rotateMatrix[1] = vec3(0.0, cos(angle), sin(angle));
    rotateMatrix[2] = vec3(0.0, -sin(angle), cos(angle));
    vec3 vert = vertex + vec3(0.0, -1.0, 0.0);
    if (vertex.y > 0.5) vert = rotateMatrix * vert;
    vert = vert + vec3(0.0, 1.0, 0.0);
    gl_Position = modelViewProjectionMatrix * vec4(vert, 1.0);
}
