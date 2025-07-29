#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec3 ourColor;
out vec3 Normal;
out vec3 FragPos;

float specularStrength = 0.5;

void main(){
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
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
    Normal = mat3(transpose(inverse(view * model))) * aNormal;  
    FragPos = vec3(view * model * vec4(aPos, 1.0));
}