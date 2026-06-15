#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec4 offset;

out VS_OUT
{
    vec3 color;
} vs_out;

void main()
{
    gl_Position = vec4(aPos, 1.0) + offset;
    vs_out.color = aColor;
}