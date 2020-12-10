#include <glew.h>
#include <iostream>
#include "Debug.h"
#include "Scene0.h"
#include "Camera.h"
#include "MeshObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "Physics.h"

Scene0::Scene0(): camera(nullptr), demoObject(nullptr), wallOne(nullptr), wallTwo(nullptr), wallThree(nullptr), wallFour(nullptr), wallFive(nullptr), wallSix(nullptr), wallSeven(nullptr), meshPtr(nullptr),shaderPtr(nullptr),texturePtr(nullptr) {
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

	//Sets plane
	demoObject = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (demoObject == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	demoObject->setPos(Vec3(-5.0, 0.0, -20.0));
	demoObject->setModelMatrix(MMath::translate(demoObject->getPos()));

	//Sets first wall location and size
	wallOne = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallOne == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallOne->setPos(Vec3(0.0, 1.0, -1.0));
	wallOne->setModelMatrix(MMath::translate(wallOne->getPos()) * MMath::scale(Vec3(4.0f, 0.5f, 0.2f)));
	
	//Sets second wall location and size
	wallTwo = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallTwo == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallTwo->setPos(Vec3(0.0, 1.0, 0.6));
	wallTwo->setModelMatrix(MMath::translate(wallTwo->getPos()) * MMath::scale(Vec3(3.0f, 0.5f, 0.2f)));


	//Sets third wall location and size
	wallThree = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallThree == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallThree->setPos(Vec3(0.0, 1.0, 2.0));
	wallThree->setModelMatrix(MMath::translate(wallThree->getPos()) * MMath::scale(Vec3(3.0f, 0.5f, 0.2f)));

	//Sets fourth wall location and size
	wallFour = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallFour == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallFour->setPos(Vec3(0.0, 1.0, 3.4));
	wallFour->setModelMatrix(MMath::translate(wallFour->getPos()) * MMath::scale(Vec3(3.0f, 0.5f, 0.2f)));

	//Sets fifth wall location and size
	wallFive = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallFive == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallFive->setPos(Vec3(0.0, 1.0, 5.0));
	wallFive->setModelMatrix(MMath::translate(wallFive->getPos()) * MMath::scale(Vec3(4.0f, 0.5f, 0.2f)));

	//Sets sixth wall location and size
	wallSix = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallSix == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallSix->setPos(Vec3(-3.8, 1.0, 1.5));
	wallSix->setModelMatrix(MMath::translate(wallSix->getPos()) * MMath::scale(Vec3(0.2f, 0.5f, 4.0f)));

	//Sets seventh wall location and size
	wallSeven = new MeshObject(meshPtr, shaderPtr, texturePtr);
	if (wallSeven == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	wallSeven->setPos(Vec3(3.8, 1.0, 1.5));
	wallSeven->setModelMatrix(MMath::translate(wallSeven->getPos()) * MMath::scale(Vec3(0.2f, 0.5f, 4.0f)));

	return true;
}

void Scene0::HandleEvents(const SDL_Event &sdlEvent) {

}

void Scene0::Update(const float deltaTime) {
	demoObject->Update(deltaTime); 
	static float rotation = 0.0f;
	rotation += 0.0f;
	//demoObject->setVel(Vec3(1.0, 0.0, 0.0));
	//Physics::SimpleNewtonMotion(*demoObject, deltaTime);
	demoObject->setModelMatrix(MMath::rotate(rotation, Vec3(0.0f, 1.0f, 0.0f)) * MMath::scale(Vec3(4.0f,0.1f,4.0f)));
	
	
	//demoObject->setModelMatrix(MMath::translate(demoObject->getPos()));
	//camera->setViewMatrix(MMath::lookAt(Vec3(demoObject->getPos().x, demoObject->getPos().y, demoObject->getPos().z + 10.0f - (demoObject->getVel().x + demoObject->getVel().y) / 1000), demoObject->getPos(), Vec3(0.0f, 1.0f, 0.0f)));

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

	//wall one
	program = wallOne->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallOne->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallOne->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos"), 1, lightSource);
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos2"), 1, lightSource2);
	glUniform3fv(wallOne->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallOne->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallOne->Render();

	//wall two
	program = wallTwo->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallTwo->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallTwo->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos"), 1, lightSource);
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos2"), 1, lightSource2);
	glUniform3fv(wallTwo->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallTwo->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallTwo->Render();

	//wall three
	program = wallThree->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallThree->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallThree->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos"), 1, lightSource);
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos2"), 1, lightSource2);
	glUniform3fv(wallThree->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallThree->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallThree->Render();

	//wall four
	program = wallFour->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallFour->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallFour->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos"), 1, lightSource);
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos2"), 1, lightSource2);
	glUniform3fv(wallFour->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallFour->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallFour->Render();

	//wall five
	program = wallFive->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallFive->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallFive->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos"), 1, lightSource);
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos2"), 1, lightSource2);
	glUniform3fv(wallFive->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallFive->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallFive->Render();

	//wall six
	program = wallSix->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallSix->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallSix->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos"), 1, lightSource);
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos2"), 1, lightSource2);
	glUniform3fv(wallSix->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallSix->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallSix->Render();

	//wall seven
	program = wallSeven->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(wallSeven->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(wallSeven->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos"), 1, lightSource);
	//glUniform3fv(demoObject->getShader()->getUniformID("lightPos2"), 1, lightSource2);
	glUniform3fv(wallSeven->getShader()->getUniformID("lightPos[0]"), 3, *lightSources);
	glUniform4fv(wallSeven->getShader()->getUniformID("colors[0]"), 3, *colors);
	wallSeven->Render();

	glUseProgram(0);
}


void Scene0::OnDestroy() {
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	if (texturePtr) delete texturePtr, texturePtr = nullptr;
	if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if (demoObject) delete demoObject, demoObject = nullptr;
}
