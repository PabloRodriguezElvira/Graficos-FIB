#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform vec3 boundingBoxMin; //Object space.
uniform vec3 boundingBoxMax; //Object space.
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

const vec4 RED = vec4(1,0,0,0);
const vec4 GREEN = vec4(0,1,0,0);
const vec4 BLUE = vec4(0,0,1,0);

bool cameraInsideBox(vec3 min, vec3 max) {
	vec3 posCam = vec3(0,0,0); //Está en eye space.
	return posCam.x >= min.x && posCam.x <= max.x && posCam.y >= min.y && posCam.y <= max.y && posCam.z >= min.z && posCam.z <= max.z;
}

void verticeCaja(bool x, bool y, bool z, vec4 color) {
	float xx = x ? boundingBoxMax.x : boundingBoxMin.x;
	float yy = y ? boundingBoxMax.y : boundingBoxMin.y;	
	float zz = z ? boundingBoxMax.z : boundingBoxMin.z;
	gl_Position = modelViewProjectionMatrix * vec4(xx, yy, zz, 1.0);
	gfrontColor = color;
	EmitVertex();
}

void dibujarCaja() {
	//Dibujar cara +X (enviar usando forma de Z por el Triangle Strip):
	verticeCaja(true, true, true, RED);
	verticeCaja(true, true, false, RED);
	verticeCaja(true, false, true, RED);
	verticeCaja(true, false, false, RED);
	EndPrimitive();

	//Dibujar cara -X (enviar usando forma de Z por el Triangle Strip):
	verticeCaja(false, false, false, RED);
	verticeCaja(false, false, true, RED);
	verticeCaja(false, true, false, RED);
	verticeCaja(false, true, true, RED);
	EndPrimitive();

	//Dibujar cara -Y (enviar usando forma de Z por el Triangle Strip):
	verticeCaja(false, false, false, GREEN);
	verticeCaja(true, false, false, GREEN);
	verticeCaja(false, false, true, GREEN);
	verticeCaja(true, false, true, GREEN);
	EndPrimitive();

	//Dibujar cara -Z (enviar usando forma de Z por el Triangle Strip):
	verticeCaja(false, false, false, BLUE);
	verticeCaja(true, false, false, BLUE);
	verticeCaja(false, true, false, BLUE);
	verticeCaja(true, true, false, BLUE);
	EndPrimitive();
}


void main( void )
{
	if (gl_PrimitiveIDIn == 0) dibujarCaja();	
	//Bounding Box en Eye Space: (camara en eye Space es (0,0,0))
	vec4 boxMinEyeSpace = modelViewMatrix * vec4(boundingBoxMin, 1.0);
	vec4 boxMaxEyeSpace = modelViewMatrix * vec4(boundingBoxMax, 1.0);
	for ( int i = 0 ; i < 3 ; i++ ) {
		if (cameraInsideBox(boxMinEyeSpace.xyz, boxMaxEyeSpace.xyz)) gfrontColor = 2.0 * vfrontColor[i];
		else gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}
