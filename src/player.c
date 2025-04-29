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

#include "player.h"

Player new_player(Game* game, char* name, SDL_Color color, int spd){
	Player player;
	player.name = name;
	player.x = 10;
	player.y = 10;
	player.w = 8 * 4;
	player.h = 8 * 4;
	player.x_vel = 0;
	player.y_vel = 0;
	player.spd = 5;
	player.weapon = new_weapon(game, "Twig", "assets/weapon/twig.png",  8 * 4, 8 * 4, color);

	SDL_Color target = {255, 255, 255};
	player.sprite = new_recolored_img(game->rend, "assets/player/sprite.png", target, color);

	return player;
}

void control_player(Game* game, Player* player, Bullet* bullets){
	if(game->keystates[SDL_SCANCODE_W]){
		player->y_vel = -player->spd;
	}
	if(game->keystates[SDL_SCANCODE_A]){
		player->x_vel = -player->spd;
	}
	if(game->keystates[SDL_SCANCODE_S]){
		player->y_vel = player->spd;
	}
	if(game->keystates[SDL_SCANCODE_D]){
		player->x_vel = player->spd;
	}
	if(game->mousestates & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)){
		/*if(player->atk_cooldown <= 0){
			printf("you attacked\n");
			player->atk_cooldown = player->atk_cooldown_time;
			int spd = 5;
			int dx = game->mouse_x - player->x;
			int dy = game->mouse_y - player->y;
			float hyp = sqrt(dy * dy + dx * dx);
			float scale = spd / hyp;
			float x_vel = dx * scale;
			float y_vel = dy * scale;
			SDL_Color projectile_color = {0, 255, 0};
			new_bullet(game, bullets, player->x, player->y, "assets/bullet/ball.png", projectile_color, x_vel, y_vel, spd);
		}*/
		use_weapon(game, &player->weapon, bullets);
	}
}

void update_player(Game* game, Player* player){
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
	update_weapon(game, &player->weapon, player->x, player->y);
}

void render_player(Game* game, Player* player){
	render_img(game->rend, &player->sprite, player->x, player->y, player->w, player->h);
	render_weapon(game, &player->weapon);
}
