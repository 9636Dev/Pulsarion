#version 410

layout (location = 0) in vec2 i_Position;
layout (location = 1) in vec2 i_TexCoord;

out vec2 v_TexCoord;
out vec2 v_Position;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
    v_TexCoord = i_TexCoord;
    v_Position = i_Position;
    gl_Position = u_ViewMatrix * u_ModelMatrix * u_ProjectionMatrix * vec4(i_Position, 1.0, 1.0);
}
