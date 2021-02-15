#version 450 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 ourColor;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
    //FragColor = vec4(0.3, 0.2, 0.7, 1.0);
}