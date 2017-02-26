#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>;
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;
GLsizei polygonRadiusSize = 50;
int numberOfSides = 5;
POINT mousePoint;
int width = 800;
int heigth = 600;
GLdouble posX, posY, posZ;
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
void  GetWorldCor()
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	double winX = (double)mousePoint.x;
	double winY = viewport[3] - (double)mousePoint.y;
	gluUnProject(mousePoint.x, mousePoint.y, 0, modelview, projection, viewport, &posX, &posY, &posZ);
	posY += heigth;
}
int parseCinToInt() {
	int input;
	while (true)
	{
		cout << "insert number of sides in polygon:" << endl;
		cin >> input;
		try {
			if (cin.fail()) {
				cout <<  "error while parsing cin";
			}
			if (input>2) {
				return input;
			}
			else
			{
				cout << "Number should be greater than 2!" << endl;
			}
		}
		catch (char* error) {
			cout << error << endl;
			break;
		}
	}
}
void mouse(int button, int state, int xIn, int yIn)
{
	//if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	//{
		mousePoint.x = xIn;
		mousePoint.y = -yIn;
	//	numberOfSides = parseCinToInt();
	//}
	GetWorldCor();
	glutPostRedisplay();
}
void mouseFunction(int xIn,int yIn) {
	mousePoint.x = xIn;
	mousePoint.y = -yIn;
	GetWorldCor();
	glutPostRedisplay();
}
void drawPolygon() {
	glBegin(GL_POLYGON);
	for (int i = 0; i < numberOfSides; i++)
	{
		float xx = posX + polygonRadiusSize * sin(2.0*M_PI*i / numberOfSides);
		float yy = posY + polygonRadiusSize * cos(2.0*M_PI*i / numberOfSides);
		glVertex2f(xx, yy);
	}
	glEnd();
}
void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	drawPolygon();
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
	glutCreateWindow("Program5");
	glutMouseFunc(mouse);
	glutMotionFunc(mouseFunction);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(10, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
	return 0;
}
