## Importujemy wszystkie konieczne biblioteki:
#from OpenGL.GL import *
#from OpenGL.GLU import *
#from OpenGL.GLUT import *
#import sys
## Deklarujemy wszystkie zmienne globalne
#global xrot # warto�� obracania wg kierunku x
#global yrot # warto�� obracania wg kierunku y
#global ambient # o�wietlanie otaczaj�ce
#global greencolor # kolor igie� choinki
#global treecolor # kolor badyla choinki
#global lightpos # Lokalizacja �r�d�a �wiat�a
## Procedura inicializacji
#def init():
#    global xrot # warto�� obracania wg kierunku x
#    global yrot # warto�� obracania wg kierunku y
#    global ambient # o�wietlanie otaczaj�ce
#    global greencolor # kolor igie� choinki
#    global treecolor # kolor badyla choinki
#    global lightpos # Lokalizacja �r�d�a �wiat�a
#    xrot = 0.0 # warto�� obracania wg kierunku x = 0
#    yrot = 0.0 # warto�� obracania wg kierunku y = 0
#    ambient = (1.0, 1.0, 1.0, 1) # Pierwsze trzy warto�ci okre�laj� kolor w postaci
#    greencolor = (0.2, 0.8, 0.0, 0.8) # kolor zielony dla igie�
#    treecolor = (0.9, 0.6, 0.3, 0.8) # kolor br�zowy dla badyla
#    lightpos = (1.0, 1.0, 1.0) # lokalizacja �r�d�a �wiat�a wg osi xyz
#    glClearColor(0.5, 0.5, 0.5, 1.0) # kolor szary dla zarysowania pocz�tkowego
#    gluOrtho2D(-1.0, 1.0, -1.0, 1.0) # okre�lamy kraw�dzi rysowania poziomo a
#    glRotatef(-90, 1.0, 0.0, 0.0) # przesuniemy si� wg osi ? na 90 stopni
#    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient) # okre�lamy bie��cy model o�wietlania
#    glEnable(GL_LIGHTING) # w��czamy o�wietlanie
#    glEnable(GL_LIGHT0) # w��czamy jedne �r�d�o �wiat�a
#    glLightfv(GL_LIGHT0, GL_POSITION, lightpos) # okre�lamy lokalizacj� �r�d�a �wiat�a

## procedura opracowania przycisk�w specjalnych

#def specialkeys(key, x, y):
#    global xrot
#    global yrot
#    # dla przucisk�w ze strza�kami
#    if key == GLUT_KEY_UP: # przycisk dog�ry
#        xrot -= 2.0 # zmniejszajmy k�t obracania wg osi ?
#    if key == GLUT_KEY_DOWN: # przucisk dodo�u
#        xrot += 2.0 # zwi�kszajmy k�t obracania wg osi ?
#    if key == GLUT_KEY_LEFT: # w lewo
#        yrot -= 2.0 # zmniejszajmy k�t obracania wg osi Y
#    if key == GLUT_KEY_RIGHT: # na prawo
#        yrot += 2.0 # zwi�kszajmy k�t obracania wg osi Y
#    glutPostRedisplay() # wywo�ujemy procedur� przerysowania
## Procedura przerysowania
#def draw():
#    global xrot
#    global yrot
#    global lightpos
#    global greencolor
#    global treecolor
#    glClear(GL_COLOR_BUFFER_BIT) # oczyszczamy ekran i ???????
#    glPushMatrix() # Zachowujemy bie��ce po�o�enie
#    glRotatef(xrot, 1.0, 0.0, 0.0) # Obracamy po osi X na wielko��
#    glRotatef(yrot, 0.0, 1.0, 0.0) # Obracamy po osi Y na wielko��
#    glLightfv(GL_LIGHT0, GL_POSITION, lightpos) # �r�d�o �wiat�a obracamy razem
#    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, treecolor)
#    glTranslatef(0.0, 0.0, -0.7) # Przesuniemy si� wzd�u� osi Z
#    glutSolidCylinder(0.1, 0.2, 20, 20)
#    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, greencolor)
#    for num in range(6,1,-1):
#        glTranslatef(0.0, 0.0, 0.2) # Przesuniemy si� wzd�u� osi Z
#        glutSolidCone(num/10, num/10, 20, 20)
#    glPopMatrix() # Wracamy zachowane po�o�enie
#    glutSwapBuffers() # Wyprowadzamy wszystko
#glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB)
#glutInitWindowSize(300, 300)
#glutInitWindowPosition(50, 50)
#glutInit(sys.argv)
#glutCreateWindow(b"Happy New Year!")
#glutDisplayFunc(draw)
#glutSpecialFunc(specialkeys)
#init()
#glutMainLoop()
#rint('Hello wsdfsdfsdffsdorld, Python')