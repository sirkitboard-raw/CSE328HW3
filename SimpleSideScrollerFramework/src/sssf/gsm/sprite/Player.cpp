#include "sssf_VS\stdafx.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include <sssf/gsm/world/World.h>
#include "Player.h"
#include "sssf/gsm/ai/Bot.h"

Player::Player() {
	jumped = 0;
	health = 10;
	frameCount = 0;
	visible = true;
	lives = 3;
	dead = false;
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

void Player::checkVisible() {
	if (health >= 10) {
		visible = true;
		frameCount = 0;
	}
	else {
		if (frameCount < 5) {
			visible = false;
		}
		else {
			visible = true;
		}
		frameCount++;
		frameCount %= ((health * 2) + 10);
	}
}

void Player::checkDead() {
	if (health == 0) {
		health = 10;
		lives--;
		diedLast = true;
	}
	if (lives<0) {
		dead = true;
	}
}

bool Player::diedLastTurn() {
	if (diedLast == false) {
		return false;
	}
	else {
		diedLast = false;
		return true;
	}
}


void Player::incrementHealth(int incr) {
	if (health + incr > 15) {
		health = 15;
	}
	else {
		health += incr;
	}
}
