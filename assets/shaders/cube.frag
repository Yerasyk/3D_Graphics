#version 330 core

out vec4 FragColor;

//Variables for colors and light
uniform vec3 objectColor;

uniform vec3 lightColor1;
uniform vec3 lightPos1;

uniform vec3 lightColor2;
uniform vec3 lightPos2;

uniform vec3 viewPos;
in vec3 fragPos;
in vec3 normal;

//textures
in vec2 texCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float proportion=0.0;

vec3 CalcLight(vec3 lightPos, vec3 lightColor)
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);

    // ambient
	float abmientStrength = 0.1;
    vec3 ambient = abmientStrength * lightColor;

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
	float specularStrength= 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;

    return ambient + diffuse + specular;
}

void main()
{	
    //Lights
    vec3 lightResult1 = CalcLight(lightPos1, lightColor1);
    vec3 lightResult2 = CalcLight(lightPos2, lightColor2);

	//Textures
	vec4 texColor  = mix(texture(texture1, texCoord), texture(texture2, texCoord), proportion); // Now its empty
	
	//Phong Light Result
    vec3 result = (lightResult1 + lightResult2) * texColor.xyz;

	FragColor = vec4(result, 1.0);
};