#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float amp = 0.5;
uniform float freq = 0.25;
uniform float time;

const float PI = 3.141592;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    float angle = amp*sin(2.0*PI*freq*time + vertex.y);
    mat4 rotateMatrix;
    rotateMatrix[0] = vec4(1.0, 0.0, 0.0, 0.0);
    rotateMatrix[1] = vec4(0.0, cos(angle), sin(angle), 0.0);
    rotateMatrix[2] = vec4(0.0, -sin(angle), cos(angle), 0.0);
    rotateMatrix[3] = vec4(0.0, 0.0, 0.0, 1.0);
    gl_Position = modelViewProjectionMatrix * rotateMatrix * vec4(vertex, 1.0);
}
