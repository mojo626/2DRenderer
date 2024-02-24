#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;
out vec4 WorldCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = vertex.zw;
    WorldCoords = vec4(vertex.xy, 0.0, 1.0) * model;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}