#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float lambda;

const vec4 RED = vec4(1,0,0,1);
const vec4 GREEN = vec4(0,1,0,1);

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    vec4 colorInterpolado = mix(RED, GREEN, lambda); 
    frontColor = colorInterpolado * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
