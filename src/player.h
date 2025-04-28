#ifndef PLAYER
#define PLAYER

#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"
#include "bullet.h"


typedef struct {
	char* name;
	Img sprite;
	int x;
	int y;
	int w;
	int h;
	int x_vel;
	int y_vel;
	int spd;
	float atk_cooldown;
	float atk_cooldown_time;
} Player;

Player new_player(Game* game, char* name, SDL_Color color, int spd);
void control_player(Game* game, Player* player, Bullet* bullets);
void update_player(Player* player);
void render_player(Game* game, Player* player);

#endif
