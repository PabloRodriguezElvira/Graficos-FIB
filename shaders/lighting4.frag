#version 330 core

in vec4 frontColor;
in vec3 N;
in vec3 vertexEyeSpace;
out vec4 fragColor;

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


vec4 Phong(vec3 N, vec3 L, vec3 V, vec3 R) {
	vec4 Ambient = matAmbient * lightAmbient;
	vec4 Diffuse = matDiffuse * lightDiffuse * max(0.0, dot(N,L));
	vec4 Specular = matSpecular * lightSpecular * max(0.0, pow(dot(R,V), matShininess));
	return Ambient + Diffuse + Specular;
}

void main()
{
    vec3 Normal = normalize(N); //normal en eye space.
    vec3 L = normalize(lightPosition.xyz-vertexEyeSpace);
    vec3 V = normalize(-vertexEyeSpace);
    vec3 R = (2.0 * dot(Normal, L)*Normal) - L; 
    fragColor = Phong(Normal, L, V, R);
}
