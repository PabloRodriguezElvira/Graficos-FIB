#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
out vec2 gtexCoord;

uniform vec4 lightPosition; //Está en eye space.
uniform float w = 0.3;
uniform mat4 projectionMatrix;

void dibujarQuad() {
	vec4 lightPosClipSpace = projectionMatrix * lightPosition;
	vec3 lightPosNDC = lightPosClipSpace.xyz/lightPosClipSpace.w;

	vec4 V1 = vec4(lightPosNDC.x - w, lightPosNDC.y - w, lightPosNDC.z, 1.0);
	vec4 V2 = vec4(lightPosNDC.x - w, lightPosNDC.y + w, lightPosNDC.z, 1.0);
	vec4 V3 = vec4(lightPosNDC.x + w, lightPosNDC.y + w, lightPosNDC.z, 1.0);
	vec4 V4 = vec4(lightPosNDC.x + w, lightPosNDC.y - w, lightPosNDC.z, 1.0);

	gtexCoord = vec2(0,1);
	gl_Position = V2;
	EmitVertex();

	gtexCoord = vec2(1,1);
	gl_Position = V3;
	EmitVertex();

	gtexCoord = vec2(0,0);
	gl_Position = V1;
	EmitVertex();

	gtexCoord = vec2(1,0);
	gl_Position = V4;
	EmitVertex(); 	

	EndPrimitive();
}


void main( void )
{
	if (gl_PrimitiveIDIn == 0) dibujarQuad();	
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gtexCoord = vec2(-1, -1);
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}
