#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"

#include "bullet.h"

// BULLET

Bullet new_bullet(Game* game, Bullet* bullets, int x, int y, int w, int h, char* filename, SDL_Color color, int lifespan, int x_vel, int y_vel, int spd){
	Bullet bullet;
	bullet.init = true;
	bullet.x = x;
	bullet.y = y;
	bullet.w = w * 4;
	bullet.h = h * 4;
	bullet.x_vel = x_vel;
	bullet.y_vel = y_vel;
	bullet.spd = spd;
	bullet.age = 0;
	bullet.lifespan = lifespan * 60; // 2 seconds of life (60 frames per second)
	bullet.dead = false;

	SDL_Color target = {0, 0, 0};
	bullet.sprite = new_recolored_img(game->rend, filename, target, color);

	push_bullet(&bullet, bullets);

	return bullet;
}

void update_bullet(Bullet* bullet, Bullet* bullets){
	bullet->age++;
	if(bullet->age >= bullet->lifespan){
		pop_bullet(bullet, bullets);
	}
	bullet->x += bullet->x_vel;
	bullet->y += bullet->y_vel;
}

void render_bullet(Game* game, Bullet* bullet){
	render_img(game->rend, &bullet->sprite, bullet->x, bullet->y, bullet->w, bullet->h);
}

void kill_bullet(Bullet* bullet, Bullet* bullets){
	pop_bullet(bullet, bullets);
}

// BULLET LIST

void push_bullet(Bullet* bullet, Bullet* bullets){
	for(int i = 0; i < MAX_BULLET; i++){
		if(!bullets[i].init){
			bullet->id = i;
			bullets[i] = *bullet;
			break;
		}
	}
}

void pop_bullet(Bullet* bullet, Bullet* bullets){
	for(int i = bullet->id; i < MAX_BULLET; i++){
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
