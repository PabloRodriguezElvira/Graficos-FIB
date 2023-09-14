#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform float step = 0.1;
uniform mat3 normalMatrix;
uniform mat4 modelViewProjectionMatrix;

const vec4 GREY = vec4(0.5, 0.5, 0.5, 1);

void verticeCubo(bool x, bool y, bool z, vec3 N, vec3 B) {
	float xx = x ? 0.5 : -0.5;
	float yy = y ? 0.5 : -0.5;
	float zz = z ? 0.5 : -0.5;
	gfrontColor = GREY * N.z;
	gl_Position = modelViewProjectionMatrix * vec4(B + vec3(xx*step, yy*step, zz*step), 1);
	EmitVertex();
}

void pintarCubo(vec3 baricentro) {
	//cara frontal
	vec3 N = normalMatrix * vec3(0,0,1);
	verticeCubo(true, true, true, N, baricentro);
	verticeCubo(false, true, true, N, baricentro);
	verticeCubo(true, false, true, N, baricentro);
	verticeCubo(false, false, true, N, baricentro);
	EndPrimitive();

	//cara top
	N = normalMatrix * vec3(0,1,0);
	verticeCubo(false, true, true, N, baricentro);
	verticeCubo(true, true, true, N, baricentro);
	verticeCubo(false, true, false, N, baricentro);
	verticeCubo(true, true, false, N, baricentro);
	EndPrimitive();

	//cara back
	N = normalMatrix * vec3(0,0,-1);
	verticeCubo(false, true, false, N, baricentro);
	verticeCubo(true, true, false, N, baricentro);
	verticeCubo(false, false, false, N, baricentro);
	verticeCubo(true, false, false, N, baricentro);
	EndPrimitive();

	//cara bottom
	N = normalMatrix * vec3(0,-1,0);
	verticeCubo(true, false, false, N, baricentro);
	verticeCubo(true, false, true, N, baricentro);
	verticeCubo(false, false, false, N, baricentro);
	verticeCubo(false, false, true, N, baricentro);
	EndPrimitive();

	//cara right
	N = normalMatrix * vec3(1,0,0);
	verticeCubo(true, true, false, N, baricentro);
	verticeCubo(true, true, true, N, baricentro);
	verticeCubo(true, false, false, N, baricentro);
	verticeCubo(true, false, true, N, baricentro);
	EndPrimitive();

	//cara left
	N = normalMatrix * vec3(-1,0,0);
	verticeCubo(false, false, false, N, baricentro);
	verticeCubo(false, false, true, N, baricentro);
	verticeCubo(false, true, false, N, baricentro);
	verticeCubo(false, true, true, N, baricentro);
	EndPrimitive();
}
void main( void )
{
	vec3 baricentro = (gl_in[0].gl_Position.xyz + gl_in[1].gl_Position.xyz + gl_in[2].gl_Position.xyz)/3.0;
	baricentro /= step;
	baricentro = vec3(int(baricentro.x), int(baricentro.y), int(baricentro.z));
	baricentro *= step;
	pintarCubo(baricentro);
}
