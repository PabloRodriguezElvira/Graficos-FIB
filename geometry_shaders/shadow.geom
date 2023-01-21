#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin;
uniform mat4 modelViewProjectionMatrix;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();		
	}
	EndPrimitive();
	for (int i = 0; i < 3; ++i) {
		// Triangulo negro:
		gfrontColor = vec4(0,0,0,1);
		vec4 pos = vec4(gl_in[i].gl_Position.x, boundingBoxMin.y, gl_in[i].gl_Position.z, gl_in[i].gl_Position.w);
		gl_Position = modelViewProjectionMatrix * pos;
		EmitVertex();
	}
    EndPrimitive();
}
