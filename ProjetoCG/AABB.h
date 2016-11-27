#ifndef AABB_H_
#define AABB_H_

#include <GL/gl.h>
#include <GL/glut.h>

typedef struct {
	GLdouble MaxX;
	GLdouble MaxZ;
	GLdouble MinX;
	GLdouble MinZ;
}tAABB;
#endif
