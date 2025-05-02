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
#include "entity.h"

#include "weapon.h"

void scaled_hyp(float* x_dist, float* y_dist, int x1, int y1, int x2, int y2, int max){
	int dx = x1 - x2;
	int dy = y1 - y2;
	float hyp = sqrt(dy * dy + dx * dx);
	float scale = max / hyp;
	*x_dist = (int)(dx * scale);
	*y_dist = (int)(dy * scale);
}

// WEAPON TYPES

Weapon_data weapon_data_table[9] = {
	{"Twig", "assets/weapon/staff/twig.png",              8,  0.5, 0, 1},
	{"Staff", "assets/weapon/staff/plasma.png",           8,  0.5, 1, 1},
	{"Scepter", "assets/weapon/staff/fireball.png",       8,  0.5, 2, 1},
	{"Wand", "assets/weapon/staff/missle.png",            8,  0.5, 3, 1},
	{"Ohnyalei", "assets/weapon/staff/sigil.png",        16,  0.5, 4, 1},
	{"Tsunami", "assets/weapon/staff/tsunami.png",       16,  0.5, 5, 5},
	{"Inferno", "assets/weapon/staff/inferno.png",       16,  0.5, 6, 3},
	{"Raphael's Staff", "assets/weapon/staff/smite.png", 16,  0.5, 7, 7},
	{"Void Reaver", "assets/weapon/staff/void.png",      16,  0.5, 8, 3}
};

// WEAPON

Weapon new_weapon(Game* game, Weapon_type type){
	Weapon weapon;
	weapon.init = true;
	weapon.data = weapon_data_table[type];
	weapon.entity = new_entity(0, 0, weapon.data.size * 4, weapon.data.size * 4, 0, 0);
	weapon.sprite = new_img(game->rend, weapon.data.filename);
	return weapon;
}

void use_weapon(Game* game, Weapon* weapon, Bullet* bullets){
	if(weapon->atk_cooldown <= 0){
		weapon->atk_cooldown = weapon->data.atk_cooldown_time;
		int dx = weapon->entity.x - game->mouse_x;
		int dy = weapon->entity.y - game->mouse_y;
		float hyp = sqrt(dx*dx + dy*dy);
		float angle = atan2(dy, dx) * (180.0 / M_PI);
		for(int i = -(weapon->data.bullet_count / 2); i < weapon->data.bullet_count - (weapon->data.bullet_count / 2); i++){
			new_bullet(game, bullets, weapon->entity.x, weapon->entity.y, angle+(i*10), weapon->data.bullet_type);
		}
	}
}

void update_weapon(Game* game, Weapon* weapon, int parent_x, int parent_y){
	float dx, dy;
	scaled_hyp(&dx, &dy, game->mouse_x, game->mouse_y, parent_x, parent_y, 50);
	weapon->entity.x = parent_x + dx;
	weapon->entity.y = parent_y + dy;
	if(weapon->atk_cooldown > 0){
		weapon->atk_cooldown -= 1.0f / 60;
	} else {
		weapon->atk_cooldown = 0;
	}
}

void render_weapon(Game* game, Weapon* weapon){
	// WEAPON
	int dx = weapon->entity.x - game->mouse_x;
	int dy = weapon->entity.y - game->mouse_y;
	float hyp = sqrt(dx*dx + dy*dy);
	float angle = atan2(dy, dx) * (180.0 / M_PI);
	render_img_rotated(game->rend, &weapon->sprite, weapon->entity.x, weapon->entity.y, weapon->entity.w, weapon->entity.h, angle - 135);

	// COOLDOWN TIMER

	int scaled = weapon->atk_cooldown * (32 / weapon->data.atk_cooldown_time);
	SDL_FRect rect = {weapon->entity.x, weapon->entity.y + weapon->entity.w + 2, scaled, 10};
	SDL_SetRenderDrawColor(game->rend, 255, 255, 255, 255);
	SDL_RenderFillRect(game->rend, &rect);
}
