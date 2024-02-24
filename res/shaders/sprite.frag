#version 330 core
in vec2 TexCoords;
in vec4 WorldCoords;
out vec4 color;

uniform sampler2D image;
uniform bool isTexture;
uniform vec3 spriteColor;
//x, y, z: tile coord x, tile coord y, tileset dimension in tiles
uniform vec3 tileData;
uniform vec3 offset;

//Lighting
uniform vec2 lightPos[100];
uniform float lightIntensity[100];
uniform int numLights;

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
        color = vec4(spriteColor, 1.0) * texture(image, (TexCoords + vec2(tileData.x, tileData.y))/tileData.z);
    }


    // vec3 worldPos = offset + WorldCoords.xyz;
    // float lightLevel = 0.5;
    // for (int i = 0; i < 100; i++)
    // {
    //     if (lightPos[i].x == 0 && lightPos[i].y == 0)
    //     {
    //         continue;
    //     }
    //     float disFromLight = distance(lightPos[i].xy, worldPos.xy);
    //     lightLevel += clamp(10-disFromLight, 0, 10)/10;
    // }

    

    


    

    

    //color *= clamp(lightLevel, 0, 1);
    
}  