#ifndef SKYBOX_H
#define SKYBOX_H
#include "GameObject.h"
#include <glew.h>
#include "Shader.h"
#include "Mesh.h"
class Skybox : public GameObject
{
private:
	GLuint skyBoxTextureID;
	Shader* skyboxShader;
	Mesh* mesh;
	bool LoadTextures(const char* posX, const char* negX, const char* posY, const char* negY, const char* posZ, const char* negZ);
public:
	inline GLuint getTextureID() const { return skyBoxTextureID; }
	inline Shader* getShader() const { return skyboxShader; }
	Skybox();
	Skybox(Mesh* mesh_, Shader* shader_);
	~Skybox();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& event) override;

};
#endif