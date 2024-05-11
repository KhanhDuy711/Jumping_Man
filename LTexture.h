#ifndef LTexture_H_
#define LTexture_H_

#include <iostream>
#include <string>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class LTexture
{
public:
    LTexture();
    ~LTexture();

    bool loadFromFile( std::string path);
    void free();
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    #if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    #endif
    int getWidth();
    int getHeight();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

private:
    SDL_Texture * mTexture;
    int mWidth;
    int mHeight;
};

#endif // LTexture_H_
