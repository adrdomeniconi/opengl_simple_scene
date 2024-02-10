# version 330                                                               
                                                                            
in vec4 vColour;          
in vec2 TexCoord;
in vec3 Normal;

out vec4 colour;  

struct DirectionalLight 
{
    vec3 colour;
    float ambientIntensity;
    vec3 direction;
    float diffuseIntensity;
};

// This is set on the UseTexture method of the Texture class by: glActiveTexture(GL_TEXTURE0) and glBindTexture(GL_TEXTURE_2D, textureID);
uniform sampler2D input_texture;

uniform DirectionalLight directionalLight;
                                                                            
void main()                                                                 
{                                           
    //Calculate the diffuse light
    //A.B = |A||B|cos(angle) -> A.B = cos(angle) So diffuseFactor is the cos on the Angle [0,1]. If angle = 90, cos = 1. Angle = 0, cos = 0.
    // The max is to esure that we'll not have negative numbers.
    float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);

    vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;
    vec4 diffuseColour = vec4(directionalLight.colour, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;

    //colour = vec4(vColour); // Use just colour.            
    //colour = texture(input_texture, TexCoord);                
    //colour = texture(input_texture, TexCoord) * vColour;  //Combining the effect from the texture and the colour                                          
    colour = texture(input_texture, TexCoord) * (ambientColour + diffuseColour);    
} 