#include "Asteroid Big.h"

#include <iostream>
#include <cstdlib>

using namespace std;

AsteroidBig::AsteroidBig(SDL_Renderer* renderer, float x, float y)
{

	active = false;

	speed = 200.0;

	SDL_Surface* surface = IMG_Load("./SpAssets/Asteroid Big.png");

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

	rockAngle = 0.0f;

	// center of the rock's sprite
	rockCenter.x = posRect.w / 2;
	rockCenter.y = posRect.h / 2;

}


// WRAPPING **************************************************

void AsteroidBig::Deactivate()
{
	active = false;

	posRect.x = -2000;

	posRect.y = -2000;

	pos_X = posRect.x;

	pos_Y = posRect.y;

}

// WRAPPING **************************************************




void AsteroidBig::Reposition()
{

	active = true;

	// location on scree 1 = left, 2 = right, 3 = top, 4 = bottom
	int location = rand() % 4 + 1;

	// movement of asterioid 1 = left or right, 2 = up or don
	int direction = rand() % 2 + 1;

	if (location == 1)// left
	{
		// off screen on the left
		posRect.x = -posRect.w;
		pos_X = posRect.x;

		// random from top to bottom
		// number for random up and down
		int bottomOfScreen = 768 - (posRect.h * 2);
		posRect.y = rand() % bottomOfScreen + posRect.h;
		pos_Y = posRect.y;

		if (direction == 1) // move right and up
		{
			xDir = 1;
			yDir = -1;
		}
		else//move right and down
		{
			xDir = 1;
			yDir = 1;
		}
			
	}
	else if (location == 2)// right
	{
		// off screen on the right
		posRect.x = 1024;
		pos_X = posRect.x;

		// random from top to bottom
		// number for random up and down
		int bottomOfScreen = 768 - (posRect.h * 2);
		posRect.y = rand() % bottomOfScreen + posRect.h;
		pos_Y = posRect.y;

		if (direction == 1) // move right and up
		{
			xDir = -1;
			yDir = -1;
		}
		else//move right and down
		{
			xDir = -1;
			yDir = 1;
		}


	}
	else if (location == 3)// top
	{ 
		// off screen on the top
		posRect.y = -posRect.h;
		pos_Y = posRect.y;

		// random from top to bottom
		// number for random up and down
		int sideOfScreen = 1024 - (posRect.w * 2);
		posRect.x = rand() % sideOfScreen + posRect.w;
		pos_X = posRect.x;

		if (direction == 1) // move right and up
		{
			xDir = -1;
			yDir = 1;
		}
		else//move right and down
		{
			xDir = 1;
			yDir = 1;
		}

	}
	else if (location == 4)// bottom
	{
		// off screen on the bootom
		posRect.y = 768;
		pos_Y = posRect.y;

		// random from top to bottom
		// number for random up and down
		int sideOfScreen = 1024 - (posRect.w * 2);
		posRect.x = rand() % sideOfScreen + posRect.w;
		pos_X = posRect.x;

		if (direction == 1) // move right and up
		{
			xDir = -1;
			yDir = -1;
		}
		else//move right and down
		{
			xDir = 1;
			yDir = -1;
		}
	}

}


void AsteroidBig::Update(float deltaTime)
{

	if (active)
	{

		// get large rock's new position
		pos_X += (speed * xDir) * deltaTime;
		pos_Y += (speed * yDir) * deltaTime;

		// adjust for precision loss
		posRect.x = (int)(pos_X + 0.5f);
		posRect.y = (int)(pos_Y + 0.5f);

		rockAngle += .1;

		// WRAPPING ************************************************************
	
		// check to see if the large rock is off the  left of the screen
		if (posRect.x < (0 - posRect.w))
		{
			posRect.x = 1024;
			pos_X = posRect.x;
		}

		// check to see if the large rock is off the right of  the screen
		if (posRect.x >  1024)
		{
			posRect.x = (0 - posRect.w);
			pos_X = posRect.x;
		}

		// check to see if the large rock is off the Top of  the screen
		if (posRect.y < (0 - posRect.h))
		{
			posRect.y = 768;
			pos_Y = posRect.y;
		}

		// check to see if the large rock is off the bottom of  the screen
		if (posRect.y > 768)
		{
			posRect.y = (0 - posRect.h);
			pos_Y = posRect.y;
		}
	
		// WRAPPING ************************************************************


	}

}


void AsteroidBig::Draw(SDL_Renderer* renderer)
{

	SDL_RenderCopyEx(renderer, texture, NULL, &posRect, rockAngle, &rockCenter, SDL_FLIP_NONE);

}
AsteroidBig::~AsteroidBig()
{
	//SDL_DestroyTexture(texture);

}