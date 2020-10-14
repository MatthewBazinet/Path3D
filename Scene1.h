#ifndef Scene1_H
#define Scene1_H
#include "Scene.h"
#include "Vector.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Camera;
class DemoObject;
class Mesh;
class Shader;
class Texture;
class SpaceShip;

class Scene1 : public Scene {
private:
	Camera* camera;
	SpaceShip* enterprise;
	Vec3 lightSources[3];
	Vec4 colors[3];
	Vec3 lightSource;
	Vec3 lightSource2;
	Mesh* meshPtr;
	Shader* shaderPtr;
	Texture* texturePtr;
	float elapsedTime;
public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // Scene1_H