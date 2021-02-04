/*******************************************************************************
  Name: EqHeat1D_CrankNicolsonMethod.h
  Copyright:
  Author: Tiago Gon�alves Cunha
  Date: 20/05/05 09:14
  Description:
*******************************************************************************/

#ifndef _EqHeat1D_CrankNicolsonMethod_H
#define _EqHeat1D_CrankNicolsonMethod_H 1

typedef float REAL;

typedef struct NO **ptrNO;
struct NO
{
    //REAL x;
    //REAL t;
    REAL u;
};

typedef struct EqCondutionHeat *EqHeat;
struct EqCondutionHeat
{
     ptrNO node;
     REAL alfa, k, c, rho, lambda;
     REAL deltaX, deltaT, L;
     REAL Uo, UL, Ui;
     long I, N;
};
// extern EqCondutionHeat *mesh;

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
void solveEqHeat_CrankNicolsonMethod(EqHeat mesh);

//==================================================================================================
//void imprimirMesh(EqHeat mesh);

//==================================================================================================
void salvarDadosEmArquivo(EqHeat mesh);

//==================================================================================================
//void imprimirSEL(const int LIN, const int COL);

//==================================================================================================
REAL *method_Gauss_Jordan(REAL **SEL, const int LIN, const int COL);

//==================================================================================================
void ler_SEL(EqHeat mesh, REAL **SEL);

//==================================================================================================
#endif
