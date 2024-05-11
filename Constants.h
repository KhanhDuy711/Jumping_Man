#ifndef CONSTANTS_H_
#define CONSTANTS_H_

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

const int TOTAL_TILE_SPRITES = 322;
const int TOTAL_TILES = 30 * 200;

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

const int TILE_OF_ROW = 23;

const int LEVEL_WIDTH = TILE_WIDTH * 30;
const int LEVEL_HEIGHT = TILE_HEIGHT * 200;

const int WALKING_ANIMATION_FRAMES = 4;

//Set the velocity
const int MIN_JUMP_VEL = 5;
const int MAX_JUMP_VEL = 25;
const int MAX_FALLING_VEL = 10;
const int MAX_JUMP_TIME = 30;
const int JUMP_VELX = 5;

const int GRAVITY = 1;

enum status
{
	IDLE,
	WALKING,
	JUMPING,
	FALLING,
	FORCING,
	COLLISION,
};

enum gameStatus
{
	MENU,
	IN_GAME,
	SETTING,
	QUIT,
	PAUSE,
	CREDIT,
	OPTIONS_IN_MENU,
	OPTIONS_IN_GAME,
	WIN,
};

enum buttonStatus
{
	PRESSING,
	PRESSED,
	MOVED_IN,
	NORMAL,
};


#endif // !CONSTANTS_H_
