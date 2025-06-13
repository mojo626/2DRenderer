#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 squareVertices;
layout(location = 1) in vec4 xyzs; // Position of the center of the particle and size of the square
layout(location = 2) in vec4 color; // Position of the center of the particle and size of the square

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec4 particlecolor;

uniform mat4 projection; // Model-View-Projection matrix, but without the Model (the position is in BillboardPos; the orientation depends on the camera)

void main()
{
	float particleSize = xyzs.w; // because we encoded it this way.
	vec3 particleCenter_wordspace = xyzs.xyz;


	// Output position of the vertex
	gl_Position = projection * vec4(squareVertices*particleSize + particleCenter_wordspace, 1.0f);
	

	// UV of the vertex. No special space for this one.
	UV = squareVertices.xy + vec2(0.5, 0.5);
	//gl_Position = vec4(UV, 0.0, 1.0);
	particlecolor = color;
}
