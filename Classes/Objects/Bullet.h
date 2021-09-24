# pragma once 
#include "cocos2d.h"
#include "Entity.h"
#include "GameDefinitions.h"

USING_NS_CC;
class Bullet : public Entity {
public:
	Bullet(int tag);

	bool move(Vec2 origin, cocos2d::Size visibleSize);
	void reset();
};