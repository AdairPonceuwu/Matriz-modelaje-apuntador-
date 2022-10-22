#ifndef PIRAMIDE
#define PIRAMIDE

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

#include "iostream"
#include "3D_bib.h"
using namespace std;



class Piramide
{
    private:
        float points[5][3]={{0,0,2},{2,0,2},{2,0,0},{0,0,0},{1,1.5,1}};
        float myA[4][4];
        float edo_rotate,edo_translate,state;
    public:
        Operaciones3D *Op3D;
        //Constructor y destructor
        Piramide(Operaciones3D *);
        ~Piramide();
        //Dibujado de la piramide
        float Norma(float p1[3], float p2[3]);
        void ImprimeMallaPiramide(int k);
        void drawPiramide();
        //modificaciones(Rotacion, traslacion, etc)
        void RotacionPiramide(float theta, float p1[3], float p2[3]);
};

#endif // PIRAMIDE
