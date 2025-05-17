#ifndef ENEMY 
#define ENEMY 

#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"
#include "bullet.h"
#include "weapon.h"
#include "entity.h"

typedef struct {
	char* name;
	Img sprite;
	Entity entity;
	int spd;
	Weapon weapon;
} Enemy;

Enemy new_enemy(Game* game, char* name, int spd);
void control_enemy(Game* game, Enemy* enemy, Bullet* bullets, Particle* particles);
void update_enemy(Game* game, Enemy* enemy, Player* player, Bullet* bullets, Particle* particles);
void render_enemy(Game* game, Enemy* enemy);

#endif

