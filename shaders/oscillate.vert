#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform bool eyespace;
uniform float time;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
uniform mat4 modelViewMatrix;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    
    //FUNCION SINUSOIDAL = ampl * sin(2pi * freq * time + ϴ) 
    //Periodo = 2pi seg ---> ampl * sin(time+fase)
    
    float r = distance(boundingBoxMin, boundingBoxMax)/2.0;
    float y = vertex.y; //coordenada y del vértex en OBJECT space.
    if (eyespace) y = (modelViewMatrix * vec4(vertex, 1.0)).y; //coordenada y del vértex en EYE space.
    float d = (r/10.0)*y;
    
    float sinusoidal = d * sin(time);
    vec4 vertexClip = modelViewProjectionMatrix * vec4(vertex.xyz + normal*sinusoidal, 1.0);
    gl_Position = vertexClip;
}
