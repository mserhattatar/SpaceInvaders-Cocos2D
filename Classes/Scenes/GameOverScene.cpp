#include "GameOverScene.h"

USING_NS_CC;
Scene* GameOverScene::createScene() {
	return GameOverScene::create();
}

bool GameOverScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* -------- Buttons & Menu ------- */
	auto* tryAgainButton = MenuItemImage::create("TryAgainButton.png", "TryAgainButton.png", CC_CALLBACK_1(GameOverScene::gameRetryCB, this));
	createButtonPhysics(tryAgainButton, -50.f);

	auto exitGameButton = MenuItemImage::create("ExitButton.png", "ExitButton.png", CC_CALLBACK_1(GameOverScene::gameExitCB, this));
	createButtonPhysics(exitGameButton, 50.f);

	// create menu from buttons and add to scene
	auto* buttonsMenu = Menu::create(exitGameButton, tryAgainButton, NULL);
	buttonsMenu->setPosition(Vec2::ZERO);
	this->addChild(buttonsMenu, 10);

	/* ---------- Game Over Label ----------- */
	// create and initialize Game Over label
	auto gameOverLabel = Label::createWithTTF("Game Over!", "fonts/arial.ttf", 50);
	gameOverLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height - gameOverLabel->getContentSize().height) / 2));
	this->addChild(gameOverLabel, 10);

	/* ------- Background ------ */
	auto sprite = Sprite::create(GAME_OVER_BACKGROUND);
	// position the sprite on the center of the screen
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	return true;
}

void GameOverScene::createButtonPhysics(cocos2d::MenuItemImage* button, float _width) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	button->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	float x = origin.x + visibleSize.width / 2 + _width;
	float y = origin.y + button->getContentSize().height * 2;
	button->setPosition(Vec2(x, y));
}

void GameOverScene::gameExitCB(Ref* ref) {
	GameManager::instance()->quitGame();
}

void GameOverScene::gameRetryCB(Ref* ref) {
	GameManager::instance()->switchScene(SCENE_GAME);
}