#include "Bullet.h"

Bullet::Bullet(int tag) : Entity(tag) {}

bool Bullet::move(Vec2 origin, cocos2d::Size visibleSize) {
	float posY = this->getPositionY();
	setPositionY(posY + BULLET_DELTA_MOVE);
	// Return true if rocket has gone out of screen to remove from parent
	return (posY > origin.y + visibleSize.height + this->getHeight());
}

void Bullet::reset() {
	if (getTag() == STRONG_BULLET_TAG)
		setBulletPower(STRONG_BULLET_POWER);
	else
		setBulletPower(WEAK_BULLET_POWER);
}