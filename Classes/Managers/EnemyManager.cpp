#include "EnemyManager.h"

USING_NS_CC;
EnemyManager* EnemyManager::_instance = nullptr;

EnemyManager* EnemyManager::instance() {
	if (_instance == nullptr) {
		_instance = new EnemyManager();
	}
	return _instance;
}

EnemyManager::EnemyManager() {
	reset();
}

void EnemyManager::update(float dt) {
	// Generate new bullet for every 10. delta time. Otherwise too many enemies are created every frame
	_enemyCreateTimer += dt;
	if (_enemyCreateTimer >= ENEMY_CREATE_TIME) {
		resetEnemyTimer();
		createEntity();
	}

	std::list<Enemy*>::iterator it;
	std::list<Enemy*> removeArray;

	for (it = _enemyList.begin(); it != _enemyList.end(); ++it) {
		Enemy* _enemy = *it;
		// Move enemy and remove it from screen if it is outside of the screen
		bool isOutside = _enemy->move(_origin);
		if (isOutside) {
			_activeSceneObject->removeChild(_enemy);
			_enemy->reset();
			removeArray.push_back(_enemy);
			sendToPool(_enemy);
		}
	}

	for (it = removeArray.begin(); it != removeArray.end(); ++it) {
		Enemy* pEntity = *it;
		_enemyList.remove(pEntity);
	}
}

void EnemyManager::resetEnemyTimer() {
	_enemyCreateTimer = 0.f;
}


void EnemyManager::createEntity() {
	// Set a random number between 1 - 5 to row
	int rowNumber = rand() % 5 + 1;
	//  Set a random number between 10 - 15 to Column
	int columnNumber = rand() % 5 + 10;

	float enemyTopBottomDistance = ENEMY_HEIGHT * 2.f;

	float columnSpace = _visibleSize.width / columnNumber - ENEMY_WIDTH;
	float enemyLeftRightDistance = columnSpace + ENEMY_WIDTH;

	for (int j = 0; j < rowNumber; j++) {
		for (int i = 0; i < columnNumber; i++) {
			// make random enemy ship
			int nEnemyType = rand() % 2;
			Enemy* pEnemy = nullptr;

			if (nEnemyType == STRONG_ENEMY_TAG)
				pEnemy = _strongEnemyPool.getEntity();
			else
				pEnemy = _weakEnemyPool.getEntity();

			pEnemy->setAnchorPoint(Vec2::ZERO);
			pEnemy->setPosition(Vec2(_origin.x + columnSpace / 2 + enemyLeftRightDistance * i,
				_visibleSize.height + _origin.y + enemyTopBottomDistance * j));

			// Check if the enemy has no scene parent to be sure 
			if (pEnemy->getParent() == NULL)
				_activeSceneObject->addChild(pEnemy);
			else {
				sendToPool(pEnemy);
				return;
			}
			_enemyList.push_back(pEnemy);
		}
	}
}

void EnemyManager::onHit(Enemy* enemy, int bulletPower) {
	// Enemy health is decreased by bulletPower
	enemy->decreaseHealth(bulletPower);
	// Kill enemy if its health is 0 or lower and update score
	if (enemy->getHealth() <= 0) {
		updateEnemyScore(enemy->getTag());
		_enemyList.remove(enemy);
		_activeSceneObject->removeChild(enemy);
		enemy->reset();
		sendToPool(enemy);
	}
}

// Update dead enemy score -> strong enemies add 2 points 
void EnemyManager::updateEnemyScore(int enemyTag) {
	if (enemyTag == STRONG_ENEMY_TAG)
		_deadEnemyScore += 2;
	else
		_deadEnemyScore += 1;
}

void EnemyManager::sendToPool(Enemy* enemy) {
	switch (enemy->getTag()) {
	case STRONG_ENEMY_TAG:
		_strongEnemyPool.addObjectToPool(enemy);
		break;
	case WEAK_ENEMY_TAG:
		_weakEnemyPool.addObjectToPool(enemy);
		break;
	default:
		log("Enemy tag is not defined.");
		return;
	}
}

void EnemyManager::reset() {
	_deadEnemyScore = 0;
	_enemyCreateTimer = 10.f;
}

EnemyManager::~EnemyManager() {
	_weakEnemyPool.destroy();
	_strongEnemyPool.destroy();
}