#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int n = 10;

void main()
{
	int linea = int(floor(gl_FragCoord.y));
	if (mod(linea, n) == 0) fragColor = frontColor;
	else discard;
}
