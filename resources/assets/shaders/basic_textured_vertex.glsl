#version 410

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec2 i_TexCoord;

out vec2 v_TexCoord;

void main()
{
    v_TexCoord = i_TexCoord;
    gl_Position = vec4(i_Position, 1.0);
}
