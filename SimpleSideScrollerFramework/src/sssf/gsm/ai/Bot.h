#pragma once

#include "sssf_VS\stdafx.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"

class Bot : public AnimatedSprite
{
	int dying;
public:
	Bot() {
		dying = 0;
	}
	~Bot()	{}

	int getDying() {
		return dying;
	}

	int kill() {
		if (dying == 0) {
			getPhysicalProperties()->setCollidable(false);
			setCurrentState(L"DEAD");
		}
		dying++;
		return dying;
	}

	// TO BE DEFINED BY BOT AI CLASSES
	virtual void think(Game *game)=0;
	virtual Bot* clone()=0;
};