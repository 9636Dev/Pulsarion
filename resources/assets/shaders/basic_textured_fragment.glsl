#version 410

in vec2 v_TexCoord;

out vec4 o_FragColor;

uniform vec4 u_DiffuseColor;
uniform sampler2D u_Texture;

void main()
{
    o_FragColor = u_DiffuseColor * texture(u_Texture, v_TexCoord);
}
