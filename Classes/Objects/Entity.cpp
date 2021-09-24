#include "Entity.h"

USING_NS_CC;
Entity::Entity(int tag) {
	// set entity body
	float width;
	char* image;

	switch (tag) {
	case WEAK_ENEMY_TAG:
		setHealth(WEAK_ENEMY_HEALTH);
		image = WEAK_ENEMY_IMAGE;
		width = ENEMY_WIDTH;
		height = ENEMY_HEIGHT;
		break;

	case STRONG_ENEMY_TAG:
		setHealth(STRONG_ENEMY_HEALTH);
		image = STRONG_ENEMY_IMAGE;
		width = ENEMY_WIDTH;
		height = ENEMY_HEIGHT;
		break;

	case WEAK_BULLET_TAG:
		setBulletPower(WEAK_BULLET_POWER);
		image = WEAK_BULLET_IMAGE;
		width = BULLET_WIDTH;
		height = BULLET_WIDTH;
		break;

	case STRONG_BULLET_TAG:
		setBulletPower(STRONG_BULLET_POWER);
		image = STRONG_BULLET_IMAGE;
		width = STRONG_BULLET_WIDTH;
		height = STRONG_BULLET_WIDTH;
		break;

	case PLAYER_TAG:
		setHealth(PLAYER_HEALTH);
		image = PLAYER_IMAGE;
		width = PLAYER_WIDTH;
		height = PLAYER_WIDTH;
		break;
	default:
		printf("Entity tag is not defined.");
		return;
	}

	this->setTag(tag);

	if (!Sprite::initWithFile(image)) {
		log("Entity image is not defined.");
		return;
	}
	setContentSize(cocos2d::Size(width, height));

	// set physics body to simulate collision
	PhysicsBody* rectBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	rectBody->setContactTestBitmask(true);
	this->setPhysicsBody(rectBody);
}