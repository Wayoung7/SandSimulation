#version 330 core

out vec4 FragColor;

in vec4 instanceColor;

void main()
{
    FragColor = instanceColor;
}