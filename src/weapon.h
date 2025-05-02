#ifndef WEAPON
#define WEAPON

#include <stdbool.h>

#include "otto-game.h"
#include "entity.h"

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
} Weapon;

Weapon new_weapon(Game* game, Weapon_type type);
void use_weapon(Game* game, Weapon* weapon, Bullet* bullets);
void update_weapon(Game* game, Weapon* weapon, int parent_x, int parent_y);
void render_weapon(Game* game, Weapon* weapon);

// WEAPONS

Weapon new_twig_weapon(Game* game);
Weapon new_staff_weapon(Game* game);
Weapon new_scepter_weapon(Game* game);
Weapon new_wand_weapon(Game* game);
Weapon new_ohnyalei_weapon(Game* game);
Weapon new_trident_weapon(Game* game);
Weapon new_blaze_weapon(Game* game);
Weapon new_raph_weapon(Game* game);
Weapon new_void_weapon(Game* game);

#endif
