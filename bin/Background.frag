uniform float iTime;
uniform vec2 iResolution;

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = (fragCoord * 2.0 - iResolution.xy) / iResolution.y;
    
    float d = length(uv);
    
    vec3 col = vec3(1.0,0.0,1.0);
    col.x *= abs(sin(iTime));
    
    d = sin(d*8. + iTime)/8.;
    d = abs(d);
    
    d = 0.05 / d;
    
    col *= abs(sin(iTime));
    col*=(d);

    // Time varying pixel color

    // Output to screen
    fragColor = vec4(col,1.0);
}

void main()
{
    // lookup the pixel in the texture
    //vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    //gl_FragColor = gl_Color * pixel;

    mainImage(gl_FragColor, gl_FragCoord);
}