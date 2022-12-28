#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

const vec4 gris_clar = vec4(0.8);
const vec4 negre = vec4(0);

void main()
{
    //vtexCoord -> [0,1]
    vec2 tex = 8.0*vtexCoord; 
    int x = int(floor(tex.s));
    int y = int(floor(tex.t));
    if (x%2 == y%2) fragColor = gris_clar;
    else fragColor = negre;
}
