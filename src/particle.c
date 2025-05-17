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

#include "particle.h"

// PARTICLE TYPES

Particle_data particle_data_table[PARTICLE_TYPE_COUNT] = {
	{"assets/particle/sparkle.png", 1 * 4, 5, 10, 0},
};

// PARTICLE

Particle new_particle(Game* game, Particle* particles, int x, int y, int angle, Particle_type type){
	Particle particle;
	particle.init = true;
	particle.age = 0;
	particle.angle = angle;

	particle.data = particle_data_table[type];
	particle.sprite = new_img(game->rend, particle.data.filename, true);

	float radians = angle * (M_PI / 180.0);
	particle.entity = new_entity(x, y, particle.data.size, particle.data.size, particle.data.spd * cos(radians), particle.data.spd * sin(radians));
	push_particle(particle, particles);

	return particle;
}

void update_particle(Particle* particle, Particle* particles){
	particle->age++;
	if(particle->age >= particle->data.lifespan){
		pop_particle(*particle, particles);
	}
	if(particle->entity.x < 0 || particle->entity.x > 600){
		if(particle->data.bounces > 0){
			particle->entity.xv = -particle->entity.xv;
			particle->angle = -particle->angle;
		} else {
			pop_particle(*particle, particles);
		}
	}
	if(particle->entity.y < 0 || particle->entity.y > 600){
		if(particle->data.bounces > 0){
			particle->entity.yv = -particle->entity.yv;
			particle->angle = -particle->angle;
		} else {
			pop_particle(*particle, particles);
		}
	}
	
	particle->entity.y -= particle->entity.yv;
	if(particle->entity.yv < 0){
		particle->entity.yv += 0.1;
	} else if(particle->entity.yv > 0){
		particle->entity.yv -= 0.1;
	} else {
		particle->entity.yv = 0;
	}

	particle->entity.x -= particle->entity.xv;
	if(particle->entity.xv < 0){
		particle->entity.xv += 0.1;
	} else if(particle->entity.xv > 0){
		particle->entity.xv -= 0.1;
	} else {
		particle->entity.xv = 0;
	}
}

void render_particle(Game* game, Particle* particle){
	rotate_img(&particle->sprite, particle->angle - 135);
	render_img(game->rend, &particle->sprite, particle->entity.x, particle->entity.y, particle->entity.w, particle->entity.h);
}


// PARTICLE LIST

void push_particle(Particle particle, Particle* particles){
	for(int i = 0; i < MAX_PARTICLE; i++){
		if(!particles[i].init){
			particle.id = i;
			particles[i] = particle;
			break;
		}
	}
}

void pop_particle(Particle particle, Particle* particles){
	for(int i = particle.id; i < MAX_PARTICLE; i++){
		if(!particles[i].init){
			break;
		}
		particles[i] = particles[i + 1];
		particles[i].id = i;
	}
}

void update_particles(Particle* particles){
	for(int i = 0; i < MAX_PARTICLE; i++){
		if(!particles[i].init){
			break;
		} else {
			update_particle(&particles[i], particles);
		}
	}
}

void render_particles(Game* game, Particle* particles){
	for(int i = 0; i < MAX_PARTICLE; i++){
		if(!particles[i].init){
			break;
		} else {
			render_particle(game, &particles[i]);
		}
	}
}

void print_particles(Particle* particles){
	printf("-= PARTICLE LIST =-\n");
	for(int i = 0; i < MAX_PARTICLE; i++){
		if(particles[i].init == true){
			printf("[%i]. -> INIT\n", i);
		} else {
			printf("[%i]. -> EMPTY\n", i);
		}
	}
}

void destroy_particles(Particle* particles){
	free(particles);
}

