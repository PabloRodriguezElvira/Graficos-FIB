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

void main()
{ 
    vec3 N = normalize(normalMatrix * normal); //normal en eye space
    frontColor = vec4(color,1.0) * N.z;
    
    vtexCoord = texCoord;
    vec4 vertexClip = modelViewProjectionMatrix * vec4(vertex, 1.0);
    float factorEscala = 0.5+abs(sin(time));
    
    vec3 vertexNDC = vertexClip.xyz/vertexClip.w;
    vec4 vertexEsc = vec4(factorEscala*vertexNDC.x, factorEscala*vertexNDC.y, vertexNDC.z, 1.0);
    gl_Position = vertexEsc;   
}

