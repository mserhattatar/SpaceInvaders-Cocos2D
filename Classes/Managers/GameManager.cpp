#include "GameManager.h"

USING_NS_CC;

GameManager* GameManager::_instance = nullptr;

GameManager* GameManager::instance() {
	if (_instance == nullptr) {
		_instance = new GameManager();
	}
	return _instance;
}

void GameManager::setManagers() {
	_enemyManager = EnemyManager::instance();
	_enemyManager->setGameScene(_activeSceneObject);
	_enemyManager->initialize(_origin, _visibleSize);

	_bulletManager = BulletManager::instance();
	_bulletManager->setGameScene(_activeSceneObject);
	_bulletManager->initialize(_origin, _visibleSize);

	_playerManager = PlayerManager::instance();
	_playerManager->setGameScene(_activeSceneObject);
	_playerManager->initialize(_origin, _visibleSize);
	_playerManager->createEntity();
}

void GameManager::update(float dt, float _touchPosX) {
	_enemyManager->update(dt);
	_playerManager->update(dt, _touchPosX);
	_bulletManager->update(dt, _playerManager->getPlayerPos());
}

void GameManager::onHit(Enemy* enemy, Bullet* bullet) {
	_enemyManager->onHit(enemy, bullet->getBulletPower());
	_bulletManager->onHit(bullet, enemy);
}

void GameManager::onHit() {
	_playerManager->onHit();
}

void GameManager::switchScene(int sceneTag) {
	cocos2d::Scene* scene;

	switch (sceneTag) {
	case SCENE_GAME_OVER:
		scene = GameOverScene::createScene();
		break;
	case SCENE_GAME:
		reset();
		scene = GameScene::createScene();
		break;
	default:
		printf("Scene is not defined.");
		return;
	}
	Director::getInstance()->replaceScene(TransitionFade::create(0.8, scene, Color3B(229, 204, 255)));
}

void GameManager::reset() {
	_bulletManager->reset();
	_enemyManager->reset();
}

void GameManager::quitGame() {
	Director::getInstance()->end();
}