#ifndef JUMP_KING_GAME
#define JUMP_KING_GAME

#include "LTexture.h"
#include "Constants.h"
#include "UTIL.h"
#include "King.h"
#include "Global.h"
#include "Tiles.h"
#include "timer.h"
#include "Princess.h"

class game
{
public:
	game();
	~game();

	//Game action
	void handleEvent();
	void update();
	void render();

	//Game run
	void run();

	void loadGame(std::string path);
	void saveGame(std::string path);

private:
	SDL_Window* mWindow;

	SDL_Event *e;

	gameStatus mode;

	King* Arthur;

	princess* Princess;

	Tile* tileset[TOTAL_TILES];

	LTimer *capTimer;

	SDL_Rect camera;

	bool music;
};

#endif // !JUMP_KING_GAME
