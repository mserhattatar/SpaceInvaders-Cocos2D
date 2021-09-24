#include "BulletManager.h"

BulletManager* BulletManager::_instance = nullptr;

BulletManager* BulletManager::instance() {
	if (_instance == nullptr) {
		_instance = new BulletManager();
	}
	return _instance;
}

BulletManager::BulletManager() {
	reset();
}

void BulletManager::update(float dt, Vec2 const playerPos) {
	// Generate new bullet for every 1.5 delta time. Otherwise too many bullets are created every frame
	_bulletCreateTimer += dt;
	if (_bulletCreateTimer >= BULLET_CREATE_TIME) {
		reloadBulletTimer();
		createEntity(playerPos + Vec2(35.f, 72.f));
	}

	std::list<Bullet*>::iterator it;
	std::list<Bullet*> removeArray;

	for (it = _bulletList.begin(); it != _bulletList.end(); ++it) {
		Bullet* pBullet = *it;
		// Move bullet and remove it from screen if it is outside of the screen
		bool isOutside = pBullet->move(_origin, _visibleSize);
		if (isOutside) {
			_activeSceneObject->removeChild(pBullet);
			removeArray.push_back(pBullet);
			sendToPool(pBullet);
		}
	}
	for (it = removeArray.begin(); it != removeArray.end(); ++it) {
		_bulletList.remove(*it);
	}
}


void BulletManager::createEntity(Vec2 const pos) {
	Bullet* _bullet;

	// Create strong bullet if user has strongBullet, otherwise create weak bullet
	if (getHasStrongBullet()) {
		// Check and set if bullet still has strongBullet
		setCreateStrongBullet(strongBulletController());
		_bullet = _strongBulletPool.getEntity();
	}
	else
		_bullet = _weakBulletPool.getEntity();

	if (_bullet->getParent() == NULL)
		_activeSceneObject->addChild(_bullet);
	else {
		sendToPool(_bullet);
		return;
	}

	_bullet->setPosition(pos);
	_bullet->setRotation(0);
	_bulletList.push_back(_bullet);
}


void BulletManager::sendToPool(Bullet* bullet) {
	switch (bullet->getTag()) {
	case STRONG_BULLET_TAG:
		_strongBulletPool.addObjectToPool((Bullet*)bullet);
		break;
	case WEAK_BULLET_TAG:
		_weakBulletPool.addObjectToPool((Bullet*)bullet);
		break;
	default:
		log("Bullet tag is not defined.");
		return;
	}
}


void BulletManager::onHit(Bullet* bullet, Enemy* enemy) {
	// Set strongBullet if weak bullet hits 5 enemies
	if ((enemy->getHealth() <= 25) && (bullet->getTag() == WEAK_BULLET_TAG)) {
		_deadEnemyCount += 1;
		if (_deadEnemyCount == 5) {
			_deadEnemyCount = 0;
			setCreateStrongBullet(true);
		}
	}

	// remove bullet if enemyhealth is more than bullet power
	bullet->decreaseBulletPower(enemy->getHealth());
	if (bullet->getBulletPower() <= 0) {
		_bulletList.remove(bullet);
		_activeSceneObject->removeChild(bullet);
		bullet->reset();
		sendToPool(bullet);
	}
}

void BulletManager::reloadBulletTimer() {
	_bulletCreateTimer = 0.f;
}

void BulletManager::reset() {
	_strongBulletCount = 0;
	_bulletCreateTimer = 0.f;
	_deadEnemyCount = 0;
	_hasStrongBullet = false;
}

BulletManager::~BulletManager() {
	_weakBulletPool.destroy();
	_strongBulletPool.destroy();
}