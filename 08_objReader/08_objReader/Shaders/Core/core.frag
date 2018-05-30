#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D texture1;

void main()
{             
    //float depth = LinearizeDepth(gl_FragCoord.z) / 2; // divide by far for demonstration
    //color = vec4(vec3(depth), 1.0);
	//color = texture(texture1, TexCoord);
	color = texture(texture1, TexCoord);

}