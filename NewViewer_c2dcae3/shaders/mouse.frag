#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform int mode = 2;

const vec4 WHITE = vec4(1,1,1,1);
const vec4 BLACK = vec4(0,0,0,1);
const vec4 GREY = vec4(0.8, 0.8, 0.8, 1);
const vec4 SKIN = vec4(1.0, 0.8, 0.6, 1);

//Centros
const vec2 centroCirc1 = vec2(0.4, 1.6);
const vec2 centroCirc2 = vec2(1.0, 0.8);
const vec2 centroCirc3 = vec2(1.6, 1.6);

const vec2 centroOval1 = vec2(1.0, 0.6);
const vec2 centroOval2 = vec2(0.9, 0.9);
const vec2 centroOval3 = vec2(1.1, 0.9);

const vec2 centroOjo1 = vec2(0.9, 1.0);
const vec2 centroOjo2 = vec2(1.1, 1.0);

const vec2 centroPupila1 = vec2(0.9, 0.9);
const vec2 centroPupila2 = vec2(1.1, 0.9);


//Radios
const float radioPequeno = 0.4;
const float radioOvalGrande = 0.3;
const float radioOvalPeque = 0.23;
const float radioGrande = 0.7;
const float radioOjo = 0.13;
const float radioPupila = 0.07;

bool insideCirculo(vec2 punto, vec2 centro, float radio, int oval) {
    vec2 V = punto - centro;
    if (oval == 1)  V = vec2(V.x*0.5, V.y);
    else if (oval == 2) V = vec2(V.x, V.y*0.5);
    return length(V) <= radio;
}

void main()
{
    vec2 coord = vtexCoord*2.0;
    //Pintamos cara:
    if (insideCirculo(coord, centroCirc1, radioPequeno, 0) || insideCirculo(coord, centroCirc3, radioPequeno, 0) || 
        insideCirculo(coord, centroCirc2, radioGrande, 0)) fragColor = BLACK;
    else fragColor = GREY;

    //Pintamos ovalos:
    if (mode == 1 || mode == 2) {
        if (insideCirculo(coord, centroOval1, radioOvalGrande, 1)) fragColor = SKIN;
        if (insideCirculo(coord, centroOval2, radioOvalPeque, 2)) fragColor = SKIN;
        if (insideCirculo(coord, centroOval3, radioOvalPeque, 2)) fragColor = SKIN;
        if (mode == 2) {
            if (insideCirculo(coord, centroOjo1, radioOjo, 2)) fragColor = WHITE;
            if (insideCirculo(coord, centroOjo2, radioOjo, 2)) fragColor = WHITE;
            if (insideCirculo(coord, centroPupila1, radioPupila, 2)) fragColor = BLACK;
            if (insideCirculo(coord, centroPupila2, radioPupila, 2)) fragColor = BLACK;
        }
    }

}
