#version 330 core

in vec2 vtexCoord;
in vec3 normalEyeSpace;

out vec4 fragColor;

uniform sampler2D window;
uniform sampler2D palm1;
uniform sampler2D background2;
uniform float time;

void main()
{
    vec3 N = normalize(normalEyeSpace);
    vec4 C = texture(window, vtexCoord);
    if (C.a == 1.0) fragColor = C;
    else {
        vec2 coords = vtexCoord + 0.25*N.xy + vec2(0.1*sin(2*time)*vtexCoord.t, 0);
        vec4 D = texture(palm1, coords);
        if (D.a >= 0.5) fragColor = D;
        else fragColor = texture(background2, vtexCoord + 0.5*N.xy); 
    }
}
