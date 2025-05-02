#ifndef WEAPON
#define WEAPON

#include <stdbool.h>

#include "otto-game.h"
#include "entity.h"

void scaled_hyp(float* x_dist, float* y_dist, float x1, float y1, float x2, int y2, float max);

// WEAPON TYPES

typedef enum {
	TWIG_WEAPON,
	STAFF_WEAPON,
	SCEPTER_WEAPON,
	WAND_WEAPON,
	OHNYALEI_WEAPON,
	TSUNAMI_WEAPON,
	INFERNO_WEAPON,
	RAPH_WEAPON,
	VOID_WEAPON
} Weapon_type;

typedef struct {
	char* name;
	char* filename;
	int size;
	float atk_cooldown_time;
	Bullet_type bullet_type;
	int bullet_count;
} Weapon_data;

extern Weapon_data weapon_data_table[9];

// WEAPON

typedef struct {
	bool init;
	int id;
	float atk_cooldown;
	Img sprite;
	Entity entity;
	Weapon_data data;
	int angle;
} Weapon;

Weapon new_weapon(Game* game, Weapon_type type);
void use_weapon(Game* game, Weapon* weapon, Bullet* bullets);
void update_weapon(Game* game, Weapon* weapon, Entity parent_entity);
void render_weapon(Game* game, Weapon* weapon);

#endif
