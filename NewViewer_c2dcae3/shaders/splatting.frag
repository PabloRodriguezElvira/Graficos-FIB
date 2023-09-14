#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

void main()
{
    float noiseValue = texture(noise0, vtexCoord).r;
    vec4 texture_rock = texture(rock1, vtexCoord);
    vec4 texture_grass = texture(grass2, vtexCoord);
    fragColor = mix(texture_rock, texture_grass, noiseValue);
}
