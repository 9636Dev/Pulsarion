#version 410

in vec2 v_TexCoord;

out vec4 o_FragColor;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    o_FragColor = u_Color * texture(u_Texture, v_TexCoord);
}
