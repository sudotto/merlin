#ifndef BULLET
#define BULLET

#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"
#include "entity.h"

#define MAX_BULLET 256

// BULLET TYPES

typedef enum {
	LEAF
} Bullet_type;

// BULLET

typedef struct {
	bool init;
	int id;
	Img sprite;
	Entity entity;
	int age;
	int lifespan;
	int bounces;
} Bullet;

Bullet new_bullet(Game* game, int x, int y, int w, int h, char* filename, int lifespan, int spd, int angle);
void update_bullet(Bullet* bullet, Bullet* bullets);
void render_bullet(Game* game, Bullet* bullet);
void kill_bullet(Bullet* bullet, Bullet* bullets);

// BULLET LIST

void push_bullet(Bullet bullet, Bullet* bullets);
void pop_bullet(Bullet bullet, Bullet* bullets);
void update_bullets(Bullet* bullets);
void render_bullets(Game* game, Bullet* bullets);
void print_bullets(Bullet* bullets);
void destroy_bullets(Bullet* bullets);

// BULLET TYPES

Bullet new_leaf_bullet(Game* game, int x, int y, int angle);
Bullet new_plasma_bullet(Game* game, int x, int y, int angle);
Bullet new_fireball_bullet(Game* game, int x, int y, int angle);
Bullet new_missle_bullet(Game* game, int x, int y, int angle);
Bullet new_sigil_bullet(Game* game, int x, int y, int angle);
Bullet new_water_bullet(Game* game, int x, int y, int angle);
Bullet new_blaze_bullet(Game* game, int x, int y, int angle);
Bullet new_smite_bullet(Game* game, int x, int y, int angle);
Bullet new_void_bullet(Game* game, int x, int y, int angle);

#endif
