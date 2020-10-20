#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene2.h"
#include "Camera.h"
#include "DemoObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"

Scene2::Scene2() : camera(nullptr), earth(nullptr), moon(nullptr), meshPtr(nullptr), shaderPtr(nullptr), texturePtr(nullptr) {
	Debug::Info("Created Scene2: ", __FILE__, __LINE__);
}

Scene2::~Scene2() {}

bool Scene2::OnCreate() {
	camera = new Camera();
	lightSource = Vec3(-100.0f, 0.0f, -10.0f);
	//lightSource2 = Vec3(100.0f, 0.0f, -10.0f);
	//lightSources[0] = Vec3(-100.0f, 0.0f, -10.0f);
//	lightSources[1] = Vec3(100.0f, 0.0f, -10.0f);
	//lightSources[2] = Vec3(0.0f, 100.0f, -10.0f);
	//colors[0] = Vec4(0.1f, 0.1f, 0.6f, 0.0f);
	//colors[1] = Vec4(0.6f, 0.1f, 0.1f, 0.0f);
	//colors[2] = Vec4(0.1f, 0.6f, 0.1f, 0.0f);

	if (ObjLoader::loadOBJ("meshes/Sphere.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	meshPeoplePtr = new Mesh(GL_POINTS, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	glPointSize(2.5);
	//shaderPtr = new Shader("multiPhongVert.glsl", "multiPhongFrag.glsl");
	shaderPtr = new Shader("textureVert.glsl", "textureFrag.glsl");
	texturePtr = new Texture();
	earthTxtr = new Texture();
	moonTxtr = new Texture();
	marsTxtr = new Texture();
	if (meshPtr == nullptr || shaderPtr == nullptr || texturePtr == nullptr || earthTxtr == nullptr || moonTxtr == nullptr || marsTxtr == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}


	if (earthTxtr->LoadImage("textures/earthclouds.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}
	if (moonTxtr->LoadImage("textures/moon.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}
	if (marsTxtr->LoadImage("textures/mars.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}

	earth = new PlanetaryObject(meshPtr, shaderPtr, earthTxtr, moonTxtr, marsTxtr);
	if (earth == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	people = new PeopleDying(meshPeoplePtr, shaderPtr, moonTxtr);
	if (people == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	/*moon = new PlanetaryObject(meshPtr, shaderPtr, moonTxtr);
	if (moon == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}*/
	earth->setPos(Vec3(0.0f,0.0f,0.0f));
	earth->setAngularVelocity(540);
	earth->setScale(2.0f);
//	earth->setVel(Vec3(20.f,2.1f,1.0f));

	/*moon->setPos(Vec3(-50.0, 0.0, 0.0));
moon->setAngularVelocity(10);
	moon->setScale(0.5f);*/


	if (ObjLoader::loadOBJ("meshes/Cube.obj") == false) {
		return false;
	}

	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	//shaderPtr = new Shader("multiPhongVert.glsl", "multiPhongFrag.glsl");
	skyboxShader = new Shader("skyboxVert.glsl", "skyboxFrag.glsl");
	texturePtr = new Texture();
	skybox = new Skybox(meshPtr, skyboxShader);
	return true;
	camera->setSkyBox(skybox);
}

void Scene2::HandleEvents(const SDL_Event& sdlEvent) {

}

void Scene2::Update(const float deltaTime) {
	earth->Update(deltaTime);
	people->Update(deltaTime);
	//moon->MoonUpdate(deltaTime, earth->getPos());

	camera->setViewMatrix(MMath::lookAt(Vec3(earth->getPos().x, earth->getPos().y,earth->getPos().z + 10.0f), earth->getPos(), Vec3(0.0f, 1.0f, 0.0f)));


}

void Scene2::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->Render();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	/// Draw your scene here
	GLuint program = earth->getShader()->getProgram();
	glUseProgram(program);

	// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(earth->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(earth->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(earth->getShader()->getUniformID("lightPos"), 1, lightSource);
	earth->Render();
	people->Render();
	
	//moon->Render();
	
	glUseProgram(0);
}


void Scene2::OnDestroy() {
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (earth) delete earth, earth = nullptr;
	if (moon) delete moon, moon = nullptr;
}
