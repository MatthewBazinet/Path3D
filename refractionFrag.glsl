#version 440

out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
in vec3 vertDir;

uniform samplerCube skyboxTexture;
uniform float indexOfRefraction;

void main()
{             
    float ratio = 1.00 / indexOfRefraction;
    vec3 I = normalize(vertDir);
    vec3 R = refract(I, normalize(Normal), ratio);
	FragColor = vec4(texture(skyboxTexture, R).rgb, 1.0);
}  