#pragma once
#include "cocos2d.h"
#include <GameDefinitions.h>
#include <GameManager.h>

class GameOverScene : public cocos2d::Scene {
private:
	void createButtonPhysics(cocos2d::MenuItemImage* button, float _width);
	void gameExitCB(Ref* sender);
	void gameRetryCB(Ref* sender);

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameOverScene);
};