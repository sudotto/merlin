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
		int dx = weapon->x - game->mouse_x;
		int dy = weapon->y - game->mouse_y;
		float hyp = sqrt(dx*dx + dy*dy);
		float angle = atan2(dy, dx) * (180.0 / M_PI);
		for(int i = -(weapon->bullet_count / 2); i < (weapon->bullet_count / 2); i++){
			Bullet bullet = new_smite_bullet(game, weapon->x, weapon->y, angle + (i*20));
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
	Bullet bullet = new_leaf_bullet(game, 0, 0, 0);
	return new_weapon(game, "Twig", "assets/weapon/staff/twig.png", 8, 8, bullet, 1);
}

Weapon new_staff_weapon(Game* game){
	Bullet bullet = new_plasma_bullet(game, 0, 0, 0);
	return new_weapon(game, "Staff", "assets/weapon/staff/staff.png", 8, 8, bullet, 1);
}

Weapon new_scepter_weapon(Game* game){
	Bullet bullet = new_fireball_bullet(game, 0, 0, 0);
	return new_weapon(game, "Scepter", "assets/weapon/staff/scepter.png", 8, 8, bullet, 1);
}

Weapon new_wand_weapon(Game* game){
	Bullet bullet = new_missle_bullet(game, 0, 0, 0);
	return new_weapon(game, "Wand", "assets/weapon/staff/wand.png", 8, 8, bullet, 1);
}

Weapon new_ohnyalei_weapon(Game* game){
	Bullet bullet = new_sigil_bullet(game, 0, 0, 0);
	return new_weapon(game, "Ohnyalei", "assets/weapon/staff/ohnyalei.png", 16, 16, bullet, 2);
}

Weapon new_trident_weapon(Game* game){
	Bullet bullet = new_water_bullet(game, 0, 0, 0);
	return new_weapon(game, "Trident", "assets/weapon/staff/trident.png", 16, 16, bullet, 3);
}

Weapon new_blaze_weapon(Game* game){
	Bullet bullet = new_blaze_bullet(game, 0, 0, 0);
	return new_weapon(game, "Blaze Bringer", "assets/weapon/staff/blaze.png", 16, 16, bullet, 5);
}

Weapon new_raph_weapon(Game* game){
	Bullet bullet = new_smite_bullet(game, 0, 0, 0);
	return new_weapon(game, "Raphael's Staff", "assets/weapon/staff/raph.png", 16, 16, bullet, 9);
}

Weapon new_void_weapon(Game* game){
	Bullet bullet = new_void_bullet(game, 0, 0, 0);
	return new_weapon(game, "Void Reaver", "assets/weapon/staff/void.png", 16, 16, bullet, 17);
}
