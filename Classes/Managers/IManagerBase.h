#pragma once
#include <cocos2d.h>

USING_NS_CC;
class IManagerBase
{
protected:
	Vec2 _origin;
	cocos2d::Size _visibleSize;
	cocos2d::Scene* _activeSceneObject;

public:
	virtual void setGameScene(cocos2d::Scene* activeSceneObject) {
		this->_activeSceneObject = activeSceneObject;
	}

	virtual void initialize(Vec2 origin, cocos2d::Size visibleSize) {
		this->_visibleSize = visibleSize;
		this->_origin = origin;
	}

	void update(float dt);
	void createEntity();
	void onHit();
	void reset();
};