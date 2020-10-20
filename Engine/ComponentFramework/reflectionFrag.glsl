#version 440

out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
in vec3 vertDir;

uniform samplerCube skyboxTexture;

void main()
{             
    vec3 I = normalize(vertDir);
    vec3 R = reflect(I, normalize(Normal));
    FragColor = vec4(texture(skyboxTexture, R).rgb, 1.0);
}