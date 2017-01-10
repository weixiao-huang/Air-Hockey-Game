#include "geometry.h"
#include "Transform.h"

int windowWidth = 500, windowHeight = 500; //	Width/Height of OpenGL window

GLdouble fovy = 45.0, zNear = 0.1, zFar = 100.0;
GLdouble r0 = 5.0, theta = -60.0*pi/180;
GLdouble eyex = r0*cos(theta), eyey = r0*sin(theta), eyez = 5.0, upx = 0.0, upy = 0.0, upz = 1.0;
GLdouble t = 0.005;	//	Very Slow
char* text;

void init()
{
	isInit = randamPosition(positionx, positiony, velx, vely, oppx);
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);

	// Enable the texture map
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	// Enable the depth test
	glEnable(GL_DEPTH_TEST) ;
	glDepthFunc (GL_LESS) ; // The default option

	// Define and enable the light
	GLfloat mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {100.0};
	GLfloat mat_position[] = {5.0, 5.0, 5.0, 0.0};
    
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    
	glLightfv(GL_LIGHT0, GL_POSITION, mat_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
    
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void reshape(int w, int h)
{
	windowWidth = w;
	windowHeight = h;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)w/(GLdouble)h, zNear, zFar) ;
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	eyex = r0*cos(theta);
	eyey = r0*sin(theta);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eyex,eyey,eyez, 0.0, 0.0, 0.0, upx,upy,upz);

	drawFloor();
	drawTable();
	drawPuck(positionx,positiony);	// Draw Puck
	glColor3d(1.0,0.0,0.0);
	drawMallet(minex, miney);		// Draw my Mallet
	glColor3d(0.0,0.0,1.0);
	drawMallet(oppx, oppy);			// Draw opp Mallet

	//	Check status
	switch(status){
		case CONTINUE:
			setPosition(positionx, positiony, velx, vely, t, oppx, oppy, minex, miney,status, isInit);	//	根据速度t设置Puck的坐标，同时计算Puck与各Mallets的碰撞状况
			opponent(positionx, positiony, oppx, oppy);		//	AI的算法
			checkMalletPositiono(oppx, oppy);	//	检查对方Mallet的各种边界条件
			break;
		case WIN:
			glColor3f(1.0, 0.0, 0.0);
			drawText((r0*cos(theta)+1.0*sin(theta))/2, (r0*sin(theta)-1.0*cos(theta))/2, 2.5, "Y O U   W I N !");
			break;
		case LOST:
			glColor3f(0.0, 0.0, 0.0);
			drawText((r0*cos(theta)+1.0*sin(theta))/2, (r0*sin(theta)-1.0*cos(theta))/2, 2.5, "Y O U   L O S T !");
			break;
	}

	glFlush();
	glutSwapBuffers();
}

void movemouse(int x, int y)
{
	screenToWord(x, y, minex, miney);
	checkMalletPositionm(minex, miney);	//	检查我方Mallet的各种边界条件
}

void pressENTER(GLint &status, bool &isInit)
{
	status = CONTINUE;
	isInit = randamPosition(positionx, positiony, velx, vely, oppx);
}

void keyboard(unsigned char key, int x, int y)
{
	double alpha = 5.0;
	switch(key) {
		case 'a':
			theta -= theta<-150*pi/180 ? 0 : alpha*pi/180;
			break;
		case 'd':
			theta += theta>-30*pi/180 ? 0 : alpha*pi/180;
			break;
		case 'q':
		case 27: 
			exit(0);
			break;
		case 13:
			pressENTER(status, isInit);
			glutPostRedisplay();
	}
}

void events(int option)
{
	switch(option) {
	case 11: 
		t = 0.005;
		glutPostRedisplay();
		break;
	case 12 :
		t = 0.01;
		glutPostRedisplay();
		break;
	case 13:
		t = 0.02;
		glutPostRedisplay();
		break;
	case 14 :
		t = 0.04;
		glutPostRedisplay();
		break;
	case 15:
		t = 0.08;
		glutPostRedisplay();
		break;
	case 2:
		status = 4;
		glutPostRedisplay();
		break;
	case 3:
		status = CONTINUE;
		glutPostRedisplay();
		break;
	case 4:
		pressENTER(status, isInit);
		glutPostRedisplay();
		break;
	case 0:
		exit(0);
		break;
	}
}

void createGLUTMenus()
{
	int menu, submenu;
	submenu = glutCreateMenu(events);
		glutAddMenuEntry("Very Slow", 11);
		glutAddMenuEntry("Slow", 12);
		glutAddMenuEntry("Middle", 13);
		glutAddMenuEntry("Fast", 14);
		glutAddMenuEntry("Very Fast", 15);
	menu = glutCreateMenu(events);
		glutAddMenuEntry("Pause", 2);
		glutAddMenuEntry("Continue", 3);
		glutAddMenuEntry("Restart", 4);
		glutAddSubMenu("Puck speed",submenu);
		glutAddMenuEntry("Exit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Air Hockey Game");

	init();

	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(movemouse);
	
	createGLUTMenus();

	glutMainLoop();

	return 0;
}