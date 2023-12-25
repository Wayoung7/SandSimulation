#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 offset;
layout (location = 2) in vec4 color;

uniform mat4 projection;
out vec4 instanceColor;

void main()
{
    gl_Position = projection * vec4(aPos + offset, 0.0, 1.0);
    instanceColor = color;
}