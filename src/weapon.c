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
#include "particle.h"
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

Weapon_data weapon_data_table[WEAPON_TYPE_COUNT] = {
	{"Staff", "assets/weapon/staff.png", 8, 20, DEFAULT_BULLET, 1, 1},
};

// WEAPON

Weapon new_weapon(Game* game, Weapon_type type){
	Weapon weapon;
	weapon.init = true;
	weapon.data = weapon_data_table[type];
	weapon.entity = new_entity(0, 0, weapon.data.size * 4, weapon.data.size * 4, 0, 0);
	weapon.sprite = new_img(game->rend, weapon.data.filename, true);
	weapon.atk_cooldown = 0;
	return weapon;
}

void use_weapon(Game* game, Weapon* weapon, Bullet* bullets, Particle* particles){
	if(weapon->atk_cooldown <= 0){
		weapon->atk_cooldown = weapon->data.atk_cooldown_time;
		for(int i = -(weapon->data.bullet_count / 2); i < weapon->data.bullet_count - (weapon->data.bullet_count / 2); i++){
			new_bullet(game, bullets, weapon->entity.x, weapon->entity.y, weapon->angle+(i*weapon->data.spread), weapon->data.bullet_type);
		}
		for(int i = 0; i < 4; i++){
			new_particle(game, particles, weapon->entity.x, weapon->entity.y, weapon->angle+(i*360/4), SPARKLE_PARTICLE);
		}
	}
}

void update_weapon(Game* game, Weapon* weapon, Entity parent, int target_x, int target_y){
	Entity target_entity = new_entity(target_x, target_y, 0, 0, 0, 0);
	clamp_entity(&weapon->entity, parent, target_entity, (float)weapon->entity.w * 0.9);
	float dx = (int)parent.x - target_x;
	float dy = (int)parent.y - target_y;
	float hyp = sqrt(dx*dx + dy*dy);
	double angle_rad = atan2(dy, dx);
	int angle_deg = (int)(angle_rad * 180.0 / M_PI);
	weapon->angle = angle_deg;
	if(weapon->atk_cooldown > 0){
		weapon->atk_cooldown -= 1;
	} else {
		weapon->atk_cooldown = 0;
	}
}

void render_weapon(Game* game, Weapon* weapon){
	// WEAPON
	int flipped = 0;
	int angle = weapon->angle - 135;
	if(weapon->angle < 90 && weapon->angle > -90){
		flipped = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
		angle = weapon->angle - 45;
	}
	rotate_img(&weapon->sprite, angle);
	flip_img(&weapon->sprite, flipped);
	render_img(game->rend, &weapon->sprite, weapon->entity.x, weapon->entity.y, weapon->entity.w, weapon->entity.h);

	// COOLDOWN TIMER

	if(weapon->atk_cooldown){
		render_bar(game->rend, weapon->atk_cooldown, weapon->data.atk_cooldown_time, weapon->entity.x, weapon->entity.y + 32 + 2, 32, 10);
	}
}
