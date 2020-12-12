#ifndef OBJECT_H
#define OBJECT_H
#include <glew.h>
#include "Matrix.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "PhysicsObject.h"

using namespace MATH;


class MeshObject : public PhysicsObject, public GameObject {	

private:
	Matrix4 modelMatrix;
	GLuint modelMatrixID;
	GLuint normalMatrixID;
	Mesh *mesh;
	Shader *shader;
	Texture *texture;
	Vec3 scale;

public:
	MeshObject(Mesh *mesh_, Shader *shader_, Texture *texture_);
	~MeshObject();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event &event);


	inline Shader* getShader() const { return shader; }
	inline void setModelMatrix(const Matrix4 &modelMatrix_) { modelMatrix = modelMatrix_; }
	inline const Matrix4& getModelMatrix() { return modelMatrix; }
	inline const Vec3 getScale() { return scale; }
	inline void setScale(Vec3 scale_) { scale = scale_; }
};

#endif

