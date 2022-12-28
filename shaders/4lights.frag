#version 330 core

uniform mat4 modelViewMatrixInverse;

out vec4 fragColor;

in vec3 N;   	// normal (en object space)
in vec3 P; 	// posicio del vertex (en object space)

uniform float time;
uniform bool rotate;

// V, N, P, lightPos han d'estar al mateix espai de coordenades
// V és el vector unitari cap a l'observador
// N és la normal
// P és la posició 
// lightPos és la posició de la llum
// lightColor és el color de la llum
vec4 light(vec3 V, vec3 N, vec3 P, vec3 lightPos, vec3 lightColor)
{
	const float shininess = 100.0;
	const float Kd = 0.5;
	N = normalize(N);
	vec3 L = normalize(lightPos - P);
	vec3 R = reflect(-L, N);
	float NdotL = max(0.0, dot(N,L));
	float RdotV = max(0.0, dot(R,V));
	float spec =  pow( RdotV, shininess);
	return vec4(Kd*lightColor*NdotL + vec3(spec),0);
}

void main()
{
	//coordenadas en eye space
	vec3 Light1Pos = vec3(0,10,0); //green
	vec3 Light2Pos = vec3(0,-10,0); //yellow
	vec3 Light3Pos = vec3(10,0,0); //blue
	vec3 Light4Pos = vec3(-10,0,0); //red
	
	float angle = 0;
	if (rotate)  {
	   angle = time;
	   float cs = cos(angle);
           float sn = sin(angle);
           mat3 R = mat3(vec3(cs, sn, 0), vec3(-sn, cs,0), vec3(0,0,1));
           Light1Pos = R*Light1Pos;
           Light2Pos = R*Light2Pos;
           Light3Pos = R*Light3Pos;
           Light4Pos = R*Light4Pos;  
        }
	vec3 V = normalize(modelViewMatrixInverse[3].xyz - P);
	vec4 c = vec4(0);
		
	//coordenadas en object space
	Light1Pos = (modelViewMatrixInverse * vec4(Light1Pos, 1)).xyz; //green
	Light2Pos = (modelViewMatrixInverse * vec4(Light2Pos, 1)).xyz; //yellow
	Light3Pos = (modelViewMatrixInverse * vec4(Light3Pos, 1)).xyz; //blue
	Light4Pos = (modelViewMatrixInverse * vec4(Light4Pos, 1)).xyz; //red
	
	c = light(V, N, P, Light1Pos.xyz, vec3(0, 1, 0)) + light(V, N, P, Light2Pos.xyz, vec3(1, 1, 0)) + light(V, N, P, Light3Pos.xyz, vec3(0, 0, 1)) + light(V, N, P, Light4Pos.xyz, vec3(1, 0, 0));
	fragColor = c;
}

