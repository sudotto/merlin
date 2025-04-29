#ifndef BULLET
#define BULLET

#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"

#define MAX_BULLET 5000

// BULLET TYPES

typedef enum {
	LEAF
} Bullet_type;

// BULLET

typedef struct {
	bool init;
	int id;
	Img sprite;
	int x;
	int y;
	int w;
	int h;
	int x_vel;
	int y_vel;
	int angle;
	int age;
	int lifespan;
	bool dead;
	int spd;
	int bounces;
} Bullet;

Bullet new_bullet(Game* game, Bullet* bullets, int x, int y, int w, int h, char* filename, SDL_Color color, int lifespan, int spd, int angle);
void update_bullet(Bullet* bullet, Bullet* bullets);
void render_bullet(Game* game, Bullet* bullet);
void kill_bullet(Bullet* bullet, Bullet* bullets);

// BULLET LIST

void push_bullet(Bullet* bullet, Bullet* bullets);
void pop_bullet(Bullet* bullet, Bullet* bullets);
void update_bullets(Bullet* bullets);
void render_bullets(Game* game, Bullet* bullets);
void print_bullets(Bullet* bullets);
void destroy_bullets(Bullet* bullets);

#endif
