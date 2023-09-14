#version 330 core

in vec4 gfrontColor;
in vec2 gtexCoord;
out vec4 fragColor;

const vec4 YELLOW = vec4(1,1,0,0);
const vec4 BLACK = vec4(0,0,0,0);

void main()
{
    if (gtexCoord.t >= 3 && gtexCoord.t <= 8 && gtexCoord.s >= 4 && gtexCoord.s <= 5) {
        fragColor = BLACK;
    } 
    else if (gtexCoord.s >= 4 && gtexCoord.s <= 7 && gtexCoord.t >= 7 && gtexCoord.t <= 8) {
        fragColor = BLACK; 
    }
    else if (gtexCoord.s >= 5 && gtexCoord.s <= 6 && gtexCoord.t >= 5 && gtexCoord.t <= 6) {
        fragColor = BLACK;
    }
    else if (gtexCoord.s >= 2 && gtexCoord.s <= 9) {
        fragColor = YELLOW;
    }
    else fragColor = gfrontColor;
}
