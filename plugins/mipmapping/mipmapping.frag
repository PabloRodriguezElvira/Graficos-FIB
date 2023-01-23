#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float quantity;

void main()
{
    fragColor = texture(colorMap, quantity*vtexCoord);
}
