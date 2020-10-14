#version 440

out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
in vec3 vertDir;

uniform samplerCube skyboxTexture;
uniform float indexOfRefraction;

void main()
{             
    float RefractionRatio = 1.0 / indexOfRefraction;
    vec3 I = normalize(vertDir);
    vec3 Refract = refract(I, normalize(Normal), RefractionRatio);
	vec4 RefractFragColor = vec4(texture(skyboxTexture, Refract).rgb, 1.0);
    vec3 Reflect = reflect(I, normalize(Normal));
    vec4 ReflectFragColor = vec4(texture(skyboxTexture, Reflect).rgb, 1.0);
	float fresnel = dot(-I, Normal);
	//fresnel = pow(fresnel, 3.0);
	FragColor = mix(ReflectFragColor, RefractFragColor, fresnel);
}  