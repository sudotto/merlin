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
	*x_dist = dx * scale;
	*y_dist = dy * scale;
}

Weapon new_weapon(Game* game, char* name, char* filename, SDL_Color bullet_color){
	Weapon weapon;
	weapon.init = true;
	weapon.name = name;
	weapon.bullet_spd = 5;
	//weapon.bullet_lifespan = ;
	weapon.bullet_bounces = 0;
	weapon.atk_cooldown = 0;
	weapon.atk_cooldown_time = 0.25;
	weapon.bullet_color = bullet_color;

	weapon.sprite = new_img(game->rend, filename);

	return weapon;
}

void use_weapon(Game* game, Weapon* weapon, Bullet* bullets, int x, int y){
	if(weapon->atk_cooldown <= 0){
		printf("you attacked\n");
		weapon->atk_cooldown = weapon->atk_cooldown_time;
		float x_vel, y_vel;
		scaled_hyp(&x_vel, &y_vel, game->mouse_x, game->mouse_y, x, y, 5);
		new_bullet(game, bullets, x, y, "assets/bullet/ball.png", weapon->bullet_color, x_vel, y_vel, weapon->bullet_spd);
	}
}

void update_weapon(Weapon* weapon){
	if(weapon->atk_cooldown > 0){
		weapon->atk_cooldown -= 1.0f / 60;
	}
}

void render_weapon(Game* game, Weapon* weapon, int x, int y, int w, int h){
	// WEAPON
	float dx = x;
	float dy = y;
	scaled_hyp(&dx, &dy, game->mouse_x, game->mouse_y, x, y, 50);
	render_img(game->rend, &weapon->sprite, x + dx, y + dy, w, h);

	// COOLDOWN TIMER

	int scaled = weapon->atk_cooldown * (32 / weapon->atk_cooldown_time);
	SDL_FRect rect = {x, y + w + 2, scaled, 10};
	SDL_SetRenderDrawColor(game->rend, 255, 255, 255, 255);
	SDL_RenderFillRect(game->rend, &rect);
}
