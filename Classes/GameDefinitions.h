#pragma once

// SCENE ID
#define SCENE_GAME 0
#define SCENE_GAME_OVER 1

// SCENE VALUE
#define DISPLAY_TIME_SPLASH_SCENE 0.4f
#define TRANSITION_TIME 0.2f

// ENTITY HEALTH & POWER VALUE
#define PLAYER_HEALTH 0
#define	WEAK_ENEMY_HEALTH 50
#define STRONG_ENEMY_HEALTH 100
#define WEAK_BULLET_POWER 25
#define STRONG_BULLET_POWER 100

// MOVEMENT VALUES
#define PLAYER_DELTA_MOVE 20.f
#define ENEMY_DELTA_MOVE 1.5f
#define BULLET_DELTA_MOVE 6.f

// Bullet create timer
#define BULLET_CREATE_TIME .15f
#define ENEMY_CREATE_TIME 10.f

// IMAGES
#define START_SCENE_BACKGROUND "SplashSBackground.png"
#define LEVEL_BACKGROUND "LevelBackground.png"
#define GAME_OVER_BACKGROUND "GameOverBackground.png"
#define FUNTACTICGAME_LOGO_IMAGE "FunTacticGamesLogo.png"
#define PLAYER_IMAGE "Player.png"
#define	WEAK_ENEMY_IMAGE "Weak_Enemy.png"
#define STRONG_ENEMY_IMAGE "Strong_Enemy.png"
#define STRONG_BULLET_IMAGE "bullet_strong.png"
#define WEAK_BULLET_IMAGE "50_bullet.png"

// IMAGES SIZES
#define PLAYER_WIDTH 70.f
#define PLAYER_HEIGHT 70.f
#define ENEMY_WIDTH 50.f
#define ENEMY_HEIGHT 50.f
#define BULLET_WIDTH 20.f
#define BULLET_HEIGHT 20.f
#define STRONG_BULLET_WIDTH 45.f
#define STRONG_BULLET_HEIGHT 45.f

// TAGS
#define WEAK_ENEMY_TAG 0
#define STRONG_ENEMY_TAG 1
#define PLAYER_TAG 2
#define WEAK_BULLET_TAG 3
#define STRONG_BULLET_TAG 4