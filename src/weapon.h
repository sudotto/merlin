#ifndef WEAPON
#define WEAPON

#include <stdbool.h>

#include "otto-game.h"
#include "entity.h"
#include "bullet.h"
#include "particle.h"

void scaled_hyp(float* x_dist, float* y_dist, float x1, float y1, float x2, int y2, float max);

#define WEAPON_TYPE_COUNT 1

// WEAPON TYPES

typedef enum {
	STAFF_WEAPON,
} Weapon_type;

typedef struct {
	char* name;
	char* filename;
	int size;
	int atk_cooldown_time;
	Bullet_type bullet_type;
	int bullet_count;
	int spread;
} Weapon_data;

extern Weapon_data weapon_data_table[WEAPON_TYPE_COUNT];

// WEAPON

typedef struct {
	bool init;
	int id;
	int atk_cooldown;
	Img sprite;
	Entity entity;
	Weapon_data data;
	int angle;
} Weapon;

Weapon new_weapon(Game* game, Weapon_type type);
void use_weapon(Game* game, Weapon* weapon, Bullet* bullets, Particle* particles);
void update_weapon(Game* game, Weapon* weapon, Entity parent_entity, int target_x, int target_y);
void render_weapon(Game* game, Weapon* weapon);

#endif
