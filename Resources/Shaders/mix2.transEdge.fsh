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
	
	vec4 texLfColor5 = texture2D(u_texture, vec2(v_texCoord.x - 2 * unitx, v_texCoord.y));	
	vec4 texRtColor5 = texture2D(u_texture, vec2(v_texCoord.x + 2 * unitx, v_texCoord.y));	
	vec4 texUpColor5   = texture2D(u_texture, vec2(v_texCoord.x, v_texCoord.y - 2 * unity));
	vec4 texDnColor5   = texture2D(u_texture, vec2(v_texCoord.x, v_texCoord.y + 2 * unity));
	
	
	float r = 	texColor.x;
	float g = 	texColor.y;
	float b = 	texColor.z;
	float a = 	texColor.w;   
    
	if(a == 0.0)
		discard;
	if( (texLfColor5.xyz != texRtColor5.xyz) ||
		(texUpColor5.xyz != texDnColor5.xyz) 
		) {
			gl_FragColor = vec4(0.0, 1.0, 1.0, 1.0);
		
		if( (texLfColor.xyz != texRtColor.xyz) ||
		(texUpColor.xyz != texDnColor.xyz) 
		) {
			discard;
			//gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
		}
		
	}else{
		a = 1.0;
		gl_FragColor = vec4(r*a, g*a, b*a, 1);
	}
}                                                             
