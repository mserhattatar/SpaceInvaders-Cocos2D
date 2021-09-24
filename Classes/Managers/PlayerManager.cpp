#include "PlayerManager.h"

USING_NS_CC;
PlayerManager* PlayerManager::_instance = nullptr;

PlayerManager* PlayerManager::instance() {
	if (_instance == nullptr) {
		_instance = new PlayerManager();
	}
	return _instance;
}

void PlayerManager::createEntity() {
	_player = new Player();
	_player->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_player->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2 - 350));
	_player->setPlayerPosY(_visibleSize.height / 2 - 350);

	cocos2d::Node* pParent = _player->getParent();
	if (pParent == NULL)
		_activeSceneObject->addChild(_player, 15);
}

//if Player hit Enemy game over
void PlayerManager::onHit() {
	_activeSceneObject->stopAllActions();

	GameManager::instance()->switchScene(SCENE_GAME_OVER);
}

void PlayerManager::update(float dt, float touchX) {
	_player->move(touchX);
}