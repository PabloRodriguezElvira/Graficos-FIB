#version 330 core

in vec4 frontColor;
in vec3 vert;
out vec4 fragColor;

void main()
{
    //Calcular la normal con derivadas parciales:
    
    vec3 dX = dFdx(vert);
    vec3 dY = dFdy(vert);
    vec3 N = normalize(cross(dX, dY));
    fragColor = frontColor * N.z;
}
