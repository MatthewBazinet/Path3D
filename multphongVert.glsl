#version 410
layout (location = 0) in  vec4 vVertex;
layout (location = 1) in  vec4 vNormal;

out vec3 vertNormal;
out vec3 lightDir;
out vec3 lightDir2;
out vec3 eyeDir; 
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightPos;
uniform vec3 lightPos2;

void main() {
	vertNormal = normalize(normalMatrix * vNormal.xyz); /// Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex); /// This is the position of the vertex from the origin
	vec3 vertDir = normalize(vertPos);
	eyeDir = -vertDir;
	lightDir = normalize(lightPos - vertPos); /// Create the light direction. I do the math with in class 
	lightDir2 = normalize(lightPos2 - vertPos);
	
	gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vVertex; 
}
