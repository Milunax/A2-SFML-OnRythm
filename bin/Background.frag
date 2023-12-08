
uniform float iTime;
uniform vec3 a;
uniform vec3 b;
uniform vec3 c;
uniform vec3 d;
uniform vec2 iResolution;

vec3 palette( float t ) {
    vec3 a2 = a;
    vec3 b2 = b;
    vec3 c2 = c;
    vec3 d2 = d;

    return a2 + b2*cos( 6.28318*(c2*t+d2) );
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = (fragCoord * 2.0 - iResolution.xy) / iResolution.y;
    vec2 uv0 = uv;
    vec3 finalColor = vec3(0.0);
    
    for (float i = 0.0; i < 3.0; i++) {
        uv = fract(uv * 1.5) - 0.5;

        float d = length(uv)  * exp(-length(uv0));

        vec3 col = palette(length(uv0) + i*.5 + iTime*.4);
        col.x *= abs(sin(iTime));

        d = sin(d*8. + iTime*1.5)/8.;
        d = abs(d);

        d = pow(0.01 / d, 1.2);

        col *= abs(sin(iTime));
        finalColor += col * d;
    }
    // Time varying pixel color

    // Output to screen
    fragColor = vec4(finalColor,1.0);
}

void main()
{
    // lookup the pixel in the texture
    //vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    //gl_FragColor = gl_Color * pixel;

    mainImage(gl_FragColor, gl_FragCoord.xy);
}