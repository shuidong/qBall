#ifdef GL_ES                                               
precision lowp float;                                         
#endif                                                         
                                                             
varying vec4 v_fragmentColor;                                 
varying vec2 v_texCoord;                                     
uniform sampler2D u_texture;    
uniform sampler2D u_mask;                   
uniform        float u_alpha_value;                             
uniform        float u_color_value;                                                     
void main()                                                     
{                                                             
    vec4 texColor = texture2D(u_texture, v_texCoord);  
	float r = 	texture2D(u_texture, v_texCoord).r;
	float g = 	texture2D(u_texture, v_texCoord).g;
	float b = 	texture2D(u_texture, v_texCoord).b;
	float a = 	texture2D(u_texture, v_texCoord).a;  
	
	float r2 = 	texture2D(u_mask, v_texCoord).r;
	float g2 = 	texture2D(u_mask, v_texCoord).g;
	float b2 = 	texture2D(u_mask, v_texCoord).b;
	float a2 = 	texture2D(u_mask, v_texCoord).a;  

                                                          
    // mimic: glAlphaFunc(GL_GREATER)                         
    // pass if ( incoming_pixel >= u_alpha_value ) => fail if incoming_pixel < u_alpha_value         
	//0.7															
    if (a <= u_alpha_value )                      
        discard;  

	if(a < a2){
		gl_FragColor = vec4(r2, g2, b2, a2); 
	}else
	{

		if(u_color_value == 0.0)gl_FragColor = vec4(1, 0, 0, a); 
		if(u_color_value == 1.0)gl_FragColor = vec4(0, 1, 0, a); 
		if(u_color_value == 2.0)gl_FragColor = vec4(0, 0, 1, a); 
		if(u_color_value == 3.0)gl_FragColor = vec4(0, 0, 0, a); 
	}
}                                                             

