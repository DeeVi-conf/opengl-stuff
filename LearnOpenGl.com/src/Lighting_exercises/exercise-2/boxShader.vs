#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec3 Normal;
out vec3 FragPos;

void main(){
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    Normal = mat3(transpose(inverse(view * model))) * aNormal;  
    FragPos = vec3(view * model * vec4(aPos, 1.0));
}