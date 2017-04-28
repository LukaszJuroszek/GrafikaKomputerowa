//#include "math.h"
//#ifdef __APPLE__
//#include <GLUT/glut.h>
//#else
//#include <GL/glut.h>
//#endif
//#define gl_pi 3.1415f
//enum
//{
//	exit // wyjęcie
//};
//// wielkość obrotów
//static GLfloat xrot = 0.0f;
//static GLfloat yrot = 0.0f;
//static GLboolean icull, idepth, ioutline;
//// funkcja wykonuje wszystkie konieczne inicjalizacje kontekstu renderowania
//void setuprc()
//{
//	// czarne tło
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	// kolor rysujący ‐ zielony
//	glColor3f(0.0f, 1.0f, 0.0f);
//	// model cieniowania kolorów ‐ płaski
//	glShadeModel(GL_FLAT);
//	// wielokąty o nawinięciu zgodnym z ruchem wskazówek zegara traktowane są
//	// jako skierowane do przodu. takie ustawienie jest konieczne, ponieważ
//	// korzystamy z wachlarzy trójkątów.
//	glFrontFace(GL_CW);
//}
//// wywoływana w celu przerysowania sceny
//void renderscene(void)
//{
//	GLfloat x, y, angle; // przechowują wartości współrzędnych i kąta
//	int ipivot = 1; // do oznaczania zamiennych kolorów
//					// wyczyszczenie okna i bufora głębi
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	// włączenie lub wyłączenie mechanizmu eliminowania ukrytych powierzchni
//	if (icull)
//		glEnable(GL_CULL_FACE);
//	else
//		glDisable(GL_CULL_FACE);
//	// włączenie lub wyłączenie mechanizmu sprawdzania głębi
//	if (idepth)
//		glEnable(GL_DEPTH_TEST);
//	else
//		glDisable(GL_DEPTH_TEST);
//	// jeżeli ten znacznik będzie ustawiony, to wielokąty zwrócone
//	// tyłem do widza będą rysowane tylko w postaci szkieletu
//	if (ioutline)
//		glPolygonMode(GL_BACK, GL_LINE);
//	else
//		glPolygonMode(GL_BACK, GL_FILL);
//	// zapisanie stanu macierzy i wykonanie obrotu
//	glPushMatrix();
//	GLROTATEF(xrot, 1.0f, 0.0f, 0.0f);
//	glrotatef(yrot, 0.0f, 1.0f, 0.0f);
//	// rozpoczęcie rysowania wachlarza trójkątów
//	glbegin(gl_triangle_fan);
//	// czubek stoka jest wspólnym wierzchołkiem wszystkich trójkątów z wachlarza
//	// wysuniętym do góry w osi z. w ten sposób zamiast koła powstanie stożek.
//	glvertex3f(0.0f, 0.0f, 100.0f);
//	// wykonujemy obrót w około i oznaczamy w równych odstępach wierzchołki
//	// tworzące wachlarz trójkątów.
//	for (angle = 0.0f; angle <= (2.0f*gl_pi); angle += (2.0*gl_pi / 5.0f))
//	{
//		// wyliczenie współrzędnych x i y kolejnego wierzchołka
//		x = 50.0f*sin(angle);
//		y = 50.0f*cos(angle);
//		// wybieranie koloru ‐ zielony lub czerwony
//		if ((ipivot % 2) == 0)
//			glcolor3f(0.0f, 1.0f, 0.0f);
//		else
//			glcolor3f(1.0f, 0.0f, 0.0f);
//		// inkrementacja zmiennej okrelającej rodzaj koloru
//		ipivot++;
//		// definiowanie kolejnego wierzchołka w wachlarzu trójkątów
//		glvertex2f(x, y);
//	}
//	// zakoczenie rysowania trójkątów stożka
//	glend();
//	// rozpoczęcie rysowania kolejnego wachlarza trójkątów
//	// zakrywającego podstaw stoka
//	glbegin(gl_triangle_fan);
//	// środek wachlarza znajduje się na początku układu współrzędnych
//	glvertex2f(0.0f, 0.0f);
//	for (angle = 0.0f; angle <= (2.0f*gl_pi); angle += (2.0*gl_pi / 5.0f))
//	{
//		// wyliczenie współrzędnych x i y kolejnego wierzchołka
//		x = 50.0f*sin(angle);
//		y = 50.0f*cos(angle);
//		// wybieranie koloru ‐ zielony lub czerwony
//		if ((ipivot % 2) == 0)
//			glcolor3f(0.0f, 1.0f, 0.0f);
//		else
//			glcolor3f(1.0f, 0.0f, 0.0f);
//		// inkrementacja zmiennej okrelającej rodzaj koloru
//		ipivot++;
//		// definiowanie kolejnego wierzchołka w wachlarzu trójkątów
//		glvertex2f(x, y);
//	}
//	// zakoczenie rysowania trójkątów podstawy stoka
//	glend();
//	// odtworzenie macierzy przekształceń
//	glpopmatrix();
//	// wysłanie poleceń do wykonania
//	glutswapbuffers();
//}
//void specialkeys(int key, int x, int y)
//{
//	if (key == glut_key_up)
//		xrot -= 5.0f;
//	if (key == glut_key_down)
//		xrot += 5.0f;
//	if (key == glut_key_left)
//		yrot = 5.0f;
//	if (key == glut_key_right)
//		yrot += 5.0f;
//	if (key > 356.0f)
//		xrot = 0.0f;
//	if (key < -1.0f)
//		xrot = 355.0f;
//	if (key > 356.0f)
//		yrot = 0.0f;
//	if (key < -1.0f)
//		yrot = 355.0f;
//	// odświeżenie zawartości okna
//	glutpostredisplay();
//}
//void changesize(int w, int h)
//{
//	GLfloat nrange = 100.0f;
//	// zabezpieczenie przed dzieleniem przez zero
//	if (h == 0)
//		h = 1;
//	// ustalenie wymiarów widoku na zgodnych z wymiarami okna
//	glviewport(0, 0, w, h);
//	// ponowne ustawienie stosu macierzy rzutowania
//	glmatrixmode(gl_projection);
//	glloadidentity();
//	// utworzenie przestrzeni ograniczającej (lewo, prawo, dół, góra, blisko, daleko)
//	if (w <= h)
//		glortho(-nrange, nrange, -nrange*h / w, nrange*h / w, -nrange, nrange);
//	else
//		glortho(-nrange*w / h, nrange*w / h, -nrange, nrange, -nrange, nrange);
//	// ponowne ustawienie stosu macierzy rzutowania
//	glmatrixmode(gl_modelview);
//	glloadidentity();
//}
//void menu(int value)
//{
//	switch (value)
//	{
//		//
//	case gl_cull_face:
//		icull = !icull;
//		glutsetwindowtitle("stozek ‐ gl_cull_face");
//		renderscene();
//		break;
//		//
//	case gl_depth_test:
//		idepth = !idepth;
//		glutsetwindowtitle("stozek ‐ gl_depth_test");
//		renderscene();
//		break;
//		//
//	case gl_line:
//		ioutline = true;
//		glutsetwindowtitle("stozek ‐ gl_line");
//		renderscene();
//		break;
//		//
//	case gl_fill:
//		ioutline = false;
//		glutsetwindowtitle("stozek ‐ gl_line");
//		renderscene();
//		break;
//		// wyjęcie
//	case exit:
//		exit(0);
//	}
//}
//int main(int argc, char* argv[])
//{
//	glutinit(&argc, argv);
//	glutinitdisplaymode(glut_double | glut_rgb | glut_depth);
//	glutcreatewindow("triangles constructing fan example");
//	glutreshapefunc(changesize);
//	glutspecialfunc(specialkeys);
//	glutdisplayfunc(renderscene);
//	setuprc();
//	// utworzenie podmenu ‐ prymitywy
//	int menuprimitive = glutcreatemenu(menu);
//	glutaddmenuentry("gl_cull_face", gl_cull_face);
//	glutaddmenuentry("gl_depth_test", gl_depth_test);
//	glutaddmenuentry("polygon mode line", gl_line);
//	glutaddmenuentry("polygon mode fill", gl_fill);
//	glutaddmenuentry("wyjecie", exit);
//	// określenie przycisku myszki obsługującego menu podręczne
//	glutattachmenu(glut_right_button);
//	glutmainloop();
//	return 0;
//}