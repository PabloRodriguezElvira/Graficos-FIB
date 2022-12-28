#version 330 core

in vec2 vtexCoord;
in vec3 N;
in vec3 vertexEyeSpace;
out vec4 fragColor;

uniform float time;
uniform sampler2D colorMap;

//Propiedades de la luz
uniform vec4 lightSpecular;	
uniform vec4 lightPosition;

//Propiedades del material
uniform vec4 matSpecular; 
uniform float matShininess;

const vec3 BLACK = vec3(0);
const vec3 GREY = vec3(0.8);


vec4 Phong(vec3 N, vec3 L, vec3 V, vec3 R, vec4 lightDiffuse, vec4 matDiffuse) {
	vec4 Diffuse = matDiffuse * lightDiffuse * max(0.0, dot(N,L));
	vec4 Specular = matSpecular * lightSpecular * max(0.0, pow(dot(R,V), matShininess));
	return Diffuse + Specular;
}

void main()
{
    vec4 lightDiffuse, matDiffuse;
    vec2 vCoord = vtexCoord * vec2(1.0/4.0, 1.0/3.0);

    if (int(time)%2 == 0) lightDiffuse = vec4(mix(BLACK, GREY, fract(time)), 1);
    else lightDiffuse = vec4(mix(GREY, BLACK, fract(time)), 1);

    float slice = 2.0;
    int frame = int(mod(time/slice, 12));

    int x = frame/3;
    int y = 2 - frame%3;
    vCoord.x += (x/4.0);
    vCoord.y += (y/3.0);
    matDiffuse = texture(colorMap, vCoord);

    vec3 Normal = normalize(N); //normal en eye space.
    vec3 L = normalize(lightPosition.xyz-vertexEyeSpace);
    vec3 V = normalize(-vertexEyeSpace);
    vec3 R = (2.0 * dot(Normal, L)*Normal) - L;

    fragColor = Phong(Normal, L, V, R, lightDiffuse, matDiffuse);

}
