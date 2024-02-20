#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform bool isTexture;
uniform vec3 spriteColor;

float dis = 0.015;

void main()
{    
    if (!isTexture)
    {
        //This gives the shape a black outline when the UV coords are close to the edges (0 and 1)
        if (TexCoords.x < dis || TexCoords.x > 1-dis || TexCoords.y < dis || TexCoords.y > 1-dis)
        {
            color = vec4(0.0, 0.0, 0.0, 1.0);
        } else {
            color = vec4(spriteColor, 1.0);
        }   
        
    } else {
        //This uses the texture if there is one
        color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
    }
    
}  