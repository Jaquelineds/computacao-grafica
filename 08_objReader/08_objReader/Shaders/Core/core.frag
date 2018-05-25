#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D texture1;

//void main(){

	//vec4 tex1 = texture( texture1, TexCoord );
	//color = tex1;

	//color = vec4(0.8f, 0.8f, 1.0f, 1.0f);

void main()
{             
    //float depth = LinearizeDepth(gl_FragCoord.z) / 2; // divide by far for demonstration
    //color = vec4(vec3(depth), 1.0);
	//color = texture(texture1, TexCoord);
	vec4 tex1 = texture( texture1, TexCoord );
	color = tex1;
}