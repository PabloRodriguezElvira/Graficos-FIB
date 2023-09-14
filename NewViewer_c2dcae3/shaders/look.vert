#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec2 mousePosition;
uniform float mouseOverrideX;
uniform vec2 viewport = vec2(800,600);

void main()
{
    //Calcular ángulo.
    float CoordXMouse = 2.0*(mousePosition.x/viewport.x); //[0,2]
    CoordXMouse = CoordXMouse - 1; //[-1,1]

    //Calcular matriz de rotación:
    mat4 rotate;
    rotate[0] = vec4(cos(CoordXMouse), 0, -sin(CoordXMouse), 0);
    rotate[1] = vec4(0, 1, 0, 0);
    rotate[2] = vec4(sin(CoordXMouse), 0, cos(CoordXMouse), 0);
    rotate[3] = vec4(0, 0, 0, 1);

    //Parámetro de interpolación.
    float t = smoothstep(1.45, 1.55, vertex.y);

    //Vértice rotado.
    vec4 vertexRotate = rotate*vec4(vertex, 1);

    vec3 newVertex = mix(vertex, vertexRotate.xyz, t);

    //Calcular la nueva normal:
    vec4 normalRotada = rotate*vec4(normal, 1);
    vec3 normalInterp = mix(normal, normalRotada.xyz, t);
    normalInterp = normalize(normalMatrix * normalInterp);

    frontColor = vec4(normalInterp.z, normalInterp.z, normalInterp.z, 1.0);
    vtexCoord = texCoord;

    gl_Position = modelViewProjectionMatrix * vec4(newVertex, 1.0);
}
