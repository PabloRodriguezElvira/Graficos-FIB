#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;
const int DNI[] = int[](4,7,6,7,2,7);

void main()
{
   	int digito = int(vtexCoord.s);
    vec2 Coord = vec2(fract(vtexCoord.s)/10.0 + DNI[digito]/10.0, vtexCoord.t);
    fragColor = texture(colorMap, Coord);
}
