#version 330 core

in vec2 TexCoord;
out vec4 color;

uniform sampler2D texture1;

float near = 0.1; 
float far  = 100.0; 

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
  
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{             
    float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
	
	vec4 texel = texture(texture1, TexCoord);
	
    color = vec4(vec3(depth), 1.0) * texel;
	
	//color = texture(texture1, v_Mapping);

	 // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    //vec3 result = (ambient + diffuse + specular) * objectColor;

	//vec4 texel = texture(texture1, TexCoord);
    
	//color = vec4(result, 1.0); //* texel

	//color = (ambient + diffuse + specular) * textel;
}