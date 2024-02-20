# version 330                                                               
                                                                            
in vec4 vColour;          
in vec2 TexCoord;
in vec3 Normal;
in vec4 WorldPosition;

out vec4 colour;  

struct Light
{
    vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight 
{
    Light base;
    vec3 direction;
};

struct Material
{
    float specularIntensity;
    float shininess;
};

// This is set on the UseTexture method of the Texture class by: glActiveTexture(GL_TEXTURE0) and glBindTexture(GL_TEXTURE_2D, textureID);
uniform sampler2D input_texture;

uniform DirectionalLight directionalLight;
uniform Material material;
uniform vec3 cameraPosition;

vec4 CalculateSpecularColour(float diffuseFactor)
{
    vec4 specularColour = vec4(0, 0, 0, 0);

    if(diffuseFactor > 0.0f)
    {
        vec3 fragmentPosition = WorldPosition.xyz;
        vec3 fragmentToCameraDirection = normalize(cameraPosition - fragmentPosition);
        vec3 reflectedVertexDirection = normalize(reflect(directionalLight.direction, normalize(Normal)));

        float specularFactor = dot(fragmentToCameraDirection, reflectedVertexDirection);
        if(specularFactor > 0.0f)
        {
            specularFactor = pow(specularFactor, material.shininess);

            specularColour = vec4(directionalLight.base.colour * material.specularIntensity * specularFactor, 1.0);
        }
    }
    return specularColour;
}

vec4 CalcLightByDirection(Light light, vec3 direction)
{
    //Calculate the diffuse light
    //A.B = |A||B|cos(angle) -> A.B = cos(angle) So diffuseFactor is the cos on the Angle [0,1]. If angle = 90, cos = 1. Angle = 0, cos = 0.
    // The max is to esure that we'll not have negative numbers.
    float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);

    vec4 ambientColour = vec4(light.colour, 1.0f) * light.ambientIntensity;
    vec4 diffuseColour = vec4(light.colour, 1.0f) * light.diffuseIntensity * diffuseFactor;
    vec4 specularColour = CalculateSpecularColour(diffuseFactor);
                                  
    return (ambientColour + diffuseColour + specularColour); 
}
                                                                            
void main()                                                                 
{                                                            
    colour = texture(input_texture, TexCoord) * CalcLightByDirection(directionalLight.base, directionalLight.direction);    

    //DEBUG
    // colour = vec4(Normal, 1.0);

} 