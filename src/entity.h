#ifndef ENTITY
#define ENTITY

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
} Facing;

typedef struct {
	float x;
	float y;
	int w;
	int h;
	float xv;
	float yv;
} Entity;

Entity new_entity(float x, float y, int w, int h, float xv, float yv);

#endif
