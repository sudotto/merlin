#ifndef PARTICLE
#define PARTICLE

#include <stdbool.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3_image/SDL_image.h>

#include "otto-game.h"
#include "entity.h"

#define PARTICLE_TYPE_COUNT 1
#define MAX_PARTICLE 256

// PARTICLE TYPES

typedef enum {
	SPARKLE_PARTICLE
} Particle_type;

typedef struct {
	char* filename;
	int size;
	int spd;
	int lifespan;
	int bounces;
} Particle_data;

extern Particle_data particle_data_table[PARTICLE_TYPE_COUNT];

// PARTICLE

typedef struct {
	bool init;
	int id;
	int age;
	int angle;
	Img sprite;
	Entity entity;
	Particle_data data;
} Particle;

Particle new_particle(Game* game, Particle* particles, int x, int y, int angle, Particle_type type);
void update_particle(Particle* particle, Particle* particles);
void render_particle(Game* game, Particle* particle);
void kill_particle(Particle* particle, Particle* particles);

// PARTICLE LIST

void push_particle(Particle particle, Particle* particles);
void pop_particle(Particle particle, Particle* particles);
void update_particles(Particle* particles);
void render_particles(Game* game, Particle* particles);
void print_particles(Particle* particles);
void destroy_particles(Particle* particles);

#endif
