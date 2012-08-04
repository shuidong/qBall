#ifdef GL_ES                                               
precision lowp float;                                         
#endif                                                         
                                                             
varying vec4 v_fragmentColor;                                 
varying vec2 v_texCoord;                                     
uniform sampler2D u_texture;   
 
uniform sampler2D u_mask; 
uniform sampler2D u2_mask; 
uniform sampler2D u3_mask; 
uniform sampler2D u4_mask; 

                             
uniform        float u_alpha_value;                             
uniform        float u_color_value;                                                     
void main()                                                     
{                                                             
    vec4 texColor = texture2D(u_texture, v_texCoord);  
	vec4 maskColor  = texture2D(u_mask, v_texCoord); 

float a = 	texture2D(u_mask, v_texCoord).a;  
float a2 = texture2D(u_mask, v_texCoord).a;  
float a3 = texture2D(u_mask, v_texCoord).a;  
float a4 = texture2D(u_mask, v_texCoord).a;  
                                                          
    // mimic: glAlphaFunc(GL_GREATER)                         
    // pass if ( incoming_pixel >= u_alpha_value ) => fail if incoming_pixel < u_alpha_value         
	//0.7															
    if (a <= u_alpha_value )                         
        discard;  
	
	
		gl_FragColor = maskColor;
	
//    if(texColor.a <= u_alpha_value + 0.001)
//		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);

}                                                             

