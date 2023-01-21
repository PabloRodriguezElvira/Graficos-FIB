#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec2 gtexCoord;

uniform mat4 modelViewProjectionMatrix;

uniform float size = 0.07;
uniform float depth = -0.01;

void dibujarRectangulo(vec4 P0, vec4 P1, vec4 P2, vec4 P3) {
	gtexCoord = vec2(2,9);
	gl_Position = P0;
	EmitVertex();

	gtexCoord = vec2(9,9);
	gl_Position = P1;
	EmitVertex();

	gtexCoord = vec2(2,2);
	gl_Position = P3;
	EmitVertex();

	gtexCoord = vec2(9,2);
	gl_Position = P2;
	EmitVertex(); 	

	EndPrimitive();
}

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		//Asignamos coordenadas de textura (-1,-1) al plane para diferenciarlo en el FS.
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
	//Centro en object space.
	vec4 centro = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position)/3.0;
	vec4 C = modelViewProjectionMatrix * centro;  //Clip space.
	C = C/C.w; //NDC 
	vec4 P0 = vec4(C.x - size, C.y + size, C.z + depth, 1.0);
	vec4 P1 = vec4(C.x + size, C.y + size, C.z + depth, 1.0);
	vec4 P2 = vec4(C.x + size, C.y - size, C.z + depth, 1.0);
	vec4 P3 = vec4(C.x - size, C.y - size, C.z + depth, 1.0);
	dibujarRectangulo(P0, P1, P2, P3);
}
