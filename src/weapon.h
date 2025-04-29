#ifndef WEAPON
#define WEAPON

#include <stdbool.h>

#include "otto-game.h"

// WEAPON

typedef struct {
	bool init;
	int id;
	char* name;
	Img sprite;
	int bullet_spd;
	int bullet_lifespan;
	int bullet_bounces;
	SDL_Color bullet_color;
	float atk_cooldown;
	float atk_cooldown_time;
} Weapon;

Weapon new_weapon(Game* game, char* name, char* filename, SDL_Color bullet_color);
void use_weapon(Game* game, Weapon* weapon, Bullet* bullets, int x, int y);
void update_weapon(Weapon* weapon);
void render_weapon(Game* game, Weapon* weapon, int x, int y, int w, int h);

#endif
