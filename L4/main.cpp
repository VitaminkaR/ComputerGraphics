#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <memory>
#include <gl\glut.h>

# define M_PI 3.14159265358979323846

int rot = 0;
int mode = 1;
int type = 1;
float lsx = 0;
float lsz = 0;
double rad = 0;

void scene() {
	glPushMatrix();

	GLfloat diffuse[3] = { 0, 1, 0 };
	GLfloat specular[3] = { 1, 1, 1 };
	GLfloat ambient[4] = { 0.1, 0.1, 0.1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32.0f);

	glPushMatrix();
	glTranslatef(-1, 0, 0);
	glutSolidSphere(0.4, 32, 32);
	glPopMatrix();

	diffuse[1] = 0; diffuse[2] = 1;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

	glPushMatrix();
	glutSolidCube(0.5f);
	glPopMatrix();

	diffuse[0] = 1; diffuse[1] = 0.75; diffuse[2] = 0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

	glPushMatrix();
	glTranslatef(1, 0, 0);
	glutSolidSphere(0.4, 32, 32);
	glPopMatrix();

	glPopMatrix();
}

void initialize() {
	glClearColor(0, 0, 0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
}

void specialkeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) { rot = rot - 2.0; glutPostRedisplay(); return; }
	if (key == GLUT_KEY_RIGHT) { rot = rot + 2.0; glutPostRedisplay(); return; }
	if (key == GLUT_KEY_UP) {
		mode++;
		char buf[128];
		sprintf(buf, "L4 T%d", mode);
		glutSetWindowTitle(buf);
		glutPostRedisplay(); return;
	}
	if (key == GLUT_KEY_DOWN) {
		mode--;
		char buf[128];
		sprintf(buf, "L4 T%d", mode);
		glutSetWindowTitle(buf);
		glutPostRedisplay(); return;
	}
	if (key == GLUT_KEY_F1)
	{
		type = 1;
		lsx += 0.1;
		glutPostRedisplay(); return;
	}
	if (key == GLUT_KEY_F2)
	{
		type = 2;
		lsx -= 0.1;
		glutPostRedisplay(); return;
	}
	if (key == GLUT_KEY_F3)
	{
		type = 3;
		lsz += 0.1;
		glutPostRedisplay(); return;
	}
	if (key == GLUT_KEY_F4)
	{
		type = 4;
		lsz -= 0.1;
		glutPostRedisplay(); return;
	}
	if (key == GLUT_KEY_F5)
	{
		type = 5;
		glutPostRedisplay(); return;
	}
	if (key == GLUT_KEY_F6)
	{
		type = 6;
		glutPostRedisplay(); return;
	}
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 720, 720);
	glLoadIdentity();

	glRotatef(rot, 0, 1, 0);

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180);

	switch (mode)
	{
	case 1:
	{
		glEnable(GL_LIGHT0);
		GLfloat position[4] = { 1, 1, 0, 0 };
		GLfloat diffuse[3] = { 1, 1, 1 };
		GLfloat specular[3] = { 1, 1, 1 };
		GLfloat ambient[4] = { 1, 1, 1 };
		if (type == 2)
		{
			position[0] = -1; position[1] = 1; position[2] = 0; position[3] = 1;
		}
		else
		{
			position[0] = -1; position[1] = 1; position[2] = 0; position[3] = 0;
		}
			
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	}
	break;
	case 2:
	{
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		GLfloat position[4] = { 1, 1, 0, 0 };
		GLfloat direction[3] = { 0, 0, -1 };
		GLfloat diffuse[3] = { 0.75, 1, 1 };
		GLfloat specular[3] = { 1, 1, 1 };
		GLfloat ambient[4] = { 0.5, 0.5, 0.5 };

		if (type == 2)
			glDisable(GL_LIGHT0);
		else if(type == 3)
			glDisable(GL_LIGHT1);

		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

		position[0] = -1;
		diffuse[0] = 1; diffuse[1] = 0.25; diffuse[2] = 0;
		specular[0] = 1; specular[1] = 0.25; specular[2] = 0.25;
		glLightfv(GL_LIGHT1, GL_POSITION, position);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	}
	break;
	case 3:
	{
		glEnable(GL_LIGHT0);
		GLfloat position[4] = { lsx, 1, lsz, 1 };
		GLfloat diffuse[3] = { 1, 1, 1 };
		GLfloat specular[3] = { 1, 1, 1 };
		GLfloat ambient[4] = { 1, 1, 1 };

		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	}
	break;
	case 4:
	{
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		GLfloat position[4] = { 1, 1, 0, 1 };
		GLfloat diffuse[3] = { 0.75, 1, 1 };
		GLfloat specular[3] = { 1, 1, 1 };
		GLfloat ambient[4] = { 0.5, 0.5, 0.5 };

		if (type == 2)
			glDisable(GL_LIGHT0);
		else if (type == 3)
			glDisable(GL_LIGHT1);

		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

		position[0] = -1;
		diffuse[0] = 1; diffuse[1] = 0.25; diffuse[2] = 0;
		specular[0] = 1; specular[1] = 0.25; specular[2] = 0.25;
		glLightfv(GL_LIGHT1, GL_POSITION, position);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	}
	break;
	case 5:
	{
		glEnable(GL_LIGHT0);
		float radians = rad * (M_PI / 180.0f);
		GLfloat position[4] = { 2 *cosf(radians), 2 * sinf(radians), 0, 1};
		GLfloat diffuse[3] = { 1, 1, 1 };
		GLfloat specular[3] = { 1, 1, 1 };
		GLfloat ambient[4] = { 1, 1, 1 };

		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

		if (rad > 360)
			rad = 0;
		rad += 0.1f;
		glutPostRedisplay();
	}
	break;
	case 6:
	{
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		GLfloat position[4] = { 1, 1, 0, 1 };
		GLfloat direction[3] = { -lsx, -1, 0 };
		GLfloat diffuse[3] = { 0.75, 1, 1 };
		GLfloat specular[3] = { 1, 1, 1 };
		GLfloat ambient[4] = { 0.5, 0.5, 0.5 };
		GLfloat cutoff = 30.0f;

		if (type == 5)
			glDisable(GL_LIGHT0);
		else if (type == 6)
			glDisable(GL_LIGHT1);

		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);

		position[0] = -1;
		diffuse[0] = 1; diffuse[1] = 0.25; diffuse[2] = 0;
		specular[0] = 1; specular[1] = 0.25; specular[2] = 0.25;
		direction[0] = -lsz; direction[1] = -1;
		cutoff = 60;
		glLightfv(GL_LIGHT1, GL_POSITION, position);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
	}
	break;
	default:
		if (mode == 0) {
			glutSetWindowTitle("L4 T1");
			mode = 1;
		}
		else {
			glutSetWindowTitle("L4 T6");
			mode = 6;
		}
		glutPostRedisplay();
		break;
	}

	scene();

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);

	glutSwapBuffers();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(720, 720);
	glutInitWindowPosition(10, 20);
	glutCreateWindow("L4 T1");
	glutDisplayFunc(Display);

	glutSpecialFunc(specialkeys);
	initialize();
	glutMainLoop();
	return 0;
}
