#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform float time;
uniform mat4 modelViewProjectionMatrix;

in vec4 vfrontColor[];
in vec3 vN[];
in vec3 vVertex[];

out vec4 gfrontColor;

const float speed = 0.5;

void main( void )
{
	vec3 trans = speed*time*((vN[0] + vN[1] + vN[2])/3.0);
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		vec3 Vpos = gl_in[i].gl_Position.xyz + trans;
		gl_Position = modelViewProjectionMatrix * vec4(Vpos, 1.0); 
		EmitVertex();
	}
    EndPrimitive();
}
