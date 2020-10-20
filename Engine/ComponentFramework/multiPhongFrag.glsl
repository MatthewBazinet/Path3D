#version 410
in  vec3 vertNormal;
in  vec3 lightDir[3];
in  vec3 eyeDir;
out vec4 fragColor;
uniform vec4 colors[3];

void main() { 
	float diff[3];
	float spec[3];
	vec3 reflection[3];
	const vec4 ks = vec4(0.3, 0.3, 0.3, 0.0);


	const vec4 ka = vec4(0.02,0.02,0.02,0.0);
	fragColor =  ka;
	

	for(int i = 0; i < 3; i++){
		diff[i] = max(dot(vertNormal, lightDir[i]), 0.0);
		/// Reflection is based incedent which means a vector from the light source
		/// not the direction to the light source
		reflection[i] = normalize(reflect(-lightDir[i], vertNormal));
		spec[i] = max(dot(eyeDir, reflection[i]), 0.0);
		if(diff[i] > 0.0){
			spec[i] = pow(spec[i],14.0);
		}
		 fragColor += (diff[i] * colors[i]) + (spec[i] * ks);
	}
		

} 

