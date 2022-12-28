#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float speed = 0.5; //en rad/s
uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    mat4 rotateMatrix;
    float angle = speed*time;
    rotateMatrix[0] = vec4(cos(angle), 0.0, -sin(angle), 0.0);
    rotateMatrix[1] = vec4(0.0, 1.0, 0.0, 0.0);
    rotateMatrix[2] = vec4(sin(angle), 0.0, cos(angle), 0.0);
    rotateMatrix[3] = vec4(0.0, 0.0, 0.0, 1.0);
    gl_Position = modelViewProjectionMatrix * rotateMatrix * vec4(vertex, 1.0);
}
