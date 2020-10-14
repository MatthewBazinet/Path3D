#ifndef Scene3_H
#define Scene3_H
#include "Scene.h"
#include "PlanetaryObject.h"
#include "PeopleDying.h"
#include "Camera.h"
#include "VMath.h"
#include "Skybox.h"
#include "Trackball.h"
union SDL_Event;
class Scene3 : public Scene {
private:
	Camera* camera;
	unsigned int lightNum = 3;
	Vec3 lightSource;
	Mesh* meshPtr;
	Shader* shaderPtr;
	Shader* skyboxShader;
	Texture* texturePtr;
	Skybox* skybox;
	DemoObject* demoObject;
	Trackball* tb;

public:
	explicit Scene3();
	virtual ~Scene3();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
};


#endif // Scene3_H