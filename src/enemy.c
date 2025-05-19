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
	enemy.sprite = new_img(game->rend, "assets/enemy/goblin.png", true);
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
	render_img(game->rend, &enemy->sprite, enemy->entity.x, enemy->entity.y, enemy->entity.w, enemy->entity.h);
	render_weapon(game, &enemy->weapon);
}
