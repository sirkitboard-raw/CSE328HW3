#include "sssf\game\Game.h"
#include "sssf\gsm\physics\Collision.h"
#include "buggin_out\BugginOutCollisionListener.h"
#include "sssf/gsm/ai/Bot.h";
#include "sssf\gsm\state\GameStateManager.h"
#include <sssf/gsm/ai/bots/RandomJumpingBot.h>

void BugginOutCollisionListener::respondToCollision(Game *game, Collision *collision)
{
	// NOTE FROM THE COLLIDABLE OBJECTS, WHICH ARE IN THE COLLISION,
	// WE CAN CHECK AND SEE ON WHICH SIDE THE COLLISION HAPPENED AND
	// CHANGE SOME APPROPRIATE STATE ACCORDINGLY

	int i=0;
	if (!collision->isCollisionWithTile())
	{
		GameStateManager *gsm = game->getGSM();
		CollidableObject *sprite = collision->getCO1();
		CollidableObject *bot = collision->getCO2();
		Bot* colBot = dynamic_cast<Bot*>(bot);
		if (sprite->getCollisionEdge() == BOTTOM_EDGE)
		{
			if (sprite->getPhysicalProperties()->getVelocityY() > 0) {
				gsm->getSpriteManager()->removeBotFromList(colBot);
			}

			// ENEMY IS DEAD - WE SHOULD PLAY A DEATH ANIMATION
			// AND MARK IT FOR REMOVAL
		}
		else if (bot->getCollisionEdge() == BOTTOM_EDGE){
			if (colBot->getPhysicalProperties()->getVelocityY() > 0) {
				RandomJumpingBot* rjb = dynamic_cast<RandomJumpingBot*>(bot);
				Player* player = dynamic_cast<Player*>(sprite);
				player->incrementHealth(-1);
				rjb->pickRandomJump(gsm->getPhysics());
			}
		}
		
		else
		{
			// PLAYER IS DEAD - WE SHOULD PLAY A DEATH ANIMATION
			// AND MARK IT FOR REMOVAL/RESPAWN/RESTART GAME, WHATEVER
			// THE DEMANDS OF THE GAME ARE
		}
	}
}