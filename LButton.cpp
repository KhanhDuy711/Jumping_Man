#include "LButton.h"
#include "Global.h"

LButton::LButton()
{
	buttonBox = { 0, 0, 0, 0 };
	pressed = false;
	button = NORMAL;
}

LButton::LButton(int posX, int posY, int width, int height)
{
	buttonBox = { posX, posY, width, height };
	pressed = false;
	button = NORMAL;
}

LButton::~LButton()
{
	buttonTexture.free();
}

void LButton::setPosition( int posX, int posY, int width, int height)
{
	if (width == 0 && height == 0)
		buttonBox = { posX, posY, buttonTexture.getWidth(), buttonTexture.getHeight() };
	else
		buttonBox = { posX, posY, width, height };
}

void LButton::handleEvent(SDL_Event *e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEMOTION)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse inside button
		bool inside = false;
		if (x < buttonBox.x)
			inside = false;
		else if (y < buttonBox.y)
			inside = false;
		else if (x > buttonBox.x + buttonBox.w)
			inside = false;
		else if (y > buttonBox.y + buttonBox.h)
			inside = false;
		else
			inside = true;

		if (inside)
		{
			button = PRESSED;

			if (e->type == SDL_MOUSEBUTTONDOWN)
			{
				button = PRESSING;
			}

			if (e->type == SDL_MOUSEBUTTONUP)
			{
				button = PRESSED;
				pressed = true;
			}
		}
		else if ( !pressed )
		{
			button = NORMAL;
		}
	}
}

void LButton::render()
{
	if (button == NORMAL)
	{
		buttonTexture.render(buttonBox.x, buttonBox.y);
	}
	else if ( button == PRESSING )
	{
		pressingButtonTexture.render(buttonBox.x, buttonBox.y);
	}
	else if (button == PRESSED || button == MOVED_IN)
	{
		touchedButtonTexture.render(buttonBox.x, buttonBox.y);
	}
}

SDL_Rect LButton::getBox()
{
	return buttonBox;
}

bool LButton::isPressted()
{
	return pressed;
}

void LButton::reverse()
{
	pressed = false;
}

void LButton::loadButtonTexture(std::string path)
{
	buttonTexture.loadFromFile(path);
}

bool LButton::loadButtonTextureFromText(std::string path, std::string str, int size, SDL_Color textColor)
{
	bool success = true;
	//Open the font
	gMenuFont = TTF_OpenFont(path.c_str(), size);
	if (gMenuFont == NULL)
	{
		std::cout << "Failed to load menu font! SDL_ttf Error: " << TTF_GetError() << "\n";
		success = false;
	}
	else
	{
		//Render text
		if (!buttonTexture.loadFromRenderedText(str, textColor ) || !touchedButtonTexture.loadFromRenderedText(str, { 255, 255, 0 }) || !pressingButtonTexture.loadFromRenderedText(str, { 255, 0, 0 }))
		{
			std::cout << "Failed to render text texture\n";
			success = false;
		}
	}
	return success;
}

int LButton::getWidth()
{
	return buttonTexture.getWidth();
}

int LButton::getHeight()
{
	return buttonTexture.getHeight();
}
