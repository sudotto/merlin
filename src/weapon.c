#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"
#include "bullet.h"

#include "weapon.h"

void scaled_hyp(float* x_dist, float* y_dist, int x1, int y1, int x2, int y2, int max){
	int dx = x1 - x2;
	int dy = y1 - y2;
	float hyp = sqrt(dy * dy + dx * dx);
	float scale = max / hyp;
	*x_dist = (int)(dx * scale);
	*y_dist = (int)(dy * scale);
}

Weapon new_weapon(Game* game, char* name, char* filename, int w, int h, Bullet bullet, int bullet_count){
	Weapon weapon;
	weapon.init = true;
	weapon.name = name;
	weapon.x = 0;
	weapon.y = 0;
	weapon.w = w * 4;
	weapon.h = h * 4;
	weapon.atk_cooldown = 0;
	weapon.atk_cooldown_time = 0.5;
	weapon.sprite = new_img(game->rend, filename);

	weapon.bullet_spd = bullet.spd;
	weapon.bullet_lifespan = bullet.lifespan;
	weapon.bullet_bounces = bullet.bounces;
	weapon.bullet_count = bullet_count;

	return weapon;
}

void use_weapon(Game* game, Weapon* weapon, Bullet* bullets){
	if(weapon->atk_cooldown <= 0){
		weapon->atk_cooldown = weapon->atk_cooldown_time;
		//float x_vel, y_vel;
		//scaled_hyp(&x_vel, &y_vel, game->mouse_x, game->mouse_y, weapon->x, weapon->y, weapon->bullet_spd);
		int dx = weapon->x - game->mouse_x;
		int dy = weapon->y - game->mouse_y;
		float hyp = sqrt(dx*dx + dy*dy);
		float angle = atan2(dy, dx) * (180.0 / M_PI);
		for(int i = 0; i < (int)ceil((float)weapon->bullet_count / 2); i++){
			Bullet bullet = new_leaf_bullet(game, weapon->x, weapon->y, angle + (i*2));
			push_bullet(bullet, bullets);
		}
		for(int i = 0; i < (int)floor((float)weapon->bullet_count / 2); i++){
			Bullet bullet = new_leaf_bullet(game, weapon->x, weapon->y, angle + (i*2));
			push_bullet(bullet, bullets);
		}
	}
}

void update_weapon(Game* game, Weapon* weapon, int parent_x, int parent_y){
	float dx, dy;
	scaled_hyp(&dx, &dy, game->mouse_x, game->mouse_y, parent_x, parent_y, 20);
	weapon->x = parent_x + dx;
	weapon->y = parent_y + dy;
	if(weapon->atk_cooldown > 0){
		weapon->atk_cooldown -= 1.0f / 60;
	} else {
		weapon->atk_cooldown = 0;
	}
}

void render_weapon(Game* game, Weapon* weapon){
	// WEAPON
	int dx = weapon->x - game->mouse_x;
	int dy = weapon->y - game->mouse_y;
	float hyp = sqrt(dx*dx + dy*dy);
	float angle = atan2(dy, dx) * (180.0 / M_PI);
	render_img_rotated(game->rend, &weapon->sprite, weapon->x, weapon->y, weapon->w, weapon->h, angle - 135);

	// COOLDOWN TIMER

	int scaled = weapon->atk_cooldown * (32 / weapon->atk_cooldown_time);
	SDL_FRect rect = {weapon->x, weapon->y + weapon->w + 2, scaled, 10};
	SDL_SetRenderDrawColor(game->rend, 255, 255, 255, 255);
	SDL_RenderFillRect(game->rend, &rect);
}

// WEAPONS

Weapon new_twig_weapon(Game* game){
	Bullet leaf = new_leaf_bullet(game, 0, 0, 0);
	return new_weapon(game, "Twig", "assets/weapon/twig.png", 8, 8, leaf, 1);
}

