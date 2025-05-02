#ifndef ENTITY
#define ENTITY

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
