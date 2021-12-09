#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <iostream>
#include <string>
// Miriam Lira   Level Up
using namespace std;

// boollean to maintain program loop
bool quit = false;

// deltaTime init() - for frame rate ind.
float deltaTime = 0.0f;
int thisTime = 0;
int lastTime = 0;

// vars for player's angle
float x, y, oldAngle;
float playerAngle;

// for precision loss
float pos_X, pos_Y;

// floats for directions 
float xDir, xDirOld;
float yDir, yDirOld;

// player speed 
float playerSpeed = 400.0f;

//Create rectange for the menu graphics
SDL_Rect playerPos;

//Player's center point
SDL_Point center;

// Bullets
#include <vector>
#include "bullet.h"

vector<Bullet> bulletList;

// declare sounds
Mix_Chunk* laser;

void CreateBullet()
{
	for (int i = 0; i < bulletList.size(); i++)
	{
		if (bulletList[i].active == false)
		{
			Mix_PlayChannel(-1, laser, 0);

			bulletList[i].active = true;

			bulletList[i].posRect.x = pos_X;

			bulletList[i].posRect.y = pos_Y;

			bulletList[i].pos_X = pos_X;

			bulletList[i].pos_Y = pos_Y;

			bulletList[i].xDir = xDirOld;

			bulletList[i].yDir = yDirOld;

			bulletList[i].Resposition();

			break;
		}

	}

}

#include <iostream>
#include <cstdlib>
using namespace std;

// large rocks
#include "Asteroid Big.h"
vector<AsteroidBig> AsteroidBigList;

// Small Rocks 
#include "AsteroidSmall.h"
vector<AsteroidSmall> AsteroidSmallList;

// declare sounds
Mix_Chunk* explosion;



int main(int argc, char* argv[])
{
	// seed random numbers
	srand(time(NULL));

	SDL_Window* window; // Declare a pointer

	// Create a render variable
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_EVERYTHING); //Initiakize SDL2

	//create an application window with the following settings:
	window = SDL_CreateWindow
	(
		"Space Rocks",		      // window Title
		SDL_WINDOWPOS_UNDEFINED,  //Initial x position
		SDL_WINDOWPOS_UNDEFINED,  //Initial y position
		1024,					 // width, in pixels
		768,					 // height, in pixels 
		SDL_WINDOW_OPENGL		 // flags - see below
	);

	// Cheack that the window was successfully created 
	if (window == NULL) 
	{
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	// create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// background image -- CREATE
	//Create a SDL surface
	SDL_Surface* surface = IMG_Load("./SpAssets/Background.png");

	//Create background textture
	SDL_Texture* bkgd;

	// place surface into the texture 
	bkgd = SDL_CreateTextureFromSurface(renderer, surface);

	// free the surface
	SDL_FreeSurface(surface);

	// craete rectangles for the menu graghics
	SDL_Rect bkgdPos;

	//set bkgd x, y, width and hight
	bkgdPos.x = 0;
	bkgdPos.y = 0;
	bkgdPos.w = 1024;
	bkgdPos.h = 768;

	// background image --CREATE END

	// player image  -- CREATE

	// create a SDL surface
	surface = IMG_Load("./SpAssets/player.png");

	// craete bkgd texture
	SDL_Texture* player;

	// place surface into the texture
	player = SDL_CreateTextureFromSurface(renderer, surface);

	// free the surface
	SDL_FreeSurface(surface);

	// set bkgdPos x, y, width and height
	playerPos.x = 1024 / 2;
	playerPos.y = 768/ 2;
	playerPos.w = 49;
	playerPos.h = 32;

	// center of the player's sprite
	center.x = playerPos.w / 2;
	center.y = playerPos.h / 2;

	//pos_X and pos_Y for precision loss
	pos_X = playerPos.x;
	pos_Y = playerPos.y;

	// the player graphic is facing right, so the xDirOld is set to 1 so bullets go in correct direction
	xDir = 1;
	xDir = 0;

	// the player graphic is facing right, so the xDirOld is set to 1 so bullets go in correct direction
	xDirOld = 1;
	xDirOld = 0;

	// player image --  CREATE END

	// SDL event to handle input
	SDL_Event event;

	// create our bulletList
	for (int i = 0; i < 10; i++)
	{
		Bullet tempBullet(renderer, -1000.0f, - 1000.0f);

		bulletList.push_back(tempBullet);
	}

	//// create our AsteroidBigList
	//for (int i = 0; i < 1; i++)
	//{
	//	AsteroidBig tempRock(renderer, -1000.0f, -1000.0f);

	//	AsteroidBigList.push_back(tempRock);
	//}


	//// Create  Our AsteroidSmallList
	//for (int i = 0; i < 2; i++)
	//{
	//	AsteroidSmall tempRock(renderer, -1000.0f, -1000.0f);

	//	AsteroidSmallList.push_back(tempRock);
	//}

	// initialize audio playback
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	// Load laser sound
	laser = Mix_LoadWAV("./SpAssets/laser.wav");

	// Load explosion sound
	explosion = Mix_LoadWAV("./SpAssets/explosion.wav");

	// LEVEL UP *********************************************
	// Rocks to start game
	int numberOfLargeRocks = 1;
	int numberOfSmallRocks = 2;

	// total rocks on the level
	int totalNumberOfRocks = numberOfLargeRocks + numberOfSmallRocks;

	// total rocks currently destroyed
	int totalRocksDestroyed = 0;


	// create our AsteroidBigList
	for (int i = 0; i < numberOfLargeRocks; i++)
	{
		AsteroidBig tempRock(renderer, -1000.0f, -1000.0f);

		AsteroidBigList.push_back(tempRock);
	}


	// Create  Our AsteroidSmallList
	for (int i = 0; i < numberOfSmallRocks; i++)
	{
		AsteroidSmall tempRock(renderer, -1000.0f, -1000.0f);

		AsteroidSmallList.push_back(tempRock);
	}

	// active all large rocks for level 1 
	for (int i = 0; i < numberOfLargeRocks; i++)
	{
		AsteroidBigList[i].Reposition();

	}

	// Basic programm loop
	while (!quit)
	{
		// create deltaTime
		thisTime = SDL_GetTicks();
		deltaTime = (float)(thisTime - lastTime) / 1000;
		lastTime = thisTime;

		// Cheak for input for closing Window and firing
		if (SDL_PollEvent(&event))
		{

			// Close window by the window's Xbutton
			if (event.type == SDL_QUIT) 
			{
				quit = true;
			}
			switch (event.type)
			{
				// look for a keypress and release
				case SDL_KEYUP:

					// Check the SDLKey values
					switch (event.key.keysym.sym)
					{
						case SDLK_SPACE:
							CreateBullet();
							break;

						//case SDLK_z:
						//	AsteroidBigList[0].Reposition(); // calling Asteroid Big.cpp
						//	break;

						//case SDLK_s:

						//	for (int i = 0; i < 2; i++)
						//	{
						//		if (AsteroidSmallList[i].active == false)
						//		{
						//			AsteroidSmallList[i].Reposition(AsteroidBigList[0].posRect.x, AsteroidBigList[0].posRect.y);
						//		}
						//	}

						//	// clear large rock
						//	AsteroidBigList.clear();

						//	break;

						//case SDLK_a:

						//	// clear large rock
						//	AsteroidBigList.clear();

						//	// clear Small
						//	AsteroidSmallList.clear();

						//	for (int i = 0; i < 1; i++)
						//	{
						//		AsteroidBig tempRock(renderer, -1000.0f, -1000.0f);

						//		AsteroidBigList.push_back(tempRock);
						//	}

						//	for (int i = 0; i < 2; i++)
						//	{
						//		AsteroidSmall tempRock(renderer, -1000.0f, -1000.0f);

						//		AsteroidSmallList.push_back(tempRock);
						//	}

						//	
						//	break;

						default:
							break;
					}
			}

		}

		// player Movement
		// get the Keyboard state
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

		// check which arrows are pressed for xDir
		if (currentKeyStates[SDL_SCANCODE_LEFT])
		{
			// if left button pressed, set xDir to -1
			xDir = -1.0f;
		}
		else if (currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			// if right button pressed, set xDir to 1
			xDir = 1.0f;
		}
		else
		{
		// if neither pressed, no X movement
			xDir = 0.0f;
		}

		// Check which arrows are pressed for xDir UP and Down arrows
		if (currentKeyStates[SDL_SCANCODE_UP])
		{
			// if UP button pressed, set yDir to -1
			yDir = -1.0f;
		}
		else if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
			// if DOWN button pressed, set yDir to 1
			yDir = 1.0f;
		}
		else
		{
			// if neither pressed, no Y movement
			yDir = 0.0f;
		}

		// STARD UPDAE *********************************************

		//player update if move
		if (xDir != 0 || yDir != 0)
		{
			// get X and Y
			x = playerPos.x - xDir;
			y = playerPos.y - yDir;

			// calculate angle
			playerAngle = atan2(yDir, xDir) * 180 / 3.14;

			// uodate Old Angle
			oldAngle = playerAngle;

			// update old direction
			xDirOld = xDir;
			yDirOld = yDir;
		}
		else
		{
			// update old angle
			oldAngle = playerAngle;
		}

		// get player's new position
		pos_X += (playerSpeed * xDir) * deltaTime;
		pos_Y += (playerSpeed * yDir) * deltaTime;

		// adjust for precision loss
		playerPos.x = (int)(pos_X + 0.5f);
		playerPos.y = (int)(pos_Y + 0.5f);

		// player wrapping
		// check to see if the player is off the left of the screen
		if (playerPos.x < (0 - playerPos.w))
		{
			playerPos.x = 1024;
			pos_X = playerPos.x;
		}

		// check to see if the player is off the right of the screen
		if (playerPos.x > 1024)
		{
			playerPos.x = (0 - playerPos.w);
			pos_X = playerPos.x;
		}

		// check to see if the player is off the top of the screen
		if (playerPos.y < (0 - playerPos.w))
		{
			playerPos.y = 768;
			pos_Y = playerPos.y;
		}

		// check to see if the player is off the bottom of the screen
		if (playerPos.y > 768)
		{
			playerPos.y = (0 - playerPos.w);
			pos_Y = playerPos.y;
		}


		// Update bullets in bulletList

		for (int i = 0; i < bulletList.size(); i++)
		{
			if (bulletList[i].active == true)
			{
				bulletList[i].Update(deltaTime);
			}
		}

		// Update AsteroidBig

		for (int i = 0; i < AsteroidBigList.size(); i++) 
		{
			if (AsteroidBigList[i].active == true)
			{
				AsteroidBigList[i].Update(deltaTime);
			}
		}

		// Update Asteroid Small
		for (int i = 0; i < AsteroidSmallList.size(); i++)
		{
			if (AsteroidSmallList[i].active == true)
			{
				AsteroidSmallList[i].Update(deltaTime);
			}
		}


		//WRAPPING (COLLISION DETECTION) *************************************************


		// Check for collision of bullets with large rocks
		// for loop to scroll through all the player's bullets
		for (int i = 0; i < bulletList.size(); i++)
		{

			// check to see if this bullet is active in the world
			if (bulletList[i].active == true)
			{

				// check all large rocks against active bullet
				for (int j = 0; j < AsteroidBigList.size(); j++)
				{
					// see if there is a collision between this bullet and this enemy using SDL
					if (SDL_HasIntersection(&bulletList[i].posRect, &AsteroidBigList[j].posRect))
					{
						// play explosion sound
						Mix_PlayChannel(-1, explosion, 0);

						// LEVEL UP *******************************
						// need two small rocks that are false as the number of small rocks grows
						int AsteroidSmallCounter = 0;


						//create 2 small rocks
						for (int i = 0; i < AsteroidSmallList.size(); i++)
						{
							if (AsteroidSmallList[i].active == false)
							{
								AsteroidSmallList[i].Reposition(AsteroidBigList[j].posRect.x, AsteroidBigList[j].posRect.y);

								// increase AsteroidSmallCounter
								AsteroidSmallCounter++;
							}

							// once we find 2 inactive rocks, exit loop
							if (AsteroidSmallCounter == 2)
							{
								break;
							}
						}

						// rest the enemy
						AsteroidBigList[j].Deactivate();

						// rest the bullet
						bulletList[i].Deactivate();

						// LEVEL UP  ********************************************

						totalRocksDestroyed++;
					}
				}
			}
		}



		// Check for collision of bullets with lSMAll rocks
		// for loop to scroll through all the player's bullets
		for (int i = 0; i < bulletList.size(); i++)
		{
			// check to see if this bullet is active in the world
			if (bulletList[i].active == true)
			{

				// check all large rocks against active bullet
				for (int j = 0; j < AsteroidSmallList.size(); j++)
				{
					// see if there is a collision between this bullet and this enemy using SDL
					if (SDL_HasIntersection(&bulletList[i].posRect, &AsteroidSmallList[j].posRect))
					{

						// play explosion sound
						Mix_PlayChannel(-1, explosion, 0);

						// rest the enemy
						AsteroidSmallList[j].Deactivate();

						// rest the bullet
						bulletList[i].Deactivate();

						// LEVEL UP  ********************************************
						// add one to total destroyed
						totalRocksDestroyed++;

						// cheak to see if all rocks on the level destroy
						if (totalRocksDestroyed >= totalNumberOfRocks)
						{
							// zero out total rocks destroyed
							totalRocksDestroyed = 0;

							// add rocks to level
							numberOfLargeRocks++; // add one large rock
							numberOfSmallRocks += 2; // add 2 small rocks

							totalNumberOfRocks = numberOfLargeRocks + numberOfSmallRocks;

							// clear large rock List
							AsteroidBigList.clear();

							// clear small rock list
							AsteroidSmallList.clear();

							// load large rocks
							for (int i = 0; i < numberOfLargeRocks; i++)
							{
								AsteroidBig tempRock(renderer, -1000.0f, -1000.0f);

								AsteroidBigList.push_back(tempRock);
							}

							// Load Small rocks
							for (int i = 0; i < numberOfSmallRocks; i++)
							{
								AsteroidSmall tempRock(renderer, -1000.0f, -1000.0f);

								AsteroidSmallList.push_back(tempRock);
							}

							// activate all large rocks for next level
							for (int i = 0; i < numberOfLargeRocks; i++)
							{
								AsteroidBigList[i].Reposition();
							}
						}
					}
				}

			}

		}


		//WRAPPING (COLLISION DETECTION) *************************************************

		// END STARD UPDATE *********************************************

		// START DRAW **********************************************

		//Draw Section 
		//clear the old buffer
		SDL_RenderClear(renderer);

		// draw bkgd
		SDL_RenderCopy(renderer, bkgd, NULL, &bkgdPos);

		// Draw bullets in bulletList
		for (int i = 0; i < bulletList.size(); i++)
		{
			if (bulletList[i].active == true)
			{
				bulletList[i].Draw(renderer);
			}
		}

		// draw Asteroid Bigs
		for (int i = 0; i < AsteroidBigList.size(); i++)
		{
			if (AsteroidBigList[i].active == true)
			{
				AsteroidBigList[i].Draw(renderer);
			}
		}

		// Draw Asteroid Small
		for (int i = 0; i < AsteroidSmallList.size(); i++)
		{
			if (AsteroidSmallList[i].active == true)
			{
				AsteroidSmallList[i].Draw(renderer);
			}
		}

		//draw player
		SDL_RenderCopyEx(renderer, player, NULL, &playerPos, playerAngle, &center, SDL_FLIP_NONE);

		//draw new info to the screen
		SDL_RenderPresent(renderer);

		//END DRAW **************************************************

	} // END Game Loop


	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();






	return 0;

}