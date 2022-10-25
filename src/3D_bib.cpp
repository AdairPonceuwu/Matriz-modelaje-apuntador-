#include "3D_bib.h"
#include <iterator>
#include <cmath>



using std::pow; using std::ostream_iterator;

Operaciones3D::Operaciones3D()
{
        //Variables para operaciones trigonometricas
        pi = 3.14159265359;
        LoadIdentity(A);
}


//recordar que (pi/180 = r/g) donde "r" son radianes y "g" grados
//se aplica la formula r
float Operaciones3D::RadToDeg(float r)
{
      return ((180*r)/pi);
}

float Operaciones3D::DegToRad(float g)
{
      return ((g*pi)/180);
}
//Multiplicacion de matrices
void Operaciones3D::MultM(float M1[][4], float M2[][4], float Res[][4])
{
  float tmp[4][4];
  int i,j,k;
  for(i=0; i<4;i++)
     for(j=0;j<4;j++){
        tmp[i][j]=0;
        for(k=0;k<4;k++)
           tmp[i][j]+=M1[i][k]*M2[k][j];
     }
  for(i=0;i<4;i++)
     for(j=0;j<4;j++)
        Res[i][j] = tmp[i][j];
}

void Operaciones3D::LoadIdentity(float M[][4])
{
  int i,j;
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      if(i==j)
         M[i][j]=1;
      else
         M[i][j]=0;
 }

 void Operaciones3D::LoadIdentity()
{
  int i,j;
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      if(i==j)
         A[i][j]=1;
      else
         A[i][j]=0;
 }

//Traslacion
void Operaciones3D::translate(float x, float y, float z)
{
  LoadIdentity(T);
  T[0][3]=x;
  T[1][3]=y;
  T[2][3]=z;
}
void Operaciones3D::translateA()
{
    MultM(A,T,A);
}
//Escalado
void Operaciones3D::scalate(float x,float y, float z,float p1[3])
{
    LoadIdentity(E);
    E[0][0]=x;
    E[1][1]=y;
    E[2][2]=z;
    E[0][3]=((1-x)*p1[0]);
    E[1][3]=((1-y)*p1[1]);
    E[2][3]=((1-z)*p1[2]);
}
void Operaciones3D::scalateA()
{
    if(x==0){
        MultM(A,E,A);
        x++;
    }else
        x++;
}
 //Rotacion paralela
void Operaciones3D::rotateX(float deg)
{
  LoadIdentity(R);
  R[1][1] = cos(deg);
  R[1][2] = -1*sin(deg);
  R[2][1] = sin(deg);
  R[2][2] = cos(deg);
 }

 void Operaciones3D::rotateXITheta(float deg)
{
  LoadIdentity(R);
  R[1][1] = cos(deg);
  R[1][2] = sin(deg);
  R[2][1] = -1*sin(deg);
  R[2][2] = cos(deg);
 }

void Operaciones3D::rotateY(float deg)
{
  LoadIdentity(R);
  R[0][0] = cos(deg);
  R[0][2] = sin(deg);
  R[2][0] = -1*sin(deg);
  R[2][2] = cos(deg);
 }

 void Operaciones3D::rotateYITheta(float deg)
{
  LoadIdentity(R);
  R[0][0] = cos(deg);
  R[0][2] = -1*sin(deg);
  R[2][0] = sin(deg);
  R[2][2] = cos(deg);
 }

void Operaciones3D::rotateZ(float deg)
{
  LoadIdentity(R);
  R[0][0] = cos(deg);
  R[0][1] = -1*sin(deg);
  R[1][0] = sin(deg);
  R[1][1] = cos(deg);
 }

//Rotacion libre
void Operaciones3D::rotateX(float b, float c,bool bandera)
{
  LoadIdentity(R);
  if(bandera){
    R[1][1] = c/d;
    R[1][2] = -(b/d);
    R[2][1] = b/d;
    R[2][2] = c/d;
  }else{
    R[1][1] = c/d;
    R[1][2] = b/d;
    R[2][1] = -(b/d);
    R[2][2] = c/d;
  }
}


void Operaciones3D::rotateYL(float a,bool bandera)
{
  LoadIdentity(R);
  if(bandera){
  R[0][0] = d;
  R[0][2] = a;
  R[2][0] = -a;
  R[2][2] = d;
  }else{
    R[0][0] = d;
    R[0][2] = -a;
    R[2][0] = a;
    R[2][2] = d;
  }
 }



//multiplica la matriz m por el punto p y regresa el resultado en el punto p
void Operaciones3D::MatPoint(float m[][4], float p[3])
{
  float tmp[4];
  int i,j;
  for(i=0; i<3; i++)
    { tmp[i] = p[i];
      p[i] = 0;
    }
  tmp[3]=1;
  for(i=0;i<3;i++)
    for(j=0;j<4;j++)
        p[i] += m[i][j]*tmp[j];
}

//multiplica la matriz m por cada punto del objeto definido por la matriz p de size x 3
void Operaciones3D::MatObject(float m[][4], int size, float p[][3])
{
     int i;
     for(i=0; i<size; i++)
       MatPoint(m,p[i]);
}

//rotacion paralela a uno de los ejes
//theta: angulo de rotacion;
//distA,distB: vector (distA,distB) que separa al eje de rotacion del objeto
//con respecto a uno de los ejes del sistema cartesiano. Si el eje es:
//X: (distA,distB) es el vector (0,distA,distB)
//Y: (distA,distB) es el vector (distA,0,distB)
//Z: (distA,distB) es el vector (distA,distB,0)
void Operaciones3D::RotacionParalela(char eje, float theta, float distA, float distB)
{
     switch(eje){
        case 'X'://rotacion paralela en "X"
                translate(0,-distA,-distB);
                rotateX(DegToRad(theta));
                MultM(R,T,A);
                translate(0,distA,distB);
                MultM(T,A,A);
             break;
        case 'Y'://rotacion paralela en "Y"
                translate(0,-distA,-distB);
                rotateY(DegToRad(theta));
                MultM(R,T,A);
                translate(0,distA,distB);
                MultM(T,A,A);
             break;
        case 'Z'://rotacion paralela en "Z"
                translate(0,-distA,-distB);
                rotateZ(DegToRad(theta));
                MultM(R,T,A);
                translate(0,distA,distB);
                MultM(T,A,A);
             break;
     }
}

void Operaciones3D::RotacionLibre(float theta, float p1[3], float p2[3])
{
    bool bandera;
    float p3[3],v,u[3];
    //p2-p1=p3
    for(int i = 0;i<3;i++){
        p3[i]=p2[i]-p1[i];
    }
    v=sqrt(pow(p3[0],2)+pow(p3[1],2)+pow(p3[2],2));
    for(int i = 0;i<3;i++){
        u[i]=p3[i]/v;
    }
    //1.-Calcular vector unitario(a,b,c) T->A
    translate(-p1[0],-p1[1],-p1[2]);//Creacion de T
    //2.-Calcular matriz rotacion con respecto a "x" del angulo "alpha"
    //2.1 Clacular d
    d=sqrt(pow(u[1],2)+pow(u[2],2));
    if(d!=0){
        //2.2 Calculo Rx(alpha)
        rotateX(u[1],u[2],bandera=true);
        //Multiplicacion
        MultM(R,T,A);
        //3.-Calcular matriz rotacion con respecto a "y" del angulo "beta" == Ry(beta)
        rotateYL(u[0],bandera=true);
        //Multiplicacion
        MultM(R,A,A);
        //4.-Calcular matriz rotacion con respecto a "z" del angulo "theta" == Rz(theta)
        rotateZ(DegToRad(theta));
        MultM(R,A,A);
        //5.-Def matriz Ry^-1(beta) (inversa de Ry(beta))
        rotateYL(u[0],bandera=false);
        MultM(R,A,A);
        //6.-Def matriz Rx^-1(alpha) (inversa de Rx(alpha))
        rotateX(u[1],u[2],bandera=false);
        MultM(R,A,A);
        //7.-Calcular inversa de T^-1*(A)->A
        translate(p1[0],p1[1],p1[2]);//Creacion de T INVERSA
        MultM(T,A,A);
    }
    else{
        rotateX(DegToRad(theta));
        MultM(R,T,A);
        translate(p1[0],p1[1],p1[2]);//Creacion de T INVERSA
        MultM(T,A,A);
    }
}



void Operaciones3D::Push()
{
    int i,j;
    Matriz *objM = new Matriz();
    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
                objM->M[i][j]=A[i][j];

    pila.push(objM);
}

void Operaciones3D::Pop()
{
    int i,j;
    Matriz *tmp = new Matriz();
    tmp=pila.top();
    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
                A[i][j]=tmp->M[i][j];
    pila.pop();
}

