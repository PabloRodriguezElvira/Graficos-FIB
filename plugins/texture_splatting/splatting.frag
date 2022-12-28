#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D sampler0; 
uniform sampler2D sampler1; 
uniform sampler2D sampler2; 

void main()
{
    float noiseValue = texture(sampler0, vtexCoord).r;
    vec4 texture1 = texture(sampler1, vtexCoord);
    vec4 texture2 = texture(sampler2, vtexCoord);
    fragColor = mix(texture1, texture2, noiseValue);
}
