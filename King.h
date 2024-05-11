#ifndef KING_H_
#define KING_H_
#include "Constants.h"
#include "Tiles.h"
#include "UTIL.h"

class King
{
public:
    //Maximum axits the velocity of the king
    static const int KING_VEL = 3;

    //Initializes the variable
    King();

    void setPosition( int posX, int posY, int _status);

    void handleEvent( SDL_Event &e );

    void setCamera( SDL_Rect &camera );

    void move( Tile * tiles[] );

    void render( SDL_Rect &camera );

    //Get dot dimensions of the king
    SDL_Rect getBox();
    status getStatus();

    void drawJumpForce();
    void setStatus();

private:
    //Current frame
    SDL_Rect currentFrame;

    //The X and Y offset of the king
    SDL_Rect mBox;

    //The velocity of the king
    int mVelX, mVelY;

    //Frame
    int frame;

    //King status
    status kingStatus;
    bool facing;

    //Jumping
    int jump_time;
};
#endif // KING_H_
