#version 330 core

in vec3 N;
in vec3 vertexEyeSpace;
out vec4 fragColor;

uniform int n = 4;

//Propiedades de la luz
uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;	

//Propiedades del material
uniform vec4 matAmbient; 
uniform vec4 matDiffuse; 
uniform vec4 matSpecular; 
uniform float matShininess;

uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;

const float pi = 3.141592;


vec4 Phong(vec3 N, vec3 L, vec3 V, vec3 R) {
	vec4 Diffuse = matDiffuse * lightDiffuse * max(0.0, dot(N,L));
	vec4 Specular = matSpecular * lightSpecular * max(0.0, pow(dot(R,V), matShininess));
	return Diffuse/sqrt(n) + Specular;
}


void main()
{
    vec3 Normal = normalize(normalMatrix*N); //normal en eye space.
    vec3 V = normalize(-vertexEyeSpace);
    
    fragColor = vec4(0);
    for (int i = 0; i < n; ++i) {
        vec3 lightPosition = vec3(10*cos(2*pi*i/n), 10*sin(2*pi*i/n), 0);
        vec3 L = normalize(lightPosition-vertexEyeSpace);
        vec3 R = (2.0 * dot(Normal, L)*Normal) - L; 
        fragColor += Phong(Normal, L, V, R);
    }

}
