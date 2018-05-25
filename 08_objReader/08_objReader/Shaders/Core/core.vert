#version 330 core

layout ( location = 0 ) in vec3 vPosition;
layout ( location = 1 ) in vec2 vMapping;
layout ( location = 2 ) in vec3 vNormals;

out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(vPosition, 1.0);
	
	TexCoord = vec2( vNormals.x, 1.0 - vNormals.y );
}