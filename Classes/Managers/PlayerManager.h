# pragma once
#include "cocos2d.h"
#include "IManagerBase.h"
#include "GameScene.h"
#include "GameManager.h"
#include "BulletManager.h"
#include "Player.h"
#include "GameDefinitions.h"

class PlayerManager : public IManagerBase {
private:
	static PlayerManager* _instance;

public:
	static PlayerManager* instance();
	Player* _player;

	void update(float dt, float touchX);
	void onHit();
	void createEntity();
	
	Vec2 getPlayerPos() const {
		return _player->getPosition();
	}
};