#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene1.h"
#include "Camera.h"
#include "DemoObject.h"
#include "SpaceShip.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"

Scene1::Scene1() : camera(nullptr), enterprise(nullptr), meshPtr(nullptr), shaderPtr(nullptr), texturePtr(nullptr) {
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
}

Scene1::~Scene1() {}

bool Scene1::OnCreate() {
	camera = new Camera();
	lightSource = Vec3(-50.0f, 0.0f, -10.0f);
	lightSource2 = Vec3(50.0f, 0.0f, -10.0f);

	lightSources[0] = Vec3(-100.0f, 0.0f, -10.0f);
	lightSources[1] = Vec3(100.0f, 0.0f, -10.0f);
	lightSources[2] = Vec3(0.0f, 100.0f, -10.0f);
	colors[0] = Vec4(0.1f, 0.1f, 0.6f, 0.0f);
	colors[1] = Vec4(0.6f, 0.1f, 0.1f, 0.0f);
	colors[2] = Vec4(0.1f, 0.6f, 0.1f, 0.0f);
	float elapsedTime = 0.0f;

	if (ObjLoader::loadOBJ("meshes/F-16C.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("multiPhongVert.glsl", "multiPhongFrag.glsl");
	//shaderPtr = new Shader("textureVert.glsl", "textureFrag.glsl");
	texturePtr = new Texture();
	if (meshPtr == nullptr || shaderPtr == nullptr || texturePtr == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}


	if (texturePtr->LoadImage("textures/ebz.png") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}

	enterprise = new SpaceShip(meshPtr, shaderPtr, texturePtr);
	if (enterprise == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	enterprise->setPos(Vec3(0.0, 0.0, -10.0));
	enterprise->setModelMatrix(MMath::translate(enterprise->getPos()));
	enterprise->setRotationalInertia(26700000000.0f);
	enterprise->setMass(1000000.0f);

	return true;
}

void Scene1::HandleEvents(const SDL_Event& sdlEvent) {

}

void Scene1::Update(const float deltaTime) {
	
	if (elapsedTime < 31.0f) {
		
			enterprise->applyForce(MMath::rotate(enterprise->getAngle(), Vec3(0.0f, 0.0f, 1.0f)) * Vec3(50000000.0f, 0.0f, 0.0f));
	}
	else if (elapsedTime >= 31.0f && elapsedTime < 51.0f) {
		enterprise->ApplyTorque(629100000.0f);
		enterprise->applyForce(MMath::rotate(enterprise->getAngle(), Vec3(0.0f, 0.0f, 1.0f)) * Vec3(50000000.0f / 2.0f, 0.0f, 0.0f));
	}
	else if (elapsedTime >= 51.0f) {
		enterprise->applyForce(Vec3());
		enterprise->ApplyTorque(0.0f);
	}
	enterprise->Update(deltaTime);
	elapsedTime += deltaTime;
	camera->setViewMatrix(MMath::lookAt(Vec3(enterprise->getPos().x, enterprise->getPos().y, enterprise->getPos().z + 10.0f - (enterprise->getVel().x + enterprise->getVel().y)/1000), enterprise->getPos(), Vec3(0.0f, 1.0f, 0.0f)));
}

void Scene1::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Draw your scene here
	GLuint program = enterprise->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(enterprise->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(enterprise->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	//glUniform3fv(enterprise->getShader()->getUniformID("lightPos"), 1, lightSource);
	//glUniform3fv(enterprise->getShader()->getUniformID("lightPos2"), 1, lightSource2);
	glUniform3fv(enterprise->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(enterprise->getShader()->getUniformID("colors[0]"), 3, *colors);
	enterprise->Render();

	glUseProgram(0);
}


void Scene1::OnDestroy() {
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (enterprise) delete enterprise, enterprise = nullptr;
}
