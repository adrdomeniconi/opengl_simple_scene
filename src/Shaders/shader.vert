# version 330                                                               
                                                                            
layout (location = 0) in vec3 pos; //This location is used to handle vertices positions in relation to the origin of the object.   
layout (location = 1) in vec2 tex; //This location is used to handle texture  
layout (location = 2) in vec3 norm; // Normal of each vertice (used for diffused lighting)   

//Out variable are going to be used on the fragment shader
out vec4 vColour;  
out vec2 TexCoord;   
out vec3 Normal;
out vec4 WorldPosition;

//Uniform variables are hadled equaly for all the vertices.
uniform mat4 model;                                                         
uniform mat4 projection;                                                         
uniform mat4 view;                                                         
                                                                            
void main()                                                                 
{                                     
    WorldPosition = model * vec4(pos, 1.0);

    gl_Position = projection * view * WorldPosition;     

    //Colour and texture are being set to be used on the fragment shader. There it can choose what to use (or combine them.)                              
    vColour = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);  
    TexCoord = tex; 

    //It is converted to a mat3 because we don't want the translation value (translation do not affect the normals. And the translation values are stored on the 4th column of the matrix).
    //The inverse and transpose are necessary to neutralize distortions caused by any non-uniform scaling on the object
    Normal = mat3(transpose(inverse(model))) * norm;                        
}                                                                           