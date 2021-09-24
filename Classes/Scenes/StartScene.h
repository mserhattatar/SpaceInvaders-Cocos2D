#pragma once
#include "cocos2d.h"

class StartScene : public cocos2d::Scene {
private:
	void GoToGameScene(float dt);

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(StartScene);
};