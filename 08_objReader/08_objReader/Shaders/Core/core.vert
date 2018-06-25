#version 330 core

layout ( location = 0 ) in vec3 vPosition;
layout ( location = 1 ) in vec2 vMapping;
layout ( location = 2 ) in vec3 vNormals;
//layout ( location = 3 ) in vec3 vKa;
//layout ( location = 4 ) in vec3 vKd;
//layout ( location = 5 ) in vec3 vKs;
//layout ( location = 6 ) in float vNs;

out vec2 Mapping; 
out vec3 Position; 
out vec3 Normal;
//out vec3 Ka;
//out vec3 Kd;
//out vec3 Ks;
//out float Ns;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	Position = vPosition;
	Mapping = vMapping;
	Normal = vNormals;
	//Ka = vKa;
	//Kd = vKd;
	//Ks = vKs;
	//Ns = vNs;
	
	Position = vec3(view * model * vec4(vPosition, 1.0));
	Normal = mat3(transpose(inverse(model))) * vNormals;
	gl_Position = projection * vec4(Position, 1.0);	
}