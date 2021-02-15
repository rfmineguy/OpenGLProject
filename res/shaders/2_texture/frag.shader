#version 450 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D tex1, tex2;

void main()
{
    FragColor = mix(texture(tex1, TexCoord), texture(tex2, TexCoord), 0.2);
}