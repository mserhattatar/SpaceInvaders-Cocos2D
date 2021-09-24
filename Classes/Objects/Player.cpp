#include "Player.h"

Player::Player() : Entity(PLAYER_TAG) {}

void Player::move(float touchX) {
	// Player Y position will always be same
	this->setPositionY(_playerPosY);

	// Check touch position and set player X movement
	float currentX = this->getPositionX();
	float diff = touchX - currentX;
	// Player goes right
	if (diff >= PLAYER_DELTA_MOVE)
		this->setPositionX(currentX + PLAYER_DELTA_MOVE);
	// Player goes left
	else if (diff <= -PLAYER_DELTA_MOVE)
		this->setPositionX(currentX - PLAYER_DELTA_MOVE);
}