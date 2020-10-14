#version 410
layout (location = 0) in  vec4 vVertex;
layout (location = 1) in  vec4 vNormal;
layout (location = 2) in  vec3 texCoords;


out vec3 vertNormal;
out vec3 lightDir;
out vec3 vertDir; 
out vec3 uvwCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightPos;
uniform float time;

void main() {
	float textureRepeat = 1.0;
	float mtime = mod(time / 10, 128);
	uvwCoords = vec3(texCoords.x + mtime/2, texCoords.y + mtime/2, mtime);
	
	vertNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex); /// Creates the vertex position (-eyeDir)
	lightDir = normalize(lightPos +  -vertPos); /// Create the light direction 
	vertDir = normalize(vertPos);
	
	gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vVertex; 
}
