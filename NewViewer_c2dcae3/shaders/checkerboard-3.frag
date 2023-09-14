#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

const vec4 gris_clar = vec4(0.8);
const vec4 negre = vec4(0);

void main()
{
    //vtexCoord -> [0,1]
    vec2 tex = n*vtexCoord*10.0;
    int x = int(floor(tex.s));
    int y = int(floor(tex.t));
    if (mod(x,10) == 0 || mod(y,10) == 0) fragColor = negre;
    else fragColor = gris_clar;
}
