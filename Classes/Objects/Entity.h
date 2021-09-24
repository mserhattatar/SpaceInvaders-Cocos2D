# pragma once 

#include "cocos2d.h"
#include "GameDefinitions.h"

class Entity : public cocos2d::Sprite {
private:
	int _health;
	float height;
	int _bulletPower;
	int _position;

public:
	Entity(int tag);

	void move();

	float getHeight() const {
		return height;
	}

	int getHealth() const {
		return _health;
	}

	void setHealth(int value) {
		_health = value;
	}

	void decreaseHealth(int value) {
		_health -= value;
	}

	int getBulletPower() const {
		return _bulletPower;
	}

	void  setBulletPower(int value) {
		_bulletPower = value;
	}

	void decreaseBulletPower(int value) {
		_bulletPower -= value;
	}
};