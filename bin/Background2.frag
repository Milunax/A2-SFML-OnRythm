uniform float iTime;
uniform vec2 iResolution;

vec3 a2 = vec3(0.667,0.500,0.500);
vec3 b = vec3(0.500,0.667,0.500);
vec3 c = vec3(0.667,0.666,0.500);
vec3 d = vec3(0.200,0.000,0.500);
float plot(float r, float pct){
	return  smoothstep( pct-0.2, pct, r) -smoothstep( pct, pct+0.2, r);
}

vec3 pal( in float t){
    return a2 + b*cos( 6.28318*(c*t+d) );
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord/iResolution.xy;
    vec3 col = vec3(1.0);
    vec2 pos = vec2(0.5) - uv;
    pos.x *= iResolution.x/iResolution.y;
    pos *= cos(iTime)*1.0+1.5;

    float r = length(pos)*2.0;
    float a = atan(pos.y,pos.x);

    float f = abs(cos(a*2.5+iTime*0.5))*sin(iTime*2.0)*0.698+cos(iTime)-4.0;
    float d = f-r;
    
    col = (vec3(smoothstep(fract(d),fract(d)+-0.200,0.160))-vec3(smoothstep(fract(d),fract(d)+-1.184,0.160)) ) 
	* pal( f);
    float pct = plot(r*0.272,fract(d*(sin(iTime)*0.45+0.5)));
	
    col += pct*pal( r);

    // Output to screen
    fragColor = vec4(col,pct*0.3);
}

void main()
{
    // lookup the pixel in the texture
    //vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    //gl_FragColor = gl_Color * pixel;

    mainImage(gl_FragColor, gl_FragCoord.xy);
}