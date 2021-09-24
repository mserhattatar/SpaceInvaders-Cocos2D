# pragma once 
#include "cocos2d.h"
#include "GameDefinitions.h"
#include "PlayerManager.h"
#include "GameManager.h"
#include "EnemyManager.h"
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"

class GameManager;

class GameScene : public cocos2d::Scene {
private:
	GameManager* _gameManager;

	cocos2d::PhysicsWorld* m_sceneWorld;
	cocos2d::Label* _enemyScoreLabel;

	bool _touchStarted;
	float _touchPosX;
	int _enemyScore;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);
	void increaseEnemyScore();

	void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { m_sceneWorld = world; };
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	bool onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	CREATE_FUNC(GameScene);
};