#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float time;
uniform sampler2D colorMap;

void main()
{
    int u, d, c;
    u = int(time)%10;
    d = int(time)/10 % 10;
    c = int(time)/100;
    if (vtexCoord.s < 1) fragColor = texture(colorMap, vec2(vtexCoord.s/10.0 + c/10.0, vtexCoord.t));
    if (vtexCoord.s < 2) fragColor = texture(colorMap, vec2(vtexCoord.s/10.0 + d/10.0 - 1/10.0, vtexCoord.t));
    if (vtexCoord.s < 3) fragColor = texture(colorMap, vec2(vtexCoord.s/10.0 + u/10.0 - 2/10.0, vtexCoord.t));
    if (fragColor.a < 0.5) discard;
    fragColor = vec4(1,0,0,0);
}
