 #version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

const vec4 blanco = vec4(1);
const vec4 rojo = vec4(1,0,0,0);

void main()
{
    vec2 centro = vec2(0.5, 0.5);
    float dist = distance(centro, vtexCoord);
    if (dist > 0.2) fragColor = blanco;
    else fragColor = rojo;
}
