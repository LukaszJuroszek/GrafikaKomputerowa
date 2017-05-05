////. (Ostrosłup SUB Kula) OR (Torus AND Kula)
//#include <GL/glut.h>
//#include <stdlib.h>
//#include "Glut/colors.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
//// stałe do obsługi menu podręcznego
//enum
//{
//	CSG_A, // tylko obiekt Kula
//	CSG_B, // tylko obiekt Torus
//	CSG_C, // tylko obiekt Ostrosłup
//	CSG_A_OR_B,
//	CSG_A_OR_C,
//	CSG_A_AND_B,
//	CSG_A_SUB_B,
//	CSG_B_SUB_A,
//	CSG_C_SUB_A,
//	CSG_OSTROSLUP_SUB_Kula_OR_TORUS_AND_KULA, //zadanie
//	FULL_WINDOW, // aspekt obrazu - całe okno
//	ASPECT_1_1, // aspekt obrazu 1:1
//	EXIT // wyjście
//};
//
//// aspekt obrazu
//
//int aspect = FULL_WINDOW;
//
//// rozmiary bryły obcinania
//
//const GLdouble left = -2.0;
//const GLdouble right = 2.0;
//const GLdouble bottom = -2.0;
//const GLdouble top = 2.0;
//const GLdouble nearr = 3.0;
//const GLdouble farr = 7.0;
//
//// kąty obrotu sceny
//
//GLfloat rotatex = 0.0;
//GLfloat rotatey = 0.0;
//
//// wskaźnik naciśnięcia lewego przycisku myszki
//
//int button_state = GLUT_UP;
//
//// położenie kursora myszki
//
//int button_x, button_y;
//
//// identyfikatory list wyświetlania
//
//GLint A, B, C;
//
//// rodzaj operacji CSG
//
//int csg_op = CSG_A_OR_B;
//
//// ustawienie bufora szablonowego tak, aby wydzielić i wyświetlić
//// te elementy obiektu A, które znajdują się we wnętrzu obiektu B;
//// stronę (przednią lub tylną) wyszukiwanych elementów obiektu A
//// określa parametr cull_face
//void CrateObject(int numberOfSides, double radius, float heigth, float x, float y, const  GLfloat*color)
//{
//	//góra
//	glTranslatef(x, y, 0);
//	glBegin(GL_POLYGON);
//	//wysokość stożka
//	glVertex3f(.0f, heigth, .0f);
//	glColor3fv(color);
//	for (int i = 0; i < numberOfSides; i++)
//	{
//		float xx = x + radius * sin(2.0*M_PI*i / numberOfSides);
//		float yy = y + radius * cos(2.0*M_PI*i / numberOfSides);
//		glVertex3f(xx, .0f, yy);
//		glColor3fv(color);
//	}
//	//namalowanie pierwszego wieszkołka do do zamknięcia figury
//	glVertex3f(x + radius * sin(0), .0f, y + radius * cos(0));
//	glColor3fv(color);
//	glEnd();
//	//malowanie podstawy
//	glRotatef(180, 0, 0, 1);
//	glBegin(GL_POLYGON);
//	for (int i = 0; i < numberOfSides; i++)
//	{
//		float xx = x + radius * sin(2.0*M_PI*i / numberOfSides);
//		float yy = y + radius * cos(2.0*M_PI*i / numberOfSides);
//		glVertex3f(xx, .0f, yy);
//		glColor4fv(color);
//	}
//	glEnd();
//}
//void Inside(GLint A, GLint B, GLenum cull_face, GLenum stencil_func)
//{
//	// początkowo rysujemy obiekt A w buforze głębokości przy
//	// wyłączonym zapisie składowych RGBA do bufora kolorów
//
//	// włączenie testu bufora głębokości
//	glEnable(GL_DEPTH_TEST);
//
//	// wyłączenie zapisu składowych RGBA do bufora kolorów
//	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
//
//	// rysowanie wybranej strony wielokątów
//	glCullFace(cull_face);
//
//	// wyświetlenie obiektu A
//	glCallList(A);
//
//	// następnie przy użyciu bufora szablonowego wykrywamy te elementy
//	// obiektu A, które znajdują się wewnątrz obiektu B; w tym celu
//	// zawartość bufora szablonowego jest zwiększana o 1, wszędzie gdzie
//	// będą przednie strony wielokątów składających się na obiekt B
//
//	// wyłączenie zapisu do bufora głębokości
//	glDepthMask(GL_FALSE);
//
//	// włączenie bufora szablonowego
//	glEnable(GL_STENCIL_TEST);
//
//	// test bufora szablonowego
//	glStencilFunc(GL_ALWAYS, 0, 0);
//
//	// określenie operacji na buforze szablonowym
//	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
//
//	// rysowanie tylko przedniej strony wielokątów
//	glCullFace(GL_BACK);
//
//	// wyświetlenie obiektu B
//	glCallList(B);
//
//	// w kolejnym etapie zmniejszamy zawartość bufora szablonowego o 1
//	// wszędzie tam, gdzie są tylne strony wielokątów obiektu B
//
//	// określenie operacji na buforze szablonowym
//	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
//
//	// rysowanie tylko tylnej strony wielokątów
//	glCullFace(GL_FRONT);
//
//	// wyświetlenie obiektu B
//	glCallList(B);
//
//	// dalej wyświetlamy te elementy obiektu A, które
//	// znajdują się we wnętrzu obiektu B
//
//	// włączenie zapisu do bufora głębokości
//	glDepthMask(GL_TRUE);
//
//	// włączenie zapisu składowych RGBA do bufora kolorów
//	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
//
//	// test bufora szablonowego
//	glStencilFunc(stencil_func, 0, 1);
//
//	// wyłączenie testu bufora głębokości
//	glDisable(GL_DEPTH_TEST);
//
//	// rysowanie wybranej strony wielokątów
//	glCullFace(cull_face);
//
//	// wyświetlenie obiektu A
//	glCallList(A);
//
//	// wyłączenie bufora szablonowego
//	glDisable(GL_STENCIL_TEST);
//}
//
//// funkcja generująca scenę 3D
//
//void DisplayScene()
//{
//	// kolor tła - zawartość bufora koloru
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//
//	// czyszczenie bufora koloru, bufora głębokości i bufora szablonowego
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//
//	// wybór macierzy modelowania
//	glMatrixMode(GL_MODELVIEW);
//
//	// macierz modelowania = macierz jednostkowa
//	glLoadIdentity();
//
//	// przesunięcie układu współrzędnych obiektów do środka bryły odcinania
//	glTranslatef(0, 0, -(nearr + farr) / 2);
//
//	// obroty całej sceny
//	glRotatef(rotatex, 1.0, 0.0, 0.0);
//	glRotatef(rotatey, 0.0, 1.0, 0.0);
//
//	// włączenie oświetlenia
//	glEnable(GL_LIGHTING);
//
//	// włączenie światła GL_LIGHT0
//	glEnable(GL_LIGHT0);
//
//	// włączenie automatycznej normalizacji wektorów normalnych
//	glEnable(GL_NORMALIZE);
//
//	// włączenie obsługi właściwości materiałów
//	glEnable(GL_COLOR_MATERIAL);
//
//	// właściwości materiału określone przez kolor wierzchołków
//	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//
//	// włączenie rysowania wybranej strony wielokątów
//	glEnable(GL_CULL_FACE);
//
//	// operacja CSG - tylko obiekt A
//	if (csg_op == CSG_A)
//	{
//		// włączenie testu bufora głębokości
//		glEnable(GL_DEPTH_TEST);
//
//		// wyświetlenie obiektu A
//		glCallList(A);
//
//		// wyłączenie testu bufora głębokości
//		glDisable(GL_DEPTH_TEST);
//	}
//
//	// operacja CSG - tylko obiekt B
//	if (csg_op == CSG_B)
//	{
//		// włączenie testu bufora głębokości
//		glEnable(GL_DEPTH_TEST);
//
//		// wyświetlenie obiektu B
//		glCallList(B);
//
//		// wyłączenie testu bufora głębokości
//		glDisable(GL_DEPTH_TEST);
//	}
//	if (csg_op == CSG_C)
//	{
//
//		// włączenie testu bufora głębokości
//		glEnable(GL_DEPTH_TEST);
//		// wyświetlenie obiektu C
//		glCallList(C);
//
//		// wyłączenie testu bufora głębokości
//		glDisable(GL_DEPTH_TEST);
//	}
//
//	// operacja CSG A lub B
//	if (csg_op == CSG_A_OR_B)
//	{
//		// włączenie testu bufora głębokości
//		glEnable(GL_DEPTH_TEST);
//
//		// wyświetlenie obiektu A i B
//		glCallList(A);
//		glCallList(B);
//
//		// wyłączenie testu bufora głębokości
//		glDisable(GL_DEPTH_TEST);
//	}
//	if (csg_op == CSG_A_OR_C)
//	{
//		// włączenie testu bufora głębokości
//		glEnable(GL_DEPTH_TEST);
//		// wyświetlenie obiektu A i B
//		glCallList(A);
//		glCallList(C);
//
//		// wyłączenie testu bufora głębokości
//		glDisable(GL_DEPTH_TEST);
//	}
//	// operacja CSG A AND B
//	if (csg_op == CSG_A_AND_B)
//	{
//		// elementy obiektu A znajdujące się we wnętrzu B
//		Inside(A, B, GL_BACK, GL_NOTEQUAL);
//		// wyłączenie zapisu składowych RGBA do bufora kolorów
//		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
//		// włączenie testu bufora głębokości
//		glEnable(GL_DEPTH_TEST);
//		// wyłączenie bufora szablonowego
//		glDisable(GL_STENCIL_TEST);
//		// wybór funkcji do testu bufora głębokości
//		glDepthFunc(GL_ALWAYS);
//		// wyświetlenie obiektu B
//		glCallList(B);
//		// wybór funkcji do testu bufora głębokości
//		glDepthFunc(GL_LESS);
//		// elementy obiektu B znajdujące się we wnętrzu A
//		Inside(B, A, GL_BACK, GL_NOTEQUAL);
//	}
//	// operacja CSG A SUB B
//	if (csg_op == CSG_A_SUB_B)
//	{
//		// elementy obiektu A znajdujące się we wnętrzu B
//		Inside(A, B, GL_FRONT, GL_NOTEQUAL);
//		// wyłączenie zapisu składowych RGBA do bufora kolorów
//		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
//		// włączenie testu bufora głębokości
//		glEnable(GL_DEPTH_TEST);
//		// wyłączenie bufora szablonowego
//		glDisable(GL_STENCIL_TEST);
//		// wybór funkcji do testu bufora głębokości
//		glDepthFunc(GL_ALWAYS);
//		// wyświetlenie obiektu B
//		glCallList(B);
//		// wybór funkcji do testu bufora głębokości
//		glDepthFunc(GL_LESS);
//		// elementy obiektu B znajdujące się we wnętrzu A
//		Inside(B, A, GL_BACK, GL_EQUAL);
//	}
//	// operacja CSG B SUB A
//	if (csg_op == CSG_B_SUB_A)
//	{
//		// elementy obiektu B znajdujące się we wnętrzu A
//		Inside(B, A, GL_FRONT, GL_NOTEQUAL);
//		// wyłączenie zapisu składowych RGBA do bufora kolorów
//		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
//		// włączenie testu bufora głębokości
//		glEnable(GL_DEPTH_TEST);
//		// wyłączenie bufora szablonowego
//		glDisable(GL_STENCIL_TEST);
//		// wybór funkcji do testu bufora głębokości
//		glDepthFunc(GL_ALWAYS);
//		// wyświetlenie obiektu A
//		glCallList(A);
//		// wybór funkcji do testu bufora głębokości
//		glDepthFunc(GL_LESS);
//		// elementy obiektu A znajdujące się we wnętrzu B
//		Inside(A, B, GL_BACK, GL_EQUAL);
//	}
//	if (csg_op == CSG_C_SUB_A)
//	{
//		// elementy obiektu B znajdujące się we wnętrzu A
//		Inside(C, A, GL_FRONT, GL_NOTEQUAL);
//		// wyłączenie zapisu składowych RGBA do bufora kolorów
//		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
//		// włączenie testu bufora głębokości
//		glEnable(GL_DEPTH_TEST);
//		// wyłączenie bufora szablonowego
//		glDisable(GL_STENCIL_TEST);
//		// wybór funkcji do testu bufora głębokości
//		glDepthFunc(GL_ALWAYS);
//		// wyświetlenie obiektu A
//		glCallList(A);
//		// wybór funkcji do testu bufora głębokości
//		glDepthFunc(GL_LESS);
//		// elementy obiektu A znajdujące się we wnętrzu B
//		Inside(A, C, GL_BACK, GL_EQUAL);
//	}
//	if (csg_op == CSG_OSTROSLUP_SUB_Kula_OR_TORUS_AND_KULA)
//	{
//		glEnable(GL_DEPTH_TEST);
//
//		Inside(C, A, GL_FRONT, GL_NOTEQUAL);
//		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
//		glEnable(GL_DEPTH_TEST);
//		glDisable(GL_STENCIL_TEST);
//		glDepthFunc(GL_ALWAYS);
//		glCallList(A);
//		glDepthFunc(GL_LESS);
//		Inside(A, C, GL_BACK, GL_EQUAL);
//
//		Inside(A, B, GL_BACK, GL_NOTEQUAL);
//		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
//		glEnable(GL_DEPTH_TEST);
//		glDisable(GL_STENCIL_TEST);
//		glDepthFunc(GL_ALWAYS);
//		glCallList(B);
//		glDepthFunc(GL_LESS);
//		Inside(B, A, GL_BACK, GL_NOTEQUAL);
//		glDisable(GL_DEPTH_TEST);
//	}
//	// skierowanie poleceń do wykonania
//	glFlush();
//
//	// zamiana buforów koloru
//	glutSwapBuffers();
//}
//// zmiana wielkości okna
//void Reshape(int width, int height)
//{
//	// obszar renderingu - całe okno
//	glViewport(0, 0, width, height);
//
//	// wybór macierzy rzutowania
//	glMatrixMode(GL_PROJECTION);
//
//	// macierz rzutowania = macierz jednostkowa
//	glLoadIdentity();
//
//	// parametry bryły obcinania
//	if (aspect == ASPECT_1_1)
//	{
//		// wysokość okna większa od wysokości okna
//		if (width < height && width > 0)
//			glFrustum(left, right, bottom * height / width, top * height / width, nearr, farr);
//		else
//
//			// szerokość okna większa lub równa wysokości okna
//			if (width >= height && height > 0)
//				glFrustum(left * width / height, right * width / height, bottom, top, nearr, farr);
//	}
//	else
//		glFrustum(left, right, bottom, top, nearr, farr);
//
//	// generowanie sceny 3D
//	DisplayScene();
//}
//// obsługa przycisków myszki
//void MouseButton(int button, int state, int x, int y)
//{
//	if (button == GLUT_LEFT_BUTTON)
//	{
//		// zapamiętanie stanu lewego przycisku myszki
//		button_state = state;
//
//		// zapamiętanie położenia kursora myszki
//		if (state == GLUT_DOWN)
//		{
//			button_x = x;
//			button_y = y;
//		}
//	}
//}
//// obsługa ruchu kursora myszki
//void MouseMotion(int x, int y)
//{
//	if (button_state == GLUT_DOWN)
//	{
//		rotatey += 30 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) *(x - button_x);
//		button_x = x;
//		rotatex -= 30 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) *(button_y - y);
//		button_y = y;
//		glutPostRedisplay();
//	}
//}
//
//// obsługa menu podręcznego
//
//void Menu(int value)
//{
//	switch (value)
//	{
//		// operacja CSG
//	case CSG_A:
//	case CSG_B:
//	case CSG_C:
//	case CSG_A_OR_B:
//	case CSG_A_OR_C:
//	case CSG_A_AND_B:
//	case CSG_A_SUB_B:
//	case CSG_B_SUB_A:
//	case CSG_C_SUB_A:
//	case CSG_OSTROSLUP_SUB_Kula_OR_TORUS_AND_KULA:
//		csg_op = value;
//		DisplayScene();
//		break;
//
//		// obszar renderingu - całe okno
//	case FULL_WINDOW:
//		aspect = FULL_WINDOW;
//		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//		break;
//
//		// obszar renderingu - aspekt 1:1
//	case ASPECT_1_1:
//		aspect = ASPECT_1_1;
//		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//		break;
//
//		// wyjście
//	case EXIT:
//		exit(0);
//	}
//}
//
//// utworzenie list wyświetlania
//
//void GenerateDisplayLists()
//{
//	// generowanie identyfikatora pierwszej listy wyświetlania
//	A = glGenLists(1);
//
//	// pierwsza lista wyświetlania
//	glNewList(A, GL_COMPILE);
//
//	// czerwony sześcian
//	glColor4fv(Red);
//	glutSolidSphere(1, 100, 100);
//
//	// koniec pierwszej listy wyświetlania
//	glEndList();
//
//	// generowanie identyfikatora drugiej listy wyświetlania
//	B = glGenLists(1);
//
//	// druga lista wyświetlania
//	glNewList(B, GL_COMPILE);
//
//	// zielona kula
//	glColor4fv(Green);
//	glutSolidTorus(.2, 1, 100, 100);
//
//	glEndList();
//	// generowanie identyfikatora trzeciej listy wyświetlania
//	C = glGenLists(1);
//
//	// druga lista wyświetlania
//	glNewList(C, GL_COMPILE);
//	glColor4fv(Brown);
//	CrateObject(5, 2, 2, 0, 0, Brown);
//	// koniec drugiej listy wyświetlania
//	glEndList();
//}
//
//int main(int argc, char * argv[])
//{
//	// inicjalizacja biblioteki GLUT
//	glutInit(&argc, argv);
//
//	// inicjalizacja bufora ramki
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
//
//	// rozmiary głównego okna programu
//	glutInitWindowSize(500, 500);
//
//	// utworzenie głównego okna programu
//	glutCreateWindow("CSG");
//
//	// dołączenie funkcji generującej scenę 3D
//	glutDisplayFunc(DisplayScene);
//
//	// dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
//	glutReshapeFunc(Reshape);
//
//	// obsługa przycisków myszki
//	glutMouseFunc(MouseButton);
//
//	// obsługa ruchu kursora myszki
//	glutMotionFunc(MouseMotion);
//
//	// utworzenie podmenu - Operacja CSG
//	int MenuCSGOp = glutCreateMenu(Menu);
//	glutAddMenuEntry("A", CSG_A);
//	glutAddMenuEntry("B", CSG_B);
//	glutAddMenuEntry("C", CSG_C);
//	glutAddMenuEntry("A OR B", CSG_A_OR_B);
//	glutAddMenuEntry("A OR c", CSG_A_OR_C);
//	glutAddMenuEntry("CSG_C_SUB_A", CSG_C_SUB_A);
//	glutAddMenuEntry("A AND B", CSG_A_AND_B);
//	glutAddMenuEntry("A SUB B", CSG_A_SUB_B);
//	glutAddMenuEntry("B SUB A", CSG_B_SUB_A);
//	glutAddMenuEntry("Zadanie", CSG_OSTROSLUP_SUB_Kula_OR_TORUS_AND_KULA);
//
//	// utworzenie podmenu - Aspekt obrazu
//	int MenuAspect = glutCreateMenu(Menu);
//#ifdef WIN32
//
//	glutAddMenuEntry("Aspekt obrazu - całe okno", FULL_WINDOW);
//#else
//
//	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
//#endif
//
//	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);
//
//	// menu główne
//	glutCreateMenu(Menu);
//	glutAddSubMenu("Operacja CSG", MenuCSGOp);
//
//#ifdef WIN32
//
//	glutAddSubMenu("Aspekt obrazu", MenuAspect);
//	glutAddMenuEntry("Wyjście", EXIT);
//#else
//
//	glutAddSubMenu("Aspekt obrazu", MenuAspect);
//	glutAddMenuEntry("Wyjscie", EXIT);
//#endif
//
//	// określenie przycisku myszki obsługującego menu podręczne
//	glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//	// utworzenie list wyświetlania
//	GenerateDisplayLists();
//
//	// wprowadzenie programu do obsługi pętli komunikatów
//	glutMainLoop();
//	return 0;
//}