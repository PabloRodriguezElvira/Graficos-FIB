#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

const vec4 CIAN = vec4(0, 1, 1, 0);

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
		//Triangulo negro:
		gfrontColor = vec4(0,0,0,1);
		vec4 pos = vec4(gl_in[i].gl_Position.x, boundingBoxMin.y, gl_in[i].gl_Position.z, gl_in[i].gl_Position.w);
		gl_Position = modelViewProjectionMatrix * pos;
		EmitVertex();
	}
	EndPrimitive();
	if (gl_PrimitiveIDIn == 0) {
		float R = distance(boundingBoxMax, boundingBoxMin)/2.0;
		vec3 C = (boundingBoxMax + boundingBoxMin)/2.0;
		float y_pos = boundingBoxMin.y-0.01;

		gfrontColor = CIAN;
		gl_Position = modelViewProjectionMatrix * vec4(C.x-R, y_pos, C.z-R, 1);
		EmitVertex();

		gfrontColor = CIAN;
		gl_Position = modelViewProjectionMatrix * vec4(C.x+R, y_pos, C.z-R, 1);
		EmitVertex();
		
		gfrontColor = CIAN;
		gl_Position = modelViewProjectionMatrix * vec4(C.x-R, y_pos, C.z+R, 1);
		EmitVertex();

		gfrontColor = CIAN;		
		gl_Position = modelViewProjectionMatrix * vec4(C.x+R, y_pos, C.z+R, 1);
		EmitVertex();
	}
	EndPrimitive();
}
