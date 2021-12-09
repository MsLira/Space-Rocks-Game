#include "bullet.h"

Bullet::Bullet(SDL_Renderer* renderer, float x, float y)
{
	active = false;

	speed = 800.0;

	SDL_Surface* surface = IMG_Load("./SpAssets/Projectile.png");

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	int w, h;

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	posRect.w = w;
	posRect.h = h;

	posRect.x = x;
	posRect.y = y;

	pos_X = x;
	pos_Y = y;

	xDir = 0;
	yDir = 0;

}

void Bullet::Resposition()
{
	if (xDir == 1 && yDir == 0) // Move to Right
	{
		posRect.x += (45);
		posRect.y += (11); //down

	}
	else if (xDir == -1 && yDir == 0)// Move to Left
	{
		posRect.x -= 8;
		posRect.y += (11); // down

	}
	else if (xDir == 0 && yDir == 1) // Move Down the screen 
	{
		posRect.x += 20; // over 20
		posRect.y += 38; //down

	}
	else if (xDir == 0 && yDir == -1) // Move Up the Screen
	{
		posRect.x += 18; // over
		posRect.y -= 16; // Up

	}
	// *****************  MOving ANGLES  ******************************************************************************
	else if (xDir == 1 && yDir == -1) // UP into the Right
	{
		posRect.x += 40;
		posRect.y -= 10;

	}
	else if (xDir == -1 && yDir == -1)// DOWN into Right
	{
		posRect.x -= 6;
		posRect.y -= 10;

	}
	else if (xDir == 1 && yDir == 1) // UP to the Rigth and DOWN
	{
		posRect.x += 40;
		posRect.y += 32;

	}
	else if (xDir == -1 && yDir == 1) // Left and Down
	{
		posRect.x -= 2;
		posRect.y += 32;

	}

	pos_X = posRect.x; // Precision Loss
	pos_Y = posRect.y;
}


// WRAPPING **************************************************

void Bullet::Deactivate()
{
	active = false;

	posRect.x = -3000;

	posRect.y = -3000;

	pos_X = posRect.x;

	pos_Y = posRect.y;
}





// WRAPPING **************************************************

void Bullet::Update(float deltaTime)
{

	if (active)
	{

		// get bullet's new position'
		pos_X += (speed * xDir) * deltaTime;
		pos_Y += (speed * yDir) * deltaTime;

		//adjust for precision loss
		posRect.x = (int)(pos_X + 0.5f);
		posRect.y = (int)(pos_Y + 0.5f);

		// check if the bullet is off the screen
		if (posRect.x < 0 || posRect.x > 1024 || posRect.y < 0 || posRect.y > 768)
		{
			active = false;

			posRect.x = -1000;
			posRect.y = -1000;

			pos_X = posRect.x;
			pos_Y = posRect.y;
		}
	}
}


void Bullet::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &posRect);

}

Bullet::~Bullet()
{
// SDL_DestroyTexture(texture);

}