#version 450 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D in_texture;

void main()
{
    FragColor = texture(in_texture, TexCoord);
}