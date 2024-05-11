#include "King.h"
#include "Global.h"
#include "UTIL.h"


King::King()
{
    //Initialize of the offsets
    currentFrame = gWalkingSpriteClip[ 0 ];
    mBox.x = LEVEL_WIDTH / 2;
    mBox.y = LEVEL_HEIGHT - 64;
    mBox.w = 52;
    mBox.h = 64;

    //King status set
    kingStatus = IDLE;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    //Set frame to started
    frame = 0;

    //Set facing direction
    facing = false;

    jump_time = 0;
}

void King::setPosition(int posX, int posY, int _status)
{
    mBox.x = posX;
    mBox.y = posY;
    kingStatus = (status) _status;
}

void King::handleEvent( SDL_Event &e )
{
    if (e.key.repeat == 0 && e.type == SDL_KEYDOWN && kingStatus == IDLE)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            mVelX -= KING_VEL;
            facing = true;
            break;

        case SDLK_RIGHT:
            mVelX += KING_VEL;
            facing = false;
            break;

        default:
            break;
        }
           
    }

    if (e.key.repeat == 0 && e.type == SDL_KEYUP && kingStatus == WALKING )
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            mVelX += KING_VEL;
            kingStatus = IDLE;
            break;

        case SDLK_RIGHT:
            mVelX -= KING_VEL;
            kingStatus = IDLE;
            break;

        default:
            break;
        }
    }
    if (e.key.keysym.sym == SDLK_SPACE)
    {
        if (e.key.repeat != 0 && e.type == SDL_KEYDOWN && kingStatus != FALLING && kingStatus != JUMPING)
        {
            kingStatus = FORCING;
            if (jump_time < MAX_JUMP_TIME)
            {
                jump_time++;
            }
        }

        if (((e.key.repeat == 0 && e.type == SDL_KEYUP) || jump_time == MAX_JUMP_TIME ) && (kingStatus == FORCING || kingStatus == IDLE))
        {
            mVelY -= MIN_JUMP_VEL + (MAX_JUMP_VEL - MIN_JUMP_VEL) * jump_time / MAX_JUMP_TIME;
            jump_time = 0;
            if (facing == true)
            {
                mVelX -= JUMP_VELX;
            }
            else
            {
                mVelX += JUMP_VELX;
            }
            Mix_PlayChannel(-1, gJumpSound, 0);
        }
    }
}

void King::move( Tile * tiles[] )
{
    //Move the king left or right
    mBox.x += mVelX;

    //If the king went too far to the left or right
    if (mBox.x < 0 || mBox.x + mBox.w > SCREEN_WIDTH || touchesWall(mBox, tiles))
    {
        //Move back
        mBox.x -= mVelX;

        //If king collision with wall
        if (kingStatus == JUMPING || kingStatus == FALLING)
        {
            kingStatus = COLLISION;
            mVelX = -1 * mVelX;
        }
    }

    //Jumping and falling
    mVelY = std::min( mVelY + 1, MAX_FALLING_VEL );

    if (kingStatus == JUMPING && mVelY > 0)
    {
        mVelX = mVelX * 2 / 3;
    }

    mBox.y += mVelY;
    if ( ( mBox.y < 0 ) || mBox.y + mBox.h > LEVEL_HEIGHT || touchesWall( mBox, tiles ) )
    {
        //Move back
        mBox.y -= mVelY;
        mVelY = 0;
        if ( kingStatus == FALLING || kingStatus == JUMPING )
        {
            mVelX = 0;
            kingStatus = IDLE;
        }
    }
}

void King::setCamera( SDL_Rect& camera )
{
    //Set the camera allway show the king
    for ( int i = 0; i < LEVEL_HEIGHT / SCREEN_HEIGHT; ++i )
    {
        if ( checkCollision( mBox, gCameraSprite[ i ] ) )
        {
            camera = gCameraSprite[i];
            return ;
        }
    }
    return ;
}

void King::render( SDL_Rect& camera )
{
    SDL_RendererFlip flip;
    if ( facing )
        flip = SDL_FLIP_HORIZONTAL;
    else
        flip = SDL_FLIP_NONE;

    if ( kingStatus == WALKING )
    {
        mBox.w = currentFrame.w;
        mBox.h = currentFrame.h;
        if ( frame >= 8 * WALKING_ANIMATION_FRAMES )
            frame = 0;
        gWalkingSpriteSheetTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gWalkingSpriteClip[ frame / 8 ], 0, NULL, flip );
        currentFrame = gWalkingSpriteClip[frame / 8];
        ++frame;
    }
    else if (kingStatus == JUMPING)
    {
        mBox.w = gJumpingTexture.getWidth();
        mBox.h = gJumpingTexture.getHeight();
        gJumpingTexture.render(mBox.x - camera.x, mBox.y - camera.y, NULL, 0, NULL, flip);
    }
    else if (kingStatus == FORCING)
    {
        mBox.w = gForcingTexture.getWidth();
        mBox.h = gForcingTexture.getHeight();
        gForcingTexture.render(mBox.x - camera.x, mBox.y - camera.y, NULL, 0, NULL, flip);
        drawJumpForce();
    }
    else if (kingStatus == FALLING)
    {
        mBox.w = gFallingTexture.getWidth();
        mBox.h = gFallingTexture.getHeight();
        gFallingTexture.render(mBox.x - camera.x, mBox.y - camera.y, NULL, 0, NULL, flip);
    }
    else if (kingStatus == COLLISION)
    {
        mBox.w = gCollisionTexture.getWidth();
        mBox.h = gCollisionTexture.getHeight();
        gCollisionTexture.render(mBox.x - camera.x, mBox.y - camera.y, NULL, 0, NULL, flip);
    }
    else
    {
        gWalkingSpriteSheetTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gWalkingSpriteClip[ 0 ], 0, NULL, flip);
        currentFrame = gWalkingSpriteClip[0];
    }
}

SDL_Rect King::getBox()
{
    return mBox;
}

status King::getStatus()
{
    return kingStatus;
}

void King::drawJumpForce()
{
    if ( jump_time != 0 )
    {
        SDL_Rect jumpForce = { SCREEN_WIDTH - 100, 0, jump_time * 100 / MAX_JUMP_TIME, 20};
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
        SDL_RenderFillRect( gRenderer, &jumpForce );
    }
}  

void King::setStatus()
{
    if (mVelX != 0 && mVelY == 0 )
    {
        kingStatus = WALKING;
    }

    if (mVelY > 0 && kingStatus != COLLISION)
    {
        kingStatus = FALLING;
    }
    if (mVelY < 0 && kingStatus != COLLISION)
    {
        kingStatus = JUMPING;
    }
}