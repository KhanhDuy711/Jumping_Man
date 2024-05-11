#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "LTexture.h"
#include "Constants.h"
#include "LButton.h"

//Renderer
extern SDL_Renderer * gRenderer;

//Font
extern TTF_Font *gMenuFont;

//Camera rect
extern SDL_Rect gCameraSprite[LEVEL_HEIGHT / SCREEN_HEIGHT];

//Tile texture
extern LTexture gTilesTexture;
extern SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

//Animation texture
extern LTexture gWalkingSpriteSheetTexture;
extern SDL_Rect gWalkingSpriteClip[ WALKING_ANIMATION_FRAMES ];
extern LTexture gJumpingTexture;
extern LTexture gForcingTexture;
extern LTexture gFallingTexture;
extern LTexture gCollisionTexture;

//Background
extern LTexture gBGTexture;
extern LTexture gMenuBGTexture;
extern LTexture gCastleBackGround;
extern LTexture gWinGameBG;

//Menu button
extern LButton gNewGameButton;
extern LButton gContinueButton;
extern LButton gCreditButton;
extern LButton gQuitButton;
extern LButton gOptionsButton;
extern LButton gResumeButton;
extern LButton gSaveExitButton;
extern LButton gRestartButton;
extern LButton gPauseOptionButton;
extern LButton gOnButton[2];
extern LButton gOffButton[2];
extern LButton gEndGame;

//Credit texture
extern LTexture gCreditTexture[10];

//Game sound
extern Mix_Chunk* gJumpSound;

//Game music
extern Mix_Music* gMusic;
#endif // GLOBAL_H_