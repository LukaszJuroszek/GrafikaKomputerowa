#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>;
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;
GLsizei polygonRadiusSize = 5;
// Rozmiar kroku (liczba pikseli) w osi x i y
// number of sides of polygon ( pentagon )
int numberOfSides = 5;
//for mouse point translating to world cor
POINT mousePoint;
int width = 800;
int heigth = 600;
GLdouble posX, posY, posZ;
GLfloat x = 0;
GLfloat y = 0;
float * helperX = new float[numberOfSides];
float * helperY = new float[numberOfSides];
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
void  GetOGLPos()
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	double winX = (double)mousePoint.x;
	double winY = viewport[3] - (double)mousePoint.y;
	cout << posX << " " << posY << " " << posY << endl;
	gluUnProject(mousePoint.x, mousePoint.y, 0, modelview, projection, viewport, &posX, &posY, &posZ);
	cout << posX << " " << posY << " " << posY << endl;
	posY += heigth;
}
void mouse(int button, int state, int xIn, int yIn)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cout << "mouse x" << xIn << endl;
		cout << "mouse y" << -yIn << endl;
		mousePoint.x = xIn;
		mousePoint.y = -yIn;
	}
	GetOGLPos();
	glutPostRedisplay();
}
void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(posX, posY, posX + radius, posY + radius);
	glFlush();
}
void SetupRC(void) {
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}
void ChangeSize(int w, int h) {
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		heigth = 250.0f*h / w;
		width = 250.0f;
	}
	else
	{
		width = 250.0f*w / h;
		heigth = 250.0f;
	}
	glOrtho(0.0f, width, 0.0f, heigth, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void TimerFunction(int value) {
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, heigth);
	glutCreateWindow("GLRect");
	glutMouseFunc(mouse);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(10, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
	delete helperX;
	delete helperY;
	return 0;
}