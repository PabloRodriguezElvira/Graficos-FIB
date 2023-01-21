#version 330 core

in vec4 gfrontColor;
in vec2 gtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;

void main()
{
    if (gtexCoord.x < 0 && gtexCoord.y < 0) fragColor = gfrontColor;
    else {
        vec4 tex = texture(colorMap, gtexCoord);
        tex = tex * tex.a;
        if (tex.a < 0.1) discard;
        else fragColor = tex; 
    }
}
