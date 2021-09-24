# pragma once 
#include "cocos2d.h"
#include "IManagerBase.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GameDefinitions.h"

USING_NS_CC;
class BulletManager : public IManagerBase {
private:
	BulletManager();
	~BulletManager();
	static BulletManager* _instance;

	int _strongBulletCount;
	int _deadEnemyCount;
	bool _hasStrongBullet;
	float _bulletCreateTimer;

	ObjectPool<Bullet, STRONG_BULLET_TAG> _strongBulletPool;
	ObjectPool<Bullet, WEAK_BULLET_TAG> _weakBulletPool;
	std::list<Bullet*> _bulletList;

	void sendToPool(Bullet* bullet);

public:
	static BulletManager* instance();

	void update(float dt, Vec2 const playerPos);
	void createEntity(Vec2 pos);
	void onHit(Bullet* bullet, Enemy* enemy);
	void reset();
	void reloadBulletTimer();

	void setCreateStrongBullet(bool value) {
		_hasStrongBullet = value;
	}

	bool getHasStrongBullet() const {
		return _hasStrongBullet;
	}

	bool strongBulletController() {
		_strongBulletCount += 1;
		if (_strongBulletCount == 15) {
			_strongBulletCount = 0;
			return false;
		}
		return true;
	}
};