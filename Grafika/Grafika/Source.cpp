#define _USE_MATH_DEFINES
#include <cmath>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
// Pocztkowy rozmiar i pozycja 

GLfloat x = 100.0f;
GLfloat y = 150.0f;
GLsizei rsize = 50;
// Rozmiar kroku (liczba pikseli) w osi x i y
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
//rozmiar okna
int width = 800;
int heigth = 600;
// iloœæ œcian wielok¹tu
int numberOfSides =4;
// Dane zmieniajcych siê rozmiarów okna
GLfloat windowWidth;
GLfloat windowHeight;
// Wywo³ywana w celu przerysowania sceny
void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < numberOfSides; i++)
	{
		GLfloat	xx = x + rsize * sin(2.0*M_PI*i / numberOfSides);
		GLfloat yy = y + rsize * cos(2.0*M_PI*i / numberOfSides);
		glVertex2f(xx, yy);
	}
	glEnd();
	glutSwapBuffers();
}
void TimerFunction(int value) {
	if (x > windowWidth - rsize || x < 0)
		xstep = -xstep;
	if (y > windowHeight - rsize || y < 0)
		ystep = -ystep;
	if (x > windowWidth - rsize)
		x = windowWidth - rsize - 1;
	if (y > windowHeight - rsize)
		y = windowHeight - rsize - 1;
	x += xstep;
	y += ystep;
	glutPostRedisplay();

	glutTimerFunc(33, TimerFunction, 1);
}

void SetupRC() {
	// Ustalenie niebieskiego koloru czyszcz¹cego     
	glClearColor(0.6f, 0.4f, 0.12f, 1.0f);
}
void ChangeSize(GLsizei w, GLsizei h) {
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;
	// Ustalenie wielkoœci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);
	// Ustalenie uk³adu wspó³rzêdnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Keep the square square, this time, save calculated
	// width and height for later use
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
	// Ustanowienie przestrzeni ograniczaj¹cej (lewo, prawo, dó³, góra, blisko, daleko)
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void program1and2(int argc, char*argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, heigth);
	glutCreateWindow("Mój pierwszy program w GLUT");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}
void program3(int argc, char*argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, heigth);
	glutCreateWindow("Mój pierwszy program w GLUT");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}
void main(int argc, char* argv[]) {
	program3(argc, argv);
	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//glutInitWindowSize(800, 600);
	//glutCreateWindow("Bounce");
	//glutDisplayFunc(RenderScene);
	//glutReshapeFunc(ChangeSize);
	//glutTimerFunc(33, TimerFunction, 1);
	//SetupRC();
	//glutMainLoop();
}
