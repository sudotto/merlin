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

Bullet new_bullet(Game* game, int x, int y, int w, int h, char* filename, int lifespan, int spd, int angle){
	Bullet bullet;
	bullet.init = true;
	bullet.x = x;
	bullet.y = y;
	bullet.w = w * 4;
	bullet.h = h * 4;
	bullet.angle = angle;
	bullet.spd = spd;
	bullet.age = 0;
	bullet.lifespan = lifespan * 60;
	bullet.bounces;
	bullet.dead = false;
	bullet.angle = angle;
	float radians = angle * (M_PI / 180.0);
	bullet.x_vel = spd * cos(radians);
	bullet.y_vel = spd * sin(radians);

	bullet.sprite = new_img(game->rend, filename);

	//push_bullet(&bullet, bullets);

	return bullet;
}

void update_bullet(Bullet* bullet, Bullet* bullets){
	bullet->age++;
	if(bullet->age >= bullet->lifespan){
		pop_bullet(*bullet, bullets);
	}
	if(bullet->x < 0 || bullet->x > 600){
		bullet->x_vel = -bullet->x_vel;
		bullet->angle = -bullet->angle;
	}
	if(bullet->y < 0 || bullet->y > 600){
		bullet->y_vel = -bullet->y_vel;
		bullet->angle = -bullet->angle;
	}
	bullet->x -= bullet->x_vel;
	bullet->y -= bullet->y_vel;
}

void render_bullet(Game* game, Bullet* bullet){
	render_img_rotated(game->rend, &bullet->sprite, bullet->x, bullet->y, bullet->w, bullet->h, bullet->angle - 135);
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
	return new_bullet(game, x, y,bullet->x_vel = -bullet->x_vel; 		bullet->angle = -bullet->angle; 	} 	if(bullet->y < 0 || bullet->y > 600){ 		bullet->y_vel = -bullet->y_vel; 		bullet->angle = -bullet->angle; 	} 	bullet->x -= bullet->x_vel; 	bullet->y -= bullet->y_vel; }  void render_bullet(Game* game, Bullet* bullet){ 	render_img_rotated(game->rend, &bullet->sprite, bullet->x, bullet->y, bullet->w, bullet->h, bullet->angle - 135); } 8, 8, "assets/bullet/magic/sigil.png", 3, 10, angle);
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
