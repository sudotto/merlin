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
#include "bullet.h"
#include "particle.h"
#include "weapon.h"
#include "entity.h"

#include "enemy.h"

Enemy new_enemy(Game* game, char* name, int spd){
	Enemy enemy;
	enemy.name = name;
	enemy.entity = new_entity(300, 300, 8*4, 8*4, 0, 0);
	enemy.spd = 5;
	Weapon twig = new_weapon(game, STAFF_WEAPON);
	enemy.weapon = twig; 

	enemy.facing = DOWN;
	char* dirname = malloc(sizeof(char) * 20);
	strcpy(dirname, "assets/enemy/goblin");
	char* filepath = malloc(sizeof(char) * 30);
	char* filenames[ENEMY_ANIM_COUNT] = {
		"/idle.png",
		"/idle.png",
	};
	for(int anim = 0; anim < ENEMY_ANIM_COUNT; anim++){
		for(int facing = 0; facing < 4; facing++){
			strcpy(filepath, dirname);
			strcat(filepath, filenames[anim]);
			enemy.anims[anim][facing] = new_anim(game->rend, filepath, 4, facing, 16 * 10, 16 * 10, true);
		}
	}
	enemy.anim = ENEMY_IDLE;
	free(dirname);
	free(filepath);
	return enemy;
}

void control_enemy(Game* game, Enemy* enemy, Bullet* bullets, Particle* particles){
}

void update_enemy(Game* game, Enemy* enemy, Player* player, Bullet* bullets, Particle* particles){
	for(int i = 0; i < MAX_BULLET; i++){
		if(!bullets[i].init){
			break;
		} else {
			Rect enemy_rect = {enemy->entity.x, enemy->entity.y, enemy->entity.w, enemy->entity.h};
			Rect bullet_rect = {bullets[i].entity.x, bullets[i].entity.y, bullets[i].entity.w, bullets[i].entity.h};
			if(rect_in_rect(enemy_rect, bullet_rect)){
				printf("HIT\n");
			}
		}
	}
	control_enemy(game, enemy, bullets, particles);

	enemy->anim = ENEMY_IDLE;
	if(enemy->entity.xv != 0 || enemy->entity.yv != 0){
		enemy->anim = ENEMY_WALK;
	}
	if(enemy->entity.xv != 0 || enemy->entity.yv != 0){
		enemy->anim = ENEMY_WALK;
	}

	enemy->entity.y += enemy->entity.yv;
	if(enemy->entity.yv < 0){
		enemy->entity.yv += 1;
	} else if(enemy->entity.yv > 0){
		enemy->entity.yv -= 1;
	} else {
		enemy->entity.yv = 0;
	}

	enemy->entity.x += enemy->entity.xv;
	if(enemy->entity.xv < 0){
		enemy->entity.xv += 1;
	} else if(enemy->entity.xv > 0){
		enemy->entity.xv -= 1;
	} else {
		enemy->entity.xv = 0;
	}
	use_weapon(game, &enemy->weapon, bullets, particles);
	update_weapon(game, &enemy->weapon, enemy->entity, player->entity.x, player->entity.y);
}

void render_enemy(Game* game, Enemy* enemy){
	render_anim(game->rend, &enemy->anims[enemy->anim][enemy->facing], enemy->entity.x, enemy->entity.y, enemy->entity.w, enemy->entity.h, 0.1);
	render_weapon(game, &enemy->weapon);
}
