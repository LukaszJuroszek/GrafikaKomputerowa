//£ukasz Juroszek inf sem 4, gr 1A 
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>;
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;

//size of polyogon figure
GLsizei polygonRadiusSize =5;
// Rozmiar kroku (liczba pikseli) w osi x i y
// number of sides of polygon ( pentagon )
int numberOfSides = 5;
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
//window size
// Dane zmieniajcych siê rozmiarów okna
GLfloat windowWidth;
GLfloat windowHeight;
GLfloat x = 0;
GLfloat y = 0;
float * helperX = new float[numberOfSides];
float * helperY = new float[numberOfSides];
int lastMouseX, lastMouseY;
float min(float * inArray) {
	float min = inArray[0];
	for (int i = 1; i < numberOfSides; i++)
	{
		if (min > inArray[i])
		{
			min = inArray[i];
		}
	}
	return min;
}
float max(float * inArray) {
	float max = inArray[0];
	for (int i = 1; i < numberOfSides; i++)
	{
		if (max < inArray[i])
		{
			max = inArray[i];
		}
	}
	return max;
}
//for program from 1 to 3;
void mouse(int button, int state, int xIn, int yIn)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cout << "mouse x" << xIn << endl;
		cout << "mouse y" << yIn << endl;
		x = xIn - lastMouseX ;
		y = yIn - lastMouseY ;
		glutPostRedisplay();

	}
	glutPostRedisplay();
}
void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(x, y, x + polygonRadiusSize, y + polygonRadiusSize);
	glutSwapBuffers();
}
// ( without homework ) TODO: correct colision 
void TimerFunction(int value) {
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}
void SetupRC() {
	glClearColor(0.6f, 0.4f, 0.12f, 1.0f);
}
void ChangeSize(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void program4(int argc, char*argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Mój pierwszy program w GLUT");
	glutMouseFunc(mouse);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(10, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
	delete helperX;
	delete helperY;
}
void main(int argc, char* argv[]) {
	program4(argc, argv);
}
