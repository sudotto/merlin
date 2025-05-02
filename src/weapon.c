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

// Figure out why you didn't add angles to entities, put scaled_hyp into entities

void scaled_hyp(float* x_dist, float* y_dist, float x1, float y1, float x2, int y2, float max){
	float dx = x2 - x1;
	float dy = y2 - y1;
	float hyp = sqrtf(dx * dx + dy * dy);
	float scale = max / hyp;
	*x_dist = (dx * scale);
	*y_dist = (dy * scale);
}

void center_entity(Entity e1, Entity* e2) {
	int center_x = e1.x + e1.w / 2;
	int center_y = e1.y + e1.h / 2;
	e2->x = center_x - e2->w / 2;
	e2->y = center_y - e2->h / 2;
}

// WEAPON TYPES

Weapon_data weapon_data_table[9] = {
	{"Twig", "assets/weapon/staff/twig.png",              8,  0.5, 0, 1},
	{"Staff", "assets/weapon/staff/staff.png",            8,  0.5, 1, 1},
	{"Scepter", "assets/weapon/staff/scepter.png",        8,  0.5, 2, 1},
	{"Wand", "assets/weapon/staff/wand.png",              8,  0.5, 3, 1},
	{"Ohnyalei", "assets/weapon/staff/ohnyalei.png",     16,  0.5, 4, 1},
	{"Tsunami", "assets/weapon/staff/tsunami.png",       16,  0.5, 5, 5},
	{"Inferno", "assets/weapon/staff/inferno.png",       16,  0.5, 6, 3},
	{"Raphael's Staff", "assets/weapon/staff/raph.png",  16,  0.5, 7, 7},
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
		for(int i = -(weapon->data.bullet_count / 2); i < weapon->data.bullet_count - (weapon->data.bullet_count / 2); i++){
			new_bullet(game, bullets, weapon->entity.x, weapon->entity.y, weapon->angle+(i*10), weapon->data.bullet_type);
		}
	}
}

void update_weapon(Game* game, Weapon* weapon, Entity parent){
	float dx, dy; 
	scaled_hyp(&dx, &dy, (float)game->mouse_x, (float)game->mouse_y, parent.x, parent.y, (float)weapon->entity.w);
	center_entity(parent, &weapon->entity);
	weapon->entity.x -= dx;
	weapon->entity.y -= dy;

	dx = (int)parent.x - game->mouse_x;
	dy = (int)parent.y - game->mouse_y;
	float hyp = sqrt(dx*dx + dy*dy);
	weapon->angle = atan2(dy, dx) * (180.0 / M_PI);
	if(weapon->atk_cooldown > 0){
		weapon->atk_cooldown -= 1.0f / 60;
	} else {
		weapon->atk_cooldown = 0;
	}
}

void render_weapon(Game* game, Weapon* weapon){
	// WEAPON
	render_img_rotated(game->rend, &weapon->sprite, weapon->entity.x, weapon->entity.y, weapon->entity.w, weapon->entity.h, weapon->angle - 135);

	// COOLDOWN TIMER

	int scaled = weapon->atk_cooldown * (32 / weapon->data.atk_cooldown_time);
	SDL_FRect rect = {weapon->entity.x, weapon->entity.y + weapon->entity.w + 2, scaled, 10};
	SDL_SetRenderDrawColor(game->rend, 255, 255, 255, 255);
	SDL_RenderFillRect(game->rend, &rect);
}
