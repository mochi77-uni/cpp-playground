
#include <iostream>
#include <GL/freeglut.h>

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
		glVertex2d(-0.9, -0.9);
		glVertex2d(-0.9, 0.9);
		glVertex2d(0.9, 0.9);
		glVertex2d(0.9, -0.9);
	glEnd();

	glFlush();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("Hello World");

	glClearColor(0.0, 0.0, 0.0, 1.0);

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}