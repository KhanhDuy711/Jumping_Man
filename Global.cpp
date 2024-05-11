#include "Global.h"

SDL_Renderer * gRenderer = NULL;

TTF_Font *gMenuFont = NULL;

SDL_Rect gCameraSprite[ LEVEL_HEIGHT / SCREEN_HEIGHT ];

LTexture gTilesTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

LTexture gWalkingSpriteSheetTexture;
SDL_Rect gWalkingSpriteClip[ WALKING_ANIMATION_FRAMES ];
LTexture gJumpingTexture;
LTexture gForcingTexture;     
LTexture gFallingTexture;
LTexture gCollisionTexture;

LTexture gBGTexture;
LTexture gMenuBGTexture;
LTexture gCastleBackGround;
LTexture gWinGameBG;

LButton gNewGameButton;
LButton gContinueButton;
LButton gCreditButton;
LButton gQuitButton;
LButton gOptionsButton;
LButton gResumeButton;
LButton gSaveExitButton;
LButton gRestartButton;
LButton gPauseOptionButton;
LButton gEndGame;

Mix_Chunk* gJumpSound;
Mix_Music* gMusic;