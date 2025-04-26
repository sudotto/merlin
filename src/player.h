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
} Player;

Player new_player(SDL_Renderer* rend, char* name, int spd);
void control_player(Player* player, const bool* keystates);
void move_player(Player* player);
void render_player(SDL_Renderer* rend, Player* player);

#endif
