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

// BULLET

Bullet new_bullet(Game* game, int x, int y, int w, int h, char* filename, int lifespan, int spd, int angle){
	Bullet bullet;
	bullet.init = true;
	bullet.age = 0;
	bullet.sprite = new_img(game->rend, filename);
	bullet.lifespan = lifespan * 60;
	bullet.bounces;

	bullet.entity.x = x;
	bullet.entity.y = y;
	bullet.entity.w = w * 4;
	bullet.entity.h = h * 4;
	bullet.entity.angle = angle;
	bullet.entity.spd = spd;

	float radians = angle * (M_PI / 180.0);
	bullet.entity.xv = spd * cos(radians);
	bullet.entity.yv = spd * sin(radians);

	return bullet;
}

void update_bullet(Bullet* bullet, Bullet* bullets){
	bullet->age++;
	if(bullet->age >= bullet->lifespan){
		pop_bullet(*bullet, bullets);
	}
	if(bullet->entity.x < 0 || bullet->entity.x > 600){
		if(bullet->bounces > 0){
			bullet->entity.xv = -bullet->entity.xv;
			bullet->entity.angle = -bullet->entity.angle;
		} else {
			pop_bullet(*bullet, bullets);
		}
	}
	if(bullet->entity.y < 0 || bullet->entity.y > 600){
		if(bullet->bounces > 0){
			bullet->entity.yv = -bullet->entity.yv;
			bullet->entity.angle = -bullet->entity.angle;
		} else {
			pop_bullet(*bullet, bullets);
		}
	}
	bullet->entity.x -= bullet->entity.xv;
	bullet->entity.y -= bullet->entity.yv;
}

void render_bullet(Game* game, Bullet* bullet){
	render_img_rotated(game->rend, &bullet->sprite, bullet->entity.x, bullet->entity.y, bullet->entity.w, bullet->entity.h, bullet->entity.angle - 135);
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

// BULLET TYPES

Bullet new_leaf_bullet(Game* game, int x, int y, int angle){
	return new_bullet(game, x, y, 4, 4, "assets/bullet/magic/leaf.png", 1, 5, angle);
}

Bullet new_plasma_bullet(Game* game, int x, int y, int angle){
	return new_bullet(game, x, y, 4, 4, "assets/bullet/magic/plasma.png", 2, 15, angle);
}

Bullet new_fireball_bullet(Game* game, int x, int y, int angle){
	return new_bullet(game, x, y, 4, 4, "assets/bullet/magic/fireball.png", 2, 20, angle);
}

Bullet new_missle_bullet(Game* game, int x, int y, int angle){
	return new_bullet(game, x, y, 4, 4, "assets/bullet/magic/missle.png", 2, 20, angle);
}

Bullet new_sigil_bullet(Game* game, int x, int y, int angle){
	return new_bullet(game, x, y, 8, 8, "assets/bullet/magic/sigil.png", 3, 10, angle);
}

Bullet new_water_bullet(Game* game, int x, int y, int angle){
	return new_bullet(game, x, y, 8, 8, "assets/bullet/magic/water.png", 2, 20, angle);
}

Bullet new_blaze_bullet(Game* game, int x, int y, int angle){
	return new_bullet(game, x, y, 8, 8, "assets/bullet/magic/blaze.png", 2, 20, angle);
}

Bullet new_smite_bullet(Game* game, int x, int y, int angle){
	return new_bullet(game, x, y, 8, 8, "assets/bullet/magic/smite.png", 1, 30, angle);
}

Bullet new_void_bullet(Game* game, int x, int y, int angle){
	return new_bullet(game, x, y, 8, 8, "assets/bullet/magic/void.png", 1, 15, angle);
}

// SPAWN BULLET

//void spawn_bullet(bullet);
