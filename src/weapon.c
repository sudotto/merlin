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

void center_entity(Entity* entity, Entity origin) {
	int center_x = origin.x + origin.w / 2;
	int center_y = origin.y + origin.h / 2;
	entity->x = center_x - entity->w / 2;
	entity->y = center_y - entity->h / 2;
}

void clamp_entity(Entity* entity, Entity origin, Entity target, float dist){
	float dx = origin.x - target.x;
	float dy = origin.y - target.y;
	float hyp = sqrtf(dx * dx + dy * dy);
	float scale = dist / hyp;
	center_entity(entity, origin);
	entity->x -= (dx * scale);
	entity->y -= (dy * scale);
}

// WEAPON TYPES

Weapon_data weapon_data_table[9] = {
	{"Twig", "assets/weapon/staff/twig.png",              8,  0.5, 0, 1},
	{"Staff", "assets/weapon/staff/staff.png",            8,  0.5, 1, 1},
	{"Scepter", "assets/weapon/staff/scepter.png",        8,  0.7, 2, 1},
	{"Wand", "assets/weapon/staff/wand.png",              8,  0.3, 3, 1},
	{"Ohnyalei", "assets/weapon/staff/ohnyalei.png",     16,  0.6, 4, 3},
	{"Tsunami", "assets/weapon/staff/tsunami.png",       16,  0.4, 5, 7},
	{"Inferno", "assets/weapon/staff/inferno.png",       16,  0.5, 6, 7},
	{"Raphael's Staff", "assets/weapon/staff/raph.png",  16,  0.7, 7, 7},
	{"Void Reaver", "assets/weapon/staff/void.png",      16,  0.5, 8, 5}
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
	Entity mouse_entity = new_entity(game->mouse_x, game->mouse_y, 0, 0, 0, 0);
	clamp_entity(&weapon->entity, parent, mouse_entity, (float)weapon->entity.w * 0.9);

	float dx = (int)parent.x - game->mouse_x;
	float dy = (int)parent.y - game->mouse_y;
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

	if(weapon->atk_cooldown){
		int scaled = weapon->data.atk_cooldown_time * (32 / weapon->data.atk_cooldown_time);
		SDL_FRect empty = {weapon->entity.x, weapon->entity.y + weapon->entity.w + 2, scaled, 10};
		SDL_SetRenderDrawColor(game->rend, 0, 0, 0, 255);
		SDL_RenderFillRect(game->rend, &empty);

		scaled = weapon->atk_cooldown * (32 / weapon->data.atk_cooldown_time);
		SDL_FRect time = {weapon->entity.x, weapon->entity.y + weapon->entity.w + 2, scaled, 10};
		SDL_SetRenderDrawColor(game->rend, 255, 0, 0, 255);
		SDL_RenderFillRect(game->rend, &time);
	}
}
