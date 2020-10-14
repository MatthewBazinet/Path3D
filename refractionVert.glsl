#version 440

layout (location = 0) in vec4 vVertex;
layout (location = 1) in vec4 vNormal;

out vec3 Normal;
out vec3 Position;
out vec3 vertDir;

uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	Normal = normalize(normalMatrix * vNormal.xyz); /// Rotate the normal to the correct orientation 
	Position = vec3(viewMatrix * modelMatrix * vVertex); /// This is the position of the vertex from the origin
	vertDir = normalize(Position);
    //gl_Position = projection * view * model * vec4(pos, 1.0);
	gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vVertex;
}  