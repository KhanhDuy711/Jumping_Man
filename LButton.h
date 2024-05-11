#ifndef LBUTTON_H_
#define LBUTTON_H_

#include "LTexture.h"
#include "Constants.h"

class LButton
{
public:
	LButton();
	LButton(int posX, int posY, int width, int height);
	~LButton();

	void setPosition( int posX, int posY, int width = 0, int height = 0);
	void handleEvent(SDL_Event *e);
	void render();
	
	void loadButtonTexture(std::string path);
	bool loadButtonTextureFromText(std::string path, std::string str, int size, SDL_Color textColor = { 255, 255, 255 });

	int getWidth();
	int getHeight();

	SDL_Rect getBox();
	bool isPressted();
	void reverse();

private:
	SDL_Rect buttonBox;

	LTexture buttonTexture;
	LTexture touchedButtonTexture;
	LTexture pressingButtonTexture;

	bool pressed;

	buttonStatus button;
};

#endif // !LBUTTON_H_
