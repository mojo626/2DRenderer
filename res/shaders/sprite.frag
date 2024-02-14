#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform bool isTexture;
uniform vec3 spriteColor;
uniform vec2 rectSize;

void main()
{    
    if (!isTexture)
    {
        color = vec4(spriteColor, 1.0);
    } else {
        color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
    }
    
}  