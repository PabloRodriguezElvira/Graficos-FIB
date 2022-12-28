#version 330 core

in vec4 frontColor;
in vec3 N;
in vec3 vert;
out vec4 fragColor;

//Propiedades de la luz
uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;	
uniform vec4 lightPosition; //está en eye space

//Propiedades del material
uniform vec4 matAmbient; 
uniform vec4 matDiffuse; 
uniform vec4 matSpecular; 
uniform float matShininess;

uniform mat4 modelViewMatrixInverse;
uniform bool world;

vec4 light(vec3 N, vec3 V, vec3 L)
{
	 N=normalize(N); V=normalize(V); L=normalize(L);
	 vec3 R = normalize( 2.0*dot(N,L)*N-L );
	 float NdotL = max( 0.0, dot( N,L ) );
	 float RdotV = max( 0.0, dot( R,V ) );
	 float Idiff = NdotL;
	 float Ispec = 0;
	 if (NdotL>0) Ispec=pow( RdotV, matShininess );
	 return
	 matAmbient * lightAmbient +
	 matDiffuse * lightDiffuse * Idiff+
	 matSpecular * lightSpecular * Ispec;
}

void main()
{

    vec3 Normal = N;
    vec3 L, V;
    if (world) { //World Space
    	L = (modelViewMatrixInverse * lightPosition).xyz-vert;
    	V = (modelViewMatrixInverse * vec4(0,0,0,1)).xyz-vert; //Camara -> 0,0,0
    }
    else { //Eye Space
    	L = lightPosition.xyz - vert;
    	V = -vert;
    }
    fragColor = light(Normal, V, L);
}
