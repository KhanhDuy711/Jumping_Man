#include "Jump_king_game.h"
#include <iomanip>

game::game()
{
	init(mWindow);
	Arthur = new King();
	Princess = new princess();
	capTimer = new LTimer;
	camera = { 0, 0, 0, 0 };
	setTiles(tileset,"Game data/Tileset/game_map.map");
	mode = MENU;
	e = new SDL_Event;
	if (!loadMedia())
	{
		std::cout << "Failed to load media\n";
	}
}

game::~game()
{
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	delete Arthur;
	delete Princess;
	delete capTimer;
	delete e;
	close(tileset);
}

void game::handleEvent()
{
	if (mode == MENU)
	{
		gNewGameButton.handleEvent(e);
		if (gNewGameButton.isPressted())
		{
			delete Arthur;
			Arthur = new King;
			mode = IN_GAME;
			gNewGameButton.reverse();
		}
		gContinueButton.handleEvent(e);
		if (gContinueButton.isPressted())
		{
			loadGame("Game data/Saved.txt");
			mode = IN_GAME;
			gContinueButton.reverse();
		}

		gOptionsButton.handleEvent(e);
		if (gOptionsButton.isPressted())
		{
			mode = OPTIONS_IN_MENU;
			gOptionsButton.reverse();
		}
		
		gCreditButton.handleEvent(e);
		if (gCreditButton.isPressted())
		{
			mode = CREDIT;
			gCreditButton.reverse();
		}
		
		gQuitButton.handleEvent(e);
		if (gQuitButton.isPressted())
		{
			mode = QUIT;
			gQuitButton.reverse();
		}
	}
	else if (mode == IN_GAME)
	{
		if (e->key.keysym.sym == SDLK_ESCAPE && e->type == SDL_KEYDOWN )
		{
			mode = PAUSE;
		}
		Arthur->handleEvent(*e);
	}
	else if (mode == PAUSE)
	{
		gResumeButton.handleEvent(e);
		if (gResumeButton.isPressted() )
		{
			mode = IN_GAME;
			gResumeButton.reverse();
		}

		gRestartButton.handleEvent(e);
		if (gRestartButton.isPressted())
		{
			Arthur = new King();
			mode = IN_GAME;
			gRestartButton.reverse();
		}

		gPauseOptionButton.handleEvent(e);
		if (gPauseOptionButton.isPressted())
		{
			mode = OPTIONS_IN_GAME;
			gPauseOptionButton.reverse();
		}

		gSaveExitButton.handleEvent(e);
		if (gSaveExitButton.isPressted())
		{
			saveGame("Game data/Saved.txt");
			mode = MENU;
			gSaveExitButton.reverse();
		}

		if ((e->key.keysym.sym == SDLK_RETURN || e->key.keysym.sym == SDLK_ESCAPE) && e->type == SDL_KEYDOWN)
		{
			mode = IN_GAME;
		}
	}
	else if (mode == WIN)
	{
		gEndGame.handleEvent(e);
		if (gEndGame.isPressted())
		{
			mode = MENU;
		}
		gEndGame.reverse();
		delete Arthur;
		Arthur = new King();
	}
}

void game::update()
{
	if (mode == IN_GAME)
	{
		Arthur->move(tileset);
		Arthur->setCamera(camera);
		Arthur->setStatus();
		if (Princess->caculate(Arthur))
		{
			mode = WIN;
		}
	}
	if (mode == PAUSE)
	{
		
	}
}

void game::render()
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gRenderer);

	if (mode == MENU)
	{
		drawRect(100, 320, 200, 300);
		gMenuBGTexture.render(0, 0);
		gNewGameButton.render();
		gContinueButton.render();
		gOptionsButton.render();
		gCreditButton.render();
		gQuitButton.render();
	}
	else if (mode == CREDIT)
	{

	}
	else if (mode == IN_GAME || mode == PAUSE )
	{
		gBGTexture.render(0, 0);
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			tileset[i]->render(camera);
		}
		Princess->render(camera);
		Arthur->render(camera);

		if (mode == PAUSE)
		{
			//Render pause screen
			drawRect(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2);
			gResumeButton.render();
			gRestartButton.render();
			gPauseOptionButton.render();
			gSaveExitButton.render();
		}
	}
	else if (mode == WIN)
	{
		gWinGameBG.render(0, 0);
		gEndGame.render();
	}
	SDL_RenderPresent(gRenderer);
}

void game::run()
{
	setSpriteClip();
	//Set quit flag
	bool quit = false;
	while (!quit)
	{
		capTimer->start();
		while (SDL_PollEvent(e) != 0)
		{
			if (e->type == SDL_QUIT || mode == QUIT)
			{
				saveGame("Game data/Saved.txt");
				quit = true;
			}
			handleEvent();
		}
		update();
		render();

		//Lock fps
		int frameTicked = capTimer->getTicks();
		if (frameTicked < SCREEN_TICK_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicked);
		}
	}
}

void game::loadGame(std::string path)
{
	std::ifstream fin(path);
	int posX, posY, status;
	fin >> posX >> posY >> status;
	Arthur->setPosition(posX, posY, status);
	fin.close();
}

void game::saveGame(std::string path)
{
	std::ofstream fout(path);
	fout << Arthur->getBox().x << " " << Arthur->getBox().y << " " << Arthur->getStatus();
	fout.close();
}

