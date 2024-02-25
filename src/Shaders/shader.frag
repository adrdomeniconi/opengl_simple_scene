# version 330                                                               
                                                                            
in vec4 vColour;          
in vec2 TexCoord;
in vec3 Normal;
in vec4 WorldPosition;

out vec4 colour;  

const int MAX_POINT_LIGHTS_COUNT = 3;
const int MAX_SPOT_LIGHTS_COUNT = 3;

struct Light
{
    vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight 
{
    Light light;
    vec3 direction;
};

struct PointLight 
{
    Light light;
    vec3 position;
    float constant;
    float linear;
    float exponent;
};

struct SpotLight 
{
    PointLight pointLight;
    vec3 direction;
    float coneAngle;
};

struct Material
{
    float specularIntensity;
    float shininess;
};

// This is set on the UseTexture method of the Texture class by: glActiveTexture(GL_TEXTURE0) and glBindTexture(GL_TEXTURE_2D, textureID);
uniform sampler2D input_texture;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS_COUNT];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS_COUNT];

uniform int pointLightsCount;
uniform int spotLightsCount;

uniform Material material;
uniform vec3 cameraPosition;

float mapValueInRange(float x, float in_min, float in_max, float out_min, float out_max) {
    return out_min + (x - in_min) * (out_max - out_min) / (in_max - in_min);
}

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

            specularColour = vec4(directionalLight.light.colour * material.specularIntensity * specularFactor, 1.0);
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

vec4 CalcDirectionalLight()
{
    return CalcLightByDirection(directionalLight.light, directionalLight.direction);    
}

vec4 CalcPointLight(PointLight pointLight)
{
    vec4 pointLightFactor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    vec3 direction = pointLight.position - WorldPosition.xyz;
    float distance = length(direction);
    direction = normalize(direction);

    pointLightFactor += CalcLightByDirection(pointLight.light, direction);
    float attenuation = pointLight.exponent * distance * distance + pointLight.linear * distance + pointLight.constant;

    return pointLightFactor/attenuation;
}

vec4 CalcSpotLight(SpotLight spotLight)
{
    vec4 spotLightFactor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    vec3 lightToFragment = normalize(WorldPosition.xyz - spotLight.pointLight.position);
    float directionFactor = dot(lightToFragment, normalize(spotLight.direction));

    if(directionFactor > spotLight.coneAngle)
    {
        spotLightFactor += CalcPointLight(spotLight.pointLight);
    }

    // if (directionFactor > spotLight.coneAngle) {
    //     spotLightFactor = vec4(1.0, 0.0, 0.0, 1.0); // Debug: Red for inside the cone
    // } else {
    //     spotLightFactor = vec4(0.0, 0.0, 1.0, 1.0); // Debug: Blue for outside the cone
    // }
    // return spotLightFactor;

    return spotLightFactor * mapValueInRange(directionFactor, spotLight.coneAngle, 1.0f, 0.0f, 1.0f);
}
                                                                            
void main()                                                                 
{                              
    vec4 lightColour = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    lightColour += CalcDirectionalLight();

    for(int i = 0; i < pointLightsCount; i++)
    {
        lightColour += CalcPointLight(pointLights[i]);
    }

    for(int i = 0; i < spotLightsCount; i++)
    {
        lightColour += CalcSpotLight(spotLights[i]);
    }

    colour = texture(input_texture, TexCoord) * lightColour;

    //DEBUG
    // colour = vec4(Normal, 1.0);

} 