uniform float iTime;
uniform vec2 iResolution;

void mainImage(out vec4 O, vec2 o) {
    vec2   c  = iResolution.xy; 
           o  += o - c;
    vec3   r  ;    
    float  e  = 0., t, d, m = iTime;
            
    for (O *= t = e; e++ < 1e2;                
        r = t*normalize(vec3(abs(o/c.y),1)),

        d  = length(r - vec3(0,0,15)) - 1.,        
        O += vec4(.2,.1,.04,0) / (1. + d/.1),
        
        r.z += m,
        r.xy = fract(r.xy*mat2(cos(sin(r.z)*sin(m)*.3+vec4(0,33,11,0))))-.5,
        
        t += d = min(d, length(r.xy) - .1),
        
        O += .05 * smoothstep(0., 1., cos(t*.1*(sin(m)+20.) + 
             vec4(0,1,2,0) * (.15+length(r.xy)*2.) - m) -.6) / 
             (1. + d) / exp(t*.1) * smoothstep(.2, 1., m*.2));
}
void main()
{
    // lookup the pixel in the texture
    //vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    //gl_FragColor = gl_Color * pixel;

    mainImage(gl_FragColor, gl_FragCoord.xy);
}