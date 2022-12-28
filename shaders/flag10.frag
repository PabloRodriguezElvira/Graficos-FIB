#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;


const vec4 GREEN = vec4(0,0.7,0.4,0);
const vec4 WHITE = vec4(1, 1, 1, 0);

const float RA = 4.0/3.0;

bool insideL(vec2 punto, vec2 centro, float radio) {
	return distance(punto, centro) < radio;
}

void main()
{
	vec2 Coord = vtexCoord * 2.0;
   	//Luna:
   	vec2 centro = vec2(1.0*RA , 1.0);
   	vec2 punto = vec2(Coord.s*RA, Coord.t);
   	if (insideL(punto, centro, 0.5) && !insideL(punto, centro, 0.25)) fragColor = GREEN;
   	else fragColor = WHITE;
    
}
