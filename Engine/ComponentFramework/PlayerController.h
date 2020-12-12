#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "PhysicsObject.h"
#include "Pawn.h"


class PlayerController : public Pawn
{
public:
	PlayerController(MeshObject* meshBody);
	~PlayerController();

	void HandleEvents(const SDL_Event& event);
	void Update(float deltaTime);

private:



};


#endif // !PlayerController



