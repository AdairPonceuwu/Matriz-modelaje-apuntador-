#include "Piramide.h"
#include "3D_bib.h"

Piramide::Piramide(Operaciones3D *data)
{
    Op3D=data;
    edo_rotate = FALSE;
    edo_translate = FALSE;
    state = FALSE;
    Op3D->LoadIdentity(myA);
}

Piramide::~Piramide()
{
    Op3D=NULL;
}


float Piramide::Norma(float p1[3], float p2[3])
{
      float n=0;
      int i;
      for(i=0;i<3;i++)
        n += pow(p2[i]-p1[i],2);
      return(sqrt(n));
}


void Piramide::ImprimeMallaPiramide(int k)
{
     int i,j;
     float U[3],d,norma;
     for(i=0;i<3;i++)
     {
        norma = Norma(points[i],points[i+1]);
        d = norma/(float)k;
        U[0] = (points[i+1][0]-points[i][0])/norma;
        U[1] = (points[i+1][1]-points[i][1])/norma;
        U[2] = (points[i+1][2]-points[i][2])/norma;
        for(j = 1; j < k; j++)
        {
           glBegin(GL_LINES);
             glVertex3f(points[4][0],points[4][1],points[4][2]);
             glVertex3f(points[i][0]+U[0]*d*j,points[i][1]+U[1]*d*j,points[i][2]+U[2]*d*j);
           glEnd();
        }
     }
     norma = Norma(points[i],points[0]);
     d = norma /(float)k;
     U[0] = (points[0][0]-points[i][0])/norma;
     U[1] = (points[0][1]-points[i][1])/norma;
     U[2] = (points[0][2]-points[i][2])/norma;
     for(j = 1; j < k; j++)
        {
           glBegin(GL_LINES);
             glVertex3f(points[4][0],points[4][1],points[4][2]);
             glVertex3f(points[i][0]+U[0]*d*j,points[i][1]+U[1]*d*j,points[i][2]+U[2]*d*j);
           glEnd();
        }

}

void Piramide::drawPiramide()
{
    Op3D->MatObject(Op3D->A,5,points);
    glBegin(GL_LINE_LOOP);
      for(int i=0;i<4;i++)
        glVertex3f(points[i][0],points[i][1],points[i][2]);
    glEnd();
    glBegin(GL_LINES);
      for(int i=0;i<4;i++){
        glVertex3f(points[4][0],points[4][1],points[4][2]);
        glVertex3f(points[i][0],points[i][1],points[i][2]);
        }
    glEnd();
    ImprimeMallaPiramide(20);
 }


