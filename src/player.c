#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"

#include "player.h"

Player new_player(SDL_Renderer* rend, char* name, SDL_Color color, int spd){
	Player player;
	player.name = name;
	player.x = 10;
	player.y = 10;
	player.w = 8 * 4;
	player.h = 8 * 4;
	player.x_vel = 0;
	player.y_vel = 0;
	player.spd = 5;
	player.atk_cooldown = 0;

	SDL_Color target = {255, 255, 255};
	player.sprite = new_recolored_img(rend, "assets/player/sprite.png", target, color);

	return player;
}

void control_player(Player* player, const bool* keystates){
	if(keystates[SDL_SCANCODE_W]){
		player->y_vel = -player->spd;
	}
	if(keystates[SDL_SCANCODE_A]){
		player->x_vel = -player->spd;
	}
	if(keystates[SDL_SCANCODE_S]){
		player->y_vel = player->spd;
	}
	if(keystates[SDL_SCANCODE_D]){
		player->x_vel = player->spd;
	}
	if(keystates[SDL_SCANCODE_SPACE]){
		if(player->atk_cooldown <= 0){
			printf("you attacked\n");
			player->atk_cooldown = 1;
		}
	}
}

void update_player(Player* player){
	if(player->atk_cooldown > 0){
		player->atk_cooldown -= 1.0f / 60;
	}

	player->y += player->y_vel;
	if(player->y_vel < 0){
		player->y_vel += 1;
	} else if(player->y_vel > 0){
		player->y_vel -= 1;
	} else {
		player->y_vel = 0;
	}

	player->x += player->x_vel;
	if(player->x_vel < 0){
		player->x_vel += 1;
	} else if(player->x_vel > 0){
		player->x_vel -= 1;
	} else {
		player->x_vel = 0;
	}
}

void render_player(SDL_Renderer* rend, Player* player){
	render_img(rend, &player->sprite, player->x, player->y, player->w, player->h);
	int scaled = player->atk_cooldown * (32 / 1);
	SDL_FRect rect = {player->x, player->y + player->w + 2, scaled, 10};
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	SDL_RenderFillRect(rend, &rect);
}
