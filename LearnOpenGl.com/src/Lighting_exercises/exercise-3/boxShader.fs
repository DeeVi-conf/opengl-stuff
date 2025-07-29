#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec3 Normal;
in vec3 FragPos; 

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

float specularStrength = 0.5;

void main(){
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  


    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(vec3(0.f) - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}