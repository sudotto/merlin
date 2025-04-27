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

Bullet new_bullet(SDL_Renderer* rend, int x, int y, char* filename, SDL_Color color, int spd){
	Bullet bullet;
	bullet.x = 100;
	bullet.y = 100;
	bullet.w = 4 * 4;
	bullet.h = 4 * 4;
	bullet.x_vel = 1;
	bullet.y_vel = 1;
	bullet.spd = 5;
	bullet.age = 0;
	bullet.lifespan = 20 * 60; // 20 seconds of life (60 frames per second)
	bullet.dead = false;

	SDL_Color target = {0, 0, 0};
	bullet.sprite = new_recolored_img(rend, filename, target, color);

	return bullet;
}

void update_bullet(Bullet* bullet/*, Bullet bullets[100]*/){
	if(bullet->age <= bullet->lifespan){
		//kill_bullet(bullet, bullets);
	}
	bullet->x += bullet->x_vel;
	bullet->y += bullet->y_vel;
}

void render_bullet(SDL_Renderer* rend, Bullet* bullet){
	render_img(rend, &bullet->sprite, bullet->x, bullet->y, bullet->w, bullet->h);
}
