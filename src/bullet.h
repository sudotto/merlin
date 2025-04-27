#ifndef BULLET
#define BULLET

#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"

typedef struct {
	Img sprite;
	int x;
	int y;
	int w;
	int h;
	int x_vel;
	int y_vel;
	int spd;
	int age;
	int lifespan;
	bool dead;
} Bullet;

Bullet new_bullet(SDL_Renderer* rend, int x, int y, char* filename, SDL_Color color, int spd);
void update_bullet(Bullet* bullet);
void render_bullet(SDL_Renderer* rend, Bullet* bullet);

#endif
