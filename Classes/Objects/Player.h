# pragma once 
#include <string>
#include "Entity.h"
#include "BulletManager.h"
#include "GameDefinitions.h"

class Player : public Entity {
private:
	float _playerPosY;
public:
	Player();

	void setPlayerPosY(float value) {
		_playerPosY = value;
	}
	void move(float touchX);
};