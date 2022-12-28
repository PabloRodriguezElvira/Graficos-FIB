#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

const vec4 colors[5] = vec4[5](
	vec4(1.0, 0.0, 0.0, 1.0), //red
 	vec4(1.0, 1.0, 0.0, 1.0), //yellow
 	vec4(0.0, 1.0, 0.0, 1.0), //green
 	vec4(0.0, 1.0, 1.0, 1.0), //cian
 	vec4(0.0, 0.0, 1.0, 1.0)); //blue

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    float altura_caja = boundingBoxMax.y - boundingBoxMin.y;
    float altura_vert = vertex.y - boundingBoxMin.y;
    float pos = (4.0*altura_vert)/altura_caja;
    int pos_entero = int(pos);
    
    frontColor = mix(colors[pos_entero], colors[pos_entero+1], fract(pos));
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}

