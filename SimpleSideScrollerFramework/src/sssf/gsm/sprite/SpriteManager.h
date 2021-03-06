/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	SpriteManager.h

	This class manages all of the sprites in a given game level. Note
	that the player sprite is also managed by this class.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\gsm\ai\BotRecycler.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "Player.h"
#include "QuadTree.h"
#include <random>

static std::random_device rd2;
static std::mt19937 gen2(rd2());
static std::uniform_int_distribution<> dis(1, 3);
static std::uniform_real_distribution<> disf(0, 1);

class SpriteManager
{
private:
	// NOTE THAT MULTIPLE SPRITES MAY SHARE ARTWORK, SO SPRITE TYPES
	// SPECIFIES A TYPE OF SPRITE, OF WHICH THERE MAY BE MANY INSTANCES
	vector<AnimatedSpriteType*> spriteTypes;


	// THESE ARE THE BOTS IN THE GAME, LIKE ENEMIES, ROCKETS, OR ANYTHING
	// THAT MOVES AROUND AND IS NOT THE PLAYER
	list<Bot*> bots;
	list<Bot*> dyingBots;
	QuadTree botTree;

	// AND THIS IS THE PLAYER. AS-IS, WE ONLY ALLOW FOR ONE PLAYER AT A TIME
	Player player;

	// THE BotRecycler MAKES SURE WE DON'T HAVE TO CONSTRUCT BOTS WHENEVER
	// WE NEED TO SPAWN THEM, INSTEAD IT WILL RECYCLE THEM FOR US
	BotRecycler recyclableBots;
	int numBotsInViewport;

public:
	// NOTHING TO INIT OR DESTROY
	SpriteManager()		{}
	~SpriteManager()	{}

	// INLINED ACCESSOR METHODS
	int						getNumberOfSprites()	{ return bots.size();		}
	Player*			getPlayer()				{ return &player;			}
	list<Bot*>::iterator	getBotsIterator()		{ return bots.begin();		}
	list<Bot*>::iterator	getEndOfBotsIterator()	{ return bots.end();		}
	QuadTree*				getBotsTree()			{ return &botTree; }
	void					fillBotTree()			{ botTree.generateTree(bots); }
	int						getNumBotsInView()		{ return numBotsInViewport; }

	// METHODS DEFINED IN SpriteManager.cpp
	void				addBot(Bot *botToAdd);
	void				addSpriteItemsToRenderList(Game *game);
	unsigned int		addSpriteType(AnimatedSpriteType *spriteTypeToAdd);
	void				addSpriteToRenderList(AnimatedSprite *sprite, RenderList *renderList, Viewport *viewport);
	void				clearSprites();
	AnimatedSpriteType* getSpriteType(unsigned int typeIndex);
	Bot*				removeBot(Bot *botToRemove);
	void				unloadSprites();
	void				update(Game *game);
	void				removeBot();
	void				removeBotFromList(Bot* bot);
	void				checkCollision(Physics* physics, int playerIndex);
	void				killBot(Bot* bot);
	void				generateBots(Game* game);
	void				makeRandomJumpingBot(Game *game, AnimatedSpriteType *randomJumpingBotType, float initX, float initY);
};