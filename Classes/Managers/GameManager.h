# pragma once

#include "cocos2d.h"
#include "IManagerBase.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "GameDefinitions.h"

class EnemyManager;
class PlayerManager;
class BulletManager;

class GameManager : public IManagerBase {
private:
	static GameManager* _instance;

public:
	static GameManager* instance();

	EnemyManager* _enemyManager;
	PlayerManager* _playerManager;
	BulletManager* _bulletManager;

	void setManagers();
	void update(float dt, float _touchPosX);
	void onHit(Enemy* enemy, Bullet* bullet);
	void onHit();
	void reset();
	void switchScene(int nScene);
	void quitGame();
};