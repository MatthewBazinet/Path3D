
#ifndef PeopleDying_H
#define PeopleDying_H
#include <glew.h>
#include "Matrix.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "PhysicsObject.h"
#include "Physics.h"
	class PeopleDying : public PhysicsObject, public GameObject {

	private:
		Matrix4 modelMatrix;
		GLuint modelMatrixID;
		GLuint normalMatrixID;
		Mesh* mesh;
		Shader* shader;
		Texture* texture;
		float scale;

	public:
		PeopleDying(Mesh* mesh_, Shader* shader_, Texture* texture_);
		~PeopleDying();
		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime_);
		virtual void Render() const;
		virtual void HandleEvents(const SDL_Event& event);
		inline float getAngle() { return PhysicsObject::getAngle(); }
		inline void applyForce(Vec3 force) { PhysicsObject::applyForce(force); }
		inline void ApplyTorque(float torque) { PhysicsObject::ApplyTorque(torque); }

		inline void setScale(const float scale_) { if (scale_ > VERY_SMALL) scale = scale_; }


		inline Shader* getShader() const { return shader; }
		inline void setModelMatrix(const Matrix4& modelMatrix_) { modelMatrix = modelMatrix_; }
		inline const Matrix4& getModelMatrix() { return modelMatrix; }
	};

#endif
