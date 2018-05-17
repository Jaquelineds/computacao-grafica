#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textCoord;

out vec3 ourColor;
out vec2 TextCoord;

uniform mat4 transform;

void main() {
	gl_Position = transform * vec4 (position, 1.0f);
	ourColor = color;

	TextCoord = vec2(textCoord.x, 1.0 - textCoord.y);
}