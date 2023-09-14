#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec2 vtexCoord;

const vec4 blanco = vec4(1);
const vec4 rojo = vec4(1,0,0,0);
const float pi = 3.1415;

uniform bool classic = true;

void main()
{
    vec2 centro = vec2(0.5, 0.5);
    float dist = distance(centro, vtexCoord);
    vec2 u = vtexCoord - centro;
    float angle = atan(u.t, u.s);
    if (classic) {
    	if (dist <= 0.2) fragColor = rojo;
    	else fragColor = blanco;
    }
    else {
    	if (dist <= 0.2) fragColor = rojo;
    	else if (mod(angle/(pi/16.0) + 0.5, 2) < 1) fragColor = rojo;
    	else fragColor = blanco;
    }
}
