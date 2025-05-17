#ifndef BULLET
#define BULLET

#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"
#include "entity.h"

#define BULLET_TYPE_COUNT 10
#define MAX_BULLET 256

// BULLET TYPES

typedef enum {
	LEAF_BULLET,
	BULLET_BULLET,
	PLASMA_BULLET,
	FIREBALL_BULLET,
	MISSILE_BULLET,
	SIGIL_BULLET,
	WATER_BULLET,
	BLAZE_BULLET,
	SMITE_BULLET,
	VOID_BULLET 
} Bullet_type;

typedef struct {
	char* filename;
	int size;
	int spd;
	int lifespan;
	int bounces;
} Bullet_data;

extern Bullet_data bullet_data_table[BULLET_TYPE_COUNT];

// BULLET

typedef struct {
	bool init;
	int id;
	int age;
	int angle;
	Img sprite;
	Entity entity;
	Bullet_data data;
} Bullet;

Bullet new_bullet(Game* game, Bullet* bullets, int x, int y, int angle, Bullet_type type);
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

#endif
