#ifndef PLAYER
#define PLAYER

#include <stdbool.h>

#include "otto-game.h"

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
} Player;

Player new_player(SDL_Renderer* rend, char* name, SDL_Color color, int spd);
void control_player(Player* player, const bool* keystates);
void update_player(Player* player);
void render_player(SDL_Renderer* rend, Player* player);

#endif
