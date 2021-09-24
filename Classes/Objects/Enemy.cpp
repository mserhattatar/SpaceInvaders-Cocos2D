#include "Enemy.h"

Enemy::Enemy(int tag) : Entity(tag) {}

bool Enemy::move(Vec2 origin) {
	// Enemy goes down
	float posY = this->getPositionY();
	this->setPositionY(posY - ENEMY_DELTA_MOVE);

	// Return true if enemy went out of the screen
	return this->getPositionY() < origin.y - this->getHeight();
}

void Enemy::reset() {
	// Reset enemy health
	if (getTag() == STRONG_ENEMY_TAG)
		setHealth(STRONG_ENEMY_HEALTH);
	else
		setHealth(WEAK_ENEMY_HEALTH);
}