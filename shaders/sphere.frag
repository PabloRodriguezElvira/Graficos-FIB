#version 330 core

in vec2 vtexCoord;
in vec3 vertexEyeSpace;
out vec4 fragColor;

uniform int mode = 1;

//Propiedades de la luz
uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;	
uniform vec4 lightPosition;

//Propiedades del material
uniform vec4 matAmbient; 
uniform vec4 matDiffuse; 
uniform vec4 matSpecular; 
uniform float matShininess;

uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

const vec4 BLACK = vec4(0,0,0,1);

bool insideCirculo(vec2 punto, vec2 centro, float radio) {
    return distance(punto, centro) <= radio;
}

vec4 Phong(vec3 N, vec3 L, vec3 V, vec3 R) {
	vec4 Ambient = matAmbient * lightAmbient;
	vec4 Diffuse = matDiffuse * lightDiffuse * max(0.0, dot(N,L));
	vec4 Specular = matSpecular * lightSpecular * max(0.0, pow(dot(R,V), matShininess));
	return Ambient + Diffuse + Specular;
}

void main()
{
    //fragColor = frontColor;
    if (mode == 0) {
        if (insideCirculo(vtexCoord, vec2(0,0), 1)) fragColor = BLACK;
        else discard;
    }
    else if (insideCirculo(vtexCoord, vec2(0,0), 1)) {
        vec3 N = vec3(vtexCoord.s, vtexCoord.t, sqrt(1 - vtexCoord.s*vtexCoord.s - vtexCoord.t*vtexCoord.t));
        vec3 point = (modelViewMatrix * vec4(N, 1.0)).xyz;
        if (mode == 1) fragColor = vec4(N.z, N.z, N.z, 1);
        else {
            vec3 Normal = normalize(normalMatrix*N); //normal en eye space.
            vec3 L = normalize(lightPosition.xyz-point);
            vec3 V = normalize(-point);
            vec3 R = (2.0 * dot(Normal, L)*Normal) - L; 
            fragColor = Phong(Normal, L, V, R);
        }
    }
    else discard;
}
