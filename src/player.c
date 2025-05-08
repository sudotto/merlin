#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"
#include "bullet.h"
#include "weapon.h"
#include "entity.h"

#include "player.h"

Player new_player(Game* game, char* name, SDL_Color color, int spd){
	Player player;
	player.name = name;
	player.entity = new_entity(10, 10, 8*4, 8*4, 0, 0);
	player.spd = 5;
	Weapon twig = new_weapon(game, INFERNO_WEAPON);
	player.weapon = twig; 

	SDL_Color target = {255, 255, 255};
	player.sprite = new_recolored_img(game->rend, "assets/player/pope.png", target, color);

	return player;
}

void control_player(Game* game, Player* player, Bullet* bullets){
	if(game->keystates[SDL_SCANCODE_W]){
		player->entity.yv = -player->spd;
	}
	if(game->keystates[SDL_SCANCODE_A]){
		player->entity.xv = -player->spd;
	}
	if(game->keystates[SDL_SCANCODE_S]){
		player->entity.yv = player->spd;
	}
	if(game->keystates[SDL_SCANCODE_D]){
		player->entity.xv = player->spd;
	}
	if(game->mousestates & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)){
		use_weapon(game, &player->weapon, bullets);
	}
}

void update_player(Game* game, Player* player){
	player->entity.y += player->entity.yv;
	if(player->entity.yv < 0){
		player->entity.yv += 1;
	} else if(player->entity.yv > 0){
		player->entity.yv -= 1;
	} else {
		player->entity.yv = 0;
	}

	player->entity.x += player->entity.xv;
	if(player->entity.xv < 0){
		player->entity.xv += 1;
	} else if(player->entity.xv > 0){
		player->entity.xv -= 1;
	} else {
		player->entity.xv = 0;
	}
	update_weapon(game, &player->weapon, player->entity);
}

void render_player(Game* game, Player* player){
	render_img(game->rend, &player->sprite, player->entity.x, player->entity.y, player->entity.w, player->entity.h);
	render_weapon(game, &player->weapon);
}
