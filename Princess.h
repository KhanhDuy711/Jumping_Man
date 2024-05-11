#ifndef PRINCESS_H_
#define PRINCESS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "LTexture.h"
#include "King.h"
#include "UTIL.h"

enum princessStatus
{
	WAITTING,
	WINNING,
};

class princess
{
public:
	princess();
	~princess();

	bool caculate(King* theKing);
	void render(SDL_Rect camera);

private:
	SDL_Rect mBox;

	SDL_Rect mSpriteClip[8];
	LTexture mSpriteSheet;

	int frame;

	const int WAITTNG_FRAME = 4;
	const int WINNING_FRAME = 8;
	princessStatus status;
};

#endif // !PRINCESS_H_
