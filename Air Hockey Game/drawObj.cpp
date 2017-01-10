#include "geometry.h"

void drawFloor()
{
	//	all about Texture map
	ID = LoadBit("floor.bmp");
	if(ID == -1) exit(0);
    glBindTexture(GL_TEXTURE_2D, ID);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//	Draw floor
	glBegin(GL_QUADS);
		glColor3d(1.0,1.0,1.0);
		glNormal3fv(normal[floorinds[1][4]]);
		for(int i=0; i<4; i++){
			glTexCoord2fv(floorTexture[i]);
			glVertex3fv(floorVerts[i]);
		}
	glEnd();
}


void drawTable()
{
	//	Draw bottom cube
	glBegin(GL_QUADS);
		for(int i=0; i<6; i++){
			glColor3fv(color[cubeinds[i][5]]);
			glNormal3fv(normal[cubeinds[i][4]]);
			for(int j=0; j<4; j++){
				glVertex3fv(cubeverts[cubeinds[i][j]]);	
			}
		}
	glEnd();

	//	Draw wall
	glBegin(GL_QUADS);
		glColor3d(1.0,1.0,1.0);
		for(int i=0; i<11; i++){
			glNormal3fv(normal[wallinds[i][4]]);
			for(int j=0; j<4; j++){
				glVertex3fv(wallverts[wallinds[i][j]]);
			}
		}
	glEnd();
	glRotated(180, 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		for(int i=0; i<11; i++){
			glNormal3fv(normal[wallinds[i][4]]);
			for(int j=0; j<4; j++){
				glVertex3fv(wallverts[wallinds[i][j]]);
			}
		}
	glEnd();
	glRotated(-180, 0.0, 0.0, 1.0);	//back to origin axis
}


void drawPuck(GLdouble x, GLdouble y)
{
	glPushMatrix();
		glTranslated(x, y, 0.0);
		glColor3d(1.0,0.0,1.0);
		GLUquadricObj *obj = gluNewQuadric();
		gluCylinder(obj, 0.1, 0.1, 0.1, 20, 20);
		glTranslated(0.0,0.0,0.1);
		gluDisk(obj, 0.0, 0.1, 20, 20);
	glPopMatrix();
}


void drawMallet(GLdouble x, GLdouble y)
{
	glPushMatrix();
		glTranslated(x, y, 0.0);
		GLUquadricObj *obj = gluNewQuadric();
		gluCylinder(obj, 0.15, 0.15, 0.1, 20, 20);
		glTranslated(0.0,0.0,0.1);
		gluDisk(obj, 0.0, 0.15, 20, 20);
	glPopMatrix();
}


void drawText(GLfloat x, GLfloat y, GLfloat z, char *text)
{
	glRasterPos3f(x, y, z);
	for (; *text != '\0'; text++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*text);
}


//	read the bitmap file
int LoadBit(const char *file)
{
	unsigned int ID;      //�����id
	int width,height,i;
	byte *image,t;          //����ͼ������
	FILE *fp;            //�ļ�ָ��
	BITMAPFILEHEADER FileHeader;    //����λͼ�ļ�ͷ
	BITMAPINFOHEADER InfoHeader;    //����λͼ��Ϣͷ
	fp=fopen(file,"rb");
	if (fp == NULL){
		perror("LoadBitmap");        //���ļ�ʧ��
		return -1;
	}
	fread(&FileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	if(FileHeader.bfType != 0x4D42){    //ȷ���ļ���һ��λͼ�ļ���Ч���ļ�����
		printf("Error: This file is not a bmp file!");
		fclose(fp);
		return -1;
	}
	fread(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	width=InfoHeader.biWidth;
	height=InfoHeader.biHeight;
	if (InfoHeader.biSizeImage == 0){          //ȷ��ͼ�����ݵĴ�С
		InfoHeader.biSizeImage = width*height*3;
	}
	fseek(fp, FileHeader.bfOffBits, SEEK_SET);  //���ļ�ָ���ƶ���ʵ��ͼ�����ݴ�
	image=(byte *)malloc(sizeof(byte)*InfoHeader.biSizeImage); //����ռ�
	if (image == NULL){
		free(image);
		printf("Error: No enough space!");
		return -1;
	}
	fread(image, 1, InfoHeader.biSizeImage, fp);
	for(i=0; i<InfoHeader.biSizeImage; i+=3){
		t=image[i];
		image[i]=image[i+2];
		image[i+2]=t;
	}
	fclose(fp); 
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width,height, GL_RGB, GL_UNSIGNED_BYTE, image);
	free(image);
	return ID; 
}
