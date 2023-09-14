#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

const vec4 CIAN = vec4(0, 0.7, 1, 0);
const vec4 RED = vec4(1, 0, 0, 0);
const vec4 YELLOW = vec4(1, 1, 0, 0);
const vec4 GREEN = vec4(0,0.7,0.4,0);
const vec4 BLUE = vec4(0, 0.4, 0.8, 0);

const float RA = 4.0/3.0;

void main()
{
	vec2 Coord = vtexCoord * 3.0;
    if (Coord.t < 1) fragColor = BLUE;
    else if (Coord.t >= 1 && Coord.t < 2) fragColor = YELLOW;
    else fragColor = GREEN;
    
    //Círculo rojo:
    vec2 centro = vec2(1.5*RA , 1.5);
    float radio = 1.0;
    vec2 punto = vec2(Coord.s*RA, Coord.t);
    if (distance(punto, centro) <= radio) fragColor = RED;
    
}
