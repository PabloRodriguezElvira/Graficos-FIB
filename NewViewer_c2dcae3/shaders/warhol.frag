#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
    //vtexCoord está entra [0,1] (coordenadas del plane).
    int posX = int(vtexCoord.s * 2.0);
    int posY = int (vtexCoord.t * 2.0);
    float x = fract(vtexCoord.s * 2.0); 
    float y = fract(vtexCoord.t * 2.0);
    vec3 colorRGB, colorHSV;
    if (posX == 0 && posY == 1) {
        colorRGB = texture(colorMap, vec2(x, y)).xyz;
        colorHSV = rgb2hsv(colorRGB);
        //Modificamos el color en HSV
        colorHSV.y = 2.0 * colorHSV.y;
        colorHSV.x = 0.4 + colorHSV.x; 
        vec3 col = hsv2rgb(colorHSV);
        fragColor = vec4(col, 1.0);
    }
    else if (posX == 1 && posY == 1) {
        colorRGB = texture(colorMap, vec2(x, y)).xyz;
        colorHSV = rgb2hsv(colorRGB.xyz); 
        //Modificamos el color en HSV
        colorHSV.y = 2.0 * colorHSV.y;
        colorHSV.x = 0.8 + colorHSV.x; 
        vec3 col = hsv2rgb(colorHSV);
        fragColor = vec4(col, 1.0);
    }
    else if (posX == 0 && posY == 0) {
        colorRGB = texture(colorMap, vec2(x, y)).xyz;
        colorHSV = rgb2hsv(colorRGB.xyz); 
        //Modificamos el color en HSV
        colorHSV.y = 2.0 * colorHSV.y;
        colorHSV.x = 0.2 + colorHSV.x; 
        vec3 col = hsv2rgb(colorHSV);
        fragColor = vec4(col, 1.0);
    }
    else {
        colorRGB = texture(colorMap, vec2(x, y)).xyz;
        colorHSV = rgb2hsv(colorRGB.xyz); 
        //Modificamos el color en HSV
        colorHSV.y = 2.0 * colorHSV.y;
        colorHSV.x = 0.6 + colorHSV.x; 
        vec3 col = hsv2rgb(colorHSV);
        fragColor = vec4(col, 1.0);
    }
}
