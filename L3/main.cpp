#include <gl\glut.h>
#include <math.h>

# define M_PI 3.14159265358979323846

const int VPSIZE = 240;

int mode;
GLfloat rot;
GLfloat alfa;
 
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

void drawModel() {
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
	glColor3f(1, 1, 1);

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0, -0.5, 0.5);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0, 0.5, 0.5);
	glVertex3f(0, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.7, 0.9);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0, 0.5, -0.5);
	glVertex3f(0, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0, 0.5, 0.5);
	glVertex3f(0, 0.5, -0.5);
	glVertex3f(0, 0, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0, -0.5, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 1);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 1);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glEnd();

	glColor3f(0.5, 1, 0.5);
	glTranslatef(0.225, 0.2, 0.25);
	glutSolidSphere(0.2, 32, 32);
}

void scene() {
	drawAxes();
	drawModel();
}

void initialize() {
	glClearColor(0.3, 0.3, 0.3, 1.0);
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
	glutPostRedisplay();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 12 сцена
	glViewport(0, VPSIZE * 2, VPSIZE, VPSIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(rot, 0, 1, 0);
	glRotatef(alfa, 1, 0, 0);
	scene();

	// фронтальная
	glViewport(VPSIZE, VPSIZE * 2, VPSIZE, VPSIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	scene();

	// сбоку
	glViewport(VPSIZE * 2, VPSIZE * 2, VPSIZE, VPSIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(-90, 0, 1, 0);
	scene();

	// сферху
	glViewport(VPSIZE * 3, VPSIZE * 2, VPSIZE, VPSIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(90, 1, 0, 0);
	scene();

	// триметрия
	glViewport(VPSIZE, VPSIZE, VPSIZE, VPSIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(20.0, 1, 0, 0);
	glRotatef(30.0, 0, 1, 0);
	scene();

	// диметрия 
	glViewport(VPSIZE * 2, VPSIZE , VPSIZE, VPSIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(7.2, 1, 0, 0);
	glRotatef(-41.4, 0, 1, 0);
	scene();

	// изометрия
	glViewport(VPSIZE * 3, VPSIZE, VPSIZE, VPSIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(35.264, 1, 0, 0);
	glRotatef(-45.0, 0, 1, 0);
	scene();

	// центральная 1
	glViewport(0, VPSIZE, VPSIZE, VPSIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5, 0.5, -0.5, 0.5, 0.5, 10.0);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.25, -0.25, -1.5);
	scene();

	// центральная 2
	glViewport(0, 0, VPSIZE, VPSIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5, 0.5, -0.5, 0.5, 0.5, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.25, -0.25, -1.5);
	glRotatef(25, 1, 0, 0);
	scene();

	// центральная 3
	glViewport(VPSIZE, 0, VPSIZE, VPSIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.5, 0.5, -0.5, 0.5, 0.5, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-0.25, -0.25, -1.5);
	glRotatef(25, 1, 0, 0);
	glRotatef(35, 0, -1, 1);
	scene();

	// косоугольная Cavalier 
	glViewport(VPSIZE * 2, 0, VPSIZE, VPSIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	float ang = 45 * M_PI / 180;
	matrix[8] = -cos(ang);
	matrix[9] = -sin(ang);
	glLoadMatrixf(matrix);

	scene();

	// косоугольная Cabinet 
	glViewport(VPSIZE * 3, 0, VPSIZE, VPSIZE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
	ang = 30 * M_PI / 180;
	matrix[8] = -0.5 * cos(ang);
	matrix[9] = -0.5 * sin(ang);
	glLoadMatrixf(matrix);

	scene();

	glutSwapBuffers();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(VPSIZE * 4, VPSIZE * 3);
	glutInitWindowPosition(10, 20);
	glutCreateWindow("L3");
	glutDisplayFunc(Display);
	glutSpecialFunc(specialkeys);
	initialize();
	glutMainLoop();
	return 0;
}
