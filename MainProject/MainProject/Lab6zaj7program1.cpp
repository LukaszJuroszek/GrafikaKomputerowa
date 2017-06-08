//#include <GL/glut.h>
//#include <stdlib.h>
//#include "Glut\colors.h"
//// stałe do obsługi menu podręcznego
//enum
//{
//	FULL_WINDOW = GL_ALWAYS + 100, // aspekt obrazu ‐ całe okno
//	ASPECT_1_1, // aspekt obrazu 1:1
//	EXIT // wyjście
//};
//// aspekt obrazu
//int aspect = FULL_WINDOW;
//// rozmiary bryły obcinania
//const GLdouble left = -2.0;
//const GLdouble right = 2.0;
//const GLdouble bottom = -2.0;
//const GLdouble top = 2.0;
//const GLdouble near_ = 3.0;
//const GLdouble far_ = 7.0;
//// kąty obrotu
//GLfloat rotatex = 0.0;
//GLfloat rotatey = 0.0;
//// wskaźnik naciśnięcia lewego przycisku myszki
//int button_state = GLUT_UP;
//// położenie kursora myszki
//int button_x, button_y;
//// rodzaj testu bufora głębokości
//GLenum depth_test = GL_LESS;
//// funkcja generująca scenę 3D
//void Display()
//{
//	// kolor tła - zawartość bufora koloru
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	// czyszczenie bufora koloru i bufora głębokości
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	// wybór macierzy modelowania
//	glMatrixMode(GL_MODELVIEW);
//	// macierz modelowania = macierz jednostkowa
//	glLoadIdentity();
//	// przesunięcie układu współrzędnych sześcianu do środka bryły odcinania
//	glTranslatef(0, 0, -(near_ + far_) / 2);
//	// obroty sześcianu
//	glRotatef(rotatex, 1.0, 0, 0);
//	glRotatef(rotatey, 0, 1.0, 0);
//	// niewielkie powiększenie sześcianu
//	glScalef(1.15, 1.15, 1.15);
//	// włączenie testu bufora głębokości
//	glEnable(GL_DEPTH_TEST);
//	// wybór funkcji do testu bufora głębokości
//	glDepthFunc(depth_test);
//	// rysowanie sześcianu RGB - 12 trójkątów
//	glBegin(GL_TRIANGLES);
//	glColor3fv(Red);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glColor3fv(Yellow);
//	glVertex3f(1.0, -1.0, 1.0);
//	glColor3fv(White);
//	glVertex3f(1.0, 1.0, 1.0);
//	glColor3fv(Red);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glColor3fv(White);
//	glVertex3f(1.0, 1.0, 1.0);
//	glColor3fv(Magenta);
//	glVertex3f(-1.0, 1.0, 1.0);
//	glColor3fv(Magenta);
//	glVertex3f(-1.0, 1.0, 1.0);
//	glColor3fv(White);
//	glVertex3f(1.0, 1.0, 1.0);
//	glColor3fv(Blue);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glColor3fv(Blue);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glColor3fv(White);
//	glVertex3f(1.0, 1.0, 1.0);
//	glColor3fv(Cyan);
//	glVertex3f(1.0, 1.0, -1.0);
//	glColor3fv(Cyan);
//	glVertex3f(1.0, 1.0, -1.0);
//	glColor3fv(White);
//	glVertex3f(1.0, 1.0, 1.0);
//	glColor3fv(Yellow);
//	glVertex3f(1.0, -1.0, 1.0);
//	glColor3fv(Cyan);
//	glVertex3f(1.0, 1.0, -1.0);
//	glColor3fv(Yellow);
//	glVertex3f(1.0, -1.0, 1.0);
//	glColor3fv(Lime);
//	glVertex3f(1.0, -1.0, -1.0);
//	glColor3fv(Lime);
//	glVertex3f(1.0, -1.0, -1.0);
//	glColor3fv(Yellow);
//	glVertex3f(1.0, -1.0, 1.0);
//	glColor3fv(Black);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glColor3fv(Black);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glColor3fv(Yellow);
//	glVertex3f(1.0, -1.0, 1.0);
//	glColor3fv(Red);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glColor3fv(Black);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glColor3fv(Red);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glColor3fv(Blue);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glColor3fv(Blue);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glColor3fv(Red);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glColor3fv(Magenta);
//	glVertex3f(-1.0, 1.0, 1.0);
//	glColor3fv(Black);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glColor3fv(Blue);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glColor3fv(Cyan);
//	glVertex3f(1.0, 1.0, -1.0);
//	glColor3fv(Lime);
//	glVertex3f(1.0, -1.0, -1.0);
//	glColor3fv(Black);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glColor3fv(Cyan);
//	glVertex3f(1.0, 1.0, -1.0);
//	// koniec definicji sześcianu RGB
//	glEnd();
//	// skierowanie poleceń do wykonania
//	glFlush();
//	// zamiana buforów koloru
//	glutSwapBuffers();
//}
//// zmiana wielkości okna
//void Reshape(int width, int height)
//{
//	// obszar renderingu - całe okno
//	glViewport(0, 0, width, height);
//	// wybór macierzy rzutowania
//	glMatrixMode(GL_PROJECTION);
//	// macierz rzutowania = macierz jednostkowa
//	glLoadIdentity();
//	// parametry bryły obcinania
//	if (aspect == ASPECT_1_1)
//	{
//		// wysokość okna większa od wysokości okna
//		if (width < height && width > 0)
//			glFrustum(left, right, bottom * height / width, top * height / width, near_,
//				far_);
//		else
//			// szerokość okna większa lub równa wysokości okna
//			if (width >= height && height > 0)
//				glFrustum(left * width / height, right * width / height, bottom, top,
//					near_, far_);
//	}
//	else
//		glFrustum(left, right, bottom, top, near_, far_);
//	// generowanie sceny 3D
//	Display();
//}
//// obsługa klawiszy funkcyjnych i klawiszy kursora
//void SpecialKeys(int key, int x, int y)
//{
//	switch (key)
//	{
//		// kursor w lewo
//	case GLUT_KEY_LEFT:
//		rotatey -= 1;
//		break;
//		// kursor w górę
//	case GLUT_KEY_UP:
//		rotatex -= 1;
//		break;
//		// kursor w prawo
//	case GLUT_KEY_RIGHT:
//		rotatey += 1;
//		break;
//		// kursor w dół
//	case GLUT_KEY_DOWN:
//		rotatex += 1;
//		break;
//	}
//	// odrysowanie okna
//	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//}
//// obsługa przycisków myszki
//void MouseButton(int button, int state, int x, int y)
//{
//	if (button == GLUT_LEFT_BUTTON)
//	{
//		// zapamiętanie stanu lewego przycisku myszki
//		button_state = state;
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
//// obsługa menu podręcznego
//void Menu(int value)
//{
//	switch (value)
//	{
//		// obszar renderingu - całe okno
//	case FULL_WINDOW:
//		aspect = FULL_WINDOW;
//		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//		break;
//		// obszar renderingu - aspekt 1:1
//	case ASPECT_1_1:
//		aspect = ASPECT_1_1;
//		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//		break;
//		// test bufora głębokości: GL_NEVER
//	case GL_NEVER:
//		depth_test = GL_NEVER;
//		Display();
//		break;
//		// test bufora głębokości: GL_LESS
//	case GL_LESS:
//		depth_test = GL_LESS;
//		Display();
//		break;
//		// test bufora głębokości: GL_EQUAL
//	case GL_EQUAL:
//		depth_test = GL_EQUAL;
//		Display();
//		break;
//		// test bufora głębokości: GL_LEQUAL
//	case GL_LEQUAL:
//		depth_test = GL_LEQUAL;
//		Display();
//		break;
//		// test bufora głębokości: GL_GREATER
//	case GL_GREATER:
//		depth_test = GL_GREATER;
//		Display();
//		break;
//		// test bufora głębokości: GL_NOTEQUAL
//	case GL_NOTEQUAL:
//		depth_test = GL_NOTEQUAL;
//		Display();
//		break;
//		// test bufora głębokości: GL_GEQUAL
//	case GL_GEQUAL:
//		depth_test = GL_GEQUAL;
//		Display();
//		break;
//		// test bufora głębokości: GL_ALWAYS
//	case GL_ALWAYS:
//		depth_test = GL_ALWAYS;
//		Display();
//		break;
//		// wyjście
//	case EXIT:
//		exit(0);
//	}
//}
//int main(int argc, char * argv[])
//{
//	// inicjalizacja biblioteki GLUT
//	glutInit(&argc, argv);
//	// inicjalizacja bufora ramki
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	// rozmiary głównego okna programu
//	glutInitWindowSize(500, 500);
//	// utworzenie głównego okna programu
//#ifdef WIN32
//	glutCreateWindow("Sześcian 5");
//#else
//	glutCreateWindow("Szescian 5");
//#endif
//	// dołączenie funkcji generującej scenę 3D
//	glutDisplayFunc(Display);
//	// dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
//	glutReshapeFunc(Reshape);
//	// dołączenie funkcji obsługi klawiszy funkcyjnych i klawiszy kursora
//	glutSpecialFunc(SpecialKeys);
//	// obsługa przycisków myszki
//	glutMouseFunc(MouseButton);
//	// obsługa ruchu kursora myszki
//	glutMotionFunc(MouseMotion);
//	// utworzenie menu podręcznego
//	glutCreateMenu(Menu);
//	// utworzenie podmenu - aspekt obrazu
//	int MenuAspect = glutCreateMenu(Menu);
//#ifdef WIN32
//	glutAddMenuEntry("Aspekt obrazu ‐ całe okno", FULL_WINDOW);
//#else
//	glutAddMenuEntry("Aspekt obrazu ‐ cale okno", FULL_WINDOW);
//#endif
//	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);
//	// utworzenie podmenu ‐ Test z‐bufora
//	int MenuZbuffer = glutCreateMenu(Menu);
//	glutAddMenuEntry("GL_NEVER", GL_NEVER);
//	glutAddMenuEntry("GL_LESS", GL_LESS);
//	glutAddMenuEntry("GL_EQUAL", GL_EQUAL);
//	glutAddMenuEntry("GL_LEQUAL", GL_LEQUAL);
//	glutAddMenuEntry("GL_GREATER", GL_GREATER);
//	glutAddMenuEntry("GL_NOTEQUAL", GL_NOTEQUAL);
//	glutAddMenuEntry("GL_GEQUAL", GL_GEQUAL);
//	glutAddMenuEntry("GL_ALWAYS", GL_ALWAYS);
//	// menu główne
//	glutCreateMenu(Menu);
//	glutAddSubMenu("Aspekt obrazu", MenuAspect);
//	glutAddSubMenu("Test z‐bufora", MenuZbuffer);
//#ifdef WIN32
//	glutAddMenuEntry("Wyjście", EXIT);
//#else
//	glutAddMenuEntry("Wyjscie", EXIT);
//#endif
//	// określenie przycisku myszki obsługującej menu podręczne
//	glutAttachMenu(GLUT_RIGHT_BUTTON);
//	// wprowadzenie programu do obsługi pętli komunikatów
//	glutMainLoop();
//	return 0;
//}
