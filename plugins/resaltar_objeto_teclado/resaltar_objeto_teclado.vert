#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 scaleMatrix;
uniform mat4 translateMatrix;

void main()
{
    frontColor = vec4(color,1.0);
    gl_Position = modelViewProjectionMatrix * translateMatrix * scaleMatrix * vec4(vertex, 1);
}