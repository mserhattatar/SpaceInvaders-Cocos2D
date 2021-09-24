#include "StartScene.h"
#include "GameScene.h"
#include "GameDefinitions.h"

USING_NS_CC;

Scene* StartScene::createScene() {
	return StartScene::create();
}

bool StartScene::init() {
	if (!Scene::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* ------- Add a background ------- */
	auto backgroundSprite = Sprite::create(START_SCENE_BACKGROUND);
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	/* ------ Add FuntacTicGame logo -------- */
	auto LogoSprite = Sprite::create(FUNTACTICGAME_LOGO_IMAGE);
	LogoSprite->setContentSize(cocos2d::Size(600, 400));
	LogoSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(LogoSprite);

	// wait a while to switch to gamescene
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(StartScene::GoToGameScene), DISPLAY_TIME_SPLASH_SCENE);

	return true;
}

void StartScene::GoToGameScene(float dt) {
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}