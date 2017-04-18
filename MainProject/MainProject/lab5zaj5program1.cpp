////wektor nolmarny
////apbiet
////wektory normalne, 
////material : mosiądz
//#include <GL/glut.h>
//#include "GLUT\glext.h"
//#ifndef WIN32
//#define GLX_GLXEXT_LEGACY
//#include <GL/glx.h>
//#define wglGetProcAddress glXGetProcAddressARB
//#endif
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//#include "GLUT\colors.h"
//#include "GLUT\materials.h"
//// wskaźnik na funkcję glWindowPos2i
//PFNGLWINDOWPOS2IPROC glWindowPos2i = NULL;
//// stałe do obsługi menu podręcznego
//enum
//{
//	// obiekty
//	OBIEKT, // moj obiekt
//	BRASS, // mosiądz
//				  // obszar renderingu
//				  FULL_WINDOW, // aspekt obrazu - całe okno
//				  ASPECT_1_1, // aspekt obrazu 1:1
//				  EXIT, // wyjście
//						AMBIENT,
//						KIERUNKOWE
//};
//// aspekt obrazu
//int aspect = FULL_WINDOW;
//// usunięcie definicji makr near i far
//#ifdef near
//#undef near
//#endif
//#ifdef far
//#undef far
//#endif
//// rozmiary bryły obcinania
//const GLdouble left = -2.0;
//const GLdouble right = 2.0;
//const GLdouble bottom = -2.0;
//const GLdouble top = 2.0;
//const GLdouble near = 3.0;
//const GLdouble far = 7.0;
//// kąty obrotu obiektu
//GLfloat rotatex = 0.0;
//GLfloat rotatey = 0.0;
//// wskaźnik naciśnięcia lewego przycisku myszki
//int button_state = GLUT_UP;
//// położenie kursora myszki
//int button_x, button_y;
//// współczynnik skalowania
//GLfloat scale = 1.0;
//// właściwości materiału - domyślnie mosiądz
//const GLfloat *ambient = BrassAmbient;
//const GLfloat *diffuse = BrassDiffuse;
//const GLfloat *specular = BrassSpecular;
//GLfloat shininess = BrassShininess;
//// wyświetlany obiekt 3D
//int object = OBIEKT;
//int Swiatlo = KIERUNKOWE;
//// kierunek źródła światła
//GLfloat light_position[4] =
//{
//	0.0,0.0,2.0,0.0
//};
//GLfloat ambient_light[4] =
//{
//	0.2,0.2,0.2,1.0
//};
//// kąty obrotu kierunku źródła światła
//GLfloat light_rotatex = 0.0;
//GLfloat light_rotatey = 0.0;
//// kierunek reflektora
//GLfloat spot_direction[3] =
//{
//	0.0,0.0,-1.0
//};
//// kąt odciêcia reflektora
//GLfloat spot_cutoff = 180.0;
//// wykładnik tłumienia kątowego reflektora
//GLfloat spot_exponent = 128.0;
//// stały współczynnik tłumienia światła
//GLfloat constant_attenuation = 1.0;
//// liniowy współczynnik tłumienia światła
//GLfloat linear_attenuation = 0.0;
//// kwadratowy współczynnik tłumienia światła
//GLfloat quadratic_attenuation = 0.0;
//// funkcja rysująca napis w wybranym miejs
//// funkcja rysująca napis w wybranym miejscu
//// (wersja korzystająca z funkcji glWindowPos2i)
//void DrawString(GLint x, GLint y, char *string)
//{
//	// położenie napisu
//	glWindowPos2i(x, y);
//	// wyświetlenie napisu
//	int len = strlen(string);
//	for (int i = 0; i < len; i++)
//		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
//}
//// funkcja generująca scenę 3D
//void Display()
//{
//	// kolor tła - zawartośæ bufora koloru
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	// czyszczenie bufora koloru i bufora głębokości
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	// wybór macierzy modelowania
//	glMatrixMode(GL_MODELVIEW);
//	// macierz modelowania = macierz jednostkowa
//	glLoadIdentity();
//	// włączenie testu bufora głębokości
//	glEnable(GL_DEPTH_TEST);
//	// włączenie oświetlenia
//	glEnable(GL_LIGHTING);
//	// włączenie światła GL_LIGHT0
//	glEnable(GL_LIGHT0);
//	// włączenie automatycznej normalizacji wektorów normalnych
//	glEnable(GL_NORMALIZE);
//	// przesunięcie układu współrzędnych obiektu do środka bryły odcinania
//	glTranslatef(0, 0, -(near + far) / 2);
//	// obroty obiektu
//	glRotatef(rotatex, 1.0, 0, 0);
//	glRotatef(rotatey, 0, 1.0, 0);
//	// skalowanie obiektu - klawisze "+" i "-"
//	glScalef(scale, scale, scale);
//	// właściwości materiału
//	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
//	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
//	// zmiana kierunku źródła światła jest wykonywana niezależnie
//	// od obrotów obiektu, stąd odłożenie na stos macierzy modelowania
//	glPushMatrix();
//	// macierz modelowania = macierz jednostkowa
//	glLoadIdentity();
//	// obroty kierunku źródła światła - klawisze kursora
//	glRotatef(light_rotatex, 1.0, 0, 0);
//	glRotatef(light_rotatey, 0, 1.0, 0);
//	// ustalenie kierunku źródła światła
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	// przywrócenie pierwotnej macierzy modelowania
//	glPopMatrix();
//	// rysowanie wybranego obiektu 3D
//	switch (object)
//	{
//		// kula
//	case OBIEKT:
//		glBegin(GL_POLYGON);
//		glVertex3f(0.0f, 1.0f, 0.0f);
//		glVertex3f(0.0f, 0.0f, 1.0f);
//		glVertex3f(0.95f, 0.0f, 0.3f);
//		glVertex3f(0.59f, 0.0f, -0.8f);
//		glVertex3f(-0.59f, 0.0f, -0.8f);
//		glVertex3f(-0.95f, 0.0f, 0.3f);
//		glVertex3f(0.0f, 0.0f, 1.0f);
//		glEnd();
//		break;
//		// czajnik
//	}
//
//	// informacje o modyfikowanych wartościach
//	// parametrów źródła światała GL_LIGHT0
//	char string[200];
//	GLfloat vec[4];
//	glColor3fv(Black);
//	// kierunek źródła światła
//	glGetLightfv(GL_LIGHT0, GL_POSITION, vec);
//	sprintf(string, "GL_POSITION = (%f,%f,%f,%f)", vec[0], vec[1], vec[2], vec[3]);
//	DrawString(2, 2, string);
//	// kąty obrotu kierunku źródła światła
//	sprintf(string, "light_rotatex = %f", light_rotatex);
//	DrawString(2, 16, string);
//	sprintf(string, "light_rotatey = %f", light_rotatey);
//	DrawString(2, 30, string);
//	// skierowanie poleceń do wykonania
//	glFlush();
//	// zamiana buforów koloru
//	glutSwapBuffers();
//}
//void Display2()
//{
//	// kolor tła - zawartośæ bufora koloru
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	// czyszczenie bufora koloru i bufora głębokości
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	// wybór macierzy modelowania
//	glMatrixMode(GL_MODELVIEW);
//	glEnable(GL_DEPTH_TEST);
//	// włączenie oświetlenia
//	glEnable(GL_LIGHTING);
//	// włączenie światła GL_LIGHT0
//	glEnable(GL_LIGHT0);
//	// macierz modelowania = macierz jednostkowa
//	glLoadIdentity();
//	// przesunięcie układu współrzędnych sześcianu do środka bryły odcinania
//	// obroty sześcianu
//	glRotatef(rotatex, 1.0, 0, 0);
//	glRotatef(rotatey, 0, 1.0, 0);
//	// niewielkie powiększenie sześcianu
//	glScalef(1.15, 1.15, 1.15);
//	// włączenie oświetlenia
//	glEnable(GL_LIGHTING);
//	// parametry globalnego światła otaczającego
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
//	// włączenie obsługi właściwości materiałów
//	glEnable(GL_COLOR_MATERIAL);
//	// właściwości materiału określone przez kolor wierzchołków
//	glColorMaterial(GL_FRONT, GL_AMBIENT);
//	// włączenie testu bufora głębokości
//	glEnable(GL_DEPTH_TEST);
//	// rysowanie sześcianu ‐ 12 trójkątów
//	switch (object)
//	{
//		// kula
//	case OBIEKT:
//		glBegin(GL_POLYGON);
//		glVertex3f(0.0f, 1.0f, 0.0f);
//		glVertex3f(0.0f, 0.0f, 1.0f);
//		glVertex3f(0.95f, 0.0f, 0.3f);
//		glVertex3f(0.59f, 0.0f, -0.8f);
//		glVertex3f(-0.59f, 0.0f, -0.8f);
//		glVertex3f(-0.95f, 0.0f, 0.3f);
//		glVertex3f(0.0f, 0.0f, 1.0f);
//		glEnd();
//		break;
//		// czajnik
//	}
//
//	// wyłączenie oświetlenia
//	glDisable(GL_LIGHTING);
//	// wyłączenie obsługi właściwości materiałów
//	glDisable(GL_COLOR_MATERIAL);
//	// wyświetlenie składowych globalnego światła otaczającego
//	char string[100];
//	GLfloat rgba[4];
//	glColor3fv(Black);
//	// pobranie wartości składowych światła otaczającego
//	// (oczywiście wartości te odpowiadają tablicy ambient_light)
//	glGetFloatv(GL_LIGHT_MODEL_AMBIENT, rgba);
//	sprintf(string, "AMBIENT: R=%f G=%f B=%f A=%f", rgba[0], rgba[1], rgba[2], rgba[3]);
//	// trzeba odpowiednio przekształciæ układ współrzędnych
//	// aby napis znajdował się na samej "górze" bryły obcinania
//	glLoadIdentity();
//	// narysowanie napisu
//	DrawString(left, bottom, string);
//	// skierowanie poleceñ do wykonania
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
//		// wysokośæ okna większa od wysokości okna
//		if (width < height && width > 0)
//			glFrustum(left, right, bottom*height / width, top*height / width, near, far);
//		else
//			// szerokośæ okna większa lub równa wysokości okna
//			if (width >= height && height > 0)
//				glFrustum(left*width / height, right*width / height, bottom, top, near,
//					far);
//	}
//	else
//		glFrustum(left, right, bottom, top, near, far);
//	// generowanie sceny 3D
//		Display();
//}
//// obsługa klawiatury
//void Keyboard(unsigned char key, int x, int y)
//{
//	switch (key)
//	{
//		// klawisz "+" - powiększenie obiektu
//	case '+':
//		scale += 0.05;
//		break;
//		// klawisz "-" - zmniejszenie obiektu
//	case '-':
//		if (scale > 0.05)
//			scale -= 0.05;
//		break;
//	case 'a':
//		if (Swiatlo == KIERUNKOWE)
//			Swiatlo = AMBIENT;
//		else
//			Swiatlo = KIERUNKOWE;
//		break;
//	}
//	// narysowanie sceny
//		Display();
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
//		rotatey += 30 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
//		button_x = x;
//		rotatex -= 30 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
//		button_y = y;
//		glutPostRedisplay();
//	}
//}
//// obsługa klawiszy funkcyjnych i klawiszy kursora
//void SpecialKeys(int key, int x, int y)
//{
//	switch (key)
//	{
//		// kursor w lewo
//	case GLUT_KEY_LEFT:
//		light_rotatey -= 5;
//		break;
//		// kursor w prawo
//	case GLUT_KEY_RIGHT:
//		light_rotatey += 5;
//		break;
//		// kursor w dół
//	case GLUT_KEY_DOWN:
//		light_rotatex += 5;
//		break;
//		// kursor w górę
//	case GLUT_KEY_UP:
//		light_rotatex -= 5;
//		break;
//	}
//	// odrysowanie okna
//		Display();
//}
//// obsługa menu podręcznego
//void Menu(int value)
//{
//	switch (value)
//	{
//		// rysowany obiekt - kula
//	case OBIEKT:
//		object = OBIEKT;
//		break;
//		// rysowany obiekt - czajnik
//	case AMBIENT:
//		Swiatlo = AMBIENT;
//		break;
//	case KIERUNKOWE:
//		Swiatlo = KIERUNKOWE;
//		break;
//		// rysowany obiekt - czajnik
//		// materiał ‐ mosiądz
//		// materiał ‐ mosiądz
//	case BRASS:
//		ambient = BrassAmbient;
//		diffuse = BrassDiffuse;
//		specular = BrassSpecular;
//		shininess = BrassShininess;
//		break;
//		// materiał ‐ brąz
//		// obszar renderingu ‐ całe okno
//	case FULL_WINDOW:
//		aspect = FULL_WINDOW;
//		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//		break;
//		// obszar renderingu ‐ aspekt 1:1
//	case ASPECT_1_1:
//		aspect = ASPECT_1_1;
//		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//		break;
//		// wyjście
//	case EXIT:
//		exit(0);
//	}
//}
//// sprawdzenie i przygotowanie obsługi wybranych rozszerzeń
//void ExtensionSetup()
//{
//	// pobranie numeru wersji biblioteki OpenGL
//	const char *version = (char*)glGetString(GL_VERSION);
//	// odczyt wersji OpenGL
//	int major = 0, minor = 0;
//	if (sscanf(version, "%d.%d", &major, &minor) != 2)
//	{
//#ifndef WIN32
//		printf("Błędny format wersji OpenGL\n");
//#else
//		printf("Bledny format wersji OpenGL\n");
//#endif
//		exit(0);
//	}
//	// sprawdzenie czy jest co najmniej wersja 1.4
//	if (major > 1 || minor >= 4)
//	{
//		// pobranie wskaźnika wybranej funkcji OpenGL 1.4
//		glWindowPos2i = (PFNGLWINDOWPOS2IPROC)wglGetProcAddress("glWindowPos2i");
//	}
//	else
//		// sprawdzenie czy jest obsługiwane rozszerzenie ARB_window_pos
//		if (glutExtensionSupported("GL_ARB_window_pos"))
//		{
//			// pobranie wskaźnika wybranej funkcji rozszerzenia ARB_window_pos
//			glWindowPos2i = (PFNGLWINDOWPOS2IPROC)wglGetProcAddress
//			("glWindowPos2iARB");
//		}
//		else
//		{
//			printf("Brak rozszerzenia ARB_window_pos!\n");
//			exit(0);
//		}
//}
//int main(int argc, char *argv[])
//{
//	// inicjalizacja biblioteki GLUT
//	glutInit(&argc, argv);
//	// inicjalizacja bufora ramki
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	// rozmiary głównego okna programu
//	glutInitWindowSize(500, 500);
//	// utworzenie głównego okna programu
//#ifdef WIN32
//	glutCreateWindow("światło kierunkowe");
//#else
//	glutCreateWindow("Swiatlo kierunkowe");
//#endif
//	// dołączenie funkcji generującej scenę 3D
//	if (Swiatlo == KIERUNKOWE)
//	{
//		glutDisplayFunc(Display);
//	}
//	else {
//		glutDisplayFunc(Display);
//	}
//	// dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
//	glutReshapeFunc(Reshape);
//	// dołączenie funkcji obsługi klawiatury
//	glutKeyboardFunc(Keyboard);
//	// dołączenie funkcji obsługi klawiszy funkcyjnych i klawiszy kursora
//	glutSpecialFunc(SpecialKeys);
//	// obsługa przycisków myszki
//	glutMouseFunc(MouseButton);
//	// obsługa ruchu kursora myszki
//	glutMotionFunc(MouseMotion);
//	// utworzenie menu podręcznego
//	glutCreateMenu(Menu);
//	// utworzenie podmenu ‐ obiekt
//	int MenuObject = glutCreateMenu(Menu);
//	glutAddMenuEntry("MojObiekt", OBIEKT);
//	int MenuSwiatlo = glutCreateMenu(Menu);
//	glutAddMenuEntry("KIERUNKOWE", KIERUNKOWE);
//	glutAddMenuEntry("AMBIENT", AMBIENT);
//	// utworzenie podmenu ‐ Materiał
//	int MenuMaterial = glutCreateMenu(Menu);
//	glutAddMenuEntry("Mosiądz", BRASS);
//	// utworzenie podmenu ‐ Aspekt obrazu
//	int MenuAspect = glutCreateMenu(Menu);
//#ifdef WIN32
//	glutAddMenuEntry("Aspekt obrazu ‐ całe okno", FULL_WINDOW);
//#else
//	glutAddMenuEntry("Aspekt obrazu ‐ cale okno", FULL_WINDOW);
//#endif
//	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);
//	// menu główne
//	glutCreateMenu(Menu);
//	glutAddSubMenu("Obiekt", MenuObject);
//	glutAddSubMenu("Swiatlo", MenuSwiatlo);
//#ifdef WIN32
//	glutAddSubMenu("Materiał", MenuMaterial);
//#else
//	glutAddSubMenu("Material", MenuMaterial);
//#endif
//	glutAddSubMenu("Aspekt obrazu", MenuAspect);
//#ifdef WIN32
//	glutAddMenuEntry("Wyjście", EXIT);
//#else
//	glutAddMenuEntry("Wyjscie", EXIT);
//#endif
//	// określenie przycisku myszki obsługującej menu podręczne
//	glutAttachMenu(GLUT_RIGHT_BUTTON);
//	// sprawdzenie i przygotowanie obsługi wybranych rozszerzeń
//	ExtensionSetup();
//	// wprowadzenie programu do obsługi pętli komunikatów
//	glutMainLoop();
//	return 0;
//}
//
