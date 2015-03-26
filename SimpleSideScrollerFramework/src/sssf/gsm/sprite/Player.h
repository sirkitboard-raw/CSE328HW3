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
	int lives=3;
	int frameCount;
	bool visible;

public:
	Player();

	int					getJumped()				{ return jumped; }
	void				resetJumped()			{ jumped = 0; }
	void				incrementJumped()		{ jumped++; }
	int					getHealth()				{ return health; }
	void				incrementHealth(int incr) { health += incr; }
	int					getFrameCount()			{ return frameCount;  }
	void				setFrameCount(int st)	{ frameCount = st; }
	bool				isVisible()				{ return visible; }
	int					getLives()				{ return lives; }
	void				setLives(int liv)		{ lives = liv; }

	int checkWin(World* world);
	void checkVisible();
};