#ifndef SNAKE_POINT
#define SNAKE_POINT

#include <stdbool.h>

typedef struct point {
	float x, y;
} point_t;

bool point_equal(point_t* p1, point_t* p2);

#endif
