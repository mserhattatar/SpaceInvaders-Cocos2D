#pragma once
#include "Entity.h"
#include "GameDefinitions.h"
#include <string>

USING_NS_CC;
class Enemy : public Entity {
public:
	Enemy(int tag);

	bool move(Vec2 origin);
	void reset();
};