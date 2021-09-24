#include "GameScene.h"

USING_NS_CC;
Scene* GameScene::createScene() {
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;
}

bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_touchPosX = visibleSize.width / 2;

	/* -------- Add background ------- */
	auto sprite = Sprite::create(LEVEL_BACKGROUND);
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	/* -------- Score Text Label -------*/
	auto scoreTextLabel = Label::createWithTTF("Score : ", "fonts/arial.ttf", 24);
	scoreTextLabel->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - 30));
	this->addChild(scoreTextLabel, 10);

	/* -------- score Text Label EnemyScore -------- */
	_enemyScoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 24);
	// position the label on the center of the screen
	Vec2 pos = Vec2(scoreTextLabel->getPositionX() + scoreTextLabel->getContentSize().width + 5.f, scoreTextLabel->getPositionY());
	_enemyScoreLabel->setPosition(pos);
	this->addChild(_enemyScoreLabel, 10);

	/* ------- Touch and Collusion Event handlers ------- */
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	/* ------- Set Game Manager -------- */
	_gameManager = GameManager::instance();
	_gameManager->setGameScene(this);
	_gameManager->initialize(origin, visibleSize);
	_gameManager->setManagers();

	_enemyScore = 0;

	this->scheduleUpdate();

	return true;
}

void GameScene::update(float dt) {
	_gameManager->update(dt, _touchPosX);

	if (_enemyScore != _gameManager->_enemyManager->getDeadEnemyScore())
		increaseEnemyScore();
}

void GameScene::increaseEnemyScore() {
	_enemyScore += 1;
	_enemyScoreLabel->setString(StringUtils::format("%d", _enemyScore));
}


bool GameScene::onTouchBegan(Touch* touch, Event* event) {
	Vec2 touchLocation = touch->getLocation();
	_touchStarted = true;
	_touchPosX = touchLocation.x;
	return true;
}

bool GameScene::onTouchMoved(Touch* touch, Event* event) {
	Vec2 touchLocation = touch->getLocation();
	_touchPosX = touchLocation.x;
	return true;
}

bool GameScene::onTouchEnded(Touch* touch, Event* event) {
	Vec2 touchLocation = touch->getLocation();
	_touchPosX = touchLocation.x;
	_touchStarted = false;
	return true;
}

bool GameScene::onContactBegin(PhysicsContact& contact) {
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	int tagA = nodeA->getTag();
	int tagB = nodeB->getTag();

	// Player and enemy hit
	if ((tagA == PLAYER_TAG && tagB == WEAK_ENEMY_TAG) || (tagB == PLAYER_TAG && tagA == WEAK_ENEMY_TAG) ||
		(tagA == PLAYER_TAG && tagB == STRONG_ENEMY_TAG) || (tagB == PLAYER_TAG && tagA == STRONG_ENEMY_TAG)) {
		_gameManager->onHit();
	}

	// Bullet and enemy hit
	if ((tagA == WEAK_BULLET_TAG && tagB == WEAK_ENEMY_TAG) || (tagB == WEAK_BULLET_TAG && tagA == WEAK_ENEMY_TAG) ||
		(tagA == STRONG_BULLET_TAG && tagB == WEAK_ENEMY_TAG) || (tagB == STRONG_BULLET_TAG && tagA == WEAK_ENEMY_TAG) ||
		(tagA == WEAK_BULLET_TAG && tagB == STRONG_ENEMY_TAG) || (tagB == WEAK_BULLET_TAG && tagA == STRONG_ENEMY_TAG) ||
		(tagA == STRONG_BULLET_TAG && tagB == STRONG_ENEMY_TAG) || (tagB == STRONG_BULLET_TAG && tagA == STRONG_ENEMY_TAG)) {
		Bullet* _bullet;
		Enemy* _enemy;
		if (tagA == WEAK_BULLET_TAG || tagA == STRONG_BULLET_TAG) {
			_bullet = (Bullet*)nodeA;
			_enemy = (Enemy*)nodeB;
		}
		else {
			_bullet = (Bullet*)nodeB;
			_enemy = (Enemy*)nodeA;
		}
		_gameManager->onHit(_enemy, _bullet);
	}
	return true;
}