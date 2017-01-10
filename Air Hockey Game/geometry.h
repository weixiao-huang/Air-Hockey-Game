#ifndef DRAWOBJ_H
#define DRAWOBJ_H
#include <GL/glut.h>
#include <iostream>

//	define the basic normal & color
enum {FRONT, BACK, LEFT, RIGHT, UP, DOWN};
enum {WHITE, GREEN};
const GLfloat normal[6][3] = {
	{0.0, -1.0, 0.0},	// FRONT = 0
	{0.0, 1.0, 0.0},	// BACK  = 1
	{-1.0, 0.0, 0.0},	// LEFT  = 2
	{1.0, 0.0, 0.0},	// RIGHT = 3
	{0.0, 0.0, 1.0},	// UP	 = 4
	{0.0, 0.0, -1.0}		// DOWN  = 5
};
const GLfloat color[2][3] = {
	{1.0, 1.0, 1.0},	// WHITE = 0
	{0.0, 1.0, 0.0}		// GREEN = 1
};
const GLfloat rm = 0.15, rp = 0.1;
const GLfloat wx = 1.0, wy = 2.0, ht = 2.0;
const GLfloat wallx = 0.4, delta = 0.1;


//	floor
const GLfloat floorVerts[4][3] = {
	{15.0, -10.0, -ht}, {15.0, 15.0, -ht}, {-15.0, 15.0, -ht}, {-15.0, -10.0, -ht}
};
const GLfloat floorTexture[4][2] = {
	{0.0, 0.0}, {16.0, 0.0}, {16.0, 16.0}, {0.0, 16.0}
};
const GLubyte floorinds[1][5] = { {0, 1, 2, 3, UP} };


//	cube
const GLfloat cubeverts[8][3] = {
	{wx, -wy, -ht}, {wx, wy, -ht}, {-wx, wy, -ht}, {-wx, -wy, -ht},
	{wx, -wy, 0.0}, {wx, wy, 0.0}, {-wx, wy, 0.0}, {-wx, -wy, 0.0}
};
const GLubyte cubeinds[6][6] = {
	{0, 1, 2, 3, DOWN, WHITE},	 // BOTTOM 
	{4, 5, 6, 7, UP, GREEN},	 // TOP 
	{0, 4, 7, 3, FRONT, WHITE},  // FRONT
	{1, 5, 6, 2, BACK, WHITE},   // BACK
	{3, 2, 6, 7, LEFT, WHITE},   // LEFT
	{0, 1, 5, 4, RIGHT, WHITE}   // RIGHT
};


//	wall
const GLfloat wallverts[16][3] = {
	{wallx, -wy-delta, 0.0}, {wx+delta, -wy-delta, 0.0}, {wx+delta, wy+delta, 0.0},{wallx, wy+delta, 0.0},			//out-down
	{wallx, -wy-delta, delta}, {wx+delta, -wy-delta, delta}, {wx+delta, wy+delta, delta},{wallx, wy+delta, delta},	//out-up
	{wallx, -wy, 0.0}, {wx, -wy, 0.0}, {wx, wy, 0.0}, {wallx, wy, 0.0},			//in-up
	{wallx, -wy, delta}, {wx, -wy, delta}, {wx, wy, delta}, {wallx, wy, delta}	//in-down
};
const GLubyte wallinds[11][5] = {
	{0, 1, 5, 4, FRONT}, // out-front
	{1, 2, 6, 5, RIGHT}, // out-right
	{2, 3, 7, 6, BACK},  // out-back
	{12,13,9, 8, BACK},  // in-front
	{13,14,10,9, LEFT},  // in-right
	{14,15,3,10, FRONT}, // in-back
	{0, 12,8, 4, LEFT},  // front-left
	{15,3, 7,11, LEFT},  // back-left
	{4, 5, 9, 8, UP},	 // top-front
	{5, 6, 10,9, UP},	 // top-right
	{6, 7,11,10, UP}	 // top-back
};


//	function & variables of Texture map
typedef unsigned char byte;
static unsigned char *bitmapData;
static unsigned int texture;
static unsigned int ID;
int LoadBit(const char *file);


//	define draw functions
void drawFloor();
void drawTable();
void drawPuck(GLdouble x, GLdouble y);
void drawMallet(GLdouble x, GLdouble y);
void drawText(GLfloat x, GLfloat y, GLfloat z, char *text);

#endif