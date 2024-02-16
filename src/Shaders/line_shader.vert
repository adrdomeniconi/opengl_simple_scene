# version 330                                                               
                                                                            
layout (location = 0) in vec3 pos;

out vec4 vColour;
out vec4 WorldPosition;

uniform mat4 model;                                                         
uniform mat4 projection;                                                         
uniform mat4 view;  
                                                   
void main()                                                                 
{            
    // WorldPosition = model * vec4(pos, 1.0);                                               
    // gl_Position = projection * view * WorldPosition; 

    gl_Position = vec4(pos, 1.0);    
                         
    vColour = vec4(0.0f, 1.0f, 0.0f, 1.0f); 
}                                                                           