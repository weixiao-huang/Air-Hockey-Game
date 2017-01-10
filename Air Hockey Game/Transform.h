#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

const double pi = 3.1415926;
enum { CONTINUE, WIN, LOST};

static GLint status = CONTINUE;
static GLdouble positionx, positiony;
static GLfloat velx, vely;
static GLdouble oppx, oppy = 1.0;
static GLdouble minex = 0.0, miney = -1.0;
static bool isInit = 0;

//	basic help function
GLfloat randam(GLfloat a, GLfloat b);
GLdouble distance(vec2 vector);


//	basic position & transform functions
bool randamPosition(GLdouble &positionx, GLdouble &positiony,GLfloat &velx,GLfloat &vely, GLdouble &oppx);
void setPosition(GLdouble &x, GLdouble &y, GLfloat &velx,GLfloat &vely, GLdouble t, 
				 GLdouble &oppx, GLdouble &oppy, 
				 GLdouble &minex, GLdouble &miney, 
				 GLint &st, bool &isInit);
void opponent(GLdouble positionx, GLdouble positiony, GLdouble &oppx, GLdouble &oppy);
void screenToWord(int x, int y, GLdouble &minex, GLdouble &miney);
void checkMalletPositionm(GLdouble &minex, GLdouble &miney);
void checkMalletPositiono(GLdouble &oppx, GLdouble &oppy);

#endif