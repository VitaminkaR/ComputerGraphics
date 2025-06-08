#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <gl\glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>

#ifdef GL_GLEXT_PROTOTYPES
GLAPI void APIENTRY glGenerateMipmap(GLenum);
#endif 
#include <vector>
#include <iostream>

int mode = 1;
GLfloat rot;

GLuint textures[32];

GLuint loadTexture(std::string name, bool mipmap = false) {
	int width, height, channels;
	unsigned char* data = stbi_load(name.c_str(), &width, &height, &channels, 0);

	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (mipmap) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(data);

	return texture;
}

GLuint loadMipmapTexture(std::vector<std::string>& filenames, int mw = 256, int mh = 256) {
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// В цикле загружаем каждый уровень
	for (size_t level = 0; level < filenames.size(); ++level) {
		int width, height, channels;
		unsigned char* data = stbi_load(filenames[level].c_str(), &width, &height, &channels, 0);
		if (!data) {
			std::cerr << "Failed to load image: " << filenames[level] << std::endl;
			continue;
		}

		glTexImage2D(GL_TEXTURE_2D, (GLint)level, GL_RGB, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cerr << "GL error after TexImage2D: " << std::hex << err << std::endl;

	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

void loadTextures() {
	textures[0] = loadTexture("bmp/128.bmp");
	textures[1] = loadTexture("bmp/1.bmp");
	textures[2] = loadTexture("bmp/2.bmp");
	textures[3] = loadTexture("bmp/3.bmp");
	textures[4] = loadTexture("bmp/4.bmp");
	textures[5] = loadTexture("bmp/5.bmp");
	textures[6] = loadTexture("bmp/6.bmp");
	//textures[7] = loadTexture("bmp/256.bmp", true);
	std::vector<std::string> tlayers = {
	"bmp/256.png",
	"bmp/128.png",
	"bmp/64.png",
	"bmp/32.png",
	"bmp/16.png",
	"bmp/8.png",
	"bmp/4.png",
	"bmp/2.png",
	"bmp/1.png",
	};
	textures[7] = loadMipmapTexture(tlayers);
}

void scene() {
	glEnable(GL_TEXTURE_2D);

	switch (mode)
	{
	case 1:
	{
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glPushMatrix();
		glBegin(GL_TRIANGLE_FAN);

		glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
		glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
		glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
		glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);

		glEnd();
		glPopMatrix();
	}
	break;
	case 2:
	{
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glPushMatrix();
		glBegin(GL_TRIANGLE_FAN);

		glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
		glTexCoord2f(2, 0); glVertex3f(1, -1, 0);
		glTexCoord2f(2, 2); glVertex3f(1, 1, 0);
		glTexCoord2f(0, 2); glVertex3f(-1, 1, 0);

		glEnd();
		glPopMatrix();
	}
	break;
	case 3:
	{
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glPushMatrix();
		glBegin(GL_TRIANGLE_FAN);

		glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
		glTexCoord2f(4, 0); glVertex3f(1, -1, 0);
		glTexCoord2f(4, 4); glVertex3f(1, 1, 0);
		glTexCoord2f(0, 4); glVertex3f(-1, 1, 0);

		glEnd();
		glPopMatrix();
	}
	break;
	case 4:
	{
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glPushMatrix();
		glRotatef(-rot, 0, 0, 1);
		glBegin(GL_TRIANGLE_FAN);

		glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
		glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
		glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
		glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);

		glEnd();
		glPopMatrix();
	}
	break;
	case 5:
	{
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glTranslatef(-0.5, -0.5, 0);
		glRotatef(rot, 0, 0, 1);
		glTranslatef(-0.5, -0.5, 0);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glRotatef(rot, 0, 0, 1);
		glBegin(GL_TRIANGLE_FAN);

		glTexCoord2f(0.1, 0.1); glVertex3f(-1, -1, 0);
		glTexCoord2f(0.9, 0.1); glVertex3f(1, -1, 0);
		glTexCoord2f(0.9, 0.9); glVertex3f(1, 1, 0);
		glTexCoord2f(0.1, 0.9); glVertex3f(-1, 1, 0);

		glEnd();

		glMatrixMode(GL_TEXTURE);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
	break;
	case 6:
	{
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		GLdouble ss[4] = { 0.5, 0, 0, 0.5 };
		GLdouble tt[4] = { 0, 0.5, 0, 0.5 };
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGendv(GL_S, GL_OBJECT_PLANE, ss);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGendv(GL_T, GL_OBJECT_PLANE, tt);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glPushMatrix();
		glBegin(GL_TRIANGLE_FAN);

		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(-1, 1, 0);

		glEnd();
		glPopMatrix();

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}
	break;
	case 7:
	{
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		GLdouble ss[4] = { 1, 0, 0, 0 };
		GLdouble tt[4] = { 0, 1, 0, 0 };
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGendv(GL_S, GL_OBJECT_PLANE, ss);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGendv(GL_T, GL_OBJECT_PLANE, tt);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glPushMatrix();
		glBegin(GL_TRIANGLE_FAN);

		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(-1, 1, 0);

		glEnd();
		glPopMatrix();

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}
	break;
	case 8:
	{
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		GLdouble ss[4] = { 2, 0, 0, 0 };
		GLdouble tt[4] = { 0, 2, 0, 0 };
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGendv(GL_S, GL_OBJECT_PLANE, ss);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGendv(GL_T, GL_OBJECT_PLANE, tt);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glPushMatrix();
		glBegin(GL_TRIANGLE_FAN);

		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(-1, 1, 0);

		glEnd();
		glPopMatrix();

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}
	break;
	case 9:
	{
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		GLdouble ss[4] = { 0.5, 0, 0, 0.5 };
		GLdouble tt[4] = { 0, 0.5, 0, 0.5 };
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGendv(GL_S, GL_OBJECT_PLANE, ss);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGendv(GL_T, GL_OBJECT_PLANE, tt);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glPushMatrix();
		glRotatef(-rot, 0, 0, 1);
		glBegin(GL_TRIANGLE_FAN);

		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(-1, 1, 0);

		glEnd();
		glPopMatrix();

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}
	break;
	case 10:
	{
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		GLdouble ss[4] = { 0.4, 0, 0, 0.5 };
		GLdouble tt[4] = { 0, 0.4, 0, 0.5 };
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGendv(GL_S, GL_OBJECT_PLANE, ss);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGendv(GL_T, GL_OBJECT_PLANE, tt);

		glBindTexture(GL_TEXTURE_2D, textures[0]);

		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glTranslatef(-0.5, -0.5, 0);
		glRotatef(rot, 0, 0, 1);
		glTranslatef(-0.5, -0.5, 0);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glRotatef(rot, 0, 0, 1);
		glBegin(GL_TRIANGLE_FAN);

		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(-1, 1, 0);

		glEnd();

		glMatrixMode(GL_TEXTURE);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}
	break;
	case 11:
	{
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		GLfloat size = 1;
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

		glPushMatrix();
		glRotatef(rot, 1.0f, 0.0f, 0.0f);
		glRotatef(rot, 0.0f, 1.0f, 0.0f);

		GLfloat vert[6][4][3] = {
			{{-size, -size,  size}, { size, -size,  size}, { size,  size,  size}, {-size,  size,  size}},
			{{ size, -size, -size}, {-size, -size, -size}, {-size,  size, -size}, { size,  size, -size}},
			{{-size, -size, -size}, {-size, -size,  size}, {-size,  size,  size}, {-size,  size, -size}},
			{{ size, -size,  size}, { size, -size, -size}, { size,  size, -size}, { size,  size,  size}},
			{{-size, -size, -size}, {-size, -size,  size}, { size, -size,  size}, { size, -size, -size}},
			{{-size,  size,  size}, {-size,  size, -size}, { size,  size, -size}, { size,  size,  size}}
		};

		GLdouble sstt[6][2][4] = {
			{ {0.5, 0, 0, 0.5}, {0, 0.5, 0, 0.5} },
			{ {-0.5, 0, 0, 0.5}, {0, 0.5, 0, 0.5} },
			{ {0, 0, -0.5, 0.5}, {0, 0.5, 0, 0.5} },
			{ {0, 0, 0.5, 0.5}, {0, 0.5, 0, 0.5} },
			{ {0.5, 0, 0, 0.5}, {0, 0, 0.5, 0.5} },
			{ {0.5, 0, 0, 0.5}, {0, 0, -0.5, 0.5} }
		};

		for (size_t i = 1; i < 7; i++)
		{
			glBindTexture(GL_TEXTURE_2D, textures[i]);

			glTexGendv(GL_S, GL_OBJECT_PLANE, sstt[i - 1][0]);
			glTexGendv(GL_T, GL_OBJECT_PLANE, sstt[i - 1][1]);

			glBegin(GL_QUADS);
			glVertex3fv(vert[i - 1][0]);
			glVertex3fv(vert[i - 1][1]);
			glVertex3fv(vert[i - 1][2]);
			glVertex3fv(vert[i - 1][3]);
			glEnd();
		}

		glPopMatrix();

		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}
	break;
	case 12:
	{
		glBindTexture(GL_TEXTURE_2D, textures[7]);
		glPushMatrix();
		glScalef(rot / 100 + 1, rot / 100 + 1, 1);
		glBegin(GL_TRIANGLE_FAN);

		glTexCoord2f(0, 1); glVertex3f(-1, -1, 0);
		glTexCoord2f(1, 1); glVertex3f(1, -1, 0);
		glTexCoord2f(1, 0); glVertex3f(1, 1, 0);
		glTexCoord2f(0, 0); glVertex3f(-1, 1, 0);

		glEnd();
		glPopMatrix();
	}
	break;
	default:
		if (mode == 0) {
			glutSetWindowTitle("L5 T1");
			mode = 1;
		}
		else {
			glutSetWindowTitle("L5 T12");
			mode = 12;
		}
		glutPostRedisplay();
		break;
	}

	glDisable(GL_TEXTURE_2D);
}

void initialize() {
	glClearColor(0, 0, 0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	loadTextures();
}

void specialkeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) { rot = rot - 2.0; glutPostRedisplay(); return; }
	if (key == GLUT_KEY_RIGHT) { rot = rot + 2.0; glutPostRedisplay(); return; }
	if (key == GLUT_KEY_UP) {
		mode++; rot = 0;
		char buf[128];
		sprintf(buf, "L5 T%d", mode);
		glutSetWindowTitle(buf);
		glutPostRedisplay(); return;
	}
	if (key == GLUT_KEY_DOWN) {
		mode--; rot = 0;
		char buf[128];
		sprintf(buf, "L5 T%d", mode);
		glutSetWindowTitle(buf);
		glutPostRedisplay(); return;
	}
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 720, 720);
	glLoadIdentity();
	scene();

	glutSwapBuffers();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(720, 720);
	glutInitWindowPosition(10, 20);
	glutCreateWindow("L5 T1");
	glutDisplayFunc(Display);
	glutSpecialFunc(specialkeys);
	initialize();
	glutMainLoop();
	return 0;
}
