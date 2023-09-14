#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D explosion;
uniform float time;

//despl horizontal -> modulo
//despl vertical -> division	

void main()
{
    float slice = 1.0/30.0;
    vec2 vCoord = vtexCoord * vec2(1.0/8.0, 1.0/6.0);
 
    int frame = int(mod(time/slice, 48));
    int x = frame%8;
    int y = 5 - frame/8; //Empieza en frame (5/6), (4/6), (3/6), ....
    vCoord.x += (x/8.0);
    vCoord.y += (y/6.0);
    fragColor = texture(explosion, vCoord);
    fragColor = fragColor * fragColor.w;
}
