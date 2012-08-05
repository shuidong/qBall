#ifdef GL_ES                                               
precision lowp float;                                         
#endif                                                         
                                                             
varying vec4 v_fragmentColor;                                 
varying vec2 v_texCoord;                                     
uniform sampler2D u_texture;   
                                                  
void main()                                                     
{                               
	float unitx = 0.0012;//1/640	
	float unity = 0.0012;//1/800	
    vec4 texColor = texture2D(u_texture, v_texCoord);
	vec4 texLfColor = texture2D(u_texture, vec2(v_texCoord.x - 1 * unitx, v_texCoord.y));	
	vec4 texRtColor = texture2D(u_texture, vec2(v_texCoord.x + 1 * unitx, v_texCoord.y));	
	vec4 texUpColor   = texture2D(u_texture, vec2(v_texCoord.x, v_texCoord.y - 1 * unity));
	vec4 texDnColor   = texture2D(u_texture, vec2(v_texCoord.x, v_texCoord.y + 1 * unity));
	
	float r = 	texColor.x;
	float g = 	texColor.y;
	float b = 	texColor.z;
	float a = 	texColor.w;   
    
	if(a == 0.0)
		discard;
	if( (texLfColor.xyz != texRtColor.xyz) ||
		(texUpColor.xyz != texDnColor.xyz) 
		) {
			gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
		
	}else{
		float f = 0.85;//1.0 - (a-0.25)/0.75;
		gl_FragColor = vec4(r*f, g*f, b*f, 1.0);
	}
}                                                             
