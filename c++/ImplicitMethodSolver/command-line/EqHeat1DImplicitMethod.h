/*******************************************************************************
  Name: EqHeat1DImplicitMethod.h
  Copyright:
  Author: Tiago Gon�alves Cunha
  Date: 20/05/05 09:14
  Description:
*******************************************************************************/

#ifndef _EqHeat1DImplicitMethod_H
#define _EqHeat1DImplicitMethod_H 1

#define I_ 6       // n� de n�s da malha
#define N_ 10      // n� de intervalos de tempo(deltaT), em segundos, para discretizar os I n�s na barra
#define L_ 10
#define K 0.49
#define C 0.2174
#define Rho 2.7
#define DeltaT 0.1

typedef float REAL;

typedef struct NO **ptrNO;
struct NO
{
    REAL x;
    REAL t;
    REAL u;
};

typedef struct EqCondutionHeat *EqHeat;
struct EqCondutionHeat
{
     ptrNO node;
     REAL alfa, k, c, rho, lambda;
     REAL deltaX, deltaT, L;
     REAL Uo, UL;
     long I, N;
};
//==================================================================================================
void alocar_SEL(const int LIN, const int COL);

//==================================================================================================
void desaloca_SEL();

//==================================================================================================
REAL calcularDeltaX(EqHeat mesh);

//==================================================================================================
void iniciarConditionContorno(EqHeat mesh);

//==================================================================================================
REAL calcularAlfa(EqHeat mesh);

//==================================================================================================
REAL calcularLambda(EqHeat mesh);

//==================================================================================================
void solveEqHeatImplicitMethod(EqHeat mesh);

//==================================================================================================
void imprimirMesh(EqHeat mesh);

//==================================================================================================
void salvarDadosEmArquivo(EqHeat mesh);

//==================================================================================================
void imprimirSEL(const int LIN, const int COL);

//==================================================================================================
REAL *method_Gauss_Jordan(REAL **SEL, const int LIN, const int COL);

//==================================================================================================
void ler_SEL(EqHeat mesh, REAL **SEL);

//==================================================================================================
#endif
