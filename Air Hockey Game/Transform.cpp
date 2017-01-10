#include "Transform.h"
#include "geometry.h"
#include <time.h>

bool randamPosition(GLdouble &positionx, GLdouble &positiony,GLfloat &velx,GLfloat &vely, GLdouble &oppx)
{
	positionx = randam(-1.0, 1.0);
	positiony = randam(-1.0, 1.0);
	velx = randam(-1.0, 1.0);
	vely = randam(-1.0, 1.0);
	oppx = randam(-1.0, 1.0);
	return 1;
}

vec2 vel;
vec2 nx(1.0, 0.0), ny(0.0,1.0);	// x and y axis' normal vector
vec2 vo, vm;
void setPosition(GLdouble &positionx, GLdouble &positiony, GLfloat &velx,GLfloat &vely, GLdouble t, 
				 GLdouble &oppx, GLdouble &oppy, 
				 GLdouble &minex, GLdouble &miney, 
				 GLint &st, bool &isInit)
{
    vec2 position(positionx, positiony);
	vec2 opp(oppx, oppy), vo;
	vec2 mine(minex, miney), vm;
    vec2 diso(positionx-oppx, positiony-oppy);
    vec2 dism(positionx-minex, positiony-miney);
    vec2 dis0;
    vec2 time(t, t);

	// whether the vel is initialized
	if(isInit != 0){
		vel = vec2(velx, vely);
		isInit = 0;
	}

	// When Puck's colliding Mallets
    if(distance(diso) <= 0.25){
        dis0 = normalize(diso);
        vel -= 2 * dot(vel,dis0) * dis0;
        position += 0.25f * dis0 - diso;
    }
    if(distance(dism) <= 0.25){
        dis0 = normalize(dism);
        vel -= 2 * dot(vel,dis0) * dis0;
        position += 0.25f * dis0 - dism;
    }

	// When Puck's colliding the wall
    while(position.x <= -0.9 || position.x >= 0.9){
		if(vel.x * position.x > 0)
			vel -= 2 * vel.x * nx;
		position += time * vel;
	}
    while(position.y <= -1.9 || position.y >= 1.9){
		if(vel.y * position.y > 0)
			vel -= 2 * vel.y * ny;
		position += time * vel;
	}

	// position added by velocity(vel)
    position += time * vel;

	// check again if the distance of Puck and Mallets is less than the add of their radius
    if(distance(diso) <= 0.25){
        dis0 = normalize(diso);
        opp -= 0.25f * dis0 - diso;
    }
    if(distance(dism) <= 0.25){
        dis0 = normalize(dism);
        mine -= 0.25f * dis0 - dism;
    }

    positionx = position.x;
    positiony = position.y;
	oppx = opp.x;
	oppy = opp.y;
	minex = mine.x;
	miney = mine.y;
	
	vo = opp;
	vm = mine;
	//When Puck arrives the wall
	if(positionx < wallx && positionx > -wallx){
		if(positiony < -ht+rp){
			st = LOST;
		}
		if(positiony > ht-rp){
			st = WIN;
		}
	}
}

GLdouble vox = 0;
GLfloat k = 0.0000005;	// const of the accelerator
void opponent(GLdouble positionx, GLdouble positiony, GLdouble &oppx, GLdouble &oppy)
{
	if (oppx < 1.1){
		vec2 r(positionx-oppx, positiony-oppy);
		vec2 r0 = normalize(r);
		GLfloat d =  dot(r,r);
		vec2 a = r0 / d * k;	//	accelerator
		vox += a.x;
		oppx += vox;
		r = vec2(positionx-oppx, positiony-oppy);
		if(abs(r.x) > 0.4)
			oppx += r.x / abs(r.x) * 0.01;
	}
}

void screenToWord(int x, int y, GLdouble &minex, GLdouble &miney)
{
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLint really;
	GLfloat winZ;
	GLdouble wx, wy, wz;
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
	really = viewport[3] - (GLint)y - 1;
	glReadPixels(x, really, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);  
	gluUnProject((GLdouble)x, (GLdouble)really, winZ, mvmatrix, projmatrix, viewport, &wx, &wy, &wz);			
	minex = wx, miney = wy;
}

void checkMalletPositionm(GLdouble &minex, GLdouble &miney)
{
	if(minex > 0.85) minex = 0.85;
	if(minex < -0.85) minex = -0.85;
	if(miney > -1.0) miney = -1.0;
	if(miney < -1.85) miney = -1.85;
}

void checkMalletPositiono(GLdouble &oppx, GLdouble &oppy)
{
	if(oppx > 0.85) oppx = 0.85;
	if(oppx < -0.85) oppx = -0.85;
	if(oppy > 1.85) oppy = 1.85;
	if(oppy < 1.2) oppy = 1.2;
}


GLfloat randam(GLfloat a, GLfloat b)	//	to generate a randam number between float a to b
{
	srand((unsigned)time(0));
	return (rand() / double(RAND_MAX)) * (b - a) + a;
}

GLdouble distance(vec2 vector) 	// to caculate the distance of a vector
{
	return sqrt(dot(vector, vector));
}