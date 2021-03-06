#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Bullet 
{
public:

	bool active;

	SDL_Texture* texture;

	SDL_Rect posRect;

	float xDir, yDir;

	float speed;

	float pos_X,  pos_Y;

	SDL_Point billetCenter;

	SDL_Rect playerPos;

	SDL_Point playerCenter;

	Bullet(SDL_Renderer* renderer, float x, float y);

	void Resposition();

	void Update(float deltaTime);

	void Draw(SDL_Renderer* renderer);

	~Bullet();

	// WRAPPING **************************************************

	void Deactivate();

};
