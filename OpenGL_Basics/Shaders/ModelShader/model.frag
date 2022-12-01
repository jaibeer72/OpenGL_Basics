#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

uniform vec3 viewPos;

void main()
{
    vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
    FragColor = texture(texture_diffuse1, TexCoords);
}
