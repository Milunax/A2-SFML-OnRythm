
uniform float iTime;
uniform vec2 iResolution;
vec3 palette(float t) {
    vec3 a = vec3(0.6, 0.4, 0.5);
    vec3 b = vec3(0.7, 0.3, 0.5);
    vec3 c = vec3(0.8, 1.0, 0.6);
    vec3 d = vec3(0.76, 0.41, 0.96);

    return a + b * cos(6.28318 * (c * t + d));
}

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    vec2 uv = (fragCoord * 2.0 - iResolution.xy) / iResolution.y;
    vec2 uv0 = uv;
    
    vec3 finalColor = vec3(0.0);
    
    for (float i = 0.0; i < 4.0; ++i) {
        uv = fract(uv * 1.6) - 0.5;
        float d = length(uv) * exp(-length(uv0));

        vec3 color = palette(length(uv0) + i * 0.2 + iTime * 0.4);
        d = sin(d * 12.0 + iTime) / 12.0;
        d = abs(d);
        d = pow(0.0015 / d, 1.3);

        finalColor += color * d;
    }
    
    
    vec3 neonColor = vec3(
        0.5 + 0.5 * sin(finalColor.r * 10.0 + iTime/4. * 30.0),
        0.5 + 0.5 * sin(finalColor.g * 10.0 + iTime/4. * 30.0 + 1.0),
        0.5 + 0.5 * sin(finalColor.b * 10.0 + iTime/4. * 30.0 + 2.0)
    );

    fragColor = vec4(neonColor, 1.0);
}


void main()
{
    // lookup the pixel in the texture
    //vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    //gl_FragColor = gl_Color * pixel;

    mainImage(gl_FragColor, gl_FragCoord);
}