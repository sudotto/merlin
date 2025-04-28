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

Bullet new_bullet(SDL_Renderer* rend, Bullet* bullets, int x, int y, char* filename, SDL_Color color, int spd){
	Bullet bullet;
	bullet.init = true;
	bullet.x = x;
	bullet.y = y;
	bullet.w = 4 * 4;
	bullet.h = 4 * 4;
	bullet.x_vel = 1;
	bullet.y_vel = 1;
	bullet.spd = 5;
	bullet.age = 0;
	bullet.lifespan = 2 * 60; // 20 seconds of life (60 frames per second)
	bullet.dead = false;

	SDL_Color target = {0, 0, 0};
	bullet.sprite = new_recolored_img(rend, filename, target, color);

	push_bullet(&bullet, bullets);

	return bullet;
}

void update_bullet(Bullet* bullet, Bullet* bullets){
	bullet->age++;
	if(bullet->age >= bullet->lifespan){
		pop_bullet(bullet, bullets);

		//kill_bullet(bullet, bullets);
	}
	bullet->x += bullet->x_vel;
	bullet->y += bullet->y_vel;
}

void render_bullet(SDL_Renderer* rend, Bullet* bullet){
	render_img(rend, &bullet->sprite, bullet->x, bullet->y, bullet->w, bullet->h);
}

void kill_bullet(Bullet* bullet, Bullet* bullets){
	pop_bullet(bullet, bullets);
}

// BULLET LIST

void push_bullet(Bullet* bullet, Bullet* bullets){
	for(int i = 0; i < 20; i++){
		if(!bullets[i].init){
			bullet->id = i;
			bullets[i] = *bullet;
			break;
		}
	}
}

void pop_bullet(Bullet* bullet, Bullet* bullets){
	for(int i = bullet->id; i < 20 - bullet->id; i++){
		if(!bullets[i].init){
			break;
		}
		bullets[i] = bullets[i + 1];
	}
}

void update_bullets(Bullet* bullets){
	for(int i = 0; i < 20; i++){
		if(!bullets[i].init){
			break;
		} else {
			update_bullet(&bullets[i], bullets);
		}
	}
}

void render_bullets(SDL_Renderer* rend, Bullet* bullets){
	for(int i = 0; i < 20; i++){
		if(!bullets[i].init){
			break;
		} else {
			render_bullet(rend, &bullets[i]);
		}
	}
}

void print_bullets(Bullet* bullets){
	printf("-= BULLET LIST =-\n");
	for(int i = 0; i < 20; i++){
		printf("\n");
	}
}

void destroy_bullets(Bullet* bullets){
	free(bullets);
}
