#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "PhysicsObject.h"
#include "Pawn.h"

class PlayerController : public Pawn
{
public:
	PlayerController(PhysicsObject* body);
	~PlayerController();


	void Update();

private:



};


#endif // !PlayerController



