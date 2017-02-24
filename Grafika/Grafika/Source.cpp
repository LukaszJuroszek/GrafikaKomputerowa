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
// Dane zmieniajcych siê rozmiarów okna
GLfloat windowWidth;
GLfloat windowHeight;
///////////////////////////////////////////////////////////
// Wywo³ywana w celu przerysowania sceny
void RenderScene(void) {
	// Wyczyszczenie okna aktualnym kolorem czyszcz¹cym
	glClear(GL_COLOR_BUFFER_BIT);
	// Aktualny kolor rysuj¹cy - czerwony
	glColor3f(1.0f, 0.0f, 0.0f);

	// Rysowanie n elementowego polygonu ( pentagramu ) 
	glBegin(GL_POLYGON);
	int numberOfSides = 5;
	GLfloat scale = 50.0f;
	for (int i = 0; i < numberOfSides; i++)
	{
		GLfloat	xx = x + scale * sin(2.0*M_PI*i / numberOfSides);
		GLfloat yy = y + scale * cos(2.0*M_PI*i / numberOfSides);
		glVertex2f(xx, yy);
	}
	glEnd();
	// Wys³anie poleceñ do wykonania - !!! dla animacji to jest inne polecenie
	glutSwapBuffers();
}
// Wywo³ywana przez bibliotek GLUT w czasie, gdy okno nie
// jest przesuwane ani nie jest zmieniana jego wielkoœæ
void TimerFunction(int value) {
	// Odwrócenie kierunku, je¿eli osi¹gniêto lew¹ lub praw¹ krawêdŸ
	if (x > windowWidth - rsize || x < 0)
		xstep = -xstep;
	// Odwrócenie kierunku, je¿eli osi¹gniêto doln¹ lub górn¹ krawêdŸ
	if (y > windowHeight - rsize || y < 0)
		ystep = -ystep;
	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno     
	// zmniejszy³o swoj wielkoœæ w czasie, gdy kwadrat odbija³ siê od     
	// krawêdzi, co mog³oby spowodowaæ, ¿e znalaz³ by siê poza      
	// przestrzeni¹ ograniczajc¹.     
	if (x > windowWidth - rsize)
		x = windowWidth - rsize - 1;
	if (y > windowHeight - rsize)
		y = windowHeight - rsize - 1;
	// Wykonanie przesuniêcia kwadratu
	x += xstep;
	y += ystep;
	// Ponowne rysowanie sceny z nowymi wspó³rzêdnymi  
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}
///////////////////////////////////////////////////////////
// Konfigurowanie stanu renderowania
void SetupRC(void) {
	// Ustalenie niebieskiego koloru czyszcz¹cego     
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}
///////////////////////////////////////////////////////////
// Wywo³ywana przez bibliotek GLUT przy ka¿dej zmianie wielkoœci okna
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
void program1(int argc, char*argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Mój pierwszy program w GLUT");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();
}
///////////////////////////////////////////////////////////
// G³ówny punkt wejœcia programu
void main(int argc, char* argv[]) {
	program1(argc, argv);
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
