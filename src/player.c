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
#include "particle.h"
#include "weapon.h"
#include "entity.h"

#include "player.h"

Player new_player(Game* game, char* name, SDL_Color color, int spd){
	Player player;
	player.name = name;
	player.entity = new_entity(10, 10, 8*4, 8*4, 0, 0);
	player.spd = 5;
	Weapon twig = new_weapon(game, STAFF_WEAPON);
	player.weapon = twig; 

	player.facing = DOWN;
	char* dirname = malloc(sizeof(char) * 20);
	strcpy(dirname, "assets/wizard");
	char* filepath = malloc(sizeof(char) * 30);
	char* filenames[PLAYER_ANIM_COUNT] = {
		"/idle.png",
		"/walk.png",
	};
	for(int anim = 0; anim < PLAYER_ANIM_COUNT; anim++){
		for(int facing = 0; facing < 4; facing++){
			strcpy(filepath, dirname);
			strcat(filepath, filenames[anim]);
			player.anims[anim][facing] = new_anim(game->rend, filepath, 4, facing, 16 * 10, 16 * 10, true);
		}
	}
	player.anim = PLAYER_IDLE;
	free(dirname);
	free(filepath);
	return player;
}

void control_player(Game* game, Player* player, Bullet* bullets, Particle* particles){
	if(game->keystates[SDL_SCANCODE_W]){
		player->entity.yv = -player->spd;
		player->facing = UP;
	}
	if(game->keystates[SDL_SCANCODE_A]){
		player->entity.xv = -player->spd;
		player->facing = LEFT;
	}
	if(game->keystates[SDL_SCANCODE_S]){
		player->entity.yv = player->spd;
		player->facing = DOWN;
	}
	if(game->keystates[SDL_SCANCODE_D]){
		player->entity.xv = player->spd;
		player->facing = RIGHT;
	}
	if(game->mousestates & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)){
		use_weapon(game, &player->weapon, bullets, particles);
	}

}

void update_player(Game* game, Player* player, Bullet* bullets, Particle* particles){
	control_player(game, player, bullets, particles);

	player->anim = PLAYER_IDLE;
	if(player->entity.xv != 0 || player->entity.yv != 0){
		player->anim = PLAYER_WALK;
	}
	if(player->entity.xv != 0 || player->entity.yv != 0){
		player->anim = PLAYER_WALK;
	}

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
	update_weapon(game, &player->weapon, player->entity, game->mouse_x, game->mouse_y);
}

void render_player(Game* game, Player* player){
	//render_img(game->rend, &player->sprite, player->entity.x, player->entity.y, player->entity.w, player->entity.h);
	render_anim(game->rend, &player->anims[player->anim][player->facing], player->entity.x, player->entity.y, player->entity.w, player->entity.h, 0.1);
	render_weapon(game, &player->weapon);
}
