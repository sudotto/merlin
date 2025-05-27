#ifndef PLAYER
#define PLAYER

#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"
#include "bullet.h"
#include "weapon.h"
#include "entity.h"

#define PLAYER_ANIM_COUNT 2

typedef enum {
	IDLE,
	WALK,
} Player_anim;

typedef struct {
	char* name;
	Img sprite;
	Anim anims[PLAYER_ANIM_COUNT][4];
	Player_anim anim;
	Facing facing;
	Entity entity;
	int spd;
	Weapon weapon;
} Player;

Player new_player(Game* game, char* name, SDL_Color color, int spd);
void control_player(Game* game, Player* player, Bullet* bullets, Particle* particles);
void update_player(Game* game, Player* player, Bullet* bullets, Particle* particles);
void render_player(Game* game, Player* player);

#endif
