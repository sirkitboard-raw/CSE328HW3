#include "sssf_VS\stdafx.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include <sssf/gsm/world/World.h>
#include "Player.h"

Player::Player() {
	jumped = 0;
	health = 10;
}


int Player::checkWin(World* world) {
	float width = world->getWorldWidth();
	float height = world->getWorldHeight();
	float playerX = getBoundingVolume()->getLeft();
	float playerY = getBoundingVolume()->getTop();
	float playerWidth = getBoundingVolume()->getWidth();
	float playerHeight = getBoundingVolume()->getHeight();

	if (playerX + playerWidth < 0) {
		return 1;
	}
	if (playerX > width) {
		return 1;
	}
	if (playerY > height) {
		return 1;
	}
	if (playerY + playerHeight < 0) {
		return 1;
	}
	return 0;
}