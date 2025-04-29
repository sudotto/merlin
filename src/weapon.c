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

Weapon new_weapon(Game* game, char* name, char* filename, int w, int h, SDL_Color bullet_color){
	Weapon weapon;
	weapon.init = true;
	weapon.name = name;
	weapon.x = 0;
	weapon.y = 0;
	weapon.w = w;
	weapon.h = h;
	
	weapon.bullet_spd = 10;
	weapon.bullet_lifespan = 1;
	weapon.bullet_bounces = 0;
	weapon.bullet_count = 10;
	weapon.atk_cooldown = 0;
	weapon.atk_cooldown_time = 0.1;
	weapon.bullet_color = bullet_color;

	weapon.sprite = new_img(game->rend, filename);

	return weapon;
}

void use_weapon(Game* game, Weapon* weapon, Bullet* bullets){
	if(weapon->atk_cooldown <= 0){
		weapon->atk_cooldown = weapon->atk_cooldown_time;
		float x_vel, y_vel;
		scaled_hyp(&x_vel, &y_vel, game->mouse_x, game->mouse_y, weapon->x, weapon->y, weapon->bullet_spd);
		for(int i = 0; i < weapon->bullet_count; i++){
			new_bullet(
				game, bullets,
				weapon->x, weapon->y,
				4, 4,
				"assets/bullet/leaf.png",
				weapon->bullet_color,
				weapon->bullet_lifespan,
				x_vel + i, y_vel + i,
				weapon->bullet_spd
			);
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
	render_img(game->rend, &weapon->sprite, weapon->x, weapon->y, weapon->w, weapon->h);

	// COOLDOWN TIMER

	int scaled = weapon->atk_cooldown * (32 / weapon->atk_cooldown_time);
	SDL_FRect rect = {weapon->x, weapon->y + weapon->w + 2, scaled, 10};
	SDL_SetRenderDrawColor(game->rend, 255, 255, 255, 255);
	SDL_RenderFillRect(game->rend, &rect);
}
