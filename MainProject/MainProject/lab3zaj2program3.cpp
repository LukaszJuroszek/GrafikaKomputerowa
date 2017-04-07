﻿//#include <math.h>
//
//#ifdef __APPLE__
//#include <GLUT/glut.h>
//#else
//#include "GL\glut.h"
//#endif
//// Wielkoci obrotów
//static GLfloat xRot = 0.0f;
//static GLfloat yRot = 0.0f;
//typedef GLfloat GLTVector2[2];      // Two component floating point vector
//typedef GLfloat GLTVector3[3];      // Three component floating point vector
//typedef GLfloat GLTVector4[4];      // Four component floating point vector
//typedef GLfloat GLTMatrix[16];
//using namespace std;
//void gltAddVectors(const GLTVector3 vFirst, const GLTVector3 vSecond, GLTVector3 vResult) {
//	vResult[0] = vFirst[0] + vSecond[0];
//	vResult[1] = vFirst[1] + vSecond[1];
//	vResult[2] = vFirst[2] + vSecond[2];
//}
//
//// Subtract one vector from another
//void gltSubtractVectors(const GLTVector3 vFirst, const GLTVector3 vSecond, GLTVector3 vResult)
//{
//	vResult[0] = vFirst[0] - vSecond[0];
//	vResult[1] = vFirst[1] - vSecond[1];
//	vResult[2] = vFirst[2] - vSecond[2];
//}
//
//// Scales a vector by a scalar
//void gltScaleVector(GLTVector3 vVector, const GLfloat fScale)
//{
//	vVector[0] *= fScale; vVector[1] *= fScale; vVector[2] *= fScale;
//}
//
//// Gets the length of a vector squared
//GLfloat gltGetVectorLengthSqrd(const GLTVector3 vVector)
//{
//	return (vVector[0] * vVector[0]) + (vVector[1] * vVector[1]) + (vVector[2] * vVector[2]);
//}
//
//// Gets the length of a vector
//GLfloat gltGetVectorLength(const GLTVector3 vVector)
//{
//	return (GLfloat)sqrt(gltGetVectorLengthSqrd(vVector));
//}
//
//// Scales a vector by it's length - creates a unit vector
//void gltNormalizeVector(GLTVector3 vNormal)
//{
//	GLfloat fLength = 1.0f / gltGetVectorLength(vNormal);
//	gltScaleVector(vNormal, fLength);
//}
//
//// Copies a vector
//void gltCopyVector(const GLTVector3 vSource, GLTVector3 vDest)
//{
//	memcpy(vDest, vSource, sizeof(GLTVector3));
//}
//
//// Get the dot product between two vectors
//GLfloat gltVectorDotProduct(const GLTVector3 vU, const GLTVector3 vV)
//{
//	return vU[0] * vV[0] + vU[1] * vV[1] + vU[2] * vV[2];
//}
//
//// Calculate the cross product of two vectors
//void gltVectorCrossProduct(const GLTVector3 vU, const GLTVector3 vV, GLTVector3 vResult)
//{
//	vResult[0] = vU[1] * vV[2] - vV[1] * vU[2];
//	vResult[1] = -vU[0] * vV[2] + vV[0] * vU[2];
//	vResult[2] = vU[0] * vV[1] - vV[0] * vU[1];
//}
//
//
//
//// Given three points on a plane in counter clockwise order, calculate the unit normal
//void gltGetNormalVector(const GLTVector3 vP1, const GLTVector3 vP2, const GLTVector3 vP3, GLTVector3 vNormal)
//{
//	GLTVector3 vV1, vV2;
//
//	gltSubtractVectors(vP2, vP1, vV1);
//	gltSubtractVectors(vP3, vP1, vV2);
//
//	gltVectorCrossProduct(vV1, vV2, vNormal);
//	gltNormalizeVector(vNormal);
//}
//
//
//
//// Transform a point by a 4x4 matrix
//void gltTransformPoint(const GLTVector3 vSrcVector, const GLTMatrix mMatrix, GLTVector3 vOut)
//{
//	vOut[0] = mMatrix[0] * vSrcVector[0] + mMatrix[4] * vSrcVector[1] + mMatrix[8] * vSrcVector[2] + mMatrix[12];
//	vOut[1] = mMatrix[1] * vSrcVector[0] + mMatrix[5] * vSrcVector[1] + mMatrix[9] * vSrcVector[2] + mMatrix[13];
//	vOut[2] = mMatrix[2] * vSrcVector[0] + mMatrix[6] * vSrcVector[1] + mMatrix[10] * vSrcVector[2] + mMatrix[14];
//}
//
//// Rotates a vector using a 4x4 matrix. Translation column is ignored
//void gltRotateVector(const GLTVector3 vSrcVector, const GLTMatrix mMatrix, GLTVector3 vOut)
//{
//	vOut[0] = mMatrix[0] * vSrcVector[0] + mMatrix[4] * vSrcVector[1] + mMatrix[8] * vSrcVector[2];
//	vOut[1] = mMatrix[1] * vSrcVector[0] + mMatrix[5] * vSrcVector[1] + mMatrix[9] * vSrcVector[2];
//	vOut[2] = mMatrix[2] * vSrcVector[0] + mMatrix[6] * vSrcVector[1] + mMatrix[10] * vSrcVector[2];
//}
//
//
//// Gets the three coefficients of a plane equation given three points on the plane.
//void gltGetPlaneEquation(GLTVector3 vPoint1, GLTVector3 vPoint2, GLTVector3 vPoint3, GLTVector3 vPlane)
//{
//	// Get normal vector from three points. The normal vector is the first three coefficients
//	// to the plane equation...
//	gltGetNormalVector(vPoint1, vPoint2, vPoint3, vPlane);
//
//	// Final coefficient found by back substitution
//	vPlane[3] = -(vPlane[0] * vPoint3[0] + vPlane[1] * vPoint3[1] + vPlane[2] * vPoint3[2]);
//}
//
//// Determine the distance of a point from a plane, given the point and the
//// equation of the plane.
//GLfloat gltDistanceToPlane(GLTVector3 vPoint, GLTVector4 vPlane)
//{
//	return vPoint[0] * vPlane[0] + vPoint[1] * vPlane[1] + vPoint[2] * vPlane[2] + vPlane[3];
//}
//// Zmiana przestrzeni widocznej i okna.
//// Wywoływana w momencie zmiany rozmiaru okna
//void ChangeSize(int w, int h)
//{
//	GLfloat fAspect;
//	// Zabezpieczenie przed dzieleniem przez zero
//	if (h == 0)
//		h = 1;
//	// Zrównanie wielkości widoku i okna
//	glViewport(0, 0, w, h);
//	fAspect = (GLfloat)w / (GLfloat)h;
//	// Ustalenie układu współrzędnych
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	// Utworzenie rzutowania perspektywicznego
//	gluPerspective(35.0f, fAspect, 1.0, 40.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//// Ta funkcja wykonuje wszystkie konieczne inicjalizacje kontekstu renderowania.
//// Tutaj, konfiguruje i inicjalizuje oświetlenie sceny
//void SetupRC()
//{
//	GLuint texture;
//	int x, y;
//	char pixels[256 * 256];
//	GLint iWidth = 256;
//	GLint iHeight = 256;
//	GLint iComponents = GL_RGB;
//	GLenum eFormat = {
//		GL_RGBA
//	};
//	// Wartoci i współrzdne światła
//	GLfloat whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
//	GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
//	GLfloat lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };
//	glEnable(GL_DEPTH_TEST); // Usuwanie ukrytych powierzchni
//	glEnable(GL_CULL_FACE); // Nie bdziemy prowadzi oblicze wntrza samolotu
//	glFrontFace(GL_CCW); // Wielokty z nawiniciem przeciwnym do ruchu wskazówek zegara
//						 // Włczenie owietlenia
//	glEnable(GL_LIGHTING);
//	// Konfiguracja i włączenie światła numer 0
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
//	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
//	glEnable(GL_LIGHT0);
//	// Włczenie ledzenia kolorów
//	glEnable(GL_COLOR_MATERIAL);
//	// Właciwoci owietlenia otoczenia i rozproszenia
//	// bd ledzi wartoci podawane funkcji glColor
//	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//	// Czarne tło
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	// Ładowanie tekstury
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	// Generate a name for the texture
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	for (y = 0; y < 256; y++)
//	{
//		for (x = 0; x < 256; x++)
//			pixels[y * 256 + x] = rand() % 256;
//	}
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 256, 256, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE,
//		pixels);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//	glEnable(GL_TEXTURE_2D);
//}
//// Reakcje na klawisze strzałek
//void SpecialKeys(int key, int x, int y)
//{
//	if (key == GLUT_KEY_UP)
//		xRot -= 5.0f;
//	if (key == GLUT_KEY_DOWN)
//		xRot += 5.0f;
//	if (key == GLUT_KEY_LEFT)
//		yRot -= 5.0f;
//	if (key == GLUT_KEY_RIGHT)
//		yRot += 5.0f;
//	xRot = (GLfloat)((const int)xRot % 360);
//	yRot = (GLfloat)((const int)yRot % 360);
//	// Odwieenie zawartoci okna
//	glutPostRedisplay();
//}
//// Wywoływana w celu przerysowania sceny
//void RenderScene(void)
//{
////	GLTVector3 vNormal;
//	GLTVector3 vCorners[6] = {
//	{ 0.0f, 1.0f, 0.0f }, // Góra 0
//	{ 0.0f, 0.0f, 1.0f }, // Lewy tył 1
//	{ 0.95f, 0.0f, 0.3f}, // Prawy tył 2
//	{ 0.59f, 0.0f, -0.8f }, // Prawy przód 3
//	{ -0.59f, 0.0f,-0.8f },
//	{ -0.95f, 0.0f, 0.3f }, };
// Lewy przód 4
//							 // Czyszczenie okna aktualnym kolorem
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	// Zapisanie stanu macierzy i wykonanie obrotów
//	glPushMatrix();
//	// Cofnięcie obiektów
//	glTranslatef(0.0f, -0.25f, -4.0f);
//	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
//	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
//	// Rysowanie piramidy
//	glColor3f(1.0f, 1.0f, 1.0f);
//	glBegin(GL_TRIANGLES);
//	//Podstawa piramidy - dwa trójkąty
//	glTexCoord2f(0.0f, 1.0f);
//	glVertex3fv(vCorners[1]);
//	glTexCoord2f(0.95f, 0.3f);
//	glVertex3fv(vCorners[2]);
//	glTexCoord2f(0.59f, -0.8f);
//	glVertex3fv(vCorners[3]);
//	//2
//	glTexCoord2f(0.59f, -0.8f);
//	glVertex3fv(vCorners[3]);
//	glTexCoord2f(0.0f, 1.0f);
//	glVertex3fv(vCorners[1]);
//	glTexCoord2f(-0.59f, -0.8f);
//	glVertex3fv(vCorners[4]);
//	//3
//	glTexCoord2f(0.0f, 1.0f);
//	glVertex3fv(vCorners[1]);
//	glTexCoord2f(-0.59f, -0.8f);
//	glVertex3fv(vCorners[4]);
//	glTexCoord2f(-0.95f, 0.3f);
//	glVertex3fv(vCorners[5]);
//	// Przednia strona
//	gltGetNormalVector(vCorners[0], vCorners[4], vCorners[3], vNormal);
//	glNormal3fv(vNormal);
//	glTexCoord2f(0.5f, 1.0f);
//	glVertex3fv(vCorners[0]);
//	glTexCoord2f(0.0f, 0.0f);
//	glVertex3fv(vCorners[4]);
//	glTexCoord2f(1.0f, 0.0f);
//	glVertex3fv(vCorners[3]);
//	// Lewa strona
//	gltGetNormalVector(vCorners[0], vCorners[3], vCorners[2], vNormal);
//	glNormal3fv(vNormal);
//	glTexCoord2f(0.5f, 1.0f);
//	glVertex3fv(vCorners[0]);
//	glTexCoord2f(0.0f, 0.0f);
//	glVertex3fv(vCorners[3]);
//	glTexCoord2f(1.0f, 0.0f);
//	glVertex3fv(vCorners[2]);
//	// Tylna strona
//	gltGetNormalVector(vCorners[0], vCorners[2], vCorners[1], vNormal);
//	glNormal3fv(vNormal);
//	glTexCoord2f(0.5f, 1.0f);
//	glVertex3fv(vCorners[0]);
//	glTexCoord2f(0.0f, 0.0f);
//	glVertex3fv(vCorners[2]);
//	glTexCoord2f(1.0f, 0.0f);
//	glVertex3fv(vCorners[1]);
//	// Prawa strona
//	gltGetNormalVector(vCorners[0], vCorners[1], vCorners[5], vNormal);
//	glNormal3fv(vNormal);
//	glTexCoord2f(0.5f, 1.0f);
//	glVertex3fv(vCorners[0]);
//	glTexCoord2f(0.0f, 0.0f);
//	glVertex3fv(vCorners[1]);
//	glTexCoord2f(1.0f, 0.0f);
//	glVertex3fv(vCorners[5]);
//	gltGetNormalVector(vCorners[0], vCorners[5], vCorners[4], vNormal);
//	glNormal3fv(vNormal);
//	glTexCoord2f(0.5f, 1.0f);
//	glVertex3fv(vCorners[0]);
//	glTexCoord2f(0.0f, 0.0f);
//	glVertex3fv(vCorners[5]);
//	glTexCoord2f(1.0f, 0.0f);
//	glVertex3fv(vCorners[4]);
//	glEnd();
//	// Odtworzenie stanu macierzy
//	glPopMatrix();
//	// Zamiana buforów
//	glutSwapBuffers();
//}
//int main(int argc, char *argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowSize(800, 600);
//	glutCreateWindow("Textured Pyramid");
//	glutReshapeFunc(ChangeSize);
//	glutSpecialFunc(SpecialKeys);
//	glutDisplayFunc(RenderScene);
//	SetupRC();
//	glutMainLoop();
//	return 0;
//}
