#version 410

layout (location = 0) in vec2 i_Position;
layout (location = 1) in vec2 i_TexCoord;

out vec2 v_TexCoord;

uniform mat3 u_ModelMatrix;

void main()
{
    v_TexCoord = i_TexCoord;
    //gl_Position = vec4(u_ModelMatrix * i_Position, 1.0);
    gl_Position = vec4(u_ModelMatrix * vec3(i_Position, 1.0), 1.0);
}
