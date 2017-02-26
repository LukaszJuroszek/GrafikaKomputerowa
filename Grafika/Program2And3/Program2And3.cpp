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
GLfloat x = 50.0f;
GLfloat y = 150.0f;
//size of polyogon figure
GLsizei polygonRadiusSize = 50;
// Rozmiar kroku (liczba pikseli) w osi x i y
// number of sides of polygon ( pentagon )
int numberOfSides = 5;
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
//window size
int width = 800;
int heigth = 600;
// Dane zmieniajcych siê rozmiarów okna
GLfloat windowWidth;
GLfloat windowHeight;
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
//for program from 1 to 3;
void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < numberOfSides; i++)
	{
		float xx = x + polygonRadiusSize * sin(2.0*M_PI*i / numberOfSides);
		float yy = y + polygonRadiusSize * cos(2.0*M_PI*i / numberOfSides);
		helperX[i] = xx;
		helperY[i] = yy;
		//cout << round(xx) << ","<< round(yy) <<"  " <<i<< endl;
		glVertex2f(xx, yy);
	}
	glEnd();
	glutSwapBuffers();
}
// ( without homework ) TODO: correct colision 
void TimerFunction(int value) {
	float minFromX = min(helperX); // left
	float maxFromX = max(helperX); // rigth
	float minFromY = min(helperY); // bottom
	float maxFromY = max(helperY); // top
	//ystep = 0;
	if (x > windowWidth - polygonRadiusSize || x < polygonRadiusSize)
		xstep = -xstep;
	if (y > windowHeight - polygonRadiusSize || y < polygonRadiusSize - minFromY)
		ystep = -ystep;
	/*if (y > windowHeight - polygonRadiusSize || (minFromY-polygonRadiusSize) <0)
		ystep = -ystep;*/
	x += xstep;
	y += ystep;
	glutReshapeWindow(width,heigth); // change window size to (width,heigth)
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}
 //for program 3* TODO: correct colision  (homework)
void TimerFunctionHomework(int value) {
	float minFromX = min(helperX); // left
	float maxFromX = max(helperX); // rigth
	float minFromY = min(helperY); // bottom
	float maxFromY = max(helperY); // top
	bool leftRigthCollision = x > windowWidth - polygonRadiusSize || x < polygonRadiusSize;
	bool topBottomCollision = y > windowHeight - polygonRadiusSize || y < polygonRadiusSize - minFromY;
	if (y > windowHeight - polygonRadiusSize )
	{
		ystep = 0;
	}
	if (x > windowWidth - polygonRadiusSize)
	{
		xstep = 0;
		ystep = -1;
	}
	if (y < polygonRadiusSize - minFromY && x > windowWidth - polygonRadiusSize)
	{
		ystep = 0;
		xstep = -1;
	}
	if (x < polygonRadiusSize &&y < polygonRadiusSize - minFromY)
	{
		xstep = 0;
		ystep = 1;
	}
	if (x < polygonRadiusSize &&y > windowHeight - polygonRadiusSize)
	{
		ystep = 0;
		xstep = 1;
	}
	x += xstep;
	y += ystep;
	//glutReshapeWindow(width, heigth); // change window size to (width,heigth)
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunctionHomework, 1);
}

void SetupRC() {
	// Ustalenie niebieskiego koloru czyszcz¹cego     
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

void program2And3(int argc, char*argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, heigth);
	glutCreateWindow("Mój pierwszy program w GLUT");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(10, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
	delete helperX;
	delete helperY;
}void program3HomeWork(int argc, char*argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, heigth);
	glutCreateWindow("Mój pierwszy program w GLUT");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(10, TimerFunctionHomework, 1);
	SetupRC();
	glutMainLoop();
	delete helperX;
	delete helperY;
}
void main(int argc, char* argv[]) {
	//program2And3(argc, argv);
	program3HomeWork(argc, argv);

}
