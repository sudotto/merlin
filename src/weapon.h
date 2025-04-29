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
	int x;
	int y;
	int w;
	int h;
	int bullet_spd;
	int bullet_lifespan;
	int bullet_bounces;
	int bullet_count;
	SDL_Color bullet_color;
	float atk_cooldown;
	float atk_cooldown_time;
} Weapon;

void scaled_hyp(float* x_dist, float* y_dist, int x1, int y1, int x2, int y2, int max);
Weapon new_weapon(Game* game, char* name, char* filename, int w, int h, SDL_Color bullet_color);
void use_weapon(Game* game, Weapon* weapon, Bullet* bullets);
void update_weapon(Game* game, Weapon* weapon, int parent_x, int parent_y);
void render_weapon(Game* game, Weapon* weapon);

#endif
