#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;

float buscarmax(vec3 v) {
    float mx = abs(v[0]);
    for (int i = 1; i < 3; ++i) {
        if (abs(v[i]) > mx) mx = abs(v[i]);
    }
    return mx;
}

void main()
{
    frontColor = vec4(color,1.0) * N.z;
    float mx = buscarmax(vertex);
    vec3 V = vertex/mx;
    gl_Position = modelViewProjectionMatrix * vec4(V, 1.0);
}
