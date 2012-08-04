// Shader from http://www.iquilezles.org/apps/shadertoy/

#ifdef GL_ES
precision highp float;
#endif

uniform vec2 center;
uniform float time;
uniform vec2 nima[100];

void main(void)
{
   vec2 p = 2.0 * (gl_FragCoord.xy - center.xy) / center.xy ;
	//float xt = nima[1].x;
	float x = gl_FragCoord.x;
	float y = gl_FragCoord.y;
	gl_FragColor = vec4(
		1.0,
		0.0,
		0.0,
		1.0);
	


		

	
}