#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene3.h"
#include "Camera.h"
#include "DemoObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"

Scene3::Scene3() : camera(nullptr), meshPtr(nullptr), shaderPtr(nullptr), texturePtr(nullptr) {
	Debug::Info("Created Scene3: ", __FILE__, __LINE__);
}

Scene3::~Scene3() {}

bool Scene3::OnCreate() {
	tb = new Trackball();
	camera = new Camera();
	lightSource = Vec3(0.0f, 0.0f, -10.0f);

	if (ObjLoader::loadOBJ("meshes/Mario.obj") == false) {
		return false;
	}

	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	//shaderPtr = new Shader("phongVert.glsl", "phongFrag.glsl");
	shaderPtr = new Shader("textureVert.glsl", "textureFrag.glsl");
	texturePtr = new Texture();
	skybox = new Skybox();
	skybox->OnCreate();
	if (meshPtr == nullptr || shaderPtr == nullptr || texturePtr == nullptr || skybox == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}
	camera->setSkyBox(skybox);
	if (texturePtr->LoadImage("textures/mario_main.png") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}
	demoObject = new DemoObject(meshPtr, shaderPtr, texturePtr);
	if (demoObject == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	
	return true;
}

void Scene3::HandleEvents(const SDL_Event& sdlEvent) {
	tb->HandleEvents(sdlEvent);
}

void Scene3::Update(const float deltaTime) {

	camera->setRotationMatix( tb->getMatrix4());
	camera->Update(deltaTime);
	demoObject->Update(deltaTime);
}

void Scene3::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Draw your scene here
	camera->Render();
	GLuint program = shaderPtr->getProgram();
	glUseProgram(program);

	Matrix4 twiceRotate = tb->getMatrix4();
	twiceRotate*=twiceRotate*twiceRotate*twiceRotate*twiceRotate*twiceRotate;
	// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(shaderPtr->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(shaderPtr->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(shaderPtr->getUniformID("lightPos"), 1, lightSource);
	demoObject->setModelMatrix(twiceRotate * MMath::rotate(180,Vec3(0.0f,1.0f,0.0f)));
	demoObject->Render();

	glUseProgram(0);


}


void Scene3::OnDestroy() {
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (skybox) delete skybox, skybox = nullptr;
	if (demoObject) delete demoObject, demoObject = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
}
