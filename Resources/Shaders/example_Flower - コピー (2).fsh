// Shader from http://www.iquilezles.org/apps/shadertoy/

#ifdef GL_ES
precision highp float;
#endif

uniform vec2 center;
uniform float time;
uniform vec2 nima[5];

void main(void)
{
  // vec2 p = 2.0 * (gl_FragCoord.xy - center.xy) / center.xy ;
	
	float x = gl_FragCoord.x;
	float y = gl_FragCoord.y;
	

	int t = int(x);
	int m = int(y);
	//if(pixel[(640*m + t)/2].x >= 0.0){
	
	gl_FragColor = vec4(
		1.0,
		0.0,
		0.0,
		1.0);
//	}
		

	
}