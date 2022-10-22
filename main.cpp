#include "3D_bib.h"
#include "Piramide.h"
#include <GL/glut.h>

//Variables dimensiones de la pantalla
int WIDTH=500;
int HEIGTH=500;
//Variables para establecer los valores de gluPerspective
float FOVY=60.0;
float ZNEAR=0.01;
float ZFAR=100.0;
//Variables para definir la posicion del observador
//gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z)
float EYE_X=10.0;
float EYE_Y=5.0;
float EYE_Z=10.0;
float CENTER_X=0;
float CENTER_Y=0;
float CENTER_Z=0;
float UP_X=0;
float UP_Y=1;
float UP_Z=0;
//Variables para dibujar los ejes del sistema
float X_MIN=-20;
float X_MAX=20;
float Y_MIN=-20;
float Y_MAX=20;
float Z_MIN=-100;
float Z_MAX=20;

//Se declara el objeto para utilizar las operaciones 3D
Operaciones3D Op3D;
Piramide myPyramid(&Op3D);

float Theta=0;
//Variables para la definicion de objetos
float P1[3]={-5.0,1.0,4.0};
float P2[3]={2.0,6.0,3.0};
float VT[3]={-1.0,0.0,0.0};



void drawAxis()
{
     glShadeModel(GL_SMOOTH);
     glLineWidth(3.0);
     //X axis in red
     glBegin(GL_LINES);
       glColor3f(1.0f,0.0f,0.0f);
       glVertex3f(X_MIN,0.0,0.0);
       glColor3f(0.5f,0.0f,0.0f);
       glVertex3f(X_MAX,0.0,0.0);
     glEnd();
     //Y axis in green
     glColor3f(0.0f,1.0f,0.0f);
     glBegin(GL_LINES);
       glColor3f(0.0f,1.0f,0.0f);
       glVertex3f(0.0,Y_MIN,0.0);
       glColor3f(0.0f,0.5f,0.0f);
       glVertex3f(0.0,Y_MAX,0.0);
     glEnd();
     //Z axis in blue
     glBegin(GL_LINES);
       glColor3f(0.0f,0.0f,1.0f);
       glVertex3f(0.0,0.0,Z_MIN);
       glColor3f(0.0f,0.0f,0.5f);
       glVertex3f(0.0,0.0,Z_MAX);
     glEnd();
     glLineWidth(1.0);
 }




//-------------------------------------------------------------------------
//funciones callbacks
void idle(void)
{
    Sleep(20);
    glutPostRedisplay();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
}
//TeclasZ
/*static void keys(unsigned char key, int x, int y)
{
    switch(key){
                case 'u':
                     Theta=1;
                     break;
                case 'd':
                     Theta=-1;
                     break;
                default:
                     Theta = 0;
                     break;
    }
    glutPostRedisplay();
}*/
//--------------------------------------------------------------------------

void display()
{
    //Inicializando el ambiente
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();
    Op3D.LoadIdentity();
    glColor3f(1.0f,1.0f,1.0f);

    //Control de pila para animacion
    Op3D.Push();
    myPyramid.drawPiramide();
    Op3D.RotacionLibre(180,P1,P2);
    //ImprimePiramide();
    Op3D.Pop();

    //Buffers
    glFlush();
    glutSwapBuffers();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, (GLfloat)WIDTH/HEIGTH, ZNEAR, ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z);
    glClearColor(0,0,0,0);
    Theta=1;

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGTH);
    glutCreateWindow("Matriz de modelado con pila");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    //glutKeyboardFunc(keys);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

