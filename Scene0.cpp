#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene0.h"
#include "Camera.h"
#include "DemoObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"

Scene0::Scene0(): camera(nullptr), demoObject(nullptr),meshPtr(nullptr),shaderPtr(nullptr),texturePtr(nullptr) {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() {}

bool Scene0::OnCreate() {
	camera = new Camera();
	lightSource = Vec3(-100.0f, 0.0f, -10.0f);
	lightSource2 = Vec3(100.0f, 0.0f, -10.0f);
	lightSources[0] = Vec3(-100.0f, 0.0f, -10.0f);
	lightSources[1] = Vec3(100.0f, 0.0f, -10.0f);
	lightSources[2] = Vec3(0.0f, 100.0f, -10.0f);
	colors[0] = Vec4(0.1f, 0.1f, 0.6f,0.0f);
	colors[1] = Vec4(0.6f, 0.1f, 0.1f,0.0f);
	colors[2] = Vec4(0.1f, 0.6f, 0.1f,0.0f);

	if (ObjLoader::loadOBJ("meshes/Cube.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("multiPhongVert.glsl", "multiPhongFrag.glsl");
	//shaderPtr = new Shader("textureVert.glsl", "textureFrag.glsl");
	texturePtr = new Texture();
	if (meshPtr == nullptr|| shaderPtr == nullptr || texturePtr == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}


	if (texturePtr->LoadImage("textures/mario_main.png") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}

	demoObject = new DemoObject(meshPtr, shaderPtr, texturePtr);
	if (demoObject == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	demoObject->setPos(Vec3(-5.0, 0.0, -20.0));
	demoObject->setModelMatrix(MMath::translate(demoObject->getPos()));
	
	return true;
}

void Scene0::HandleEvents(const SDL_Event &sdlEvent) {

}

void Scene0::Update(const float deltaTime) {
	demoObject->Update(deltaTime); 
	static float rotation = 0.0f;
	rotation += 0.5f;
	//demoObject->setVel(Vec3(1.0, 0.0, 0.0));
	//Physics::SimpleNewtonMotion(*demoObject, deltaTime);
	demoObject->setModelMatrix(MMath::rotate(rotation, Vec3(0.0f, 1.0f, 0.0f)) * MMath::scale(Vec3(4.0f,0.1f,4.0f)));
	
	
	//demoObject->setModelMatrix(MMath::translate(demoObject->getPos()));
	
}

void Scene0::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Draw your scene here
	GLuint program = demoObject->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(demoObject->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(demoObject->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos"), 1, lightSource);
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos2"), 1, lightSource2);
	glUniform3fv(demoObject->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(demoObject->getShader()->getUniformID("colors[0]"), 3, *colors);
	demoObject->Render();

	glUseProgram(0);
}


void Scene0::OnDestroy() {
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (demoObject) delete demoObject, demoObject = nullptr;
}
