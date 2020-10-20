#version 410
in vec3 vertNormal;
in vec3 lightDir;
in vec3 vertDir;
in vec3 uvwCoords;
out vec4 fragColor;

uniform sampler3D myTexture; 

void main() { 

	float spec = 0.0;
	const vec4 specLightColor = vec4(0.2, 0.2, 0.2, 0.0);
	float diff = max(dot(vertNormal, lightDir), 0.0);
	diff = 1.0;
	vec4 textureColor = texture(myTexture, uvwCoords);

	if(diff > 0.0){
		vec3 reflection = normalize(reflect(lightDir, vertNormal));
		spec = max(dot(vertDir, reflection), 0.0);
		spec = pow(spec,12.0);
	}
	vec4 ka = vec4(0.3,0.09,0.0,0.0);
	ka = textureColor * 0.1;
	fragColor = ka + (diff * textureColor)  + (spec * specLightColor);	
} 

