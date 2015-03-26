#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\physics\CollidableObject.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gui\Viewport.h"
#include "AnimatedSprite.h"

class Player : public AnimatedSprite {
private:
	int jumped;
	int health;
	int state;

public:
	Player();

	int					getJumped()				{ return jumped; }
	void				resetJumped()			{ jumped = 0; }
	void				incrementJumped()		{ jumped++; }
	int					getHealth()				{ return health; }
	void				incrementHealth(int incr) { health += incr; }
	int					getState()				{ return state;  }
	void					setState(int st)				{ state = st; }
	int checkWin(World* world);
};