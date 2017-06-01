/*
(c) Janusz Ganczarski
http://www.januszg.hg.pl
JanuszG@enter.net.pl
*/
#include <GL/glut.h>
#include <GLUT/glext.h>
#ifndef WIN32
#define GLX_GLXEXT_LEGACY
#include <GL/glx.h>
#define wglGetProcAddress glXGetProcAddressARB
#endif
#include <stdio.h>
#include <stdlib.h>
#include <GLUT\colors.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
// wska�nik na funkcj� glWindowPos2i
PFNGLWINDOWPOS2IPROC glWindowPos2i = NULL;
#define NUM_PARTICLES 1000 /* Number of particles */
#define NUM_DEBRIS 70 /* Number of debris */
/* GLUT menu entries */
#define PAUSE 0
#define NORMALIZE_SPEED 1
#define QUIT 2
/* A particle */
struct particleData
{
	float position[3];
	float speed[3];
	float color[3];
};
typedef struct particleData particleData;
/* A piece of debris */
struct debrisData
{
	float position[3];
	float speed[3];
	float orientation[3]; /* Rotation angles around x, y, and z axes */
	float orientationSpeed[3];
	float color[3];
	float scale[3];
};
typedef struct debrisData debrisData;
/* Globals */
particleData particles[NUM_PARTICLES];
debrisData debris[NUM_DEBRIS];
int fuel = 0; /* "fuel" of the explosion */
float angle = 0.0; /* camera rotation angle */
				   /* Light sources and
				   material */
GLfloat light0Amb[4] = { 1.0, 0.6, 0.2, 1.0 };
GLfloat light0Dif[4] = { 1.0, 0.6, 0.2, 1.0 };
GLfloat light0Spec[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light0Pos[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light1Amb[4] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light1Dif[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1Spec[4] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1Pos[4] = { 0.0, 5.0, 5.0, 0.0 };
GLfloat materialAmb[4] = { 0.25, 0.22, 0.26, 1.0 };
GLfloat materialDif[4] = { 0.63, 0.57, 0.60, 1.0 };
GLfloat materialSpec[4] = { 0.99, 0.91, 0.81, 1.0 };
GLfloat materialShininess = 27.8;
int wantNormalize = 0; /* Speed vector normalization flag */
int wantPause = 0; /* Pause flag */
				   /*
				   * newSpeed
				   *
				   * Randomize a new speed vector.
				   *
				   */
				   // sta�e do obs�ugi menu podr�cznego
enum
{
	FULL_WINDOW = GL_ALWAYS + 100, // aspekt obrazu - ca�e okno
	ASPECT_1_1, // aspekt obrazu 1:1
	EXIT // wyj�cie
};
// aspekt obrazu
int aspect = FULL_WINDOW;
// usuni�cie definicji makr near i far
#ifdef near
#undef near
#endif
#ifdef far
#undef far
#endif
 // rozmiary bry�y obcinania
const GLdouble left = -2.0;
const GLdouble right = 2.0;
const GLdouble bottom = -2.0;
const GLdouble top = 2.0;
const GLdouble near = 3.0;
const GLdouble far = 7.0;
// k�ty obrotu
GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;
// wska�nik naci�ni�cia lewego przycisku myszki
int button_state = GLUT_UP;
// po�o�enie kursora myszki
int button_x, button_y;
// identyfikator listy wy�wietlania
GLuint CUBE_LIST;
// wskaz�wki jako�ci generacji mg�y
GLint fog_hint = GL_DONT_CARE;
// pocz�tek i koniec oddzia�ywania mg�y liniowej
GLfloat fog_start = 3.0;
GLfloat fog_end = 5.0;
// g�sto�� mg�y
GLfloat fog_density = 0.5;
// rodzaj mg�y
GLfloat fog_mode = GL_LINEAR;
// funkcja rysuj�ca napis w wybranym miejscu
// (wersja korzystaj�ca z funkcji glWindowPos2i)
void DrawString(GLint x, GLint y, char * string)
{
	// po�o�enie napisu
	glWindowPos2i(x, y);
	// wy�wietlenie napisu
	int len = strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
}
// funkcja generuj�ca scen� 3D
void DisplayScene()
{
	// kolor t�a - zawarto�� bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// czyszczenie bufora koloru i bufora g��boko�ci
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// wyb�r macierzy modelowania
	glMatrixMode(GL_MODELVIEW);
	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();
	// przesuni�cie uk�adu wsp�rz�dnych sze�cianu do �rodka bry�y odcinania
	glTranslatef(0.0, 0.0, -(near + far) / 2);
	// obroty sze�cianu
	glRotatef(rotatex, 1.0, 0.0, 0.0);
	glRotatef(rotatey, 0.0, 1.0, 0.0);
	// niewielkie powi�kszenie sze�cianu
	glScalef(1.15, 1.15, 1.15);
	// w��czenie testu bufora g��boko�ci
	glEnable(GL_DEPTH_TEST);
	// w��czenie efektu mg�y
	glEnable(GL_FOG);
	// wskaz�wki jako�ci generacji mg�y
	glHint(GL_FOG_HINT, fog_hint);
	// kolor mg�y
	glFogfv(GL_FOG_COLOR, White);
	// g�sto�� mg�y
	glFogf(GL_FOG_DENSITY, fog_density);
	// rodzaj mg�y
	glFogf(GL_FOG_MODE, fog_mode);
	// pocz�tek i koniec oddzia�ywania mg�y liniowej
	glFogf(GL_FOG_START, fog_start);
	glFogf(GL_FOG_END, fog_end);
	// wy�wietlenie sze�cianu
	if (fuel == 0)
	{
		glCallList(CUBE_LIST);
		// wy��czenie efektu mg�y
		glDisable(GL_FOG);
	}
	if (fuel > 0)
	{
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glBegin(GL_POINTS);
		for (int i = 0; i < NUM_PARTICLES; i++)
		{
			glColor3fv(particles[i].color);
			glVertex3fv(particles[i].position);
		}
		glEnd();
		glPopMatrix();
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		glNormal3f(0.0, 0.0, 1.0);
		for (int i = 0; i < NUM_DEBRIS; i++)
		{
			glColor3fv(debris[i].color);
			glPushMatrix();
			glTranslatef(debris[i].position[0],
				debris[i].position[1],
				debris[i].position[2]);
			glRotatef(debris[i].orientation[0], 1.0, 0.0, 0.0);
			glRotatef(debris[i].orientation[1], 0.0, 1.0, 0.0);
			glRotatef(debris[i].orientation[2], 0.0, 0.0, 1.0);
			glScalef(debris[i].scale[0],
				debris[i].scale[1],
				debris[i].scale[2]);
			glBegin(GL_TRIANGLES);
			glVertex3f(0.0, 0.5, 0.0);
			glVertex3f(-0.25, 0.0, 0.0);
			glVertex3f(0.25, 0.0, 0.0);
			glEnd();
			glPopMatrix();
		}
	}
	// wy�wietlenie wybranych informacji
	char string[200];
	GLfloat var[4];
	glColor3fv(Black);
	// g�sto�� mg�y
	glGetFloatv(GL_FOG_DENSITY, var);
	sprintf(string, "GL_FOG_DENSITY = %f", var[0]);
	DrawString(2, 2, string);
	// informacja o wskaz�wkach generacji mg�y
	glGetFloatv(GL_FOG_HINT, var);
	switch ((int)var[0])
	{
	case GL_FASTEST:
		sprintf(string, "GL_FOG_HINT = GL_FASTEST");
		break;
	case GL_DONT_CARE:
		sprintf(string, "GL_FOG_HINT = GL_DONT_CARE");
		break;
	case GL_NICEST:
		sprintf(string, "GL_FOG_HINT = GL_NICEST");
		break;
	}
	DrawString(2, 16, string);
	// pocz�tek i koniec oddzia�ywania mg�y liniowej
	glGetFloatv(GL_FOG_START, var);
	glGetFloatv(GL_FOG_END, var + 1);
	sprintf(string, "GL_FOG_START = %f GL_FOG_END = %f", var[0], var[1]);
	DrawString(2, 30, string);
	// rodzaj mg�y
	glGetFloatv(GL_FOG_MODE, var);
	switch ((int)var[0])
	{
	case GL_LINEAR:
		sprintf(string, "GL_FOG_MODE = GL_LINEAR");
		break;
	case GL_EXP:
		sprintf(string, "GL_FOG_MODE = GL_EXP");
		break;
	case GL_EXP2:
		sprintf(string, "GL_FOG_MODE = GL_EXP2");
		break;
	}
	DrawString(2, 44, string);
	// skierowanie polece� do wykonania
	glFlush();
	// zamiana bufor�w koloru
	glutSwapBuffers();
}

void newSpeed(float dest[3])
{
	float x;
	float y;
	float z;
	float len;
	x = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
	y = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
	z = (2.0 * ((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
	/*
	* Normalizing the speed vectors gives a "fireball" effect
	*
	*/
	if (wantNormalize)
	{
		len = sqrt(x * x + y * y + z * z);
		if (len)
		{
			x = x / len;
			y = y / len;
			z = z / len;
		}
	}
	dest[0] = x;
	dest[1] = y;
	dest[2] = z;
}
void newExplosion(void)
{
	int i;
	for (i = 0; i < NUM_PARTICLES; i++)
	{
		particles[i].position[0] = 0.0;
		particles[i].position[1] = 0.0;
		particles[i].position[2] = 0.0;
		particles[i].color[0] = 1.0;
		particles[i].color[1] = 1.0;
		particles[i].color[2] = 0.5;
		newSpeed(particles[i].speed);
	}
	for (i = 0; i < NUM_DEBRIS; i++)
	{
		debris[i].position[0] = 0.0;
		debris[i].position[1] = 0.0;
		debris[i].position[2] = 0.0;
		debris[i].orientation[0] = 0.0;
		debris[i].orientation[1] = 0.0;
		debris[i].orientation[2] = 0.0;
		debris[i].color[0] = 0.7;
		debris[i].color[1] = 0.7;
		debris[i].color[2] = 0.7;
		debris[i].scale[0] = (2.0 *
			((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
		debris[i].scale[1] = (2.0 *
			((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
		debris[i].scale[2] = (2.0 *
			((GLfloat)rand()) / ((GLfloat)RAND_MAX)) - 1.0;
		newSpeed(debris[i].speed);
		newSpeed(debris[i].orientationSpeed);
	}
	fuel = 100;
}
void keyboard(unsigned char key,
	int x,
	int y)
{
	switch (key)
	{
	case ' ':
		newExplosion();
		break;
	case 27:
		exit(0);
		break;
	case 'p':
		wantPause = 1 - wantPause;
		break;
	}
}
/*
* idle
*
* Update animation variables.
*
*/
void idle(void)
{
	int i;
	if (!wantPause)
	{
		if (fuel > 0)
		{
			for (i = 0; i < NUM_PARTICLES; i++)
			{
				particles[i].position[0] += particles[i].speed[0] * 0.2;
				particles[i].position[1] += particles[i].speed[1] * 0.2;
				particles[i].position[2] += particles[i].speed[2] * 0.2;
				particles[i].color[0] -= 1.0 / 500.0;
				if (particles[i].color[0] < 0.0)
				{
					particles[i].color[0] = 0.0;
				}
				particles[i].color[1] -= 1.0 / 100.0;
				if (particles[i].color[1] < 0.0)
				{
					particles[i].color[1] = 0.0;
				}
				particles[i].color[2] -= 1.0 / 50.0;
				if (particles[i].color[2] < 0.0)
				{
					particles[i].color[2] = 0.0;
				}
			}
			for (i = 0; i < NUM_DEBRIS; i++)
			{
				debris[i].position[0] += debris[i].speed[0] * 0.1;
				debris[i].position[1] += debris[i].speed[1] * 0.1;
				debris[i].position[2] += debris[i].speed[2] * 0.1;
				debris[i].orientation[0] += debris[i].orientationSpeed[0] * 10;
				debris[i].orientation[1] += debris[i].orientationSpeed[1] * 10;
				debris[i].orientation[2] += debris[i].orientationSpeed[2] * 10;
			}
			--fuel;
		}
		angle += 0.3; /* Always continue to rotate the camera */
	}
	glutPostRedisplay();
}
 // zmiana wielko�ci okna
void Reshape(int width, int height)
{
	// obszar renderingu - ca�e okno
	glViewport(0, 0, width, height);
	// wyb�r macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();
	// parametry bry�y obcinania
	if (aspect == ASPECT_1_1)
	{
		// wysoko�� okna wi�ksza od wysoko�ci okna
		if (width < height && width > 0)
			glFrustum(left, right, bottom * height / width, top * height / width, near, far);
		else
			// szeroko�� okna wi�ksza lub r�wna wysoko�ci okna
			if (width >= height && height > 0)
				glFrustum(left * width / height, right * width / height, bottom, top, near, far);
	}
	else
		glFrustum(left, right, bottom, top, near, far);
	// generowanie sceny 3D
	DisplayScene();
}
// obs�uga klawiatury
void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+')
		fog_density += 0.05;
	else
		// klawisz -
		if (key == '-' && fog_density > 0.05)
			fog_density -= 0.05;

	switch (key)
	{
	case ' ':
		newExplosion();
		break;
	case 27:
		exit(0);
		break;
	case 'p':
		wantPause = 1 - wantPause;
		break;
	}

	// narysowanie sceny
	DisplayScene();
}
// obs�uga klawiszy funkcyjnych i klawiszy kursora
void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		// kursor w g�r�
	case GLUT_KEY_UP:
		fog_start += 0.1;
		fog_end += 0.1;
		break;
		// kursor w d�
	case GLUT_KEY_DOWN:
		fog_start -= 0.1;
		fog_end -= 0.1;
		break;
	}
	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
// obs�uga przycisk�w myszki
void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// zapami�tanie stanu lewego przycisku myszki
		button_state = state;
		// zapami�tanie po�o�enia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}
// obs�uga ruchu kursora myszki
void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		rotatey += 30 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) *(x - button_x);
		button_x = x;
		rotatex -= 30 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) *(button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}
// obs�uga menu podr�cznego
void Menu(int value)
{
	switch (value)
	{
		// rodzaj mg�y
	case GL_LINEAR:
	case GL_EXP:
	case GL_EXP2:
		fog_mode = value;
		DisplayScene();
		break;
		// GL_FOG_HINT
	case GL_FASTEST:
	case GL_DONT_CARE:
	case GL_NICEST:
		fog_hint = value;
		DisplayScene();
		break;
		// obszar renderingu - ca�e okno
	case FULL_WINDOW:
		aspect = FULL_WINDOW;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
		// obszar renderingu - aspekt 1:1
	case ASPECT_1_1:
		aspect = ASPECT_1_1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
		// wyj�cie
	case EXIT:
		exit(0);
	}
}
// utworzenie list wy�wietlania
void GenerateDisplayLists()
{
	// generowanie identyfikatora listy wy�wietlania
	CUBE_LIST = glGenLists(1);
	// lista wy�wietlania
	glNewList(CUBE_LIST, GL_COMPILE);
	// rysowanie sze�cianu RGB - 12 tr�jk�t�w
	glBegin(GL_POLYGON);
	glColor3fv(Red);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.95f, 0.0f, 0.3f);
	glVertex3f(0.59f, 0.0f, -0.8f);
	glVertex3f(-0.59f, 0.0f, -0.8f);
	glVertex3f(-0.95f, 0.0f, 0.3f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	// koniec definicji sze�cianu RGB
	glEnd();
	// koniec listy wy�wietlania
	glEndList();
}
// sprawdzenie i przygotowanie obs�ugi wybranych rozszerze�
void ExtensionSetup()
{
	// pobranie numeru wersji biblioteki OpenGL
	const char * version = (char *)glGetString(GL_VERSION);
	// odczyt wersji OpenGL
	int major = 0, minor = 0;
	if (sscanf(version, "%d.%d", &major, &minor) != 2)
	{
#ifdef WIN32
		printf("B��dny format wersji OpenGL\n");
#else
		printf("Bledny format wersji OpenGL\n");
#endif
		exit(0);
	}
	// sprawdzenie czy jest co najmniej wersja 1.4
	if (major > 1 || minor >= 4)
	{
		// pobranie wska�nika wybranej funkcji OpenGL 1.4
		glWindowPos2i = (PFNGLWINDOWPOS2IPROC)wglGetProcAddress("glWindowPos2i");
	}
	else
		// sprawdzenie czy jest obs�ugiwane rozszerzenie ARB_window_pos
		if (glutExtensionSupported("GL_ARB_window_pos"))
		{
			// pobranie wska�nika wybranej funkcji rozszerzenia ARB_window_pos
			glWindowPos2i = (PFNGLWINDOWPOS2IPROC)wglGetProcAddress
			("glWindowPos2iARB");
		}
		else
		{
			printf("Brak rozszerzenia ARB_window_pos!\n");
			exit(0);
		}
}
int main(int argc, char * argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);
	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// rozmiary g��wnego okna programu
	glutInitWindowSize(500, 500);
	// utworzenie g��wnego okna programu
#ifdef WIN32
	glutCreateWindow("Mg�a odleg�o�ciowa");
#else
	glutCreateWindow("Mgla odleglosciowa");
#endif
	glutIdleFunc(idle);
	// do��czenie funkcji generuj�cej scen� 3D
	glutDisplayFunc(DisplayScene);
	// do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);
	// do��czenie funkcji obs�ugi klawiatury
	glutKeyboardFunc(Keyboard);
	// do��czenie funkcji obs�ugi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);
	// obs�uga przycisk�w myszki
	glutMouseFunc(MouseButton);
	// obs�uga ruchu kursora myszki
	glutMotionFunc(MouseMotion);

	// utworzenie menu podr�cznego
	glutCreateMenu(Menu);
	// utworzenie podmenu - aspekt obrazu
	int MenuAspect = glutCreateMenu(Menu);
#ifdef WIN32
	glutAddMenuEntry("Aspekt obrazu - ca�e okno", FULL_WINDOW);
#else
	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
#endif
	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);
	// utworzenie podmenu - Rodzaj mg�y
	int MenuFogMode = glutCreateMenu(Menu);
	glutAddMenuEntry("GL_LINEAR", GL_LINEAR);
	glutAddMenuEntry("GL_EXP", GL_EXP);
	glutAddMenuEntry("GL_EXP2", GL_EXP2);
	// utworzenie podmenu - GL_FOG_HINT
	int MenuFogHint = glutCreateMenu(Menu);
	glutAddMenuEntry("GL_FASTEST", GL_FASTEST);
	glutAddMenuEntry("GL_DONT_CARE", GL_DONT_CARE);
	glutAddMenuEntry("GL_NICEST", GL_NICEST);
	// menu g��wne
	glutCreateMenu(Menu);
#ifdef WIN32
	glutAddSubMenu("Rodzaj mg�y", MenuFogMode);
	glutAddSubMenu("GL_FOG_HINT", MenuFogHint);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
	glutAddMenuEntry("Wyj�cie", EXIT);
#else
	glutAddSubMenu("Rodzaj mgly", MenuFogMode);
	glutAddSubMenu("GL_FOG_HINT", MenuFogHint);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
	glutAddMenuEntry("Wyjscie", EXIT);
#endif
	// okre�lenie przycisku myszki obs�uguj�cej menu podr�czne
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	// sprawdzenie i przygotowanie obs�ugi wybranych rozszerze�
	ExtensionSetup();
	// utworzenie list wy�wietlania
	GenerateDisplayLists();
	// wprowadzenie programu do obs�ugi p�tli komunikat�w
	glutMainLoop();
	return 0;
}