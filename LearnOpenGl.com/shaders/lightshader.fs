#version 330 core
out vec4 FragColor;
in vec3 ourColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    FragColor = vec4(1.0); // set all 4 vector values to 1.0
}