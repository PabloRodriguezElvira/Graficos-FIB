#version 330 core

out vec4 fragColor;

uniform sampler2D colorMap0; 
uniform float size;

void main()
{
    fragColor = texture(colorMap0, (gl_FragCoord.xy-vec2(0.5))/size);
}
