#include <gl\glut.h>

int mode;
GLfloat rot;
GLfloat alfa;
int ex = GLUT_KEY_F1;
 
void drawAxes(int axesSize = 2) {
	glBegin(GL_LINES);
	glColor3f(axesSize, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(axesSize, 0, 0);

	glColor3f(0, axesSize, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, axesSize, 0);

	glColor3f(0, 0, axesSize);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, axesSize);
	glEnd();
}

void drawSnowMan() {
	drawAxes();
	glPushMatrix();

	glColor3f(1, 1, 1);
	glutSolidSphere(0.5, 32, 32);

	glTranslatef(0, 0.75, 0);
	glutSolidSphere(0.25, 32, 32);

	glTranslatef(0.10, 0.05, 0.225);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.05, 16, 16);

	glTranslatef(-0.20, 0, 0);
	glutSolidSphere(0.05, 16, 16);

	glColor3f(0.8, 0.5, 0.5);
	glTranslatef(0.10, -0.1, 0);
	glutSolidCone(0.05, 0.3, 16, 16);

	glPopMatrix();
}

void scene() {
	switch (ex)
	{
	case GLUT_KEY_F1:
	{
		drawAxes();
		glPushMatrix();

		glTranslatef(0, 0.5, 0);

		glColor3f(1, 1, 1);
		glutSolidSphere(0.5, 32, 32);

		glTranslatef(0.75, -0.25, 0);
		glutSolidSphere(0.25, 16, 16);

		glTranslatef(0.3, -0.175, 0);
		glColor3f(0, 0, 0);
		glutSolidSphere(0.05, 16, 16);

		glTranslatef(0.15, 0, 0);
		glutSolidSphere(0.05, 16, 16);

		glColor3f(0.8, 0.5, 0.5);
		glTranslatef(0.15, -0.05, 0);
		glRotatef(270, 1, 0, 0);
		glutSolidCone(0.05, 0.3, 16, 16);

		glPopMatrix();
	}
	break;
	case GLUT_KEY_F2:
	{
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);

		drawSnowMan();

		glPopMatrix();
	}
	break;
	case GLUT_KEY_F3:
	{
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);

		glTranslatef(-0.9, 0, 0);
		drawSnowMan();

		glTranslatef(0.85, 0, 0);
		glScalef(0.7, 0.7, 0.7);
		drawSnowMan();

		glTranslatef(0.85, 0, 0);
		glScalef(0.7, 0.7, 0.7);
		drawSnowMan();

		glPopMatrix();
	}
	break;
	case GLUT_KEY_F4:
	{
		glPushMatrix();

		glTranslatef(0, 0, -0.5);
		drawSnowMan();

		glTranslatef(0, 0, 0.85);
		glScalef(0.7, 0.7, 0.7);
		glPushMatrix();
		glTranslatef(0, 0.75, 0);
		glRotatef(rot, 0, 0, 1);
		glTranslatef(0, -0.75, 0);
		drawSnowMan();
		glPopMatrix();

		glTranslatef(0, 0, 0.85);
		glScalef(0.7, 0.7, 0.7);
		drawSnowMan();

		glPopMatrix();
	}
	break;
	case GLUT_KEY_F5:
	{
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);

		glTranslatef(0, -0.9, 0);
		drawSnowMan();

		glTranslatef(0, 1.35, 0);
		glScalef(0.7, 0.7, 0.7);
		drawSnowMan();

		glTranslatef(0, 1.35, 0);
		glScalef(0.7, 0.7, 0.7);
		drawSnowMan();

		glPopMatrix();
	}
	break;
	case GLUT_KEY_F6:
	{
		glPushMatrix();

		glTranslatef(-0.9, -0.9, 0);
		glRotatef(rot, 0, 1, 0);
		glRotatef(alfa, 1, 1, 1);
		drawSnowMan();

		// 3^(1/2) * x = 0.5 (находим координаты вектора, зная его длину (радиусы сфер)) x = 0.28867526
		glTranslatef(0.28867526 * 1.7, 0.28867526 * 1.7, 0.28867526 * 1.7);
		glScalef(0.7, 0.7, 0.7);
		drawSnowMan();

		glTranslatef(0.28867526 * 1.7, 0.28867526 * 1.7, 0.28867526 * 1.7);
		glScalef(0.7, 0.7, 0.7);
		drawSnowMan();

		glPopMatrix();
	}
	break;
	case GLUT_KEY_F7:
	{
		drawAxes();
		glPushMatrix();

		glTranslatef(0, 0.35, 0);
		glScalef(0.7, 0.7, 0.7);
		glRotatef(rot, 0, 1, 0);
		glPushMatrix();
		glRotatef(180, 0, 0, 1);
		drawSnowMan();
		glPopMatrix();

		glScalef(10 / 7.0, 10 / 7.0, 10 / 7.0);
		glTranslatef(-0.85, 0.15, 0);
		drawSnowMan();

		glTranslatef(1.445, -0.255, 0);
		glScalef(0.49, 0.49, 0.49);
		drawSnowMan();

		glPopMatrix();
	}
	break;
	case GLUT_KEY_F8:
	{
		drawAxes();
		glPushMatrix();
		glTranslatef(0, 0.5, 0);

		glTranslatef(-0.25, 0, 0);
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		drawSnowMan();
		glPopMatrix();

		glTranslatef(0.85, -0.15, 0);
		glScalef(0.7, 0.7, 0.7);
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		drawSnowMan();
		glPopMatrix();

		glTranslatef(0.85, -0.15, 0);
		glScalef(0.7, 0.7, 0.7);
		glPushMatrix();
		glRotatef(rot, 0, 1, 0);
		drawSnowMan();
		glPopMatrix();

		glPopMatrix();
	}
	break;
	case GLUT_KEY_F9:
	{
		drawAxes();
		glPushMatrix();
		glTranslatef(0.595, 0.255, 0);
		glScalef(0.49, 0.49, 0.49);
		glRotatef(rot, 0, 1, 0);
		drawSnowMan();

		glScalef(10 / 7.0, 10 / 7.0, 10 / 7.0);
		glTranslatef(-0.85, 0.15, 0);
		drawSnowMan();

		glScalef(10 / 7.0, 10 / 7.0, 10 / 7.0);
		glTranslatef(-0.85, 0.15, 0);
		drawSnowMan();

		glPopMatrix();
	}
	break;
	case GLUT_KEY_F10:
	{
		drawAxes();
		glPushMatrix();

		glColor3f(1, 1, 1);
		glutSolidSphere(0.5, 32, 32);

		glRotatef(-rot, 0, 0, 1);

		glTranslatef(0, 0.75, 0);
		glRotatef(rot, 0, 0, 1);
		glutSolidSphere(0.25, 32, 32);

		glTranslatef(0.10, 0.05, 0.225);
		glColor3f(0, 0, 0);
		glutSolidSphere(0.05, 16, 16);

		glTranslatef(-0.20, 0, 0);
		glutSolidSphere(0.05, 16, 16);

		glColor3f(0.8, 0.5, 0.5);
		glTranslatef(0.10, -0.1, 0);
		glutSolidCone(0.05, 0.3, 16, 16);

		glPopMatrix();
	}
	break;
	case GLUT_KEY_F11:
	{
		drawAxes();
		glPushMatrix();

		glTranslatef(-0.5, 0, 0);
		drawSnowMan();

		glRotatef(rot, 0, 1, 0);
		glTranslatef(1, 0, 0);
		glScalef(0.7, 0.7, 0.7);
		drawSnowMan();

		glPushMatrix();

		glRotatef(rot, 0, 0, 1);
		glTranslatef(0, 10/7.0, 0);
		glRotatef(-rot, 0, 0, 1);
		glScalef(0.7, 0.7, 0.7);
		drawSnowMan();

		glPopMatrix();

		glRotatef(rot, 0, 1, 0);
		glTranslatef(1, 0.5 * 0.7 + 0.25 * 0.7, 0);
		glScalef(0.49, 0.49, 0.49);
		drawSnowMan();

		glPopMatrix();
	}
	break;
	}
}

void initialize() {
	glClearColor(0.3, 0.3, 0.3, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
}

void specialkeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) { rot = rot - 2.0; }
	else
		if (key == GLUT_KEY_RIGHT) { rot = rot + 2.0; }
		else
			if (key == GLUT_KEY_UP) { alfa = alfa - 2.0; }
			else
				if (key == GLUT_KEY_DOWN) { alfa = alfa + 2.0; }
				else {
					ex = key;
					rot = 0;
					alfa = 0;
				}
	glutPostRedisplay();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 800, 800);
	glLoadIdentity();
	scene();

	glViewport(800, 0, 800, 800);
	glRotatef(90, 1, 0, 0);
	scene();

	glutSwapBuffers();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1600, 800);
	glutInitWindowPosition(10, 20);
	glutCreateWindow("L2");
	glutDisplayFunc(Display);
	glutSpecialFunc(specialkeys);
	initialize();
	glutMainLoop();
	return 0;
}
