#ifndef SCENE2_H
#define SCENE2_H
#include "Scene.h"
#include "PlanetaryObject.h"
#include "PeopleDying.h"
#include "Camera.h"
#include "VMath.h"
union SDL_Event;
class Scene2 : public Scene {
private:
	Camera* camera;
	Skybox* skybox;
	Shader* skyboxShader;
	unsigned int lightNum = 3;
	PlanetaryObject* earth;
	PlanetaryObject* moon;
	PeopleDying* people;
	Vec3 lightSources[3];
	Vec4 colors[3];
	Vec3 lightSource;
	Vec3 lightSource2;
	Mesh* meshPtr;
	Mesh* meshPeoplePtr;
	Shader* shaderPtr;
	Texture* texturePtr;
	Texture* earthTxtr;
	Texture* moonTxtr;
	Texture* marsTxtr;
public:
	explicit Scene2();
	virtual ~Scene2();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
};


#endif // SCENE2_H