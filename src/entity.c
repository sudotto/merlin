#include "entity.h"

Entity new_entity(float x, float y, int w, int h, float xv, float yv){
	Entity entity;
	entity.x = x;
	entity.y = y;
	entity.w = w;
	entity.h = h;
	entity.xv = xv;
	entity.yv = yv;
	return entity;
}
