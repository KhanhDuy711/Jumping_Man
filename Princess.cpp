#include "Princess.h"

princess::princess()
{
	mBox = { 558, 448, 32, 32 };
	frame = 0;
	mSpriteSheet.loadFromFile("Game data/Character/Princess.png");
	for (int i = 0; i < WINNING_FRAME; ++i)
	{
		mSpriteClip[i] = {i * 64, 0, 64, 64};
	}
	status = WAITTING;
}

princess::~princess()
{
}

bool princess::caculate(King * theKing)
{
	if (checkCollision(theKing->getBox(), mBox ))
	{
		status = WINNING;
	}
	if (status == WINNING)
		return true;	

	return false;
}

void princess::render(SDL_Rect camera)
{
	if (checkCollision(mBox, camera))
	{
		mSpriteSheet.render(mBox.x - camera.x, mBox.y - camera.y, &mSpriteClip[frame/8]);
		frame++;
		if (frame >= WAITTNG_FRAME * 8)
		{
			frame = 0;
		}
	}
	
}
