#version 330 core

layout ( location = 0 ) in vec3 vPosition;
layout ( location = 1 ) in vec2 vMapping;
layout ( location = 2 ) in vec3 vNormals;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	TexCoord = vMapping;

	FragPos = vec3(model * vec4(vPosition, 1.0));
    Normal = mat3(transpose(inverse(model))) * vNormals;  
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
	
}