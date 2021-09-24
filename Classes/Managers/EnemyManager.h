# pragma once

#include "cocos2d.h"
#include "IManagerBase.h"
#include "ObjectPool.h"
#include "GameScene.h"
#include "BulletManager.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GameDefinitions.h"

class EnemyManager : public IManagerBase {
private:
	EnemyManager();
	~EnemyManager();
	static EnemyManager* _instance;

	int _deadEnemyScore;
	float _enemyCreateTimer;

	ObjectPool<Enemy, STRONG_ENEMY_TAG> _strongEnemyPool;
	ObjectPool<Enemy, WEAK_ENEMY_TAG> _weakEnemyPool;
	std::list<Enemy*> _enemyList;

	void sendToPool(Enemy* enemyEntity);
	void resetEnemyTimer();
	void createEntity();
	void updateEnemyScore(int enemyTag);

public:
	static EnemyManager* instance();

	void update(float dt);
	void onHit(Enemy* enemy, int bulletPower);
	void reset();

	int getDeadEnemyScore() const {
		return _deadEnemyScore;
	}
};