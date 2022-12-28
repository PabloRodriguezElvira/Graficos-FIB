#version 330 core

in vec4 frontColor;
in vec3 NormalEyeSpace;
out vec4 fragColor;

void main()
{
    vec3 N = normalize(NormalEyeSpace);
    fragColor = frontColor * N.z;
}
