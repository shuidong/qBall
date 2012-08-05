#ifdef GL_ES                                               
precision lowp float;                                         
#endif                                                         
                                                             
varying vec4 v_fragmentColor;                                 
varying vec2 v_texCoord;                                     
uniform sampler2D u_texture;   
                                                  
void main()                                                     
{                                                             
    vec4 texColor = texture2D(u_texture, v_texCoord);  
	float r = 	texture2D(u_texture, v_texCoord).r;
	float g = 	texture2D(u_texture, v_texCoord).g;
	float b = 	texture2D(u_texture, v_texCoord).b;
	float a = 	texture2D(u_texture, v_texCoord).a;   
    
	if(a == 0.0)
		discard;
		
	if( (r== 1.0 && g== 0.0 && b==0.0) || (r== 0.0 && g== 1.0 && b==0.0) || (r== 0.0 && g== 0.0 && b==1.0) || (r== 0.0 && g== 0.0 && b==0.0) ){
		gl_FragColor = vec4(r, g, b, 1.0);
	}else{
		gl_FragColor = vec4(r, g, b, 1.0);
	}
}                                                             

