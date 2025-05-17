#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"
#include "entity.h"

#include "bullet.h"

// BULLET TYPES

Bullet_data bullet_data_table[BULLET_TYPE_COUNT] = {
	{"assets/bullet/magic/leaf.png",     4 * 4, 10, 60, 0},
	{"assets/bullet/range/bullet.png",   4 * 4, 10, 60, 0},
	{"assets/bullet/magic/plasma.png",   4 * 4, 20, 60, 1},
	{"assets/bullet/magic/fireball.png", 4 * 4, 20, 60, 0},
	{"assets/bullet/magic/missle.png",   4 * 4, 20, 60, 0},
	{"assets/bullet/magic/sigil.png",    8 * 4, 30, 60, 2},
	{"assets/bullet/magic/water.png",    8 * 4, 10, 60, 2},
	{"assets/bullet/magic/blaze.png",    8 * 4, 30, 60, 0},
	{"assets/bullet/magic/smite.png",    8 * 4, 40, 60, 0},
	{"assets/bullet/magic/void.png",     8 * 4, 20, 60, 3}
};

// BULLET

Bullet new_bullet(Game* game, Bullet* bullets, int x, int y, int angle, Bullet_type type){
	Bullet bullet;
	bullet.init = true;
	bullet.age = 0;
	bullet.angle = angle;

	bullet.data = bullet_data_table[type];
	bullet.sprite = new_img(game->rend, bullet.data.filename, true);

	float radians = angle * (M_PI / 180.0);
	bullet.entity = new_entity(x, y, bullet.data.size, bullet.data.size, bullet.data.spd * cos(radians), bullet.data.spd * sin(radians));
	push_bullet(bullet, bullets);

	return bullet;
}

void update_bullet(Bullet* bullet, Bullet* bullets){
	bullet->age++;
	if(bullet->age >= bullet->data.lifespan){
		pop_bullet(*bullet, bullets);
	}
	if(bullet->entity.x < 0 || bullet->entity.x > 600){
		if(bullet->data.bounces > 0){
			bullet->entity.xv = -bullet->entity.xv;
			bullet->angle = -bullet->angle;
		} else {
			pop_bullet(*bullet, bullets);
		}
	}
	if(bullet->entity.y < 0 || bullet->entity.y > 600){
		if(bullet->data.bounces > 0){
			bullet->entity.yv = -bullet->entity.yv;
			bullet->angle = -bullet->angle;
		} else {
			pop_bullet(*bullet, bullets);
		}
	}

	bullet->entity.y -= bullet->entity.yv;
	if(bullet->entity.yv < 0){
		bullet->entity.yv += 0.1;
	} else if(bullet->entity.yv > 0){
		bullet->entity.yv -= 0.1;
	} else {
		bullet->entity.yv = 0;
	}

	bullet->entity.x -= bullet->entity.xv;
	if(bullet->entity.xv < 0){
		bullet->entity.xv += 0.1;
	} else if(bullet->entity.xv > 0){
		bullet->entity.xv -= 0.1;
	} else {
		bullet->entity.xv = 0;
	}
}

void render_bullet(Game* game, Bullet* bullet){
	rotate_img(&bullet->sprite, bullet->angle - 135);
	render_img(game->rend, &bullet->sprite, bullet->entity.x, bullet->entity.y, bullet->entity.w, bullet->entity.h);
}

// BULLET LIST

void push_bullet(Bullet bullet, Bullet* bullets){
	for(int i = 0; i < MAX_BULLET; i++){
		if(!bullets[i].init){
			bullet.id = i;
			bullets[i] = bullet;
			break;
		}
	}
}

void pop_bullet(Bullet bullet, Bullet* bullets){
	for(int i = bullet.id; i < MAX_BULLET; i++){
		if(!bullets[i].init){
			break;
		}
		bullets[i] = bullets[i + 1];
		bullets[i].id = i;
	}
}

void update_bullets(Bullet* bullets){
	for(int i = 0; i < MAX_BULLET; i++){
		if(!bullets[i].init){
			break;
		} else {
			update_bullet(&bullets[i], bullets);
		}
	}
}

void render_bullets(Game* game, Bullet* bullets){
	for(int i = 0; i < MAX_BULLET; i++){
		if(!bullets[i].init){
			break;
		} else {
			render_bullet(game, &bullets[i]);
		}
	}
}

void print_bullets(Bullet* bullets){
	printf("-= BULLET LIST =-\n");
	for(int i = 0; i < MAX_BULLET; i++){
		if(bullets[i].init == true){
			printf("[%i]. -> INIT\n", i);
		} else {
			printf("[%i]. -> EMPTY\n", i);
		}
	}
}

void destroy_bullets(Bullet* bullets){
	free(bullets);
}
