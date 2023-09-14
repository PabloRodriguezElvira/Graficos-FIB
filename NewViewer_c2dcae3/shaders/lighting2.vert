#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

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
    vec3 N = normalize(normalMatrix * normal); //Normal en eye space
    vec4 VertexEyeSpace = modelViewMatrix * vec4(vertex, 1.0);
    vec3 L = normalize(lightPosition.xyz - VertexEyeSpace.xyz);
    vec3 R = 2.0 * dot(N,L)*N - L;
    vec3 V = normalize(-VertexEyeSpace.xyz); //(0,0,0) - Vertex
    frontColor = Phong(N, L, V, R);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
